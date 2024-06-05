#include "sensor.h"
# include <Arduino.h>

Sensor::Sensor(int tPin, int ePin): tPin{tPin},ePin{ePin}{}

// setup sets pin modes;
void Sensor::setup()
{
    pinMode(tPin, OUTPUT);
    pinMode(ePin, INPUT_PULLUP);
}

// none blocking trigger and echo distance measurement
void Sensor::echo()
{
    uint32_t now = millis();
    int interval = now - this->_break;

    // 2 milliseconds since  measurement
    if(interval > 2 && !echoing){
        // turn on pin
        digitalWrite(tPin, HIGH);
        // set echoing to true
        this->echoing = true;
    }
    // 10 mealliseconds since trigger was fired 
    // we take measurement here
    if(interval > 13 && echoing){
        // read data and turn off
        int duration = pulseIn(ePin, HIGH);
        // distance = duration / 29 / 2 because eduArdu`s gitHub has it like this.
        this->distance = duration /29 / 2 ;

        // we turn pin off and repeat whenever called
        digitalWrite(tPin, LOW);
        this->_break = now;
        echoing = false;
    }
    
}

// getter
int Sensor::getDistance()
{
    return this->distance;
}
