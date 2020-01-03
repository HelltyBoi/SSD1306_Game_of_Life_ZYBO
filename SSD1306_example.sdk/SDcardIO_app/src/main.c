/*
 * main.c
 *
 *  Created on: Dec 13, 2019
 *      Author: 0036472890
 */
#include "ff.h"
#include "xsdps.h"
#include "xparameters.h"
#include "xil_printf.h"
#include "sleep.h"
#include <time.h>
#include <stdio.h>

void f_result(FRESULT Res){
	switch(Res){
		case FR_OK: xil_printf("Success\n\r"); break;
		case FR_DISK_ERR: xil_printf("(1) A hard error occurred in the low level disk I/O layer"); break;
		case FR_INT_ERR: xil_printf("(2) Assertion failed\n\r"); break;
		case FR_NOT_READY: xil_printf("(3) The physical drive cannot work\n\r"); break;
		case FR_NO_FILE: xil_printf("(4) Could not find the file\n\r"); break;
		case FR_NO_PATH: xil_printf("(5) Could not find the path\n\r"); break;
		case FR_INVALID_NAME: xil_printf("(6) The path name format is invalid\n\r"); break;
		case FR_DENIED: xil_printf("(7) Access denied due to prohibited access or directory full\n\r"); break;
		case FR_EXIST: xil_printf("(8) Access denied due to prohibited access\n\r"); break;
		case FR_INVALID_OBJECT: xil_printf("(9) The file/directory object is invalid\n\r"); break;
		case FR_WRITE_PROTECTED: xil_printf("(10) The physical drive is write protected\n\r"); break;
		case FR_INVALID_DRIVE: xil_printf("(11) The logical drive number is invalid\n\r"); break;
		case FR_NOT_ENABLED: xil_printf("(12) The volume has no work area\n\r"); break;
		case FR_NO_FILESYSTEM: xil_printf("(13) There is no valid FAT volume\n\r"); break;
		case FR_MKFS_ABORTED: xil_printf("(14) The f_mkfs() aborted due to any parameter error\n\r"); break;
		case FR_TIMEOUT: xil_printf("(15) Could not get a grant to access the volume within defined period\n\r"); break;
		case FR_LOCKED: xil_printf("(16) The operation is rejected according to the file sharing policy\n\r"); break;
		case FR_NOT_ENOUGH_CORE: xil_printf("(17) LFN working buffer could not be allocated\n\r"); break;
		case FR_TOO_MANY_OPEN_FILES: xil_printf("(18) Number of open files > _FS_SHARE\n\r"); break;
		case FR_INVALID_PARAMETER: xil_printf("(19) Given parameter is invalid\n\r"); break;
		default: xil_printf("Something is really fucked\n\r");
	}
}

int main(void){

static char File[32]="ssd1306.txt";
static char *SDfile;
FRESULT Res;
static FIL stream;
TCHAR *Path = "0:/";
static FATFS fatfs;
char data[1024]="sekkusu2";
const TCHAR *DataSend;
char *percent="%256s";

u8 Wdata[64] __attribute__ ((aligned(32))) ="sekkusu";
u8 Rdata[256*22] __attribute__((aligned(32)));

UINT Nbytes=256*22;
UINT NbytesWritten;

DataSend=(const TCHAR *)data;
SDfile=(char *)File;

	Res=f_mount(&fatfs, Path, 0);
	xil_printf("f_mount: ");
	f_result(Res);

	Res=f_open(&stream, SDfile,  FA_READ );
	xil_printf("f_open: ");
	f_result(Res);

	Res = f_lseek(&stream, 0);
	xil_printf("f_lseek: ");
	f_result(Res);

	/*usleep(100000);
	Res=f_printf(&stream, "%256s", "sekkusu");
	xil_printf("f_printf: ");
	f_result(Res);
	xil_printf("Res:-%d-\n\r", Res);


	Res = f_lseek(&stream, 0);
	xil_printf("f_lseek: ");
	f_result(Res);
	xil_printf("Res:-%d-\n\r", Res);

	Res=f_write(&stream, (const void *)Wdata, Nbytes, &NbytesWritten);
	xil_printf("f_write: ");
	f_result(Res);
	xil_printf("Bytes written: %d\n\r", NbytesWritten);

	Res = f_lseek(&stream, 0);
	xil_printf("f_lseek: ");
	f_result(Res);

	Res= f_read(&stream, (void*)Rdata, Nbytes, &NbytesWritten);
	xil_printf("f_read: ");
	f_result(Res);

	xil_printf("\n\rData read: %s\n\r\n", Rdata);

	Res=f_close(&stream);
	xil_printf("f_close: ");
	f_result(Res);

	xil_printf("\n\r\n");
*/
	int i=0;
	while(1){
		Res= f_read(&stream, (void*)Rdata, Nbytes, &NbytesWritten);
		if(*Rdata=='.') break;
		xil_printf("%c", *Rdata);
		f_lseek(&stream,i++);
	}
	return 0;
}
