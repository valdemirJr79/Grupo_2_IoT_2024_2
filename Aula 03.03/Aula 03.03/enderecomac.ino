#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Obtendo endereço MAC...");
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
}

void loop() {
}


Endereço MAC: 84:0d:8e:aa:be:f3
