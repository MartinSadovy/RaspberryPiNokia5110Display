#include "nokia5110.h"
#include <wiringPi.h>
#include <wiringShift.h>
#include <iostream>
 
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

	width = 84;
	height = 48;
	_buffer = new unsigned char[width*height/8];
	for (unsigned int i = 0; i < width * height / 8; i++) _buffer[i] = 0x00;

	
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
 
unsigned int Nokia5110::getBufferBit(unsigned char x, unsigned char y)
{
	unsigned int r = y / 8;
	char c = _buffer[r*width+x];
	return (c >> (y%8)) & 1;
}

void Nokia5110::setBufferBit(unsigned char x, unsigned char y, unsigned int bit)
{
	unsigned int r = y / 8;
	if (bit == 0) {
		_buffer[r*width+x] &= ~(1 << (y%8));
	} else { // 1 or more
		_buffer[r*width+x] |= (1 << (y%8));
	}
}

void Nokia5110::setBufferBlock(unsigned char x, unsigned char y, unsigned char bitBlock)
{
	_buffer[y*width+x] = bitBlock;
}

void Nokia5110::printBuffer()
{
	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width; j++)
			std::cout << (getBufferBit(j, i) ? 'X' : ' ');
		std::cout << "|\n";
	}
}

//Turn on all of the pixels at once
void Nokia5110::fill()
{
	for (unsigned int i = 0; i < width * height / 8; i++)
	{
		writeData(0xff);
	}
	for (unsigned int i = 0; i < width * height / 8; i++) _buffer[i] = 0xff;
}

void Nokia5110::clear()
{
    for (unsigned int i = 0; i < width * height / 8; i++)
	{
		writeData(0x00);
	}
	for (unsigned int i = 0; i < width * height / 8; i++) _buffer[i] = 0x00;
}

void Nokia5110::showProgress(unsigned char position, unsigned char percentage)
{
	unsigned int cursor = width * (percentage / 100.0);
	setCursor(0, position);
	
	for (unsigned int i = 0; i < width; i++)
	{
		if(i < cursor) {
			setBufferBlock(i, position, 0xff);
			writeData(0xff);
		} else {
			setBufferBlock(i, position, 0x00);
			writeData(0x00);
		}
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