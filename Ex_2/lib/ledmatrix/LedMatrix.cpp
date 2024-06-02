/*
LED_Matrix is a Library to drive the Olimex 8x8 (non-rgb) matrix
Based on the original library LED_Matrix created by Lutz Reiter, Dec 2014.
*/
#include "LedMatrix.h"

//
LedMatrix::LedMatrix(int latchPin, int dataPin, int clockPin) {
	this->dataPin = dataPin;
	this->latchPin = latchPin;
	this->clockPin = clockPin;

	pinMode (latchPin, OUTPUT);
	pinMode (clockPin, OUTPUT);
	pinMode (dataPin, OUTPUT);

	this->clear();
}

void LedMatrix::clear() {
	for (int i=0; i<8; i++) {
		this->displayBuffer[i] = 0;
	}
}

void LedMatrix::drawColumn(uint8_t column, byte mask) {
	if (column < 8) {
		displayBuffer[7-column] = mask;
	}
}

byte* LedMatrix::getDisplayBuffer() {
	return displayBuffer;
}

void LedMatrix::drawPixel(uint8_t x, uint8_t y, bool state) {
	if (x < 8 && y < 8) {
		if (state) {
			displayBuffer[7-x] |= (1 << y);
		} else {
			displayBuffer[7-x] &= ~(1 << y);
		}
	}
}

// shifts the data to the led-matrix to display it
//the multiplexing has to be done by the arduino, so this function has to be called constantly
void LedMatrix::update() {
	for (byte i=0; i<8; i++) {
		// bitwise operations are faster
		PORTB = PORTB & 0x7F;	//digitalWrite(this->latchPin, LOW);
		shiftOut(this->dataPin, this->clockPin, LSBFIRST, displayBuffer[i]);
		shiftOut(this->dataPin, this->clockPin, LSBFIRST, 1 << i);
		PORTB = PORTB | 0x80;	//digitalWrite(this->latchPin, HIGH);
	}
	// first column is permanently on, all others are not.
	// therefore switch first column off, so that all columns behave the same
	PORTB = PORTB & 0x7F;	//digitalWrite(this->latchPin, LOW);
	shiftOut(this->dataPin, this->clockPin, LSBFIRST, 0);
	shiftOut(this->dataPin, this->clockPin, LSBFIRST, 1);
	PORTB = PORTB | 0x80;	//digitalWrite(this->latchPin, HIGH);
}


LedMatrixTextBuffer::LedMatrixTextBuffer(LedMatrix& ledMatrix) : ledMatrix(ledMatrix) {
}

bool LedMatrixTextBuffer::drawChar(uint8_t index, char c) {
	if (index < STRING_MAX_CHAR) {
		int i;
		for (i=0; i<CHAR_WIDTH; i++) {
			if (i == CHAR_WIDTH - 1) {
				textBuffer[index*CHAR_WIDTH + i] = 0;
			} else {
				textBuffer[index*CHAR_WIDTH + i] = FontLookup[c-0x20][i];
			}
		}
		dirtyFlag = true;
		return true;
	}
	return false;
}

int LedMatrixTextBuffer::drawText(char str[], uint8_t index) {
	int i;
	for (i=0; str[i]; i++) {
		if (!drawChar(index+i, str[i])) {
			break;
		}
	}
	textLen = i;
	return textLen;
}

void LedMatrixTextBuffer::slideRight (int positions)
{
	textOffset = textOffset - positions;
	if (textOffset < 0)
		textOffset = textOffset + (CHAR_WIDTH * textLen);
	dirtyFlag = true;
}

void LedMatrixTextBuffer::slideLeft (int positions)
{
	textOffset = (textOffset + positions) % (CHAR_WIDTH * textLen);
	dirtyFlag = true;
}

void LedMatrixTextBuffer::commitText() {
	int i;
	ledMatrix.clear();
	for (i=0; i<8; i++) {
		ledMatrix.drawColumn (i, BitReverseTable256[textBuffer[(textOffset + i)%(CHAR_WIDTH * textLen)]]);
	}
	dirtyFlag = false;
}

void LedMatrixTextBuffer::update() {
	if (dirtyFlag) {
		commitText();
	}
	ledMatrix.update();
}
