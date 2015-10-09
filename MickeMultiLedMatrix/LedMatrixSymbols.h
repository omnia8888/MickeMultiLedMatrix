// LedMatrixSymbols.h

#ifndef _LEDMATRIXSYMBOLS_h
#define _LEDMATRIXSYMBOLS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class LedMatrixSymbols
{
 protected:


 public:
	//LedMatrixSymbols(byte i)

private:

};


byte symbolSun[] = {
		B10010010,
		B01010100,
		B00111000,
		B11111110,
		B00111000,
		B01010100,
		B10010010,
		B00000000,
	};

byte *symbolToDisplay;

#endif

