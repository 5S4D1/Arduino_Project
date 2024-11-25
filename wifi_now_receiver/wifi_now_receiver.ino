#include <WiFi.h>
#include <esp_now.h>

// Callback function when data is received
void onDataReceive(const esp_now_recv_info_t *recvInfo, const uint8_t *data, int dataLen) {
  char message[dataLen + 1];
  memcpy(message, data, dataLen);
  message[dataLen] = '\0'; // Null-terminate the received data

  // Print sender MAC address
  Serial.print("Message received from: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(recvInfo->src_addr[i], HEX);
    if (i < 5) Serial.print(":");
  }
  Serial.print("\nMessage: ");
  Serial.println(message);
}

void setup() {
  Serial.begin(115200);

  // Initialize WiFi in station mode
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register receive callback
  esp_now_register_recv_cb(onDataReceive);
}

void loop() {
  // Do nothing, waiting for data
}
