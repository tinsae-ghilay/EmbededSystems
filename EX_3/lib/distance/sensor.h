/*
* created by TGK
* Jun 2,2024
* for Computer structures and embeded systems
*/
# include<Arduino.h>


#ifndef SENSOR_H
#define SENSOR_H
class Sensor{
    private:

    int distance;
    uint8_t tPin;
    uint8_t ePin;


    public:

    Sensor(uint8_t tPin, uint8_t ePin);

    void setup();
    void echo();
    uint8_t getDistance();
};
#endif//SENSOR_H