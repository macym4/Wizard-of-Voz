#include <WiFi.h>
#include <esp_now.h>
#include <BleKeyboard.h>

BleKeyboard bleKeyboard("WOV Keyboard bluetooth", "ESP32", 100);

// ===== HUB BUTTON =====
#define PIN_ENTER    4 // CHANGE the enter button pin number
#define DEBOUNCE_MS  40

// ===== KEY IDS ===== // DO NOT CHANGE any code below this point
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

//=========== ESP-NOW RECEIVE CALLBACK (2.x + 3.x COMPATIBLE)=======
#if ESP_IDF_VERSION_MAJOR >= 5
// ----- ESP32 core 3.x -----
void onReceive(const esp_now_recv_info_t *info,
               const uint8_t *data,
               int len) {
#else
// ----- ESP32 core 2.x -----
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
    return;
  }

  esp_now_register_recv_cb(onReceive);

  bleKeyboard.begin();
}

void loop() {
  unsigned long now = millis();
  bool curEnter = digitalRead(PIN_ENTER);

  if (enterArmed &&
      lastEnter == HIGH &&
      curEnter == LOW &&
      now - lastEnterTime >= DEBOUNCE_MS) {

    if (bleKeyboard.isConnected()) {
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
