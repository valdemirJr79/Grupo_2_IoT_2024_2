#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "html.h"

#define DS18B20PIN D2

OneWire oneWire(DS18B20PIN);
DallasTemperature sensor(&oneWire);

ESP8266WebServer server(80);

float _temperature = 0;

const char* ssid = "REDEWORK";
const char* password = "Acessonet05";

unsigned long lastRead = 0;
const unsigned long interval = 1000; // 1 segundo

void MainPage() {
  server.send_P(200, "text/html", html_page);
}

void Temp() {
  server.send(200, "text/plain", String(_temperature));
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.println(WiFi.localIP());

  sensor.begin();

  server.on("/", MainPage);
  server.on("/readTemp", Temp);

  server.begin();
}

void loop() {

  // 🔥 Leitura não-bloqueante
  if (millis() - lastRead >= interval) {
    lastRead = millis();

    sensor.requestTemperatures();
    _temperature = sensor.getTempCByIndex(0);

    Serial.print("Temperature: ");
    Serial.println(_temperature);
  }

  server.handleClient(); // nunca pode travar
}