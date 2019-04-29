
#include "tw2.h"
#include "turbowieszcz_v2.h"
#include "Nokia_lcd_gdc.h"

extern Nokia_lcd_gdc lcd;



tw2::tw2()
{
  lcd = NULL;
  count = DEFAULT_ZWR;
  mode = ABAB;
  powtorzeniaOk = false;
}

void tw2::DecCount(bool cycle=false)
{
  if (cycle)
  {
    byte tmp = GetCount()-1;
    if (tmp < 1) tmp = MAX_ZWR;
    SetCount(tmp);
  }
  else
  {
    if (count > 1) count--;
  }
}

void tw2::IncCount(bool cycle=false)
{
  if (cycle)
  {
    byte tmp = GetCount()+1;
    if (tmp > MAX_ZWR) tmp = 1;
    SetCount(tmp);
  }
  else
  {
    if (count < MAX_ZWR) count++;
  }
}

void tw2::SetCount(int pcount)
{
  if ((pcount > 0) && (pcount <= MAX_ZWR)) count = pcount;
}

void tw2::SetMode(RhymeMode pmode)
{
  mode = pmode;
}

void tw2::SetPowt(bool ppowt)
{
  powtorzeniaOk = ppowt;
}

void tw2::SwitchPowt()
{
  powtorzeniaOk = !powtorzeniaOk;
}

void tw2::Generate(void)
{byte z, w;

  //if ((count < 1) || (count >= XLIMIT)) return;    //won't happen here really

  for (z = 0; z < count; z++)
    for (w = 0; w <= 3; w++)
      numer[w][z] = -1;

  title_id = (byte)random(TCNT);

/*
  for (z = 0; z < count; z++)
  {
    ending[0][z] = (byte)random(ECNT2);
    ending[1][z] = (byte)random(ECNT1);
  }
*/

  for (z = 0; z < count; z++)
    for (w = 0; w <= 3; w++)
      Setrndrow(z, w);
}

void tw2::ShowOne(byte n)
{
  lcd->printFlash(CASTTEXT(titles[title_id]), 2, 2, YELLOW);  //print title
  lcd->last_y = lcd->last_y+8+2;
  Zwrotka(n); //print poem (one part at once)
}

/*
void tw2::Koniec(byte z, byte w)
{bool chk = true;
 char *p = NULL;

  if ((w == 1) && chk) p = CASTTEXT(ENDINGS2[ending[0][z]]);
  if ((w == 3) && chk) p = CASTTEXT(ENDINGS1[ending[1][z]]);
  if (!p) return;
  lcd->printFlash(p, lcd->last_x, lcd->last_y, WHITE);  //ending
}
*/

void tw2::Wers(byte z, byte w, byte w0)
{byte ndx;
 int c;

  //if ((z < 0) || (z >= count)) return;
  ndx = numer[w][z];
  if (w0&1) c = CYAN; else c = WHITE;
  lcd->printFlash(CASTTEXT(data[w][ndx]), 2, lcd->last_y+8, c);
  //lcd->printFlash(CASTTEXT(data[w][ndx]), 2, 8+8+2+w*(8+2)*2, c);
  //Koniec(z, w0);
}

void tw2::Zwrotka(byte z)
{
  const byte MODE2ORDER[3][4] = {{0, 1, 2, 3}, {0, 1, 3, 2}, {0, 2, 1, 3}};  //ABAB, ABBA, AABB
  byte w, m2o;

  //if ((z < 0) || (z >= count)) return;
  for (w = 0; w <= 3; w++)
  {
    m2o = MODE2ORDER[mode][w]; //tu cos? mode ok wiec wtf?
    Wers(z, m2o, w);
  }
}

bool tw2::CheckUniqOK(byte z, byte w, byte value)
{byte i;
 bool r;
  
  r = true;
  if (!powtorzeniaOk)
    for(i = 0; i < z; i++)
      if (numer[w][i] == value) r = false;
  return r;
}

void tw2::Setrndrow(byte z, byte w)
{
  do
  {
    numer[w][z] = (byte)random(XLIMIT);
  }
  while ((z != 0) && (!CheckUniqOK(z, w, numer[w][z])));
}

