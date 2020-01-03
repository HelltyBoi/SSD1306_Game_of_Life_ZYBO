#include<stdio.h>
#include<stdlib.h>
#include"ssd1306_header.h"
#include"xparameters.h"
#include"platform.h"
#include"sleep.h"

#define BIT_ARRAY 8192
#define BYTE_ARRAY 1024



int main(void){

	//u8 bit_array[10000]={0};
	//u8 bit_array_corrected[10000]={0};
	//u8 bit_array_aux[1024]={0};
	u8 *bit_array;
	u8 *bit_array_aux;
	unsigned int i,j,k,test;

	bit_array=(u8*)malloc(8192*sizeof(u8));
	if(bit_array==NULL) xil_printf("allocation of bit_array failed\n\r");
	bit_array_aux=(u8*)malloc(8192*sizeof(u8));
	if(bit_array_aux==NULL) xil_printf("allocation of bit_array_aux failed\n\r");
	u8 byte_array[]={

			0x0C,0x06,0x07,0x1E,0xF8,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
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

	};

	for(i=0; i<BIT_ARRAY; i++){//this section turns bytes into a bit velues
		for(j=0; j<8; ++j){
			bit_array[i*8+j]=((byte_array[i]<<j)&(128))/128;
		}
		// printf("\n");
	}


		printf("\n\n\n");
	for(i=0; i<BIT_ARRAY;i++){
		if(i%128==0&&(i>0)){
		printf("\n");}
		printf("%d", bit_array[i]);
}



	//ggram correction eg. this section flipps ssd1306 bitmapped data to a monocrome128x64
	//8 pages // 128 segments // 8 pixs in each segment
	// to check if your data rearangment works correctly bit_array_corrected[i*8*128+k*128+j]=test++;
/*	for(i=0; i<8; i++){
		for(j=0; j<128; j++){
			for(k=0; k<8; k++){
				bit_array_corrected[i*8*128+(8-k)*128+j]=bit_array[test++];
			}
		}
	}*/



	//int index=0;
	init_platform();

	InitIIC(XPAR_PS7_I2C_0_DEVICE_ID);

	InitSSD1306();

	//Draw(&happybdayHiragana[0], (sizeof(happybdayHiragana)/sizeof(happybdayHiragana[0])));

	Draw128x64(byte_array);

	//writeSSD1306("tinko mandolinko");

	//while(1){
		//for(index=0; index<(sizeof(DrawBuffer)/sizeof(DrawBuffer[0])); index++){
			//Draw(&DrawBuffer[index][0], sizeof(DrawBuffer[index])/sizeof(DrawBuffer[index][0]));
			//usleep(80000);
		//}
	//}

	xil_printf("\n\rfin\n\r");
	free(bit_array_aux);
	free(bit_array);
    cleanup_platform();


	return 0;
}


