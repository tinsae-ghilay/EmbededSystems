#include <Arduino.h>
# include <temprature.h>


// setup
TempratureSensor sensor;
void setup() {
  // always begin serial, who knows
  Serial.begin(9600);
  delay(1000);
  sensor.begin();
  // set resolution to (0b11 or 3)12 bit
  sensor.setResolution(3);
  delay(1000);
}

// loop
uint16_t start = millis();
void loop() {
  sensor.update();
  uint16_t now = millis();
  if(now - start > 1000){
    Serial.print("Current temprature: ");
    Serial.println(sensor.getTemperature(false));
    start = now;
  }
}