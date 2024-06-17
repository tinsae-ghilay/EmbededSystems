
#include <Arduino.h>
#include "sleep_delay.h"

#define LED_PIN		12
void setup() {
	Serial.begin(9600);
	// LED to indicate start up
	digitalWrite(LED_PIN,HIGH);
    delay(1000);
	digitalWrite(LED_PIN, LOW);
	Serial.println(F("Done with Start up, Going to sleep"));
	delay(20);
}
void loop() {
	sleep_delay(10);
	// LED to indicate status, On when awake and off when asleep
	digitalWrite(LED_PIN, HIGH);
	Serial.println(F("Awake"));
	delay(1000);
	Serial.println(F("Sleeping"));
	delay(20);
	// LED off befor going to sleep
	digitalWrite(LED_PIN, LOW);
}