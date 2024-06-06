#ifndef DIBSE_H
#define DIBSE_H

#include <Adafruit_NeoPixel.h>



class DibsE{
private:
bool ledOn = false;
uint16_t duration = 500;
uint8_t r = 100,g = 100,b = 0;
int16_t pin = A4;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, pin, NEO_GRB + NEO_KHZ800);

public:
    // wird in der setup-Funktion eines Arduino Programms aufgerufen. 
    // Diese Funktion macht derzeit noch nichts ;-)
    void setup();
    // wird in der loop-Funktion eines Arduino Programms aufgerufen.
    void loop(); 
    // Diese Funktion soll das RGB-LED von DiBS▪E abwechselnd für die Dauer von int duration leuchten lassen bzw. ausschalten. 
    // Die Farbe wird dabei durch einen RGB-Wert (int red, int green & int blue) bestimmt.
    void simpleBlinkOn(int red, int green, int blue); 
    // stoppt das Blinken.
    void simpleBlinkOff(); 
    // sets the on -> off interval
    void setDuration(uint16_t duration);
    // sets RGB channels
    void setChannels(int r, int g, int b);
    // sets proximity (distance) so duration can be set accordingly
    void setProximity(int dist);
    // getter
    int getDuration();

};
#endif