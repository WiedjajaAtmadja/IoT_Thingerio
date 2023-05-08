#define THINGER_SERIAL_DEBUG

#include <ThingerESP32.h>
#include <DHTesp.h>
#include <BH1750.h>
#include "arduino_secrets.h"
#define LED_GREEN  4
#define LED_YELLOW 5
#define LED_RED    18
#define PUSH_BUTTON 23
#define DHT_PIN 19

DHTesp dht;
BH1750 lightMeter;
ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  // open serial for debugging
  Serial.begin(115200);

  pinMode(PUSH_BUTTON, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);
  dht.setup(DHT_PIN, DHTesp::DHT11);
  Wire.begin();
  lightMeter.begin(); 

  thing.add_wifi(SSID, SSID_PASSWORD);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["led_builtins"] << digitalPin(LED_BUILTIN);
  thing["led_green"] << digitalPin(LED_GREEN);
  thing["led_yellow"] << digitalPin(LED_YELLOW);
  thing["led_red"] << digitalPin(LED_RED);

  // resource output example (i.e. reading a sensor value)
  thing["push_button"] >> outputValue(digitalRead(PUSH_BUTTON));
  thing["millis"] >> outputValue(millis());
  thing["temperature"] >> outputValue(dht.getTemperature());
  thing["humidity"] >> outputValue(dht.getHumidity());
  thing["light"] >> outputValue(lightMeter.readLightLevel());

  // more details at http://docs.thinger.io/arduino/
}

void loop() {
  thing.handle();
}