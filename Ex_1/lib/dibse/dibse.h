#ifndef DIBSE_H
#define DIBSE_H

#include <Adafruit_NeoPixel.h>



class DibsE{
private:

int16_t pin = A4;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, pin, NEO_GRB + NEO_KHZ800);

public:
    //wird in der setup-Funktion eines Arduino Programms aufgerufen. 
    //Diese Funktion macht derzeit noch nichts ;-)
    void setup();
    void loop(); //wird in der loop-Funktion eines Arduino Programms aufgerufen.
    void simpleBlinkOn(int duration, int red, int green, int blue); //Diese Funktion soll das RGB-LED von DiBS▪E abwechselnd für die Dauer von int duration leuchten lassen bzw. ausschalten. Die Farbe wird dabei durch einen RGB-Wert (int red, int green & int blue) bestimmt.
    void simpleBlinkOff(); //stoppt das Blinken.

};
#endif