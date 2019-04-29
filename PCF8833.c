/* PCF8833.c  -- c program for NOkia 6610 (Philips) LCD */
/* most of the source code are extracted from James Lynch's LCD application note */

#include <avr/io.h>
#include "Arduino.h"
#include "PCF8833.h"
#include "vox-font.bin.h"


void SendLcd_color(unsigned char color)
{
  LCD_DATA(LCDData);                     // set up first bit as command or data
  LCD_CLK(0);							// Pull Clock LOW
  LCD_CLK(1);							// Pull Clock HIGH
  LCD_CLK(0);
  SPCR |= 0x50;						// Enable Hardware SPI
  SPSR |= 0x1;
  SPDR = color; 						// send data
  while (!(SPSR & 0x80)) ;				// wait until send complete
  // disable device CS
  SPCR &= ~0x50;						// Disable Hardware SPI, this releases the SPI pins
  LCD_CLK(0);										// for general IO use. which is used to send the 1'st bit out
}

void SendLcd(unsigned char type, unsigned char dat)
{
  byte i;

  LCD_DATA(type);         // set up first bit as command or data
  LCD_CS(0);							// Enable device CS
  LCD_CLK(0);							// Pull Clock LOW
  LCD_CLK(1);							// Pull Clock HIGH

/* test: on my board works w/o this
  if (dat == 0x0) {      // spi cannot transfer zero??
    LCD_DATA(0);
    for (i = 0; i < 8; i++) {
      LCD_CLK(0);							// Pull Clock LOW
      LCD_CLK(1);
    }
  }
  else {
*/
    SPCR |= 0x50;						// Enable Hardware SPI
    SPSR |= 0x1;
    SPDR = dat; 						// send data
    while (!(SPSR & 0x80));				// wait until send complete
/* test
  }
*/
  SPCR &= ~0x50;						// Disable Hardware SPI, this releases the SPI pins
  // for general IO use. which is used to send the 1'st bit out
  LCD_CS(1);							// disable device CS
}


void LCD_Init(void)
{
  LCD_CS(1);
  LCD_CLK(0);
  LCD_DATA(0);

  LCD_RESET(1);
  delay(50);
  LCD_RESET(0);
  delay(50);
  LCD_RESET(1);
  delay(50);

  LCD_CS(1);
  LCD_CLK(1);
  LCD_DATA(1);
  delay(10);

  SendLcd(LCDCommand, SWRESET);
  delay(10);
  SendLcd(LCDCommand, SLEEPOUT); // Sleepout
  SendLcd(LCDCommand, NORON);    // Invert display mode
  SendLcd(LCDCommand, BSTRON);   // BoostON
  SendLcd(LCDCommand, MADCTL);   // memory access control - odwrocenie, zostawic to
  SendLcd(LCDData, 0x50);        // Nowy LCD
  SendLcd(LCDCommand, SETCON);   // Set Contrast
  //? SendLcd(LCDData, 0x3a);
  SendLcd(LCDData, 0x2a); //moze za duzo, chyba, ze txt i easy gfx
  delay(10);
  SendLcd(LCDCommand, DISPON); // Display On
  SendLcd(LCDCommand, COLMOD); // Set Color Mode
  SendLcd(LCDData, 0x03);			 // 12bit per pixel
  SendLcd(LCDCommand, NOP);    // Set Color Mode (?)
}

//  *****************************************************************************************
//  Draws a rectangle in the specified color from (x1,y1) to (x2,y2), filled with color ONLY
//
// In:  x     = row address (0 .. 131)
//      y     = column address  (0 .. 131)
//      color = 12-bit color value (rrrrggggbbbb)
// (...)
//    (ORIG) Author:  James P Lynch      July 7, 2007
//  *****************************************************************************************

void LCD_Box(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, int color)
{
  unsigned char xmin, xmax, ymin, ymax;
  int i, n;

    //best way to create a filled rectangle is to define a drawing box and loop two pixels at a time
    //calculate the min and max for x and y directions
    xmin = (x0 <= x1) ? x0 : x1;
    xmax = (x0 > x1) ? x0 : x1;
    ymin = (y0 <= y1) ? y0 : y1;
    ymax = (y0 > y1) ? y0 : y1;

    //specify the controller drawing box according to those limits
    SendLcd(LCDCommand, PASET);   // Row address set (command 0x2B)
    SendLcd(LCDData, xmin);
    SendLcd(LCDData, xmax);
    SendLcd(LCDCommand, CASET);   // Column address set (command 0x2A)
    SendLcd(LCDData, ymin);
    SendLcd(LCDData, ymax);
    SendLcd(LCDCommand, RAMWR);   // WRITE MEMORY
    //loop on total number of pixels / 2
    n = ((((xmax - xmin + 1) * (ymax - ymin + 1)) / 2 ) + 1 );
    for (i = 0; i < n; i++)
    {
      //output 3 data bytes covering two pixels
      LCD_CS(0);
      SendLcd_color((color >> 4) & 0xFF );
      SendLcd_color(((color & 0xF) << 4) | ((color >> 8) & 0xF) );
      SendLcd_color(color & 0xFF);
      LCD_CS(1);
    }
    SendLcd(LCDCommand, NOP);
}

void LCD_Bitmap1(unsigned char start_x, unsigned char start_y, unsigned char h_size, unsigned char v_size, unsigned char *bitmap_data)
{
  int i, n;
  unsigned char *pBitmap;
  unsigned char bitmap, c1, c2, c3, j;

  // specify the controller drawing box according to those limits
  SendLcd(LCDCommand, PASET);  // Row address set (command 0x2B)
  SendLcd(LCDData, start_x);
  SendLcd(LCDData, start_x + h_size - 1);
  SendLcd(LCDCommand, CASET);  // Column address set (command 0x2A)
  SendLcd(LCDData, start_y);
  SendLcd(LCDData, start_y + v_size - 1);

  SendLcd(LCDCommand, RAMWR);  // WRITE MEMORY
  pBitmap = bitmap_data;

  n = (h_size*v_size) / 8;
  for (i = 0; i < n; i++)
  {
    LCD_CS(0);
    bitmap = pgm_read_byte(pBitmap++);
    for (j = 0; j < 4; j++)
    {
      c2 = 0;
      if (bitmap & 0x80) {c1 = 0xff; c2 |= 0xf0;} else c1 = 0;
      if (bitmap & 0x40) {c3 = 0xff; c2 |= 0x0f;} else c3 = 0;
      SendLcd_color(c1 ^ 0xff);
      SendLcd_color(c2 ^ 0xff);
      SendLcd_color(c3 ^ 0xff);
      bitmap = bitmap << 2;
    }
    LCD_CS(1);
  }
  SendLcd(LCDCommand, NOP);
}

//helper
void LCD_Send2PixelsIn3Bytes(unsigned int Word0, unsigned int Word1)
{
  SendLcd_color((Word0>>4)&255);
  SendLcd_color(((Word0&15)<<4)|((Word1>>8)&15));
  SendLcd_color(Word1&255);
}

void LCD_Char(char c, unsigned char x, unsigned char y, int fColor, int bColor)
{
  byte i, j, PixelRow;
  //unsigned int Word0, Word1;
  unsigned char *pChar;

  pChar = (unsigned char *)FONT8x8 + (8 * (c - 0x1F-1));  //pointer to the last byte of the character

  for (i = 0; i < 8; i++) {
    PixelRow = pgm_read_byte(pChar++);

    SendLcd(LCDCommand, PASET);                           // page start/end ram
    SendLcd(LCDData, y);                                  // Start Page to display to
    SendLcd(LCDData, y+7);                                // End Page to display to
    SendLcd(LCDCommand, CASET);                           // column start/end ram
    SendLcd(LCDData, x+i);                                // Start Column to display to
    SendLcd(LCDData, x+i);                                // End Column to display to

    SendLcd(LCDCommand, RAMWR);
    LCD_CS(0);
      LCD_Send2PixelsIn3Bytes(((PixelRow & 0x80) == 0)?bColor:fColor, ((PixelRow & 0x40) == 0)?bColor:fColor);
      LCD_Send2PixelsIn3Bytes(((PixelRow & 0x20) == 0)?bColor:fColor, ((PixelRow & 0x10) == 0)?bColor:fColor);
      LCD_Send2PixelsIn3Bytes(((PixelRow & 0x08) == 0)?bColor:fColor, ((PixelRow & 0x04) == 0)?bColor:fColor);
      LCD_Send2PixelsIn3Bytes(((PixelRow & 0x02) == 0)?bColor:fColor, ((PixelRow & 0x01) == 0)?bColor:fColor);
    /*
      Word0 = ((PixelRow & 0x80) == 0)?bColor:fColor;
      Word1 = ((PixelRow & 0x40) == 0)?bColor:fColor;
      LCD_Send2PixelsIn3Bytes(Word0, Word1);
      Word0 = ((PixelRow & 0x20) == 0)?bColor:fColor;
      Word1 = ((PixelRow & 0x10) == 0)?bColor:fColor;
      LCD_Send2PixelsIn3Bytes(Word0, Word1);
      Word0 = ((PixelRow & 0x08) == 0)?bColor:fColor;
      Word1 = ((PixelRow & 0x04) == 0)?bColor:fColor;
      LCD_Send2PixelsIn3Bytes(Word0, Word1);
      Word0 = ((PixelRow & 0x02) == 0)?bColor:fColor;
      Word1 = ((PixelRow & 0x01) == 0)?bColor:fColor;
      LCD_Send2PixelsIn3Bytes(Word0, Word1);
    */
    LCD_CS(1);
    SendLcd(LCDCommand, NOP);
  }
}

