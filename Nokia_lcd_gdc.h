/*
	Nokia_lcd_gdc.h
*/

#ifndef NOKIALCDGDC_H
#define NOKIALCDGDC_H

#include <inttypes.h>
#include "Arduino.h"
#include "PCF8833.h"

class Nokia_lcd_gdc
{
  public:
    //Nokia_lcd_gdc();
    byte last_x;
    byte last_y;
    void cLCD_Init(void);
    void cLCD_Box(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, int color);
    void cLCD_String(char *pString, unsigned char  x, unsigned char y, int fColor, int bColor);
    void cLCD_Bitmap1(unsigned char start_x, unsigned char start_y, unsigned char h_size, unsigned char v_size, unsigned char *bitmap_data);
    void printFlash(const unsigned char *s, unsigned char x, unsigned char y, int fntc, int bkc=BLACK);
};	

#endif

