/*
 * SDcardWrite.c

 *
 *  Created on: Dec 9, 2019
 *      Author: 0036472890
 */

#include "ff.h"
#include "xsdps.h"
#include "xparameters.h"
#include "xil_printf.h"

int main(void){


static char File[32]="sekkusu.txt";
static char *SDfile;
FRESULT Res;
static FIL stream;
TCHAR *Path = "0:/";
FATFS fatfs;
char data[51]="sekkusu";
const TCHAR *DataSend;


DataSend=(const TCHAR *)data;
SDfile=(char *)File;

	Res=f_mount(&fatfs, Path, 0);
		if(Res!=FR_OK){
			xil_printf("f_mount failed\n\r");
		}

	Res=f_open(&stream, SDfile, FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
		if(Res){
			xil_printf("f_open failed\n\r");
			//return 0;
			}

	Res=f_printf(&stream, "%s", "sekkusu");
		if(Res){
			xil_printf("f_printf failed\n\r");
			//return 0;
			}

	Res=f_close(&stream);
		if(Res){
			xil_printf("f_close failed\n\r");
			//return 0;
			}

	xil_printf("f_printf executed successfully\n\r\n");

	return 0;}
