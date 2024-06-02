#include <Arduino.h>
# include <JoystickHigh.h>
# include <JoystickLow.h>
# include <dibse.h>
#include <stdint.h>

const int16_t SW_pin = PE2; // digital pin connected to SW
const int16_t X_pin = 0; // analog pin connected to VRx
const int16_t Y_pin = 1; // analog pin connected to VRy
const int16_t DEAD_ZONE = 25;
// put function declarations here
JoystickHigh js = JoystickHigh(X_pin, Y_pin, SW_pin);
DibsE dibse;
// Joystick low
JoystickLow jsL = JoystickLow(X_pin, Y_pin, SW_pin);


void setup()
{
  Serial.begin(9600);
  
  dibse.setup();
  //js.setDeadzone(DEAD_ZONE);
  //js.begin();
  jsL.begin();
  jsL.setDeadzone(DEAD_ZONE);
}

unsigned long lastTime = 0;
// forward declaration of functions
int dur = 10;

void loop() {
  unsigned long time = millis();
	if (time - lastTime >= 1000) {
      //testBitOperation();
      //js.loop();
      jsL.loop();
  
		lastTime = time;
	}
  if(dur > -1){
    dur--;
  }
  if(dur>0){
    dibse.loop();
  }
  if(dur == 0){
    Serial.println("Turning RGB off");
    dibse.simpleBlinkOff();
  }
}



