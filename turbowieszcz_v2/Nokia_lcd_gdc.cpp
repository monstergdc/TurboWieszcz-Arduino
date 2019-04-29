//wrapper class for PCF8838.c , Nokia 6610 Color LCD (Philips Variant)
//rewritten, optimized and simplified by me

extern "C" {
	#include "PCF8833.h"
//	#include <avr/pgmspace.h>
}
#include "Nokia_lcd_gdc.h"

//delta x or y for one char (pixel size)
#define DXY 8

//Nokia_lcd_gdc::Nokia_lcd_gdc() {}

//init
void Nokia_lcd_gdc::cLCD_Init(void)
{
	LCD_Init();
}

//filled box
void Nokia_lcd_gdc::cLCD_Box(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, int color)
{ 
	LCD_Box(x0, y0, x1, y1, color);
}

//print string
void Nokia_lcd_gdc::cLCD_String(char *pString, unsigned char x, unsigned char y, int fColor, int bColor)
{unsigned char b, x1 = x, y1 = y;
 int fColor1 = fColor;
 const int CLMAP[8] = {BLACK, BLUE, RED, MAGENTA, GREEN, CYAN, YELLOW, WHITE};

  if (!pString) return;

  while (*pString != 0x00)  //loop until null-terminator
  {
    if (y1 > 131)
    {
      break;
    }
    if ((*pString == 0x0a) || (*pString == 0x0d)) //new line
    {
      x1 = 0+2;
      y1 += DXY;
      pString++;
    }
    else if (*pString & 0x80) //color encoded in text
    {
      fColor1 = CLMAP[(*pString) & 0x07];
      pString++;
    }
    else  //actual char
    {
      LCD_Char(*pString++, y1, x1, fColor1, bColor); //draw char
      x1 = x1 + DXY;  //advance y position
      if (x1+DXY > 131) {x1 = 0+2; y1 += DXY;}
    }
    last_x = x1;  //store for continuation
    last_y = y1;
  }
}

//draw BW bitmap
void Nokia_lcd_gdc::cLCD_Bitmap1(unsigned char start_x, unsigned char start_y, unsigned char h_size, unsigned char v_size, unsigned char *bitmap_data)
{
  LCD_Bitmap1(start_x, start_y, h_size, v_size, bitmap_data);
}

//print text from PROGMEM
void Nokia_lcd_gdc::printFlash(const unsigned char *s, unsigned char x, unsigned char y, int fntc, int bkc)
{
#define MAX_BUFF_SIZE (16*16+256)
  char buffer[MAX_BUFF_SIZE];  //should be ok
  strncpy_P(buffer, s, MAX_BUFF_SIZE);
  cLCD_String(buffer, x, y, fntc, bkc);
}

