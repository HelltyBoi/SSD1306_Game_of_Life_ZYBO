

#include<stdio.h>
//#include<time.h>
#include"xil_printf.h"
#include"xparameters.h"
#include"sleep.h"
#include"ssd1306_header.h"
#include"platform.h"

#define SLAVE_ADDR 0x3C
#define BIT_ARRAY 8192
#define BYTE_ARRAY 1024

	u8 byte_array_fin[1024];
	u8 bit_array[10000]={0};
	u8 bit_array_corrected[10000]={0};
	u8 bit_array_aux[10000]={0};

int main (void){

	init_platform();

	InitIIC(XPAR_PS7_I2C_0_DEVICE_ID);




	//clock_t begin=clock();
	//float elapsed,cps;
	unsigned int i=0;
	unsigned int j=0;
	unsigned int k=0;
	unsigned int test=0;
	unsigned int ctr_sum;
	int status;
	int loop;
	XIicPs Iic;

	u8 byte_array[1024]={
			/*0x0C,0x06,0x07,0x1E,0xF8,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xE0,0x60,0x00,0x00,0x00,0x80,0xE0,0x60,0x00,
		0x00,0x00,0x80,0xC0,0x60,0x60,0xC0,0x00,0x00,0x00,0x00,0x80,0xE0,0x60,0x20,0x20,
		0xA0,0xE0,0x60,0x00,0x80,0xE0,0x60,0x20,0x20,0xA0,0xE0,0x60,0x00,0x00,0x20,0xE0,
		0xC0,0x80,0xC0,0x40,0x20,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xF0,0xF8,0x3C,0x0F,0x06,0x0C,0x18,

		0x80,0x80,0x00,0x00,0x00,0x07,0x05,0x04,0x06,0x06,0x06,0x06,0x06,0x66,0xFE,0xBC,
		0x8C,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x04,0x07,0x03,0x01,0x01,0x01,0x05,0x07,0x03,0x00,0x04,
		0x06,0x03,0x01,0x01,0x01,0x01,0x07,0x06,0x00,0x00,0x04,0x07,0x03,0x01,0x01,0x01,
		0x01,0x01,0x00,0x04,0x07,0x03,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x04,
		0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xFE,
		0xF6,0x66,0x06,0x06,0x06,0x06,0x04,0x04,0x03,0x0F,0x00,0x00,0x40,0x00,0x80,0xA0,

		0x1F,0x1F,0xCC,0x00,0x03,0x11,0x10,0x00,0x00,0x40,0xE0,0x20,0x30,0x38,0x18,0x0F,
		0x0F,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xF0,0xB0,0x90,0x90,0x90,0xD0,
		0x70,0x30,0x00,0x00,0xC0,0xF0,0x30,0x00,0x00,0x00,0xC0,0xF0,0xB0,0x90,0x90,0x90,
		0xD0,0xF0,0x30,0x00,0x10,0x10,0xD0,0xF0,0x30,0x10,0x10,0x10,0x00,0x00,0xC0,0xF0,
		0xB0,0x80,0x80,0x80,0xC0,0xF0,0x30,0x00,0x00,0x00,0xC0,0xF0,0x30,0x10,0x10,0x10,
		0x10,0xF0,0xF0,0x00,0x80,0xC0,0xE0,0x70,0xF0,0xF0,0x00,0x00,0x00,0x00,0x10,0x70,
		0xF0,0xC0,0x60,0x30,0x10,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x1C,
		0x3C,0x38,0x30,0x20,0x60,0xC0,0x40,0x00,0x00,0x20,0x02,0x12,0x50,0x1F,0x1F,0x3F,

		0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,0xC0,0x87,0xFF,0xFC,0xF0,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x03,0x03,0x02,0x02,0x02,0x02,0x03,
		0x01,0x00,0x00,0x02,0x03,0x01,0x00,0x00,0x00,0x02,0x03,0x01,0x00,0x01,0x03,0x03,
		0x02,0x02,0x00,0x00,0x00,0x02,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x02,0x03,0x01,
		0x00,0x00,0x00,0x02,0x03,0x01,0x00,0x00,0x00,0x02,0x03,0x03,0x02,0x02,0x02,0x02,
		0x03,0x01,0x02,0x03,0x03,0x01,0x01,0x01,0x03,0x03,0x03,0x00,0x00,0x00,0x00,0x02,
		0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0xF0,0xF8,0xFC,0x87,0x83,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xE0,0x70,

		0x01,0x03,0x03,0x04,0x0C,0x04,0x04,0x07,0x07,0x01,0x03,0x03,0x03,0x03,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0x10,0x00,0x00,0x00,0x00,
		0xC0,0xC0,0xD0,0xB0,0x70,0x60,0x60,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0xC0,
		0xC0,0xC0,0xC0,0xE0,0xE0,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x80,0xE0,0xE0,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0xC0,0xF0,0xF0,0x60,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x03,0x03,0x03,0x03,0x03,0x1F,0x0C,0x0C,0x04,0x06,0x02,0x03,0x01,0x00,0x00,

		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x80,0x80,0xC0,0xF0,0xFF,0x7F,0x7F,0x30,0x30,0x38,0x38,0x18,0x18,
		0x1C,0x1C,0x01,0x01,0x00,0x00,0x00,0x80,0x80,0xC0,0xC0,0x60,0xE1,0xE1,0xF1,0x78,
		0x7C,0x6F,0xE7,0xC3,0xC0,0xC0,0xE0,0xFC,0xFE,0x0E,0x02,0x00,0x00,0x00,0x00,0x00,
		0xC0,0xF8,0xFE,0x3F,0x0F,0x01,0x00,0x00,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
		0x03,0x03,0x03,0x03,0x03,0x00,0x00,0x00,0x00,0x0C,0x0C,0xCC,0xEC,0xFC,0x7C,0x1F,
		0x0F,0x0F,0xCC,0xFC,0xFC,0x3C,0x00,0x02,0x0F,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,
		0x7E,0xFF,0xE7,0xC3,0xC1,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0x40,0x00,0x00,
		0x00,0x00,0x00,0x00,0x18,0x3E,0x3F,0x37,0x31,0x38,0x1E,0x0F,0x07,0x01,0x00,0x80,
		0xC0,0xE0,0x70,0x3C,0x1E,0x0F,0x07,0x03,0x03,0x07,0x07,0x02,0x00,0x80,0xF0,0xFE,
		0x7F,0x0F,0x01,0x00,0x00,0x08,0x0C,0x1C,0x1C,0x38,0x38,0x30,0x30,0x30,0x30,0x30,
		0x30,0x30,0x00,0x00,0x00,0x40,0xE0,0xF0,0x78,0x1E,0x0F,0x67,0x71,0x70,0x60,0x60,
		0x78,0x3E,0x1F,0x07,0x01,0x00,0x00,0x00,0x00,0x03,0x03,0x03,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00

			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x20,0xE0,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x2D,0xED,0x2D,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00


		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x0A,
		0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00*/

			/*0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x28,0x04,0x44,0x04,0x24,0x1C,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x08,0x08,0x18,0x00,0xB3,0xAA,0x18,0x00,0x18,0xAA,0xB3,0x00,0x18,
			0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x02,0x02,0x03,0x00,0x39,0x0A,0x03,0x00,0x03,0x0A,0x39,0x00,0x03,
			0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00*/

			0x38,0x18,0x18,0x88,0x84,0x84,0xC6,0xC6,0x46,0x62,0xA1,0xA1,0x71,0x71,0x79,0x39,
			0x39,0x39,0x39,0x3C,0x1C,0x9E,0x9E,0xCE,0xCE,0xC6,0xE6,0xE6,0xF7,0xF7,0xF7,0xFF,
			0xFF,0xFF,0xFB,0xFB,0xFB,0xFB,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
			0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
			0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
			0xFF,0xBF,0xBF,0xBF,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
			0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xFE,0xFE,
			0xFF,0xFD,0xF9,0xF9,0xF9,0xFB,0xFF,0xFF,0xF7,0xF7,0xE7,0xEF,0xEF,0xDF,0xDF,0xDF,

			0x0E,0x07,0x07,0x81,0xC1,0xC2,0x43,0x61,0x31,0xB0,0xF8,0xF8,0xFC,0xFC,0x7C,0x7E,
			0x3E,0xBF,0x7F,0x3F,0x3F,0x3F,0xBF,0xDF,0xDF,0xCF,0xCF,0xEF,0x7F,0x7F,0xBF,0xFF,
			0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0xBF,0xFF,0xFF,0xDF,0xEF,0xFF,0x7F,
			0x7F,0xBF,0xBF,0xBF,0x7F,0x7F,0x3F,0x3F,0x2F,0x3F,0x3F,0x3F,0x1F,0x1F,0x1F,0x1F,
			0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x17,0x07,0x07,0x07,0x07,0x0F,0x0F,0x0F,0x1F,0x1F,
			0x1F,0x3F,0x2F,0x2F,0x2F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x1D,0x1F,0x7F,0x7F,
			0xFF,0xFF,0x7B,0x7B,0x7B,0x7F,0x7F,0xF7,0xF7,0xFF,0xFF,0xFF,0xFF,0xEF,0xEF,0xDF,
			0xDF,0xFF,0xBF,0xBF,0xFF,0xFF,0x7F,0x7F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,

			0x46,0x22,0x33,0x19,0x19,0x0C,0x06,0x86,0x83,0x43,0x61,0x61,0x21,0x10,0x18,0x98,
			0x99,0xCC,0xC6,0x66,0x66,0x73,0x33,0x9B,0xD9,0xED,0xED,0xE6,0xFE,0xFB,0xBD,0xDF,
			0xEF,0xEF,0xF7,0xFB,0x59,0xDD,0xEF,0xE6,0xE6,0xC7,0x03,0x83,0x83,0x01,0x01,0x21,
			0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x01,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
			0x07,0x07,0x07,0x0F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,

			0x00,0x10,0x00,0x84,0xC6,0xC2,0x60,0x21,0x30,0x30,0x98,0x88,0x4E,0x46,0x23,0x33,
			0x31,0x19,0x99,0xCE,0xCE,0xDE,0xF7,0xFB,0xFF,0xFF,0xF7,0xFE,0xFF,0xFF,0xFF,0x3F,
			0x7F,0x03,0x01,0x00,0x00,0x07,0x9D,0xEF,0xBF,0xFF,0xFF,0xEF,0xFF,0xFE,0xFE,0xFE,
			0xFC,0xD8,0x30,0x38,0xF0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x1E,0x38,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,

			0x04,0x03,0x01,0x80,0x80,0xC0,0xE0,0xF0,0xF0,0xF0,0xF8,0xFC,0xFC,0xFC,0xFE,0xFE,
			0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x4F,0x7F,0x88,0x02,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x0F,0x7B,0x9F,0xFF,0xF3,0xF3,0xB7,
			0x1F,0x0F,0x00,0x00,0x00,0x00,0x0F,0x1F,0xF0,0xE8,0x20,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x7E,0xF0,0x00,0x00,0x00,0x00,0x00,0x06,0x1F,0xFE,0xFC,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x80,0xC0,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,

			0xF8,0x7E,0x7F,0xDF,0xFF,0xEF,0xF7,0xFF,0x7D,0xFF,0xBF,0x9F,0xFF,0xEF,0xF7,0xF7,
			0xFF,0xFD,0xFF,0xFD,0x7F,0x7F,0x7F,0x1F,0x17,0x05,0x07,0x01,0x00,0x00,0x07,0x1C,
			0x70,0xE0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x06,0x0B,0x1F,
			0x1E,0x7E,0x78,0xF8,0xF0,0xF0,0xF0,0xF8,0xFF,0xFF,0xEF,0xCF,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x0F,0xFE,0xF8,0x00,0x00,0x00,0x60,0x70,0x0F,0x0F,0x00,0x00,0x00,0x00,0x00,
			0x00,0x80,0xF0,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,

			0xFF,0x3F,0x9F,0xEF,0xE7,0xF3,0xF9,0xFE,0xFF,0x7F,0xBF,0x7F,0x3F,0x1F,0x0F,0x07,
			0x07,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x03,0x07,0x0C,0x1C,0x3C,0xF0,0xF0,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x03,0x00,0x00,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x00,0xFC,0xFE,0x00,0x00,0x00,0x00,
			0x00,0x00,0x7F,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,0xF8,
			0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,

			0xFC,0x7F,0x3F,0x13,0x0B,0x07,0x01,0x02,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x03,0x03,0x0F,0x1C,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x1C,0x07,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xF0,0xFC,0xFF,0xFF,0xFF,0xFF,
			0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
};

	InitSSD1306();

	while(1){

	for(i=0; i<(sizeof(byte_array)/sizeof(byte_array[0])); i++){//this section turns bytes into a bit velues
		for(j=0; j<8; ++j){
			bit_array[i*8+j]=((byte_array[i]<<j)&(128))/128;
		}
	}

	//ggram correction eg. this section flipps ssd1306 bitmapped data to a monocrome128x64
	//8 pages // 128 segments // 8 pixs in each segment
	// to check if your data rearangment works correctly bit_array_corrected[i*8*128+k*128+j]=test++;
	test=0;
	for(i=0; i<8; i++){
		for(j=0; j<128; j++){
			for(k=0; k<8; k++){
				bit_array_corrected[i*8*128+(7-k)*128+j]=bit_array[test++];
			}
		}
	}

	for(i=0; i<64; i++){//this section calculates neighbo	 	r cells for individual cell
		for(j=0; j<128; j++){

			ctr_sum=bit_array_corrected[((i+1)%64)*128+(j)%128]+
			bit_array_corrected[((i-1)%64)*128+(j)%128]+
			bit_array_corrected[((i)%64)*128+(j+1)%128]+
			bit_array_corrected[((i)%64)*128+(j-1)%128]+
			bit_array_corrected[((i+1)%64)*128+(j+1)%128]+
			bit_array_corrected[((i+1)%64)*128+(j-1)%128]+
			bit_array_corrected[((i-1)%64)*128+(j-1)%128]+
			bit_array_corrected[((i-1)%64)*128+(j+1)%128];

			if((bit_array_corrected[i*128+j]==1)&&((1<ctr_sum)&&(ctr_sum<4)))
				bit_array_aux[i*128+j]=1;
			else if((bit_array_corrected[i*128+j]==0)&&(ctr_sum==3))
				bit_array_aux[i*128+j]=1;
			else
				bit_array_aux[i*128+j]=0;

			/*if((bit_array_corrected[i*128+j]==1)&&(ctr_sum<2))
				bit_array_aux[i*128+j]=0;
			else if((bit_array_corrected[i*128+j]==1)&&(ctr_sum==2)&&(ctr_sum==3))
				bit_array_aux[i*128+j]=1;
			else if((bit_array_corrected[i*128+j]==1)&&(ctr_sum>3))
				bit_array_aux[i*128+j]=0;
			else if((bit_array_corrected[i*128+j]==0)&&(ctr_sum==3))
				bit_array_aux[i*128+j]=1;*/

		}
	}

	//this section flips monocrpme128x64 array to ssd1306 array
	test=0;
	for(i=0; i<8; i++){
		for(j=0; j<128; j++){
			for(k=0; k<8; k++){
				bit_array[test++]=bit_array_aux[i*8*128+(7-k)*128+j];
			}
		}
	}

	//this section turns bites into a byte velues
	for(i=0; i<(sizeof(bit_array)/sizeof(bit_array[0]))/8; ++i){
		for(j=0; j<8; ++j){
			byte_array_fin[i]=(byte_array_fin[i] + (bit_array[i*8+7-j]<<j));
		}
	}

/*	xil_printf("\n\r\n\r\n\r");
	for(i=0; i<(BYTE_ARRAY);i++){
		if(i%16==0&&(i>0)){
		xil_printf("\n\r");}
		xil_printf("%x ", byte_array_fin[i]);
	}*/
	usleep(100000);
	Draw128x64(byte_array_fin);

	for(i=0; i<sizeof(byte_array)/sizeof(byte_array[0]); i++){
		byte_array[i]=byte_array_fin[i];
		byte_array_fin[i]=0;
	}

/*
	//for(i=0;i<8192;i++) bit_array[i]=0;
	for(i=0; i<(BYTE_ARRAY); i++){//this section turns bytes into a bit velues
		for(j=0; j<8; ++j){
			bit_array[i*8+j]=((byte_array[i]<<j)&(128))/128;
		}
		// xil_printf("\n\r");
	}

	//ggram correction eg. this section flips ssd1306 bitmaped data to a monocrome128x64
	//8 pages // 128 segments // 8 pixs in each segment
	// to check if your data rearengment works correctly bit_array_corrected[i*8*128+k*128+j]=test++;
	for(i=0; i<8; i++){
		for(j=0; j<128; j++){
			for(k=0; k<8; k++){
				bit_array_corrected[i*8*128+(8-k)*128+j]=bit_array[test++];
			}
		}
	}

		xil_printf("\n\r\n\r\n\r");
	for(i=0; i<(BIT_ARRAY);i++){
		if(i%128==0&&(i>0)){
		xil_printf("\n\r");}
		xil_printf("%d", bit_array_corrected[i]);
	}

	for(i=0; i<64; i++){
		for(j=0; j<128; j++){

			ctr_sum=bit_array_corrected[((i+1)%64)*128+(j)%128]+
			bit_array_corrected[((i-1)%64)*128+(j)%128]+
			bit_array_corrected[((i)%64)*128+(j+1)%128]+
			bit_array_corrected[((i)%64)*128+(j-1)%128]+
			bit_array_corrected[((i+1)%64)*128+(j+1)%128]+
			bit_array_corrected[((i+1)%64)*128+(j-1)%128]+
			bit_array_corrected[((i-1)%64)*128+(j-1)%128]+
			bit_array_corrected[((i-1)%64)*128+(j+1)%128];

			if((bit_array_corrected[i*128+j]==1)&&((4>ctr_sum)&&(ctr_sum>1)))
				bit_array_aux[i*128+j]=1;
			else if((bit_array_corrected[i*128+j]==0)&&(ctr_sum==3))
				bit_array_aux[i*128+j]=1;
			else
				bit_array_aux[i*128+j]=0;

		}
		//xil_printf("\n\r");
	}

	//this section flips monocrpme128x64 array to ssd1306 array
	test=0;
	for(i=0; i<8; i++){
		for(j=0; j<128; j++){
			for(k=0; k<8; k++){
				bit_array[test++]=bit_array_aux[i*8*128+(8-k)*128+j];
			}
		}
	}

 		xil_printf("\n\r\n\r\n\r");
	for(i=0; i<(BIT_ARRAY);i++){
		if(i%128==0&&(i>0)){
		xil_printf("\n\r");}
		xil_printf("%d", bit_array[i]);
	}

	//this section turns bites into a byte values
	for(i=0; i<(BIT_ARRAY)/8; ++i){
		for(j=0; j<8; ++j){
			byte_array_fin[i]=(byte_array_fin[i] + (bit_array[i*8+7-j]<<j));
		}
	}

	status=Draw128x64(&byte_array_fin[0]);
	if(status==XST_SUCCESS)
		//xil_printf("success Draw128x64");

	xil_printf("\n\r\n\r\n\r");
	for(i=0; i<(BYTE_ARRAY);i++){
		if(i%16==0&&(i>0)){
		xil_printf("\n\r");}
		xil_printf("%x ", byte_array_fin[i]);
	}

	xil_printf("fin\n\r");


    */
	}
	cleanup_platform();
return 0;
}
