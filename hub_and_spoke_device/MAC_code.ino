#include <WiFi.h>
#include <esp_wifi.h>

void setup() {
  Serial.begin(115200);
  delay(3000);

  WiFi.mode(WIFI_STA);

  esp_wifi_start();
  delay(200);

  uint8_t mac[6];
  esp_wifi_get_mac(WIFI_IF_STA, mac);

  Serial.println();
  Serial.print("uint8_t HUB_MAC[] = { ");

  for (int i = 0; i < 6; i++) {
    Serial.print("0x");
    if (mac[i] < 16) Serial.print("0");
    Serial.print(mac[i], HEX);
    if (i < 5) Serial.print(", ");
  }

  Serial.println(" };");
}

void loop() {}
