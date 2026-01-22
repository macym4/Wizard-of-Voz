#include <WiFi.h>
#include <esp_now.h>

// ===== HUB MAC (Dirección MAC del dispositivo principal) ===== 
//CHANGE THIS MAC ADDRESS TO MATCH THE ADDRESS FROM THE HUB ARDUINO
//CAMBIE ESTA DIRECCIÓN MAC PARA QUE COINCIDA CON LA DIRECCIÓN DEL HUB ARDUINO
uint8_t HUB_MAC[] = { 0x6C, 0xC8, 0x40, 0x8C, 0xBB, 0x60 };

// ===== BUTTON PINS (PINES DE BOTÓN) ===== 
//CHANGE THESE PIN NUMBERS TO MATCH THE WIRING IN YOUR DEVICE. We recommend pins 4,5,18,19,21.
//CAMBIE ESTOS NÚMEROS DE PIN PARA QUE COINCIDAN CON EL CABLEADO DE SU DISPOSITIVO. Recomendamos los pines 4,5,18,19,21. 
#define PIN_UP     4
#define PIN_DOWN   18
#define PIN_LEFT   5
#define PIN_RIGHT  19

//DO NOT CHANGE any code below these lines
// NO CAMBIE ningún código debajo de estas líneas
// ===== KEY IDS ===== 
#define KEY_UP     1
#define KEY_DOWN   2
#define KEY_LEFT   3
#define KEY_RIGHT  4

#define DEBOUNCE_MS 160

typedef struct {
  uint8_t key;
} Packet;

Packet pkt;

// ===== BUTTON STATE =====
struct Button {
  uint8_t pin;
  uint8_t key;
  bool lastState;
  unsigned long lastTime;
};

Button buttons[] = {
  { PIN_UP,    KEY_UP,    HIGH, 0},
  { PIN_DOWN,  KEY_DOWN,  HIGH, 0 },
  { PIN_LEFT,  KEY_LEFT,  HIGH, 0},
  { PIN_RIGHT, KEY_RIGHT, HIGH, 0 }
};

const int NUM_BUTTONS = sizeof(buttons) / sizeof(buttons[0]);

void setup() {
  Serial.begin(115200);
  delay(300);

  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(buttons[i].pin, INPUT_PULLUP);
  }

  // ---- WiFi / ESP-NOW INIT ----
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true, true);
  delay(100);
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    return;
  }

  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, HUB_MAC, 6);
  peer.channel = 0;
  peer.encrypt = false;

  esp_now_del_peer(HUB_MAC);
  delay(10);

  if (esp_now_add_peer(&peer) != ESP_OK) {
    return;
  }
}

void loop() {
  unsigned long now = millis();

  for (int i = 0; i< NUM_BUTTONS; i++) {
    bool current = digitalRead(buttons[i].pin);

    if (buttons[i].lastState == HIGH &&
        current == LOW &&
        now - buttons[i].lastTime >= DEBOUNCE_MS) {

      pkt.key = buttons[i].key;

      esp_now_send(
        HUB_MAC,
        (uint8_t*)&pkt,
        sizeof(pkt)
      );

      Serial.print("Sent key: ");
      Serial.println(buttons[i].key);

      buttons[i].lastTime =now;
    }

    buttons[i].lastState =current;
  }
}
