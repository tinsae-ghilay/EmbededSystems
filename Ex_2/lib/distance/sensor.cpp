#include "sensor.h"
# include <Arduino.h>

Sensor::Sensor(uint8_t tPin, uint8_t ePin): tPin(tPin),ePin(ePin){}

// setup sets pin modes;
void Sensor::setup()
{
    pinMode(tPin, OUTPUT);
    pinMode(ePin, INPUT);
}

// echo and measure distance
void Sensor::echo()
{
    digitalWrite(tPin, LOW);
    delay(2);
    // turn on pin
    digitalWrite(tPin, HIGH);
    // read data and turn off
    int duration = pulseIn(ePin, HIGH);
    // distance = duration / 29 / 2 because eduArdu`s gitHub has it like this.
    this->distance = duration * 0.017;
}

// getter
int Sensor::getDistance()
{
    return this->distance;
}
