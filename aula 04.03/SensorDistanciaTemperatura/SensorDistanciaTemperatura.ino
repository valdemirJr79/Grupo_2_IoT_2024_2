#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Ultrasonic.h>
#include "html.h"

// ---------- PINOS ----------
#define DS18B20PIN D2
#define pino_trigger D6 
#define pino_echo D1

// ---------- OBJETOS ----------
OneWire oneWire(DS18B20PIN);
DallasTemperature sensor(&oneWire);
Ultrasonic ultrasonic(pino_trigger, pino_echo);
ESP8266WebServer server(80);

// ---------- VARIÁVEIS ----------
float _temperature;
long _distancia;

const char* ssid = "REDEWORK";
const char* password = "Acessonet05";

// ---------- PÁGINA PRINCIPAL ----------
void MainPage() {
  String _html_page = html_page;
  server.send(200, "text/html", _html_page);
}

// ---------- ROTA TEMPERATURA ----------
void Temp() {
  String TempValue = String(_temperature);
  server.send(200, "text/plain", TempValue);
}

// ---------- ROTA DISTÂNCIA ----------
void Dist() {
  String DistValue = String(_distancia);
  server.send(200, "text/plain", DistValue);
}

// ---------- SETUP ----------
void setup(void){

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  sensor.begin();

  server.on("/", MainPage);
  server.on("/readTemp", Temp);
  server.on("/readDist", Dist);

  server.begin();

  Serial.println("Sistema iniciado...");
}

void loop() {

  server.handleClient(); // SEMPRE primeiro

  static unsigned long lastRead = 0;

  if (millis() - lastRead >= 1000) {

    lastRead = millis();

    // Temperatura
    sensor.requestTemperatures();
    _temperature = sensor.getTempCByIndex(0);

    Serial.print("Temperature = ");
    Serial.println(_temperature);

    // Distância
    _distancia = ultrasonic.read();

    Serial.print("Distancia = ");
    Serial.println(_distancia);
  }
}