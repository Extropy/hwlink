#include <Arduino.h>
#include <WiFi.h>              // Built-in
#include "WiFiCredentials.h"

int wifi_signal;
IPAddress mqttserver(10,1,1,11);
WiFiClient wificlient;


void arduino_setup() {
  Serial.begin(115200);
  Serial.print("coap test\n");

  WiFi.persistent(false);
  IPAddress dns(8, 8, 8, 8); // Google DNS
  WiFi.disconnect();
  WiFi.mode(WIFI_STA); // switch off AP
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
  //IPAddress ip(10,1,2,50);
  //IPAddress gateway(10,1,2,1);
  //IPAddress subnet(255,255,255,0);
  //WiFi.config(ip,gateway,subnet);
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
    wifi_signal = WiFi.RSSI(); // Get Wifi Signal strength now, because the WiFi will be turned off to save power!
    Serial.println("WiFi connected at: " + WiFi.localIP().toString());
  }
  else Serial.println("WiFi connection *** FAILED ***");

}


void arduino_loop() {
  Serial.printf("coap test...\n");
  delay(1000);
}
