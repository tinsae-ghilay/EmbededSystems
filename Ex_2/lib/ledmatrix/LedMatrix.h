/*
LedMatrix is a Library to drive the Olimex 8x8 (non-rgb) matrix
Based on the library LED_Matrix created by Olimex and the original library LED_Matrix created by Lutz Reiter, Dec 2014.
*/

#ifndef _LEDMATRIX_H
#define _LEDMATRIX_H

#include <Arduino.h>

#include "LedMatrixFont.h"

#define STRING_MAX_CHAR  32

/**
 * Driver for the Olimex 8x8 LED matrix.
 *
 * Provides simple drawing methods.
 * All drawing operations are first written into a display buffer, and only shown on the display after a call to update().
 */
class LedMatrix {
public:
	/**
	 * Constructor
	 */
	LedMatrix(int latchPin, int dataPin, int clockPin);

	/**
	 * Clears the display buffer.
	 */
	void clear();

	/**
	 * Draws a single pixel into the display buffer.
	 *
	 * A call to update() is required to see any changes on the display!
	 *
	 * \param x x-coordinate
	 * \param y y-coordinate
	 * \param state whether the pixel is on or off
	 */
	void drawPixel(uint8_t x, uint8_t y, bool state);

	/**
	 * Draws a single column.
	 *
	 * A call to update() is required to see any changes on the display!
	 *
	 * \param mask column pixel mask
	 */
	void drawColumn(uint8_t column, byte mask);

	/**
	 * Returns the internal display buffer.
	 *
	 * The display buffer size is 8 byte.
     * Each byte of the display buffer represents all pixel of the display column at the respective index.
     *
	 * A call to update() is required to see any changes on the display!
     *
     * \returns display buffer
	 */
	byte* getDisplayBuffer();

	/**
	 * Shifts the display buffer data to the led matrix to display it.
	 *
	 * This methods causes the display to light up for a short time.
	 * To have a permanent display, this method needs to be constantly called.
	 * The time interval between calls to this method influences the brightness of the display.
	 */
	void update();

private:
	int latchPin,dataPin,clockPin;
	byte displayBuffer[8];
};


/**
 * Displays text on the Olimex 8x8 LED matrix.
 *
 * The Text is written into a text buffer and can be left or right shifted.
 * It is only shown on the display after a call to update().
 */
class LedMatrixTextBuffer {
public:
	/**
	 * Constructor
	 */
	LedMatrixTextBuffer(LedMatrix& ledMatrix);

	/**
	 * Draws a character into the text buffer at position index.
	 *
	 * A call to update() is required to see any changes on the display!
	 *
	 * \param index index of buffer
	 * \param c character
	 * \returns false when index out of range, otherwise true
	 */
	bool drawChar(uint8_t index, char c);

	/**
	 * Draws the given null-terminated string into the text buffer starting at position index.
	 *
	 * A call to update() is required to see any changes on the display!
	 *
	 * \param str null-terminated string
	 * \param index buffer index
	 * \returns number of characters written into the text buffer
	 */
	int drawText(char str[], uint8_t index = 0);

	/**
	 * Slides the text on the display to the left.
	 *
	 * A call to update() is required to see any changes on the display!
	 *
	 * \param positions how many columns should the text be shifted
	 */
	void slideLeft (int positions);

	/**
	 * Slides the text on the display to the right.
	 *
	 * A call to update() is required to see any changes on the display!
	 *
	 * \param positions how many columns should the text be shifted
	 */

	void slideRight (int positions);

	/**
	 * Writes changes of the text buffer into the display buffer.
	 *
	 * Usually no need to explicitly call this function.
	 */
	void commitText();

	/**
	 * Writes changes of the text buffer into the display buffer and shifts the display buffer data to the led matrix to display it.
	 */
	void update();

private:
	LedMatrix& ledMatrix;
	int textOffset = 0, textLen = 0;
	bool dirtyFlag = false;
	char textBuffer[STRING_MAX_CHAR * CHAR_WIDTH];
};

#endif
