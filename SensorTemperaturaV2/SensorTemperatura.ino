#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "html.h"

#define DS18B20PIN D2   // No ESP8266 use D2

OneWire oneWire(DS18B20PIN);
DallasTemperature sensor(&oneWire);

ESP8266WebServer server(80);

float _temperature;

const char* ssid = "REDEWORK";
const char* password = "Acessonet05";

void MainPage() {
  String _html_page = html_page;
  server.send(200, "text/html", _html_page);
}

void Temp() {
  String TempValue = String(_temperature);
  server.send(200, "text/plain", TempValue);
}

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

  server.begin();
}

void loop(void){
  sensor.requestTemperatures();
  _temperature = sensor.getTempCByIndex(0);

  Serial.print("Temperature = ");
  Serial.print(_temperature);
  Serial.println(" ºC");

  server.handleClient();
  delay(1000);
}