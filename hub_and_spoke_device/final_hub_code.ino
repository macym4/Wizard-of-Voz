#include <WiFi.h>
#include <esp_now.h>
#include <BleKeyboard.h>

// "WOV Keyboard bluetooth" is the name of your device. To change the name, add the new name between the quotation marks (ex: "New Name")
// "WOV Keyboard bluetooth" es el nombre de su dispositivo. Para cambiarlo, añada el nuevo nombre entre comillas (ej: "Nuevo nombre")
BleKeyboard bleKeyboard("WOV Keyboard bluetooth", "ESP32", 100);

// ===== HUB BUTTON =====
//CHANGE THIS PIN NUMBER TO MATCH THE WIRING IN YOUR DEVICE
//CAMBIE ESTE NÚMERO DE PIN PARA QUE COINCIDAN CON EL CABLEADO DE SU DISPOSITIVO
#define PIN_ENTER    4
#define DEBOUNCE_MS  40

//DO NOT CHANGE any code below these lines
// NO CAMBIE ningún código debajo de estas líneas
// ===== KEY IDS =====
#define KEY_UP     1
#define KEY_DOWN   2
#define KEY_LEFT   3
#define KEY_RIGHT  4

typedef struct {
  uint8_t key;
} Packet;

// ===== ENTER BUTTON STATE =====
bool lastEnter = HIGH;
unsigned long lastEnterTime = 0;
bool enterArmed = true;

//=========== ESP-NOW RECEIVE CALLBACK ===========
#if ESP_IDF_VERSION_MAJOR >= 5
void onReceive(const esp_now_recv_info_t *info,
               const uint8_t *data,
               int len) {
#else
void onReceive(const uint8_t *mac,
               const uint8_t *data,
               int len) {
#endif
  if (len != sizeof(Packet)) return;
  if (!bleKeyboard.isConnected()) return;

  Packet pkt;
  memcpy(&pkt, data, sizeof(pkt));

  switch (pkt.key) {
    case KEY_UP:    bleKeyboard.write(KEY_UP_ARROW);    break;
    case KEY_DOWN:  bleKeyboard.write(KEY_DOWN_ARROW);  break;
    case KEY_LEFT:  bleKeyboard.write(KEY_LEFT_ARROW);  break;
    case KEY_RIGHT: bleKeyboard.write(KEY_RIGHT_ARROW); break;
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(PIN_ENTER, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  Serial.print("HUB MAC: ");
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_peer_info_t peer = {};
  memset(peer.peer_addr, 0xFF, 6);  // accept any sender
  peer.channel = 0;
  peer.encrypt = false;

  esp_now_add_peer(&peer);

  esp_now_register_recv_cb(onReceive);

  bleKeyboard.begin();
  Serial.println("HUB READY");
}

void loop() {
  static bool buttonPressed = false;
  static unsigned long lastChange = 0;

  bool curEnter = digitalRead(PIN_ENTER);
  unsigned long now = millis();

  // debounce
  if (now - lastChange < DEBOUNCE_MS) return;

  // detect press
  if (!buttonPressed && curEnter == LOW) {
    lastChange = now;
    buttonPressed = true;

    if (bleKeyboard.isConnected()) {
      bleKeyboard.write(' '); 
    }
  }

  // detect release
  if (buttonPressed && curEnter == HIGH) {
    lastChange = now;
    buttonPressed = false;
  }
}
