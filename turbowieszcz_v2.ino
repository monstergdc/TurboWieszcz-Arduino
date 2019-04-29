
//  TurboWieszcz++ v2.0 / Arduino port
//  (c)2018 Noniewicz.com, Jakub Noniewicz aka MoNsTeR/GDC

//  TurboWieszcz++ / Arduino is free software: you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public License
//  as published by the Free Software Foundation, either version 3 of
//  the License, or (at your option) any later version.
//
//  TurboWieszcz++ / Arduino is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.


//created: 20180106
//updates:
//20180106 2200-2300
//20180106 2330-0000
//20180107 0000-0100
//20180107 1350-1600
//20180107 1615-1925
//20180107 2040-2125
//20180107 2205-2230
//20180107 2300-0000
//20180107 0000-0315  //hardware - RGB
//20180107 0315-0450
//20180107 1520-1720
//20180107 1815-2030
//20180107 2055-2125
//20180107 2155-2310
//20180107 2340-0000
//20180108 0000-0050
//20180108 1520-1610
//20180112 1210-1240
//20180112 1430-1450
//20180114 1555-1625
//20180115 1515-1535
//20180115 1550-1635
//20180116 1805-1825
//20180116 1850-1925
//20180116 2010-2105
//20180116 2130-2220
//20180117 1430-1605
//20180117 1635-1705
//20180117 2055-2110
//20180117 2145-2235
//20180117 2350-0020
//20180118 1500-1520
//20180118 1630-1700
//20180118 1900-1935
//20180119 1550-1605
//20180120 1510-1540
//20180120 1610-1635
//---
//20180409 ????-????
//20180411 1835-1900


//note: LCD shield used: ArdGraph132
//note: usable display is 128x128, but to clear 132x132 is required
//note: no PINs for full RGB LED

/* todo:
# MAIN:
- ALL SEEMS DONE!
# LATER:
- entery miedzy wersami zle czasem (fix maybe?)
.- code cleanup / revision / kod lcd czysto
- open source?
*/

//compile with optional RGB LED for effects
#define USE_RGB_LED

#include "arduino.h"
#include "Nokia_lcd_gdc.h"
#include <avr/pgmspace.h>
#include "turbowieszcz_v2.h"
#include "mickiewicz.h"
#include "tw2.h"

//?
#define BL_PIN 3

//keypad debounce parameter
#define DEBOUNCE_MAX 15
#define DEBOUNCE_ON  10
#define DEBOUNCE_OFF 3

#define NUM_KEYS 5
//joystick number
#define UP_KEY 1
#define LEFT_KEY 2
#define CENTER_KEY 4
#define DOWN_KEY 3
#define RIGHT_KEY 0

//adc preset value, represent top value,incl. noise & margin, that the adc reads, when a key is pressed
//set noise & margin = 30 (0.15V@5V)
int  adc_key_val[NUM_KEYS] = {10, 155, 341, 517, 751};
//      145
//331   741    0
//      507

//debounce counters
byte button_count[NUM_KEYS];
//button status - pressed/released
byte button_status[NUM_KEYS];
//button on flags for user program
byte button_flag[NUM_KEYS];

//menu colors
#define NORMAL_FG_COLOR WHITE
#define NORMAL_BK_COLOR BLUE
#define HIGHLIGHT_FG_COLOR YELLOW
#define HIGHLIGHT_BK_COLOR RED
#define OPT_BK_COLOR RED


void generate(void);
void about(void);
void init_MENU(void);
void showzwr(void);
void setzwr_dec(void);
void setzwr_inc(void);
void setrym(void);
void setpowt(void);


//menu
#define MENU_X 0
#define MENU_Y 97
#define MENU_DY 12
void (*menu_funcs[NUM_MENU_ITEM])(void) = {generate, setzwr_inc, setrym, setpowt, about};  //menu calls
byte menuypos[NUM_MENU_ITEM] = {MENU_Y-MENU_DY*6, MENU_Y-MENU_DY*1, MENU_Y-MENU_DY*0, MENU_Y+MENU_DY*1, MENU_Y+MENU_DY*2};
char current_menu_item;


//--- global objects

Nokia_lcd_gdc lcd = Nokia_lcd_gdc();
tw2 tw = tw2();

//--- RGB LED

#ifdef USE_RGB_LED

int flasher;
byte state;

#define LEDPin 13 //built-in red LED

#define blueLEDPin 5
#define greenLEDPin 6
#define redLEDPin 4 // only 4 avail wtf 3 (used?) //was 9 (can't, used by display) //was 7 (lame)

void setup_rgb()
{
  pinMode(LEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
}

void RGB(unsigned char r, unsigned char g, unsigned char b, int d)
{
  analogWrite(redLEDPin, r);
  analogWrite(greenLEDPin, g);
  analogWrite(blueLEDPin, b);
  delay(d);
}

void _SMDLED(unsigned char r)
{
  analogWrite(LEDPin, r);
}

#endif

//--- tools

//wait for center key press
void waitfor_OKkey()
{
  byte i;
  byte key = 0xFF;
  while (key != CENTER_KEY)
  {
    for (i = 0; i < NUM_KEYS; i++)
    {
      if (button_flag[i] != 0)
      {
        button_flag[i] = 0; // reset button flag
        if (i == CENTER_KEY) key = CENTER_KEY;
      }
    }
  }
}

//wait for any key press
byte waitfor_Anykey()
{
  byte i;
  byte key = 0xFF;
  while (key == 0xFF)
  {
    for (i = 0; i < NUM_KEYS; i++)
    {
      if (button_flag[i] != 0)
      {
        button_flag[i] = 0; // reset button flag
        key = i;
        return key;
      }
    }
  }  
}

#define BUTTON_Y0 (80+32)
#define BUTTON_H 14
#define BUTTON_COLOR BLUE
 
//draw OK button
void putOK(int x0 = 50, int y0 = BUTTON_Y0)
{
  lcd.cLCD_Box(x0, y0, x0+30-4, y0+BUTTON_H, BUTTON_COLOR);
  lcd.printFlash(CASTTEXT(alltxt[TEXT_OK]), x0+6, y0+4, WHITE, BUTTON_COLOR);
}

//draw menu button
void putMENU(int x0 = 2, int y0 = BUTTON_Y0)
{
  lcd.cLCD_Box(x0, y0, x0+50, y0+BUTTON_H, BUTTON_COLOR);
  lcd.printFlash(CASTTEXT(alltxt[TEXT_MENU]), x0+6, y0+4, WHITE, BUTTON_COLOR);
}

//draw next button
void putNEXT(int x0 = 70, int y0 = BUTTON_Y0)
{
  lcd.cLCD_Box(x0, y0, x0+58, y0+BUTTON_H, BUTTON_COLOR);
  lcd.printFlash(CASTTEXT(alltxt[TEXT_NEXT]), x0+6, y0+4, WHITE, BUTTON_COLOR);
}

//draw 'new' button
void putNEW(int x0 = 8, int y0 = BUTTON_Y0)
{
  lcd.cLCD_Box(x0, y0, x0+48, y0+BUTTON_H, BUTTON_COLOR);
  lcd.printFlash(CASTTEXT(alltxt[TEXT_NEW]), x0+6, y0+4, WHITE, BUTTON_COLOR);
}

//clear screen (fill rect)
void cls(int color = BLACK)
{
  lcd.cLCD_Box(0, 0, 131, 131, color);
}

//---

void setup(void) {
  randomSeed(analogRead(2));
#ifdef USE_RGB_LED
  flasher = 0;
  setup_rgb();
  state = 0;
#endif

  tw.lcd = &lcd;  //lcd obj known to tw2 obj

  // setup interrupt-driven keypad arrays, reset button arrays
  for (byte i = 0; i < NUM_KEYS; i++)
  {
    button_count[i] = 0;
    button_status[i] = 0;
    button_flag[i] = 0;
  }

  // Setup timer2 -- Prescaler/256
  TCCR2A &= ~((1 << WGM21) | (1 << WGM20));
  TCCR2B &= ~(1 << WGM22);
  TCCR2B = (1 << CS22) | (1 << CS21);

  ASSR |= (0 << AS2);

  //Use normal mode
  TCCR2A = 0;
  //Timer2 Overflow Interrupt Enable
  TIMSK2 |= (0 << OCIE2A);
  TCNT2 = 0x6; // counting starts from 6
  TIMSK2 = (1 << TOIE2);

  SREG |= 1 << SREG_I;

  DDRB = 0x2F;  //InitPort();

  lcd.cLCD_Init();
  cls();
  digitalWrite(BL_PIN, HIGH);   // turn on backlight
  init_MENU();  //menu initialization
}


void loop(void)
{
  byte i;
#ifdef USE_RGB_LED
  byte n = (flasher >> 3) & 0x1f | 0x02;
  if (flasher & 0x100) RGB(0, 0, n, 0); else RGB(0, n, 0, 0);
  if (flasher & 0x80) _SMDLED(255); else _SMDLED(0);
#endif

  for (i = 0; i < NUM_KEYS; i++)
  {
    if (button_flag[i] != 0)
    {
      button_flag[i] = 0;  //reset button flag
      switch (i)
      {
        case UP_KEY:
          lcd.printFlash(CASTTEXT(menu_items[current_menu_item]), MENU_X, menuypos[current_menu_item], NORMAL_FG_COLOR, NORMAL_BK_COLOR);
          current_menu_item -= 1;
          if (current_menu_item < 0)  current_menu_item = NUM_MENU_ITEM - 1;
          lcd.printFlash(CASTTEXT(menu_items[current_menu_item]), MENU_X, menuypos[current_menu_item], HIGHLIGHT_FG_COLOR, HIGHLIGHT_BK_COLOR);
          break;
        case DOWN_KEY:
          lcd.printFlash(CASTTEXT(menu_items[current_menu_item]), MENU_X, menuypos[current_menu_item], NORMAL_FG_COLOR, NORMAL_BK_COLOR);
          current_menu_item += 1;
          if (current_menu_item > (NUM_MENU_ITEM - 1))  current_menu_item = 0;
          lcd.printFlash(CASTTEXT(menu_items[current_menu_item]), MENU_X, menuypos[current_menu_item], HIGHLIGHT_FG_COLOR, HIGHLIGHT_BK_COLOR);
          break;
        case LEFT_KEY:
          if (current_menu_item == 1)
          {
            setzwr_dec();
          }
          break;
//        case RIGHT_KEY:
//          break;
        case CENTER_KEY:
          if ((current_menu_item == 1) || (current_menu_item == 2) || (current_menu_item == 3))
          {
            (*menu_funcs[current_menu_item])();
            break;
          }
          cls();
          state = 1;
          (*menu_funcs[current_menu_item])();
          state = 0;
          init_MENU();
          break;
      }
    }
  }
}

//---

void showzwr(void)
{
  char buff1[6];  //should be ok, need max 2+1
  sprintf(buff1, "%02d", tw.GetCount());
  lcd.cLCD_String(buff1, MENU_X+8*5, menuypos[1], NORMAL_FG_COLOR, OPT_BK_COLOR);  //note: no printFlash here, from RAM
}

void setzwr_dec(void)
{
  tw.DecCount(true);
  showzwr();
}

void setzwr_inc(void)
{
  tw.IncCount(true);
  showzwr();
}

void showrym(void)
{
  byte tmp = tw.GetMode();
  unsigned char *p = NULL;
  if (tmp == tw2::RhymeMode::ABAB) p = CASTTEXT(alltxt[TEXT_ABAB]);
  if (tmp == tw2::RhymeMode::ABBA) p = CASTTEXT(alltxt[TEXT_ABBA]);
  if (tmp == tw2::RhymeMode::AABB) p = CASTTEXT(alltxt[TEXT_AABB]);
  lcd.printFlash(p, MENU_X+8*5, menuypos[2], NORMAL_FG_COLOR, OPT_BK_COLOR);
}

void setrym(void)
{
  byte tmp = 1+tw.GetMode();
  if (tmp > tw2::RhymeMode::AABB) tmp = tw2::RhymeMode::ABAB;
  tw.SetMode(tmp);
  showrym();
}

void showpowt(void)
{
  unsigned char *p = NULL;
  if (tw.GetPowt())
  {
    p = CASTTEXT(alltxt[TEXT_TAK]);
  }
  else
  {
    p = CASTTEXT(alltxt[TEXT_NIE]);
  }
  lcd.printFlash(p, MENU_X+8*6, menuypos[3], NORMAL_FG_COLOR, OPT_BK_COLOR);
}

void setpowt(void)
{
  tw.SwitchPowt();
  showpowt();
}

//generate new poem
void generate()
{byte key, i;

#ifdef USE_RGB_LED
  RGB(0, 0, 0, 0);
#endif

  //scary backlight + SMD LED flash
  for(i=0;i<3+random(17);i++)
  {
    delay(8+random(80));
    digitalWrite(BL_PIN, LOW);   // turn off backlight
    _SMDLED(0);
#ifdef USE_RGB_LED
    RGB(0, random(255), 0, 0);
#endif
    delay(8+random(250));
    digitalWrite(BL_PIN, HIGH);   // turn on backlight
    _SMDLED(255);
#ifdef USE_RGB_LED
    RGB(0, 0, random(255), 0);
#endif
  }

#ifdef USE_RGB_LED
  RGB(0, 0, 24, 0);
#endif

  do
  {
    tw.Generate();

    for (i=0;i<tw.GetCount();i++)
    {
      tw.ShowOne(i);
      bool islast = (i == tw.GetCount()-1);   //last
    
      if (islast)
      {
        putNEW();
        putOK(80);
      }
      else
      {
        putMENU();
        putNEXT();
      }

      do
      {
        key = waitfor_Anykey();
      }
      while ( !(islast && (key == UP_KEY)) && !(!islast && (key == LEFT_KEY)) && !(key == CENTER_KEY));

      if (islast)
      {
        if (key == UP_KEY) cls();
      }
      else
      {
        if (key == LEFT_KEY) break;
        cls();
      }
    }
  }
  while (key == UP_KEY);
}

byte menu_next_wait()
{
  putMENU();
  putNEXT();
  return waitfor_Anykey();
}

//display about screen(s)
void about() {
  byte key;

#ifdef USE_RGB_LED
  RGB(0, 24, 0, 0);
#endif

  lcd.printFlash(CASTTEXT(alltxt[TEXT_ABOUT1]), 2, 2, WHITE);
  if (menu_next_wait() == LEFT_KEY) return;
  cls();
  lcd.printFlash(CASTTEXT(alltxt[TEXT_ABOUT2]), 2, 2, WHITE);
  if (menu_next_wait() == LEFT_KEY) return;
  cls();
  lcd.printFlash(CASTTEXT(alltxt[TEXT_ABOUT3]), 2, 2, WHITE);
  if (menu_next_wait() == LEFT_KEY) return;
  cls();
  lcd.printFlash(CASTTEXT(alltxt[TEXT_ABOUT4]), 2, 2, WHITE);
  putOK();
  waitfor_OKkey();
}

//
void init_MENU(void) {
#ifdef USE_RGB_LED
  RGB(0, 0, 0, 0);
#endif

  lcd.cLCD_Bitmap1(2, 2, 128, 128, mickiewicz);
  lcd.cLCD_Box(0, 0, 131, 2+8+2, RED);
  lcd.printFlash(CASTTEXT(alltxt[TEXT_APPNAME]), 3, 3, WHITE, RED);

  lcd.printFlash(CASTTEXT(menu_items[0]), MENU_X, menuypos[0], HIGHLIGHT_FG_COLOR, HIGHLIGHT_BK_COLOR);
  for (byte i = 1; i < NUM_MENU_ITEM; i++) {
    lcd.printFlash(CASTTEXT(menu_items[i]), MENU_X, menuypos[i], NORMAL_FG_COLOR, NORMAL_BK_COLOR);
  }
  current_menu_item = 0;
  showzwr();
  showrym();
  showpowt();
}

//--- this part is inherited from example, I have no idea how it does what it does

//The followinging are interrupt-driven keypad reading
//which includes DEBOUNCE ON/OFF mechanism, and continuous pressing detection

//Convert ADC value to key number
char get_key(unsigned int input)
{ char k;

  for (k = 0; k < NUM_KEYS; k++)
  {
    if (input < adc_key_val[k]) return k;
  }
  if (k >= NUM_KEYS) k = -1;  //No valid key pressed
  return k;
}

void update_adc_key()
{ int adc_key_in;
  char key_in;
  byte i;

  adc_key_in = analogRead(0);
  key_in = get_key(adc_key_in);
  for (i = 0; i < NUM_KEYS; i++)
  {
    if (key_in == i)  //one key is pressed
    {
      if (button_count[i] < DEBOUNCE_MAX)
      {
        button_count[i]++;
        if (button_count[i] > DEBOUNCE_ON)
        {
          if (button_status[i] == 0)
          {
            button_flag[i] = 1;
            button_status[i] = 1; //button debounced to 'pressed' status
          }
        }
      }
    }
    else // no button pressed
    {
      if (button_count[i] > 0)
      {
        button_flag[i] = 0;
        button_count[i]--;
        if (button_count[i] < DEBOUNCE_OFF)
        {
          button_status[i] = 0;   //button debounced to 'released' status
        }
      }
    }
  }
}

//Timer2 interrupt routine - 1/(160000000/256/(256-6)) = 4ms interval
ISR(TIMER2_OVF_vect) {
  TCNT2 = 6;
  update_adc_key();
#ifdef USE_RGB_LED
  flasher++;
#endif
}


