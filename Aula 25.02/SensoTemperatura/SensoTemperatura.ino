#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const char* ssid = "Supa";
const char* password = "1234578";

#define ONE_WIRE_BUS D2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.print("Conectando");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConectado!");
  Serial.println(WiFi.localIP());

  sensors.begin();
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  sensors.requestTemperatures();
  float temperatura = sensors.getTempCByIndex(0);

  String html = "<!DOCTYPE html><html>";
  html += "<head><meta http-equiv='refresh' content='5'/>";
  html += "<title>Monitor de Temperatura</title></head>";
  html += "<body style='text-align:center;font-family:Arial;'>";
  html += "<h1>Temperatura Atual</h1>";
  html += "<h2>";
  html += temperatura;
  html += " °C</h2>";
  html += "</body></html>";

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println(html);

  delay(1000);
}