/*
* created by TGK
* Jun 2,2024
* for Computer structures and embeded systems
*/


#ifndef SENSOR_H
#define SENSOR_H

class Sensor{
    private:

    int distance, _break;
    int tPin;
    int ePin;
    bool echoing;


    public:

    Sensor(int tPin, int ePin);

    void setup();
    void echo();
    int getDistance();
};
#endif//SENSOR_H