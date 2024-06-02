#include <Arduino.h>
# include <dibse.h>
# include <Timer.h>
# include <sensor.h>
# include <display.h>
DibsE d;
Timer t;
int pinOut = 8;
int pinIn = 4;
auto s = Sensor(pinOut, pinIn);
Display display;
void setup() {
  s.setup();
  d.setup();
  t.start();
  display.start();
}


int last = 0;
void loop() {
  int now = t.read();
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