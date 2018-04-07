#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)

#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic :-)

#include <IFTTTWebhook.h>         //https://github.com/romkey/IFTTTWebHook IFTTT Trigger Magic :-)
#define IFTTT_API_KEY "dsUmSj2OHYHVND5G8QTO2r"
#define IFTTT_EVENT_NAME "button_pressed"

volatile bool BUTTON_state = false;

void button_pressed() {
  noInterrupts();
  BUTTON_state = true;
  interrupts();
}

void setup() {
  WiFiManager wifiManager;
  wifiManager.autoConnect("MARINO_ESP", "1234");

  attachInterrupt(D3, button_pressed, FALLING); //CHANGE, RISING, FALLING Lógica inversa

  Serial.begin(115200);

  Serial.println(WiFi.localIP());
}

void loop() {
  while (!BUTTON_state)
    yield();

  IFTTTWebhook myWebHook(IFTTT_API_KEY, IFTTT_EVENT_NAME);
  myWebHook.trigger();
  
  Serial.println("botón pulsado");  
  BUTTON_state = false;
}
