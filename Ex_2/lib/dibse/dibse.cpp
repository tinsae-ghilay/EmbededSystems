# include "dibse.h"

//wird in der setup-Funktion eines Arduino Programms aufgerufen. 
void DibsE::setup()
{
    // check serial, and start t if not running.
    if(!Serial){
        Serial.begin(9600);
    }
    //source eduArdu software on github.
    strip.begin();
    // Initialize all pixels to 'off'
    this->simpleBlinkOff();
    // trun LED on
    this->simpleBlinkOn(r,g,b);
}

// loop to blink RGB LED cndinously for a duration
// none blocking
uint32_t _break = 0;
void DibsE::loop()
{
    uint16_t now = millis();
    if(now - _break > this->duration){
        if(ledOn){
            simpleBlinkOff();
        }else{
            simpleBlinkOn(this->r, this->g,this->b);
        }
        _break = now;
    }

}

// turns RGB LED on
void DibsE::simpleBlinkOn(int red, int green, int blue)
{
    ledOn =  true;
    // set colors of RGB 
    strip.setPixelColor(0, strip.Color(red, green, blue));
    // display lights
    strip.show();
}

// Turns RGB LED off
void DibsE::simpleBlinkOff()
{
    // clear RGB values (set them all to 0)
    strip.clear();
    ledOn = false;
    // makes cler() take effect
    strip.show();
}

void DibsE::setDuration(uint16_t duration)
{
    this->duration = duration;
}

void DibsE::setChannels(int r, int g, int b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

// changes LED color and duration depending on proximity
// by mapping distance to apropriate range;
void DibsE::setProximity(int dist)
{
    this->r = map(dist,0,500,255,0);
    this->g = map(dist,0,500,0,255);
    this->duration = map(dist,0,500,0,2000);
}

int DibsE::getDuration()
{
    return  this->duration;
}
