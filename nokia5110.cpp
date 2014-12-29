#include "nokia5110.h"
#include <wiringPi.h>
#include <wiringShift.h>
 
//Create an new Nokia display object on certain pins
Nokia5110::Nokia5110(unsigned char reset, unsigned char ce, unsigned char dc, unsigned char din, unsigned char clock, unsigned char contrast)
{
    //save data here
	_reset = reset;
	_ce = ce;
	_dc = dc;
	_din = din;
	_clock = clock;
	_contrast = contrast;
	
	//run initialization stuff here
	pinMode(_reset, OUTPUT);
	pinMode(_ce, OUTPUT);
	pinMode(_dc, OUTPUT);
	pinMode(_din, OUTPUT);
	pinMode(_clock, OUTPUT);
	
	digitalWrite(_reset, LOW);
	delay(500);
	digitalWrite(_reset, HIGH);
	
	writeCommand(0x21); // LCD extended commands
	writeCommand(0xB8); // set LCD Vop (contrast)
	writeCommand(0x04); // set temp coefficent
	writeCommand(0x14); // LCD bias mode 1:40
	writeCommand(0x20); // LCD basic commands
	writeCommand(0x0C); // normal display mode
}
 
//Turn on all of the pixels at once
void Nokia5110::fill()
{
	for (int i = 0; i < 84 * 6; i++)
	{
		writeData(0xff);
	}
}

void Nokia5110::clear()
{
    for (int i = 0; i < 84 * 6; i++)
	{
		writeData(0x00);
	}
}

void Nokia5110::showProgress(unsigned char position, unsigned char percentage)
{
	int cursor = 84 * (percentage / 100.0);
	setCursor(0, position);
	
	for (int i = 0; i < 84; i++)
	{
		if(i < cursor)
			writeData(0xff);
		else
			writeData(0x00);
	}
}

void Nokia5110::setCursor(unsigned char x, unsigned char y)
{
	writeCommand(0x80 | x);
	writeCommand(0x40 | y);
}
  
void Nokia5110::writeData(unsigned char data)
{
	digitalWrite(_dc, HIGH); //DC pin is HIGH for data
	digitalWrite(_ce, LOW);
	shiftOut(_din, _clock, MSBFIRST, data); //transmit serial data
	digitalWrite(_ce, HIGH);
}

//Send a command to the display
void Nokia5110::writeCommand(unsigned char command)
{
	digitalWrite(_dc, LOW); //DC pin is low for commands
	digitalWrite(_ce, LOW);
	shiftOut(_din, _clock, MSBFIRST, command); //transmit serial data
	digitalWrite(_ce, HIGH);
}