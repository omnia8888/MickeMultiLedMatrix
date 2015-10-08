/*
Name:		MatrixTemperature.ino
Created:	10/8/2015 5:25:37 AM
Author:	Micke
*/

//We always have to include the library
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
	byte r = 0, c = 10;
	oneDot(r, c, true);

	int valToDisplay = B10101101;
	byte startDisplay = 0;
	byte startRow = 2;
	byte startCol = 2;

	int totalVal;
	byte displayNo, row, col, SingleDispVal;
	byte ledState;
	//Check display value for individual led state
	for (byte i = 0; i < 15; i++)
	{
		//ledState = (i >> valToDisplay) & 1;

		ledState = (valToDisplay >> i) & 1;
		col = (startCol + i);



		oneDot(startRow, col, ledState);

		Serial.print(i);
		Serial.print("=");
		Serial.println(ledState);

	}

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

void displaySymbol(byte row, byte col, byte symbol[7], bool visable)
{
	static byte currentMatrixStates[NUM_OF_DISPLAYS][8];

	byte singleDisplLedMatrix[7];
	//Calculate on what display the symbol begins.
	byte displayBegin = (col / 8);

	//check if symbol is located on a single display

	//convert the row value to row values for each single display


}
