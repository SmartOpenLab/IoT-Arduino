#include <ESP8266WiFi.h>
#define RELE_GPIO D1

const char* ssid = "Orange-152A";
const char* password = "3EE529C4";
bool RELE_estado = LOW;

WiFiServer server(80); //objeto servidor que inicializaremos en el puerto 80
 
void setup() {
  Serial.begin(115200);

  // Poner el módulo WiFi en modo station y desconectar de cualquier red a la que pudiese estar previamente conectado
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(2000);

  pinMode(RELE_GPIO, OUTPUT);
  digitalWrite(RELE_GPIO, LOW);
 
  //Conectar a la red WiFi
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Conectado, la IP del dispositivo es: ");
  Serial.println(WiFi.localIP());
 
  //Iniciar server
  server.begin();
  Serial.println("Servidor iniciado");
}
 
void loop() {
  //chequeamos si se ha conectado un cliente, en caso contrario terminar (se reiniciaría)
  WiFiClient client = server.available();
  if (!client)
    return;
 
  //Esperar hasta que el cliente envíe algún dato
  while(!client.available())
    delay(1);
 
  //Lee la request del cliente
  String request = client.readStringUntil('\r');
  client.flush(); //vaciamos por seguridad

  //Request en un objeto String que contiene la URL completa, incluyendo parámetros. Buscamos si contien la cadena "/RELE=ON"
  if (request.indexOf("/RELE=ON") != -1){
    digitalWrite(RELE_GPIO, HIGH);
    RELE_estado=HIGH;
  }
  else
    if (request.indexOf("/RELE=OFF") != -1){
      digitalWrite(RELE_GPIO, LOW);
      RELE_estado=LOW;
    }
      
  //Parte "response" del servidor hacia el cliente, una página Web
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //requerido
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("<p>RELE ");
   if(RELE_estado == HIGH)
    client.print("encendido</p>");
  else
    client.print("apagado</p>");

  client.println("<a href=\"/RELE=ON\"><button>Turn On </button></a>");
  client.println("<a href=\"/RELE=OFF\"><button>Turn Off </button></a><br />");
  client.println("</html>");
 
  Serial.println("Client disconnected");
}
