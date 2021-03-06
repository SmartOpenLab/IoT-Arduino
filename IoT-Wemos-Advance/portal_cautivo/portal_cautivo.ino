#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)

#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic :-)


void setup() {
  WiFiManager wifiManager;
  wifiManager.autoConnect("MARINO_ESP", "1234");

  Serial.begin(115200);

  Serial.println(WiFi.localIP());
}

void loop() {
}
