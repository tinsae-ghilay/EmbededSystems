#include "display.h"

// sets the number of LEDs to be fired up on x axis(Horizontal)
// I light only one line here but it is possible to light up to 8 lines
void Display::setProximity(int duration)
{
    this->x = map(duration, 0, 450, 8, 1);
    
}

// reset the matrix when starting.
void Display::start()
{
    this->matrix.clear();
}

// update vertical and horizontal lines
void Display::loop()
{
    matrix.clear();
    for(int i = 0; i < x; i++){
        // draws dots horizontally (one column at a time)
        matrix.drawColumn(i,1);
        // draws line vertically
        matrix.drawPixel(0,i,true);
    }
    matrix.update();
}
