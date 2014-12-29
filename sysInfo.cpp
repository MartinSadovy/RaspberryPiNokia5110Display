/*
sys-info
1.0

A simple program to display CPU usage, RAM usage, uptime, and IP Address
on a Nokia 5110 display. A compatible board for Raspberry Pi can be
found on Amazon.

Wesley Carlsen
12-28-14
*/

#include <iostream>
#include <ctime>
#include <wiringPi.h>
#include "nokia5110.h"

using namespace std;

#define reset 4
#define ce 3
#define dc 2
#define din 1
#define sclock 0

#define contrast 60 //normal is 30-90, default is 45

int main()
{
	if (wiringPiSetup() == -1)
	{
		cout << "wiringPi Error" << endl;
		return 1;
	}
	
	Nokia5110 display(reset, ce, dc, din, sclock, contrast);
	display.clear();
	
	int x = 0;
	
	while(true)
	{
		cout << x << endl;
		display.showProgress(1, x);
		delay(100);
		
		x++;
		if(x > 100) x = 0;
	}
	
	return 0;
}