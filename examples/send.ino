// Toggle with Handshake Communication.
// ------------------------------------
//
// This communication is written for the VGAx/MDAx code.
// It transfers a byte from a primary Arduino to a secondary Arduino.
// The Slave Arduino is running the VGAx code.
// The Slave code does not use delays, no interrupts,
// and interrupts are not disabled.
//
// Signals are active HIGH, and default LOW.
// LSB first, bit 0 is the first bit to be send.
//
// Four signal wires plus GND:
//   dat = data (from Master)
//   dtr = data ready (from Master)
//   ack = acknowledge (from Slave)
//   stx = first bit (from Master)
//   GND (connect also both GND of the Arduino boards)
//
// Transfer rate is about 1400 bytes per second for two Arduino Uno boards.
//
// This is the first version, the code might not be fully fail safe at the moment.
//
#include <FreqCount.h>
const int pinDat = A1;
const int pinDtr = A2;
const int pinAck = A3;
const int pinStx = A4;
//  text[20];
void setup()
{
  FreqCount.begin(1000);
  Serial.begin(9600);
  Serial.println(F("Master"));

  pinMode( pinDat, OUTPUT);
  pinMode( pinDtr, OUTPUT);
  pinMode( pinAck, INPUT);
  pinMode( pinStx, OUTPUT);
}

void loop()
{

//////////////////////////
  if (FreqCount.available()) {
    unsigned long count = (FreqCount.read()*2);

    char text[20] = "";
    ltos(count, text , 10);
    text[strlen(text)] = char(10);
    //Serial.println(strlen(text));
    //Serial.println(text);

    for ( int i = 0; i < strlen(text); i++)
    {
      int n = ToggleSend( text[i]);
      if ( n == 0)
        Serial.println(F("ToggleSend failed"));
    }

  }
  //////////////////////////////////////////
  
}

// ToggleSend
// ----------
// Send a single byte.
// This function waits for the Slave with a timeout,
// and returns after the byte has been send.
// The return value is the number of bytes that are send.
// At this moment only one byte is send.
//
int ToggleSend( const byte data)
{
  unsigned long toggleMillis;
  int error = 0;
  int n = 0;          // number of bytes that are send
  digitalWrite( pinStx, HIGH);   // indicate start (HIGH for first bit)
  for ( int i = 0; i < 8 && error == 0; i++)
  {
    digitalWrite( pinDat, bitRead( data, i) == 1 ? HIGH : LOW);
    digitalWrite( pinDtr, HIGH);    // everything is ready, make it high

    // wait for ack to be HIGH
    toggleMillis = millis();
    while ( digitalRead( pinAck) == LOW)
    {
      if ( millis() - toggleMillis >= 1000UL)
      {
        error = -1;
        Serial.println(F("timeout waiting for ack high"));
        break;
      }
    }
    digitalWrite( pinStx, LOW);  // stx low for other bits
    digitalWrite( pinDtr, LOW);  // everything is ready, make it low.

    if ( error == 0)
    {
      // wait for ACK to go low.
      toggleMillis = millis();
      while ( digitalRead( pinAck) == HIGH)
      {
        if ( millis() - toggleMillis >= 1000UL)
        {
          error = -2;
          Serial.println(F("timeout waiting for ack low"));
          break;
        }
      }
    }
  }

  // If an error occured, the byte is probably not send.
  if ( error != 0)
    n = 0;
  else
    n = 1;

  return ( n);
}
char *ultos_recursive(unsigned long val, char *s, unsigned radix, int pos)
{
  int c;

  if (val >= radix)
    s = ultos_recursive(val / radix, s, radix, pos + 1);
  c = val % radix;
  c += (c < 10 ? '0' : 'a' - 10);
  *s++ = c;
  if (pos % 3 == 0) *s++ = ',';
  return s;
}

char *ltos(long val, char *s, int radix)
{
  if (radix < 2 || radix > 36) {
    s[0] = 0;
  } else {
    char *p = s;
    if (radix == 10 && val < 0) {
      val = -val;
      *p++ = '-';
    }
    p = ultos_recursive(val, p, radix, 0) - 1;
    *p = 0;
  }
  return s;
}
