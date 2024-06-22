#include "dibse.h"

// wird in der setup-Funktion eines Arduino Programms aufgerufen.
void DibsE::setup()
{
    // check serial, and start t if not running.
    if (!Serial)
    {
        Serial.begin(9600);
    }
    // source eduArdu software on github.
    strip.begin();
    // Initialize all pixels to 'off'
    this->simpleBlinkOff();
    // set up Clap detector with pin for microphone an threshold
    cl.setup(MICROPHONE, 300);
}

// loop to blink RGB LED cndinously for a duration
// none blocking
uint32_t _break = millis();

// rnds variable to hold how many times RGB LED Blinked
uint8_t rnds = 0;
void DibsE::loop()
{
    // update clap detector so it listens to sound
    cl.update();
    // and get the claps it recorded
    clap state = cl.getState();
    // if we have double claps, we turn RGB LED strip on
    if (state == DOUBLE)
    {
        Serial.println("Double claps detected LED ON");
        simpleBlinkOn(this->r, this->g, this->b);
        // this makes LED ON duration consistent
        _break = millis();
    }
    // if we have a tripple clap, we have to blink
    // for this we set flag blinking to true
    // so we can blink 3 times while this flag is set to true
    if (state == TRIPPLE)
    {
        Serial.println("Tripple claps detected LED BLINK");
        this->blinking = true;
        // and start blinking
        simpleBlinkOn(this->r, this->g, this->b);
        // this makes LED ON duration consistent
        _break = millis();
    }
    // we also need to count time for blinking
    uint32_t now = millis();
    uint16_t elapsed = now - _break;
    
    // two claps turn led on and off
    // three claps Blink LED and of
    // LED blinks or turns off by itself

    // if no claps are detected, clap detection has completed
    // check if RGB LED is on or we have to blink
    if (state == NONE && elapsed > this->duration)
    {

        if (this->blinking && rnds < 4)
        { /* we have to blink */
            // LED on when rnds is odd, and off when even
            (rnds % 2 == 1) ? simpleBlinkOn(this->r, this->g, this->b) : simpleBlinkOff();
            // keep track of round of blinks
            rnds++;
            if (rnds == 4)
            { // if we are done with blinking
                // set flag to false
                this->blinking = false;
                // and rounds to 0
                rnds = 0;
            }
        }
        else
        { // we have to turn off RGB LED , if it's on
            if (this->ledOn)
                simpleBlinkOff();
        }
        // and record time for further use
        _break = now;
    }
}

// turns RGB LED on
void DibsE::simpleBlinkOn(int red, int green, int blue)
{
    ledOn = true;
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

// duration of blinking
void DibsE::setDuration(uint16_t duration)
{
    this->duration = duration;
}

// RGB channels to set RGB LED colour
void DibsE::setChannels(int r, int g, int b)
{
    // red
    this->r = r;
    // green
    this->g = g;
    // blue
    this->b = b;
}

// changes LED color and duration depending on proximity
// by mapping distance to apropriate range;
void DibsE::setProximity(int dist)
{
    this->r = map(dist, 0, 500, 255, 0);
    this->g = map(dist, 0, 500, 0, 255);
    this->duration = map(dist, 0, 500, 0, 2000);
}

int DibsE::getDuration()
{
    return this->duration;
}
