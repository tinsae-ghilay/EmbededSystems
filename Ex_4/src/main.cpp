#include <Arduino.h>
# include <temprature.h>


// setup
TempratureSensor sensor;
void setup() {
  // always begin serial, who knows
  Serial.begin(9600);
  sensor.begin();
  // set resolution to (0b11 or 3)12 bit
  sensor.setResolution(3);
  //sensor.switchToOneShotMode();
  sensor.switchToContinuousMode();
  delay(100);
}

// loop
uint16_t start = millis();
uint16_t n = 1;
void loop() {

  uint16_t now = millis();
  if(now - start > 1000){
    Serial.print("Current temprature: ");
    Serial.println(sensor.getTemperature(false));
    sensor.update();
    start = now;
    n++;
    if(n % 20 == 0){
      sensor.switchToContinuousMode();
      n = 1;
  } else if(n % 10 == 0){
      sensor.switchToOneShotMode();
  }
  }
}