#include <Arduino.h>
# include <ample.h>
# include <sleep_delay.h>
#define LED_PIN		12


Ample amp;
void setup() {
	Serial.begin(96000);
	amp.start();
}

void loop() {
	amp.loop();
}