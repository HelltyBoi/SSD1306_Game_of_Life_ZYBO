/*
 * ssd1306_heather.h
#
 *
 *  Created on: Dec 5, 2019
 *      Author: 0036472890
 */
#include"xparameters.h"
#include"xiicps.h"

#ifndef SSD1306_HEATHER_H_
#define SSD1306_HEATHER_H_

void writeSSD1306(char *chr);
int InitIIC(u16 DeviceId);
int InitSSD1306(void);
int Draw(u8 DrawBuffer[],u32 DrawBufferSize);
int Draw128x64(u8 *DrawBuffer);

#endif /* SSD1306_HEATHER_H_ */

