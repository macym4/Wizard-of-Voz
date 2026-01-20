#include <WiFi.h>
#include <esp_now.h>

// ===== HUB MAC =====
uint8_t HUB_MAC[] = { 0x6C, 0xC8, 0x40, 0x8C, 0xD9, 0xD0 }; // Use the MAC address retrieval code to get the MAC address and replace this line with the MAC address of the arduino for the HUB

// ===== BUTTON PINS ===== // CHANGE these pins to match the wiring in the devices
#define PIN_UP     4
#define PIN_DOWN   5
#define PIN_LEFT   6
#define PIN_RIGHT  7


// ===== KEY IDS ===== // DO NOT CHANGE ANY CODE BELOW THIS LINE!
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
  { PIN_UP,    KEY_UP,    HIGH, 0 },
  { PIN_DOWN,  KEY_DOWN,  HIGH, 0 },
  { PIN_LEFT,  KEY_LEFT,  HIGH, 0 },
  { PIN_RIGHT, KEY_RIGHT, HIGH, 0 }
};

const int NUM_BUTTONS = sizeof(buttons) / sizeof(buttons[0]);

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(buttons[i].pin, INPUT_PULLUP);
  }

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  Serial.print("SPOKE MAC: ");
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("❌ ESP-NOW init failed");
    return;
  }

  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, HUB_MAC, 6);
  peer.channel = 0;
  peer.encrypt = false;

  if (esp_now_add_peer(&peer) != ESP_OK) {
    Serial.println("❌ Failed to add peer");
    return;
  }

  Serial.println("✅ SPOKE READY (USB-powered)");
}

void loop() {
  unsigned long now = millis();

  for (int i = 0; i < NUM_BUTTONS; i++) {
    bool current = digitalRead(buttons[i].pin);

    if (buttons[i].lastState == HIGH &&
        current == LOW &&
        now - buttons[i].lastTime >= DEBOUNCE_MS) {

      pkt.key = buttons[i].key;
      esp_now_send(HUB_MAC, (uint8_t*)&pkt, sizeof(pkt));

      Serial.print("➡️ Sent key: ");
      Serial.println(buttons[i].key);

      buttons[i].lastTime = now;
    }

    buttons[i].lastState = current;
  }
}