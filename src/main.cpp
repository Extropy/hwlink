#include <Arduino.h>
#include <WiFi.h>
#include <coap-simple.h>

#include "WiFiCredentials.h"

int wifi_signal;
WiFiClient wificlient;


void arduino_setup() {
  Serial.begin(115200);
  printf("coap test\n");

  WiFi.persistent(false);
  WiFi.disconnect();
  WiFi.mode(WIFI_STA); // switch off AP
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
  WiFi.begin(WIFISSID,WIFIPASSWORD);
  
  unsigned long start = millis();
  uint8_t connectionStatus;
  bool AttemptConnection = true;
  
  while (AttemptConnection) {
    connectionStatus = WiFi.status();
    if (millis() > start + 15000) { // Wait 15-secs maximum
      AttemptConnection = false;
    }
    if (connectionStatus == WL_CONNECTED || connectionStatus == WL_CONNECT_FAILED) {
      AttemptConnection = false;
    }
    delay(50);
  }
  if (connectionStatus == WL_CONNECTED) {
    wifi_signal = WiFi.RSSI();
    Serial.println("WiFi connected at: " + WiFi.localIP().toString());
  }
  else Serial.println("WiFi connection *** FAILED ***");

}


void arduino_loop() {
  Serial.printf("coap test...\n");
  delay(1000);
}
