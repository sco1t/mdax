#include <MDAX.h>
#include <MDAXUtils.h>

#define FNT_NANOFONT_HEIGHT 6
#define FNT_NANOFONT_SYMBOLS_COUNT 90 // was 95

//data size=570 bytes
const unsigned char fnt_nanofont_data[FNT_NANOFONT_SYMBOLS_COUNT][1 + FNT_NANOFONT_HEIGHT] PROGMEM = {
  { 1, 128, 128, 128, 0, 128, 0, }, //glyph '!' code=0
  { 3, 160, 160, 0, 0, 0, 0, }, //glyph '"' code=1
  { 5, 80, 248, 80, 248, 80, 0, },  //glyph '#' code=2
  { 5, 120, 160, 112, 40, 240, 0, },  //glyph '$' code=3
  { 5, 136, 16, 32, 64, 136, 0, },  //glyph '%' code=4
  { 5, 96, 144, 104, 144, 104, 0, },  //glyph '&' code=5
  { 2, 128, 64, 0, 0, 0, 0, },  //glyph ''' code=6
  { 2, 64, 128, 128, 128, 64, 0, }, //glyph '(' code=7
  { 2, 128, 64, 64, 64, 128, 0, },  //glyph ')' code=8
  { 3, 0, 160, 64, 160, 0, 0, },  //glyph '*' code=9
  { 3, 0, 64, 224, 64, 0, 0, }, //glyph '+' code=10
  { 2, 0, 0, 0, 0, 128, 64, },  //glyph ',' code=11
  { 3, 0, 0, 224, 0, 0, 0, }, //glyph '-' code=12
  { 1, 0, 0, 0, 0, 128, 0, }, //glyph '.' code=13
  { 5, 8, 16, 32, 64, 128, 0, },  //glyph '/' code=14
  { 4, 96, 144, 144, 144, 96, 0, }, //glyph '0' code=15
  { 3, 64, 192, 64, 64, 224, 0, },  //glyph '1' code=16
  { 4, 224, 16, 96, 128, 240, 0, }, //glyph '2' code=17
  { 4, 224, 16, 96, 16, 224, 0, },  //glyph '3' code=18
  { 4, 144, 144, 240, 16, 16, 0, }, //glyph '4' code=19
  { 4, 240, 128, 224, 16, 224, 0, },  //glyph '5' code=20
  { 4, 96, 128, 224, 144, 96, 0, }, //glyph '6' code=21
  { 4, 240, 16, 32, 64, 64, 0, }, //glyph '7' code=22
  { 4, 96, 144, 96, 144, 96, 0, },  //glyph '8' code=23
  { 4, 96, 144, 112, 16, 96, 0, },  //glyph '9' code=24
  { 1, 0, 128, 0, 128, 0, 0, }, //glyph ':' code=25
  { 2, 0, 128, 0, 0, 128, 64, },  //glyph ';' code=26
  { 3, 32, 64, 128, 64, 32, 0, }, //glyph '<' code=27
  { 3, 0, 224, 0, 224, 0, 0, }, //glyph '=' code=28
  { 3, 128, 64, 32, 64, 128, 0, },  //glyph '>' code=29
  { 4, 224, 16, 96, 0, 64, 0, },  //glyph '?' code=30
  { 4, 96, 144, 176, 128, 112, 0, },  //glyph '@' code=31
  { 4, 96, 144, 240, 144, 144, 0, },  //glyph 'A' code=32
  { 4, 224, 144, 224, 144, 224, 0, }, //glyph 'B' code=33
  { 4, 112, 128, 128, 128, 112, 0, }, //glyph 'C' code=34
  { 4, 224, 144, 144, 144, 224, 0, }, //glyph 'D' code=35
  { 4, 240, 128, 224, 128, 240, 0, }, //glyph 'E' code=36
  { 4, 240, 128, 224, 128, 128, 0, }, //glyph 'F' code=37
  { 4, 112, 128, 176, 144, 112, 0, }, //glyph 'G' code=38
  { 4, 144, 144, 240, 144, 144, 0, }, //glyph 'H' code=39
  { 3, 224, 64, 64, 64, 224, 0, },  //glyph 'I' code=40
  { 4, 240, 16, 16, 144, 96, 0, },  //glyph 'J' code=41
  { 4, 144, 160, 192, 160, 144, 0, }, //glyph 'K' code=42
  { 4, 128, 128, 128, 128, 240, 0, }, //glyph 'L' code=43
  { 5, 136, 216, 168, 136, 136, 0, }, //glyph 'M' code=44
  { 4, 144, 208, 176, 144, 144, 0, }, //glyph 'N' code=45
  { 4, 96, 144, 144, 144, 96, 0, }, //glyph 'O' code=46
  { 4, 224, 144, 224, 128, 128, 0, }, //glyph 'P' code=47
  { 4, 96, 144, 144, 144, 96, 16, },  //glyph 'Q' code=48
  { 4, 224, 144, 224, 160, 144, 0, }, //glyph 'R' code=49
  { 4, 112, 128, 96, 16, 224, 0, }, //glyph 'S' code=50
  { 3, 224, 64, 64, 64, 64, 0, }, //glyph 'T' code=51
  { 4, 144, 144, 144, 144, 96, 0, },  //glyph 'U' code=52
  { 3, 160, 160, 160, 160, 64, 0, },  //glyph 'V' code=53
  { 5, 136, 168, 168, 168, 80, 0, },  //glyph 'W' code=54
  { 4, 144, 144, 96, 144, 144, 0, },  //glyph 'X' code=55
  { 3, 160, 160, 64, 64, 64, 0, },  //glyph 'Y' code=56
  { 4, 240, 16, 96, 128, 240, 0, }, //glyph 'Z' code=57
  { 2, 192, 128, 128, 128, 192, 0, }, //glyph '[' code=58
  { 5, 128, 64, 32, 16, 8, 0, },  //glyph '\' code=59
  { 2, 192, 64, 64, 64, 192, 0, },  //glyph ']' code=60
  { 5, 32, 80, 136, 0, 0, 0, }, //glyph '^' code=61
  { 4, 0, 0, 0, 0, 240, 0, }, //glyph '_' code=62
  { 2, 128, 64, 0, 0, 0, 0, },  //glyph '`' code=63
  { 3, 0, 224, 32, 224, 224, 0, },  //glyph 'a' code=64
  { 3, 128, 224, 160, 160, 224, 0, }, //glyph 'b' code=65
  { 3, 0, 224, 128, 128, 224, 0, }, //glyph 'c' code=66
  { 3, 32, 224, 160, 160, 224, 0, },  //glyph 'd' code=67
  { 3, 0, 224, 224, 128, 224, 0, }, //glyph 'e' code=68
  { 2, 64, 128, 192, 128, 128, 0, },  //glyph 'f' code=69
  { 3, 0, 224, 160, 224, 32, 224, },  //glyph 'g' code=70
  { 3, 128, 224, 160, 160, 160, 0, }, //glyph 'h' code=71
  { 1, 128, 0, 128, 128, 128, 0, }, //glyph 'i' code=72
  { 2, 0, 192, 64, 64, 64, 128, },  //glyph 'j' code=73
  { 3, 128, 160, 192, 160, 160, 0, }, //glyph 'k' code=74
  { 1, 128, 128, 128, 128, 128, 0, }, //glyph 'l' code=75
  { 5, 0, 248, 168, 168, 168, 0, }, //glyph 'm' code=76
  { 3, 0, 224, 160, 160, 160, 0, }, //glyph 'n' code=77
  { 3, 0, 224, 160, 160, 224, 0, }, //glyph 'o' code=78
  { 3, 0, 224, 160, 160, 224, 128, }, //glyph 'p' code=79
  { 3, 0, 224, 160, 160, 224, 32, },  //glyph 'q' code=80
  { 3, 0, 224, 128, 128, 128, 0, }, //glyph 'r' code=81
  { 2, 0, 192, 128, 64, 192, 0, },  //glyph 's' code=82
  { 3, 64, 224, 64, 64, 64, 0, }, //glyph 't' code=83
  { 3, 0, 160, 160, 160, 224, 0, }, //glyph 'u' code=84
  { 3, 0, 160, 160, 160, 64, 0, },  //glyph 'v' code=85
  { 5, 0, 168, 168, 168, 80, 0, },  //glyph 'w' code=86
  { 3, 0, 160, 64, 160, 160, 0, },  //glyph 'x' code=87
  { 3, 0, 160, 160, 224, 32, 224, },  //glyph 'y' code=88
  { 2, 0, 192, 64, 128, 192, 0, },  //glyph 'z' code=89
 // { 3, 96, 64, 192, 64, 96, 0, }, //glyph '{' code=90
 // { 1, 128, 128, 128, 128, 128, 0, }, //glyph '|' code=91
 // { 3, 192, 64, 96, 64, 192, 0, },  //glyph '}' code=92
 // { 3, 96, 192, 0, 0, 0, 0, },  //glyph '~' code=93
 // { 4, 48, 64, 224, 64, 240, 0, },  //glyph '£' code=94
};


MDAX mda;
MDAXUtils mdaU;


void mdaPrint(const char* str, byte x, byte y) {
  mda.printSRAM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str, x, y, 1);
}

char volt[5];
char range[10];
char fuk[15];
  
int j, g=1, r = 1,oldr=1,reset=0,oldadc=0;
float voltage;
float oldvoltage;
unsigned long oldmilis = 0;

const int pinDat = A1;
const int pinDtr = A2;
const int pinAck = A3;
const int pinStx = A4;
#define CH0  11
#define CH1  10
#define CH2  8


void setup() {
  analogReference(EXTERNAL);
  mda.begin();
  mda.clear(0);
  
  pinMode( pinDat, INPUT);
  pinMode( pinDtr, INPUT);
  pinMode( pinAck, OUTPUT);
  pinMode( pinStx, INPUT);
  pinMode(A0, INPUT) ;
  pinMode(CH0, OUTPUT);
  pinMode(CH1, OUTPUT);
  pinMode(CH2, OUTPUT);

  mdaPrint("V:", 0, 0);
  mdaPrint("F:", 47, 0);
  mdaPrint("VP:", 0, MDAX_HEIGHT - 5);
  mdaPrint("Range :", 48, MDAX_HEIGHT - 5);
mdaU.draw_line(46, MDAX_HEIGHT - 7, 46,MDAX_HEIGHT, 1); // line next to vp
   
  mdaU.draw_line(0, 7, MDAX_WIDTH, 7, 1); // line under volt
  mdaU.draw_line(45, 0, 45, 7, 1); // line next to volt
  mdaU.draw_line(0, MDAX_HEIGHT - 7, MDAX_WIDTH, MDAX_HEIGHT - 7, 1); // line over vp
  delay(500);
}
void loop() {

  byte data;
  while ( ToggleCheck(&data) >= 1)
  { if (data != 10 )
    {
      fuk[j] = data;
      j++;
    }
    else
    {
      fuk[j] = 'h';
      fuk[j + 1] = 'z';
      fuk[j + 2] = '\0';
      j = 0;
      mda.fillrect(57, 0, 63, 6, 0);
      mdaPrint(fuk, 57, 0);

    }
  }

//---------------------------------------------------------------

  
  if (vtimer >= oldmilis + 15)
  {oldmilis += 15;
    voltage = analogRead(A0);
    
   mda.putpixel(g, (MDAX_HEIGHT /2) + constrain(oldadc - voltage,-21,21) , 1);// DRAW GRAPH
   oldadc=voltage;
  g++;
       

  
      if (voltage < 200 and r != 2)
           {        r ++;    }
      if (voltage == 1023 and r != 0)
      {   r--;  }

         if (r == 2) {
        voltage = mapy(voltage, 278, 837, 2.5, 7.5);
      }
      else if (r == 1) {
        voltage = voltage * 47.82 / 1023;
      }else{
        voltage = voltage * 265 / 1023;
      }
   
       if (oldvoltage != voltage or oldr != r ){
 dtostrf(r, 1, 0, range);  
 mda.fillrect(76,MDAX_HEIGHT - 5, 25, 5, 0);//clear old range

  mdaPrint(range, 78, MDAX_HEIGHT - 5);// show range
                oldr = r;
   
      //dtostrf(r, 1, 0, range);  mdaPrint(range, 80, MDAX_HEIGHT - 5);
        ch_select(r);
        
      dtostrf(voltage, 5, 2, volt);
      
      mda.fillrect(8, 0, 35, 7, 0);// clear volts
      mdaPrint(volt, 10, 0);
      
        if (voltage > oldvoltage or reset == 1)
      {
      mda.fillrect(10, MDAX_HEIGHT -5, 35, 7, 0);// clear volts
      mdaPrint(volt, 13, MDAX_HEIGHT - 5);  
      reset = 0;
      }
     
      if (voltage ==0.01 and voltage > oldvoltage +1 )
      {reset = 1;}
       oldvoltage = voltage;
    }
  }
  
  if (g == 120)
  { g = 0;mda.fillrect(0, 8, MDAX_WIDTH, MDAX_HEIGHT - 15, 0);}// clear old graph
  
}


int ToggleCheck(byte *pdata)
{
  static byte toggle_Data;                // variable in which the bits are stored to make a byte.
  static byte toggle_Index;               // index of bits
  static boolean toggle_Ready = true;     // ready to read a bit

  int n = 0;

  int toggleDtr = digitalRead( pinDtr);        // read dtr signal first
  int toggleStx = digitalRead( pinStx);
  int toggleDat = digitalRead( pinDat);

  if ( toggle_Ready && toggleDtr == HIGH)
  {
    if ( toggleStx == HIGH)
    {
      toggle_Index = 0;
      toggle_Data = 0;
    }

    if ( toggleDat == HIGH)
      bitSet( toggle_Data, toggle_Index);

    digitalWrite( pinAck, HIGH);
    toggle_Ready = false;

    toggle_Index++;
    if ( toggle_Index >= 8)
    {
      toggle_Index = 0;

      // All 8 bits of the data byte have been received.
      // Write to *pdata only if the complete and valid data was received.
      *pdata = toggle_Data;
      n = 1;
    }
  }
  else if (!toggle_Ready && toggleDtr == LOW)
  {
    digitalWrite( pinAck, LOW);
    toggle_Ready = true;
  }
  return ( n);
}

int ch_select(int n) {
  switch (n) {
    case 0:
      digitalWrite(CH0, HIGH);//H
      digitalWrite(CH1, LOW);
      digitalWrite(CH2, LOW);
      break;
    case 1:
      digitalWrite(CH0, LOW);
      digitalWrite(CH1, HIGH);//h
      digitalWrite(CH2, LOW);
      break;
    case 2:
      digitalWrite(CH0, LOW);
      digitalWrite(CH1, LOW);
      digitalWrite(CH2, HIGH);//h
  }
}
float mapy(float x, long in_min, long in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
