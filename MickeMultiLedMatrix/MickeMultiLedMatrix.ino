/*
Name:		MatrixTemperature.ino
Created:	10/8/2015 5:25:37 AM
Author:	Micke
*/

//We always have to include the library
#include "LedMatrixSymbols.h"
#include <LedControl.h>


/*
Now we need a LedControl to work with.
***** These pin numbers will probably not work with your hardware *****
pin 12 is connected to the DataIn
pin 11 is connected to the CLK
pin 10 is connected to LOAD
We have only a single MAX72XX.
*/


////Max row index of display matrix. Depending on total number of rows on display matrix. Starting from 0
//#define MAX_DISPLAY_ROW_INDEX 7 
//
////Max column index of display matrix.Depending on total number of columns on display matrix. Starting from 0
//#define MAX_DISPLAY_COL_INDEX 31

#define LED_MATRIX_MODULE_ROWS 8 //Defines the number of rows on a single dot matrix module used
#define LED_MATRIX_MODULE_COLUMNS 8 //Defines the number of columns on a single dot matrix module used

//Total number of displays.
#define NUM_OF_DISPLAYS 5

const byte maxDisplayNumIndex = (NUM_OF_DISPLAYS - 1);
const byte maxSingleRowIndex = (LED_MATRIX_MODULE_ROWS - 1);
const byte maxSingleColIndex = (LED_MATRIX_MODULE_COLUMNS - 1);

LedControl lc = LedControl(12, 11, 10, NUM_OF_DISPLAYS);

int my_array[] = { 1,23,17,4,-5,100 };
int *ptr;

byte symTestdata[] = {
	B10010010,
	B01010100,
	B00111000,
	B11111110,
	B00111000,
	B01010100,
	B10010010,
	B00000000,
};

byte *testSymbol;



// the setup function runs once when you press reset or power the board
void setup()
{



	//For debugging
	Serial.begin(9600);

	//Init Displays
	/*
	The MAX72XX is in power-saving mode on startup,
	we have to do a wakeup call
	*/
	for (int i = 0; i < 8; i++)
	{
		lc.shutdown(i, false);
		/* Set the brightness to a medium values */
		lc.setIntensity(i, 8);
		/* and clear the display */
		lc.clearDisplay(i);
	}
	delay(1000);

	int i;
	ptr = &my_array[0];     /* point our pointer to the first
							element of the array */

	for (i = 0; i < 6; i++)
	{
		Serial.print(i);
		Serial.print("=");
		Serial.println(*(ptr + i));
	}
	
	//int x, z;
	//byte b;
	//x = (33 + 256);
	//for (byte i = 0; i < 2; i++)
	//{
	//	z = x >> i * 7;
	//	b = lowByte(z);
	//	Serial.print(z);
	//	Serial.print("=");
	//	Serial.println(b);
	//}

}

// the loop function runs over and over again until power down or reset
void loop()
{


	//displaySingleRow(0, 0, b);

	testSymbol = &symTestdata[0];

	displaySymbol(0, 17, symTestdata, true);
	
	displaySymbol(0, 0, &symTestdata[0], true);
	//lc.setRow(startDisplay, startRow, SingleDispVal);

	//Update the led segments in display matrix

}

/*	Sets the state of a single led segment on the multi display matrix.
with row and column index based on total display layout starting from upper left corner.
*/
void oneDot(byte row, byte col, bool state)
{
	//Calculate on what display the dot is located.
	byte displayNum = (maxDisplayNumIndex - (col / 8));

	//Calculate column index on the single display
	byte singleCol = (col % 8);
	//Serial.println(singleCol);

	lc.setLed(displayNum, row, singleCol, state);
}

//void displaySymbol(byte row, byte col, byte symbol[8], bool visable)

void displaySymbol(byte row, byte col,byte* symbol, bool visable)
{
	byte value;
	//Print out each row of symbol on multi display
	for (uint8_t i = 0; i < LED_MATRIX_MODULE_ROWS; i++)
	{
		value = (*(symbol+i));
		displaySingleRow(i, col, value);
	}

}


void displaySingleRow(byte row,byte col,byte value){

	int totalVal;
	byte displayNo,ledRow,ledCol,
		SingleDispVal,ledState;
	
	//Check display value for individual led state on two displays.
	for (byte i = 0; i < 15; i++)
	{
		ledState = (value >> i) & 1;
		ledCol = (col + i);

		//Update one individual led segment state
		oneDot(row, ledCol, ledState);

		//Serial.print(i);
		//Serial.print("=");
		//Serial.println(ledState);

	}
}
