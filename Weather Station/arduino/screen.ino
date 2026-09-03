#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);		// select the pins used on the LCD panel

// define some values used by the panel and buttons
int switchKey	=	0;
int switchValue	=	0;

#define switchPin	0						// A0

#define btnRIGHT	0
#define btnUP		1
#define btnDOWN		2
#define btnLEFT		3
#define btnSELECT	4
#define btnNONE		5

int read_LCD_buttons()
{											// read the buttons
	switchValue = analogRead(switchPin);	// read the value from the sensor 

											// my buttons when read are centered at these valies: 0, 144, 329, 504, 741, we add approx 50 to those values and check to see if we are close. We make this the 1st option for speed reasons since it will be the most likely result.

	if (switchValue > 1000)	return btnNONE;

	if (switchValue < 50)	return btnRIGHT;
	if (switchValue < 250)	return btnUP;
	if (switchValue < 450)	return btnDOWN;
	if (switchValue < 650)	return btnLEFT;
	if (switchValue < 850)	return btnSELECT;

	return btnNONE;							// when all others fail, return this.
}

void setup()
{
	lcd.begin(16, 2);						// start the library
	lcd.setCursor(0,0);						// set the LCD cursor position
	lcd.print("Push the buttons");			// print a simple message on the LCD

	Serial.begin(9600);						// start serial port
	while (!Serial) 
	{
		;									// wait for serial port to connect. Needed for Leonardo only
	}
}

void loop()
{
	lcd.setCursor(9,1);						// move cursor to second line "1" and 9 spaces over
	lcd.print(millis()/1000);				// display seconds elapsed since power-up

	lcd.setCursor(0,1);						// move to the begining of the second line
	switchKey = read_LCD_buttons();			// read the buttons

	switch (switchKey)
	{										// depending on which button was pushed, we perform an action

		case btnRIGHT:
		{									// push button "RIGHT" and show the word on the screen
			lcd.print("RIGHT ");
			Serial.println("Right");
			break;
		}
		
		case btnLEFT:
		{
			lcd.print("LEFT  ");			//	push button "LEFT" and show the word on the screen
			Serial.println("Left");
			break;
		}
		
		case btnUP:
		{
			lcd.print("UP    ");			//	push button "UP" and show the word on the screen
			Serial.println("Up");
			break;
		}
		
		case btnDOWN:
		{
			lcd.print("DOWN  ");			//	push button "DOWN" and show the word on the screen
			Serial.println("Down");
			break;
		}
		
		case btnSELECT:
		{
			lcd.print("SELECT");			//	push button "SELECT" and show the word on the screen
			Serial.println("Select");
			break;
		}
		
		case btnNONE:
		{
			lcd.print("NONE  ");			//	No action	will show "None" on the screen
			Serial.println(millis());
			break;
		}
	}
}
