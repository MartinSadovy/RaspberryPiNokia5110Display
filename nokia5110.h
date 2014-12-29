#ifndef Nokia5110_H
#define Nokia5110_H
 
class Nokia5110
{
	unsigned char _reset;
	unsigned char _ce;
	unsigned char _dc;
	unsigned char _din;
	unsigned char _clock;
	unsigned char _contrast;
	
	void setCursor(unsigned char x, unsigned char y);
	void writeData(unsigned char data);
	void writeCommand(unsigned char command);
	
	public:
		Nokia5110(unsigned char reset, unsigned char ce, unsigned char dc, unsigned char din, unsigned char clock, unsigned char contrast);	
		void fill();
		void clear();
		void showProgress(unsigned char position, unsigned char percentage);
};
 
#endif