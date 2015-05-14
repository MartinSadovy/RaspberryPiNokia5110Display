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


	unsigned char *_buffer; // 84*48/8

	void setCursor(unsigned char x, unsigned char y);
	void writeData(unsigned char data);
	void writeCommand(unsigned char command);


	void setBufferBlock(unsigned char x, unsigned char y, unsigned char bitBlock);
	
	public:
		unsigned int width; // 84
		unsigned int height; // 48

		Nokia5110(unsigned char reset, unsigned char ce, unsigned char dc, unsigned char din, unsigned char clock, unsigned char contrast);	
		void fill();
		void clear();
		void showProgress(unsigned char position, unsigned char percentage);


		unsigned int getBufferBit(unsigned char x, unsigned char y);
		void setBufferBit(unsigned char x, unsigned char y, unsigned int bit);

		void printBuffer();

};
 
#endif