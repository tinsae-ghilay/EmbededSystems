#ifndef	_FONT_H
#define	_FONT_H

extern const unsigned char BitReverseTable256[];

// CHAR_WIDTH is 1 larger than the actual font itself so we can create a small space between characters

#define	CHAR_WIDTH	6
extern const unsigned char  FontLookup [][5];
extern const unsigned char BitReverseTable256[];
#endif
