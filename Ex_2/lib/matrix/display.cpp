#include "display.h"

Display::Display(int latchPin, int dataPin, int clockPin)
            :lPin(latchPin),dPin(dataPin),cPin(clockPin)
{
    pinMode (latchPin, OUTPUT);
	pinMode (clockPin, OUTPUT);
	pinMode (dataPin, OUTPUT);
}

// sets the number of LEDs to be fired up on x axis(Horizontal)
// I light only one line here but it is possible to light up to 8 lines
void Display::setProximity(int duration)
{
    this->x = map(duration, 0, 500, 8, 0);
}

// reset the matrix when starting.
void Display::start()
{
    clear();
}

// update vertical and horizontal lines
void Display::loop()
{
    clear();
    on();
    update();
}

// shifts the data to the led-matrix to display it
//the multiplexing has to be done by the arduino, so this function has to be called constantly
void Display::update() {
	for (byte i=0; i<8; i++) {
		// bitwise operations are faster
		PORTB = PORTB & 0x7F;	//digitalWrite(this->latchPin, LOW);
		shiftOut(this->dPin, this->cPin, LSBFIRST, buffer[i]);
		shiftOut(this->dPin, this->cPin, LSBFIRST, 1 << i);
		PORTB = PORTB | 0x80;	//digitalWrite(this->latchPin, HIGH);
	}
	// first column is permanently on, all others are not.
	// therefore switch first column off, so that all columns behave the same
	shiftOut(this->dPin, this->cPin, LSBFIRST, 0);
	shiftOut(this->dPin, this->cPin, LSBFIRST, 1);
}

void Display::clear()
{
    for(byte b = 0; b < 8; b++){
        buffer[b] = 0;
    }
}


void Display::on() {
  for (byte b = 0; b < this->x; b++) {
        buffer[7] |= HIGH << b;
        buffer[7-b] |= HIGH << 0;
    }
}
