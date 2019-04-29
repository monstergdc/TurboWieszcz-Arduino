
#ifndef TW2_H
#define TW2_H

#include "Arduino.h"
#include "Nokia_lcd_gdc.h"

#define DEFAULT_ZWR 4
#define MAX_ZWR 32
#define CRLF "\n"


class tw2
{
public:
  enum RhymeMode {
    ABAB = 0,
    ABBA = 1,
    AABB = 2
  };

private:
  byte count;
  byte title_id;
  RhymeMode mode;
  bool powtorzeniaOk;

  byte numer[4][MAX_ZWR];
  //byte ending[2][MAX_ZWR];

  //void Koniec(byte z, byte w);
  void Wers(byte z, byte w, byte w0);
  void Zwrotka(byte z);
  bool CheckUniqOK(byte z, byte w, byte value);
  void Setrndrow(byte z, byte w);

public:
  tw2();
  Nokia_lcd_gdc *lcd; //note: will crash if NULL
  void DecCount(bool cycle=false);
  void IncCount(bool cycle=false);
  void SetCount(int pcount);
  byte GetCount() {return count;}
  void SetMode(RhymeMode pmode);
  RhymeMode GetMode(void) {return mode;}
  void SetPowt(bool ppowt);
  void SwitchPowt();
  bool GetPowt() {return powtorzeniaOk;}
  void Generate(void);
  void ShowOne(byte n);
};

#endif

