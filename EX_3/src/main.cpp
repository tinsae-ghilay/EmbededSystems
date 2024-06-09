#include <Arduino.h>
# include <ample.h>
# include <sleep_delay.h>
#define LED_PIN		12


Ample amp;
void setup() {
	Serial.begin(96000);
	amp.start();

	/*for (int i = 0; i < 5; i++) {
		digitalWrite(LED_PIN, HIGH);
		delay(500);
		digitalWrite(LED_PIN, LOW);
		delay(500);
	}*/
}

void loop() {
	/*
	Serial.println(F("Enter sleep mode"));
	digitalWrite(LED_PIN, HIGH);
	sleep_delay(7);
	digitalWrite(LED_PIN, LOW);
	Serial.println(F("Exit sleep mode"));
	delay(2000);*/
	amp.loop();
}