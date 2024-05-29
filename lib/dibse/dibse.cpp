#include "dibse.h"

void DibsE::setup()
{
    //source eduArdu software on github.
    strip.begin();
    // Initialize all pixels to 'off'
    this->simpleBlinkOff();
    // trun LED on
    this->simpleBlinkOn(1000,255,255,0);
}
// number to determine color 
// based on Modulo 3, colors will alternate between Red, Greed and Blue
int a = 0;
void DibsE::loop()
{
    int r,g,b;
    int round = a % 3;
    switch (round)
    {
    case 0:
        r = 255;
        g = 0;
        b = 0;
        break;
    case 1:
        r = 0;
        g = 255;
        b = 0;
        break;
    
    default:
        r = 0;
        g = 0;
        b = 255;
        break;
    }
    this->simpleBlinkOn(1000,r,g,b);
    a++;
}

void DibsE::simpleBlinkOn(int duration, int red, int green, int blue)
{
    // set colors of RGB 
    strip.setPixelColor(0, strip.Color(red, green, blue));
    // display lights
    strip.show();
    // delay for duration.
    delay(duration);
}

void DibsE::simpleBlinkOff()
{
    // clear RGB values (set them all to 0)
    strip.clear();
    // makes cler() take effect
    strip.show();
}
