#include <Arduino.h>
# include <dibse.h>



DibsE dibse;

void setup()
{
  // set up DibsE class
  dibse.setup();
  Serial.begin(115200);
}


void loop()
{
  // clap detector is integrated in DibsE
  // thus, we only call DibsE's loop function continously
  dibse.loop();
}