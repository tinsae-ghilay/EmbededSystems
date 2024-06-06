#include <Arduino.h>
# include <dibse.h>
# include <sensor.h>
# include <display.h>
DibsE d;
int pinOut = 8;
int pinIn = 4;
auto s = Sensor(pinOut, pinIn);
auto  display = Display(11,16,15);
void setup() {
  s.setup();
  d.setup();
  display.start();
  display.setProximity(150);
}
int last = 0;
void loop() {
  int now = millis();
  d.loop();
  s.echo();
  display.loop();
  if(now - last > 1000){
    int distance = s.getDistance();
    d.setProximity(distance);
    display.setProximity(distance);
    Serial.println(distance);
    last = now;
  }
}