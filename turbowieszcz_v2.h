
//

#ifndef TURBOWIESZCZ2_H
#define TURBOWIESZCZ2_H

//unique possibilities per row = max zwrotek
#define XLIMIT 32
//titles count
#define TCNT 32
/*
//wiecej kropek zeby zmienic rozklad prawdopodob.
#define ECNT1 5
#define ECNT2 5
*/

#define CASTTEXT(s) (char *)pgm_read_word(&s)

/*
const char EN1_0[] PROGMEM = ".";
const char EN1_1[] PROGMEM = "...";
const char EN1_2[] PROGMEM = "!";   //was "."
const char EN1_3[] PROGMEM = "!";
const char EN1_4[] PROGMEM = "...";   //was "."

const char EN2_0[] PROGMEM = "!";  //was ""
const char EN2_1[] PROGMEM = "...";
const char EN2_2[] PROGMEM = "";
const char EN2_3[] PROGMEM = "!";
const char EN2_4[] PROGMEM = "";

const char * const ENDINGS1[ECNT1] PROGMEM = {
  EN1_0, EN1_1, EN1_2, EN1_3, EN1_4
};

const char * const ENDINGS2[ECNT2] PROGMEM = {
  EN2_0, EN2_1, EN2_2, EN2_3, EN2_4
};
*/

//                           0123456789ABCDEF = 16 max
const char TT1[] PROGMEM  = "Zaglada";
const char TT2[] PROGMEM  = "To juz koniec";
const char TT3[] PROGMEM  = "Swiat ginie";
const char TT4[] PROGMEM  = "Wizyta w piekle";  //"Z wizyta w piekle";
const char TT5[] PROGMEM  = "Kataklizm";
const char TT6[] PROGMEM  = "Dzien z zycia"; //"Dzien z zycia..."
const char TT7[] PROGMEM  = "Masakra";
const char TT8[] PROGMEM  = "Katastrofa";
const char TT9[] PROGMEM  = "Wszyscy zginiemy";  //"Wszyscy zginiemy..."
const char TT10[] PROGMEM = "Spokoj";
const char TT11[] PROGMEM = "Koniec";
const char TT12[] PROGMEM = "Koniec ludzkosci";
const char TT13[] PROGMEM = "Telefon do Boga";
const char TT14[] PROGMEM = "Wieczna ciemnosc";  //"Wieczne ciemnosci"
const char TT15[] PROGMEM = "Mrok";
const char TT16[] PROGMEM = "Mrok w sloncu"; //"Mrok w srodku dnia"
const char TT17[] PROGMEM = "Ciemnosc";
const char TT18[] PROGMEM = "Piorunem w leb";
const char TT19[] PROGMEM = "Marsz troli";
const char TT20[] PROGMEM = "Szyderstwa Zlego";
const char TT21[] PROGMEM = "Okropnosc swiata";  //"Okropnosci swiata"
const char TT22[] PROGMEM = "Umrzec okrutnie";  //"Umrzec po raz ostatni"
const char TT23[] PROGMEM = "Potepienie";
const char TT24[] PROGMEM = "Bol mogzu";
const char TT25[] PROGMEM = "Wieczne wymioty";
const char TT26[] PROGMEM = "Zatrute dusze";
const char TT27[] PROGMEM = "Uciekaj";
const char TT28[] PROGMEM = "Apokalipsa";
const char TT29[] PROGMEM = "Zludzenie pryska";
const char TT30[] PROGMEM = "Makabra";
const char TT31[] PROGMEM = "Zaglada swiata";
const char TT32[] PROGMEM = "Smierc";

//                            0123456789ABCDEF 123456789ABCDEF = 16 max per row
const char D0_0[] PROGMEM  = "A na te zbrodnie nie bedzie kary";
const char D0_1[] PROGMEM  = "Opustoszaly bag-na, moczary";
const char D0_2[] PROGMEM  = "Na nic sie mod- ly zdadza ni    czary";
const char D0_3[] PROGMEM  = "Z krwi mordowa- nych sacza pu-  chary";
const char D0_4[] PROGMEM  = "To nietoperze,  weze, kalmary";
const char D0_5[] PROGMEM  = "Prozno nieszcze-sni sypia talary";
const char D0_6[] PROGMEM  = "Za co nam znosic takie ciezary";
const char D0_7[] PROGMEM  = "Zlowrogo iskrza kobr okulary";
const char D0_8[] PROGMEM  = "Prozno swe modly wznosi wikary";
const char D0_9[] PROGMEM  = "Pustosza sny    twoje te nocne  mary";
const char D0_10[] PROGMEM = "Prozno nieszcze-sny sypie talary"; //Prozno nieszczesnik sypie talary
const char D0_11[] PROGMEM = "Przedziwnie tka-ny zycia loga-  rytm";
const char D0_12[] PROGMEM = "Juz Strach wypu-szcza swoje oga-ry";
const char D0_13[] PROGMEM = "I oto giniesz w paszczy poczwary";
const char D0_14[] PROGMEM = "Wbijaja pale    zlote kafary";
const char D0_15[] PROGMEM = "Zycie odkrywa   swoje przywary";
const char D0_16[] PROGMEM = "Na dnie ponurej, pustej pieczary";
const char D0_17[] PROGMEM = "Apokalipsy nade-szly czary";
const char D0_18[] PROGMEM = "Upadly aniol    wspomina chwale";
const char D0_19[] PROGMEM = "Zycie ukrywa    swoje przywary";
const char D0_20[] PROGMEM = "Dziwnych owadow wzlatuja chmary";
const char D0_21[] PROGMEM = "Bombowce biora  nasze namiary";
const char D0_22[] PROGMEM = "Nie da sie wyr- wac czartom to- waru";
const char D0_23[] PROGMEM = "Prozno frajerzy sypia talary";
const char D0_24[] PROGMEM = "Po co nam saczyc podle browary";
const char D0_25[] PROGMEM = "Diler juz nie   dostarczy towaru";
const char D0_26[] PROGMEM = "Smutno patrzysz na puste bazary";
const char D0_27[] PROGMEM = "Lokomotywa nie  ma juz pary";
const char D0_28[] PROGMEM = "Gdy nie kazdego stac na browary";
const char D0_29[] PROGMEM = "Pozarl Hilary   swe okulary";
const char D0_30[] PROGMEM = "Spowily nas tru-jace opary";
const char D0_31[] PROGMEM = "To nie jest cal-ka ani logarytm";

//                            0123456789ABCDEF 123456789ABCDEF = 16 max per row
const char D1_0[] PROGMEM  = "Juz na arene    krew tryska";
const char D1_1[] PROGMEM  = "Juz piana ciek- nie im z pyska";
const char D1_2[] PROGMEM  = "Juz hen w oddali gdzies blyska";
const char D1_3[] PROGMEM  = "Smierc w kacie  czai sie bliska";
const char D1_4[] PROGMEM  = "Niesamowite du- chow igrzyska";
const char D1_5[] PROGMEM  = "Juz zaciskajac  lapiska";
const char D1_6[] PROGMEM  = "Zamiast pozostac w zamczyskach";
const char D1_7[] PROGMEM  = "Rzeka wylewa z  lozyska";
const char D1_8[] PROGMEM  = "Nieszczesc wyla-la sie miska";
const char D1_9[] PROGMEM  = "Juz zaciskajac  zebiska";
const char D1_10[] PROGMEM = "Otwarta nieszcz-esc walizka";
const char D1_11[] PROGMEM = "Niczym na rzym- skich boiskach";
const char D1_12[] PROGMEM = "Czart wznieca   swe paleniska";
const char D1_13[] PROGMEM = "A w mroku swieca zebiska";
const char D1_14[] PROGMEM = "Zewszad dochodza wyzwiska";
const char D1_15[] PROGMEM = "Swietych glod   wiary przyciska";
const char D1_16[] PROGMEM = "Ponuro patrzy z ich pyska";
const char D1_17[] PROGMEM = "Mgla stoi na    uroczyskach";
const char D1_18[] PROGMEM = "Kosci pogrzebia uwriska";
const char D1_19[] PROGMEM = "Glod wiary tak  nas przyciska";
const char D1_20[] PROGMEM = "Runely skalne   zwaliska";
const char D1_21[] PROGMEM = "Czart rozpala   paleniska";
const char D1_22[] PROGMEM = "Juz w mroku     swieca zebiska";
const char D1_23[] PROGMEM = "Znow pusta zeb- raka miska";
const char D1_24[] PROGMEM = "Diabelskie to sa igrzyska";
const char D1_25[] PROGMEM = "Nie powiedz dia-blu nazwiska";
const char D1_26[] PROGMEM = "Najglosniej sly-chac wyzwiska";
const char D1_27[] PROGMEM = "Diabelskie maja nazwiska";
const char D1_28[] PROGMEM = "Tam uciekaja lu-dziska";
const char D1_29[] PROGMEM = "Tak rzecze stara hipiska";
const char D1_30[] PROGMEM = "Gdzie dawne lu- dzi siedliska";
const char D1_31[] PROGMEM = "Najglosniej     piszczy hipiska";

//                            0123456789ABCDEF 123456789ABCDEF = 16 max per row
const char D2_0[] PROGMEM  = "Rwa pazurami    swoje ofiary";
const char D2_1[] PROGMEM  = "Nic nie pomoze  tu druid stary";
const char D2_2[] PROGMEM  = "To nocne zjawy  i senne mary";
const char D2_3[] PROGMEM  = "Niegrozne przy  nich nawet Atari";
const char D2_4[] PROGMEM  = "Pod wodza ksiez-nej diablic Aza-ry";
const char D2_5[] PROGMEM  = "Z dala straszli-we trabia fanfa-ry";
const char D2_6[] PROGMEM  = "Takie sa oto    piekla bezmiary";
const char D2_7[] PROGMEM  = "Zas dookola     luny, pozary";
const char D2_8[] PROGMEM  = "A teraz nagle   jestes juz stary";
const char D2_9[] PROGMEM  = "Tu nie pomoze   juz sila wiary";
const char D2_10[] PROGMEM = "Cudze nieszcze- scie moje nekta-ry";
const char D2_11[] PROGMEM = "Wszystko zalewa wrzacy liparyt";
const char D2_12[] PROGMEM = "Zabojcze sa ich niecne zamiary";
const char D2_13[] PROGMEM = "Zatrute dusze   lacza sie w pa- ry";
const char D2_14[] PROGMEM = "Swiat pokazuje  swoje wymiary";
const char D2_15[] PROGMEM = "Tu nie pomoze   elektryk stary";
const char D2_16[] PROGMEM = "Brak uczuc, che-ci a takze wiary";
const char D2_17[] PROGMEM = "Pomnij, a mowil Mickiewicz stary";
const char D2_18[] PROGMEM = "Spalonych lasow strasza hektary";
const char D2_19[] PROGMEM = "Mordercy licza  swoje ofiary";
const char D2_20[] PROGMEM = "Ksiadz pozostaje nagle bez wiary";
const char D2_21[] PROGMEM = "Papiez zaczyna  odprawiac czary";
const char D2_22[] PROGMEM = "Tu nie pomoze   paciorek, stary";
const char D2_23[] PROGMEM = "Upada oto dab   ten prastary";
const char D2_24[] PROGMEM = "I uderzaja z    sila Niagary";
const char D2_25[] PROGMEM = "Bystro smigaja  nawet niezdary";
const char D2_26[] PROGMEM = "Juz nieruchome  ich awatary";
const char D2_27[] PROGMEM = "I bez wartosci  sa juz dolary";
const char D2_28[] PROGMEM = "Gdzie podzialy  sie te nenufary";  //Gdzie sie podzialy te nenufary
const char D2_29[] PROGMEM = "Tak nas zabija  grozne pulsary";
const char D2_30[] PROGMEM = "Powodz zalewa   wielkie obszary";
const char D2_31[] PROGMEM = "Az rozpadaja sie i filary";

//                            0123456789ABCDEF 123456789ABCDEF = 16 max per row
const char D3_0[] PROGMEM  = "Wnet na nas tez przyjdzie kryska";
const char D3_1[] PROGMEM  = "Znikad zadnego  schroniska";
const char D3_2[] PROGMEM  = "Powietrze tnie  swist biczyska";
const char D3_3[] PROGMEM  = "Rodem z czarcie-go urwiska";
const char D3_4[] PROGMEM  = "I swad nieznosny sie wciska";
const char D3_5[] PROGMEM  = "Huk, jak z wiel-kiego lotniska";
const char D3_6[] PROGMEM  = "Zlowrogo brzmia ich nazwiska";
const char D3_7[] PROGMEM  = "W kacie niesmia-lo ktos piska";
const char D3_8[] PROGMEM  = "Ktos obok mordu-je liska";
const char D3_9[] PROGMEM  = "Krwia ociekaja  zebiska";
const char D3_10[] PROGMEM = "Wokolo dzikie   piarzyska";
const char D3_11[] PROGMEM = "I zadza czai sie niska";
const char D3_12[] PROGMEM = "Diabel cie dzi- siaj wyzyska";
const char D3_13[] PROGMEM = "Plona zaglady   ogniska";
const char D3_14[] PROGMEM = "Gwalt niech sie gwaltem odciska";
const char D3_15[] PROGMEM = "Stoisz na skraju urwiska";
const char D3_16[] PROGMEM = "Tam szatan czar-ta wyiska";
const char D3_17[] PROGMEM = "Uciekaj, przysz-losc jest mgli- sta";
const char D3_18[] PROGMEM = "Nadziei zludze- nie pryska";
const char D3_19[] PROGMEM = "Wydziobia oczy  ptaszyska";
const char D3_20[] PROGMEM = "Padaja lby na   klepisko";
const char D3_21[] PROGMEM = "Smierc zbiera   zniwo w kolys-  kach";
const char D3_22[] PROGMEM = "Cos znowu zgrzy-ta w lozyskach";
const char D3_23[] PROGMEM = "Spadasz z wiel- kiego urwiska";
const char D3_24[] PROGMEM = "Lawa spod ziemi wytryska";
const char D3_25[] PROGMEM = "Wokolo grzmi    albo blyska";
const char D3_26[] PROGMEM = "Falszywe zloto  polyska";
const char D3_27[] PROGMEM = "Najwiecej czart tu uzyska";
const char D3_28[] PROGMEM = "Owieczki Zly tu pozyska";
const char D3_29[] PROGMEM = "Owieczki spadly z urwiska";
const char D3_30[] PROGMEM = "Snuja sie dymy  z ogniska";
const char D3_31[] PROGMEM = "To czarne leca  ptaszyska";

//---

//that was tricky,
//see https://github.com/arduino/Arduino/wiki/1.6-Frequently-Asked-Questions
//also https://www.arduino.cc/reference/en/language/variables/utilities/progmem/

const char * const data[4][XLIMIT] PROGMEM = {
  {D0_0, D0_1, D0_2, D0_3, D0_4, D0_5, D0_6, D0_7, D0_8, D0_9, D0_10, D0_11, D0_12, D0_13, D0_14, D0_15, D0_16, D0_17, D0_18, D0_19, D0_20,
   D0_21, D0_22, D0_23, D0_24, D0_25, D0_26, D0_27, D0_28, D0_29, D0_30, D0_31
  },
  {D1_0, D1_1, D1_2, D1_3, D1_4, D1_5, D1_6, D1_7, D1_8, D1_9, D1_10, D1_11, D1_12, D1_13, D1_14, D1_15, D1_16, D1_17, D1_18, D1_19, D1_20,
  D1_21, D1_22, D1_23, D1_24, D1_25, D1_26, D1_27, D1_28, D1_29, D1_30, D1_31
  },
  {D2_0, D2_1, D2_2, D2_3, D2_4, D2_5, D2_6, D2_7, D2_8, D2_9, D2_10, D2_11, D2_12, D2_13, D2_14, D2_15, D2_16, D2_17, D2_18, D2_19, D2_20,
  D2_21, D2_22, D2_23, D2_24, D2_25, D2_26, D2_27, D2_28, D2_29, D2_30, D2_31
  },
  {D3_0, D3_1, D3_2, D3_3, D3_4, D3_5, D3_6, D3_7, D3_8, D3_9, D3_10, D3_11, D3_12, D3_13, D3_14, D3_15, D3_16, D3_17, D3_18, D3_19, D3_20,
  D3_21, D3_22, D3_23, D3_24, D3_25, D3_26, D3_27, D3_28, D3_29, D3_30, D3_31
  }
};

const char * const titles[TCNT] PROGMEM = {
  TT1, TT2, TT3, TT4, TT5, TT6, TT7, TT8, TT9, TT10,
  TT11, TT12, TT13, TT14, TT15, TT16, TT17, TT18, TT19, TT20,
  TT21, TT22, TT23, TT24, TT25, TT26, TT27, TT28, TT29, TT30, 
  TT31, TT32
};

//---

#define NUM_MENU_ITEM 5

//#define MENU_ITEM_ID_X0 0
//#define MENU_ITEM_ID_X1 1
//#define MENU_ITEM_ID_X2 2
//#define MENU_ITEM_ID_X3 3
//#define MENU_ITEM_ID_X4 4
//#define MENU_ITEM_ID_X5 5
//#define MENU_ITEM_ID_X6 6

const char MENU_1[] PROGMEM = " NOWY ";
const char MENU_2[] PROGMEM = " ZWR=";
const char MENU_3[] PROGMEM = " RYM=";
const char MENU_4[] PROGMEM = " POWT=";
const char MENU_5[] PROGMEM = " O PROGRAMIE ";

const char * const menu_items[NUM_MENU_ITEM] PROGMEM = {MENU_1, MENU_2, MENU_3, MENU_4, MENU_5};

//---

const char TX_OK[] PROGMEM = "OK";
const char TW_APPNAME[] PROGMEM = "Turbo Wieszcz ++";
const char TX_ABOUT1[] PROGMEM = //
  "\x82" //
  "Turbo Wieszcz ++" //
  "\x87" //
  "generator poezji" //
  "wersja " //
  "\x84" //
  "Arduino\n" //
  "\x87" //
  "(c)2018\n" //
  "Noniewicz.com,\n" //
  "Jakub Noniewicz\n" //
  "aka MoNsTeR/GDC\n" //
  "Strofy (c):\n" //
  "Grych, Freeak,  Monster, Fred\ni Marek Pampuch.";
const char TX_ABOUT2[] PROGMEM = //
  "Wg poprzednich\n" //
  "moich wersji:\n" //
  "- C-64,\n" //
  "- ZX Spectrum,\n" //
  "- Android,\n" //
  "- Windows,\n" //
  "opartych z kolei" //
  "na idei z\n" //
  "Magazynu Amiga\n" //
  "by M. Pampuch.";
const char TX_ABOUT3[] PROGMEM = //
  "Zainspirowany\n" //
  "wersjami:\n" //
  "- iPhone (" //
  "\x85" //
  "Grych" //
  "\x87" //
  ")" //
  "- Arduino (" //
  "\x85" //
  "Fred" //
  "\x87" //
  ")(zaginiona).\n" //
  "Hardware support" //
  "\x85" //
  "Karol\nSobierajski.\n\n" //
  "\x87" //
  "Historia wiesz-\ncza w magazynie\n" //
  "\x86" //
  "HA!ART 47 3/2014";
const char TX_ABOUT4[] PROGMEM = //
  "\x87" //
  "Greetings to:\n\n" //
  "\x86" //
  "Grych " //
  "\x85" //
  "Freeak    " //
  "\x84" //
  "Trygrys " //
  "\x83" //
  "V0yager " //
  "\x82" //
  "Fred " //
  "\x81" //
  "Royal " //
  "\x86" //
  "Katka" //
  "\x85" //
  "Kya " //
  "\x84" //
  "Anthon " //
  "\x83" //
  "Smash" //
  "\x82" //
  "Beeth " //
  "\x81" //
  "RomeoAD   " //
  "\x86" //
  "Pampuch " //
  "\x85" //
  "PMarecki" //
  "\x84" //
  "Jolka " //
  "\x83" //
  "Da_None   " //
  "\x82" //
  "XTD " //
  "\x81" //
  "Hak " //
  "\x86" //
  "Yoga    " //
  "\x85" //
  "Jubal " //
  "\x84" //
  "Cromax    " //
  "\x83" //
  "Dudi " //
  "\x82" //
  "Maxym";

const char TX_MENU[] PROGMEM = "<MENU";
const char TX_NEXT[] PROGMEM = "DALEJ*";
const char TX_NEW[] PROGMEM = "NOWY^";
const char OP_MENU_NIE[] PROGMEM = "NIE";
const char OP_MENU_TAK[] PROGMEM = "TAK";
const char OP_MENU_ABAB[] PROGMEM = "ABAB";
const char OP_MENU_ABBA[] PROGMEM = "ABBA";
const char OP_MENU_AABB[] PROGMEM = "AABB";

#define TEXT_OK 0
#define TEXT_APPNAME 1
#define TEXT_ABOUT1 2
#define TEXT_ABOUT2 3
#define TEXT_ABOUT3 4
#define TEXT_ABOUT4 5
#define TEXT_NEXT 6
#define TEXT_MENU 7
#define TEXT_NEW 8
#define TEXT_NIE 9
#define TEXT_TAK 10
#define TEXT_ABAB 11
#define TEXT_ABBA 12
#define TEXT_AABB 13

const unsigned char * const alltxt[] PROGMEM = {
  TX_OK, TW_APPNAME, TX_ABOUT1, TX_ABOUT2, TX_ABOUT3, TX_ABOUT4, TX_NEXT, TX_MENU, TX_NEW, OP_MENU_NIE, OP_MENU_TAK,
  OP_MENU_ABAB, OP_MENU_ABBA, OP_MENU_AABB
};

#endif

