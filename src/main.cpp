#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <coap-simple.h>

#include "WiFiCredentials.h"
#include <pb_encode.h>
#include <pb_decode.h>
#include "proto/helloworld.pb.h"

int wifi_signal;
WiFiClient wificlient;

WiFiUDP udp;
Coap coap(udp);
sayhello m = sayhello_init_zero;
uint8_t b[256];
int n = 0;

void coapCallBackInfo(CoapPacket &packet, IPAddress ip, int port) {
  char p[packet.payloadlen+1];
  memcpy(p,packet.payload,packet.payloadlen);
  p[packet.payloadlen] = NULL;
  String message(p);
  //printf("coapCallBackInfo received"); for (int i = 0; i < packet.payloadlen; i++) printf(" %02x",packet.payload[i]);
  printf("coapCallBackInfo received %s",message);
  printf(", messageid=%d, payloadlen=%d\n",packet.messageid,packet.payloadlen);
  coap.sendResponse(ip,port,packet.messageid,"ESP32 at your service");
}


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

  //setup message buffer
  //pb_ostream_t s = pb_ostream_from_buffer(b,sizeof(b));
  //bool status = pb_encode(&s, sayhello_fields, &m);
  //if (status) printf("pb_encode OK\n"); else printf("pb_encode failed: %s\n",PB_GET_ERROR(&s));
  
  m.n = 42;

  coap.server(coapCallBackInfo,"info");
  coap.start();
}


void arduino_loop() {
  if ((n++ % 10) == 0)  Serial.printf("coap test WiFi rssi = %d\n",WiFi.RSSI());
  delay(100);
  coap.loop();
}
