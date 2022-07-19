#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <InfluxDb.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4
#define INFLUXDB_HOST "192.168.0.146"
#define WIFI_SSID "SSID"
#define WIFI_PASS "PASSWORD"
ESP8266WiFiMulti WiFiMulti;
Influxdb influx(INFLUXDB_HOST);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  WiFiMulti.addAP(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WIFI");
  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  influx.setDb("hvac");
  Serial.println("Setup Complete.");
}

void loop() {
  delay(5000);
  InfluxData row("room1");
  row.addValue("temperature", random(1, 20));
  influx.write(row);
  delay(20000);
  long t = millis();
}
