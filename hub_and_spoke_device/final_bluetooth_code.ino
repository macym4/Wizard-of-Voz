#include <WiFi.h>
#include <esp_now.h>
#include <BleKeyboard.h>

BleKeyboard bleKeyboard("WOV Keyboard bluetooth", "ESP32", 100);

// ===== HUB BUTTON =====
#define PIN_ENTER  4
#define DEBOUNCE_MS 40

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

// ===== ESP-NOW RECEIVE =====
void onReceive(const esp_now_recv_info_t *info,
               const uint8_t *data,
               int len) {

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

  esp_now_init();
  esp_now_register_recv_cb(onReceive);

  bleKeyboard.begin();
  Serial.println("✅ HUB READY — pair BLE keyboard");
}

void loop() {
  unsigned long now = millis();
  bool curEnter = digitalRead(PIN_ENTER);

  if (enterArmed &&
      lastEnter == HIGH &&
      curEnter == LOW &&
      now - lastEnterTime >= DEBOUNCE_MS) {

    if (bleKeyboard.isConnected()) {
      Serial.println("⏎ ENTER");
      bleKeyboard.write(' ');
    }

    enterArmed = false;
    lastEnterTime = now;
  }

  if (curEnter == HIGH) {
    enterArmed = true;
  }

  lastEnter = curEnter;
}
