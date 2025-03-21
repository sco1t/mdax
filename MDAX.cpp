#include "MDAX.h"

//HSYNC pin used by TIMER2
#if defined(__AVR_ATmega2560__)
  #define HSYNCPIN 9
#else
  #define HSYNCPIN 3
#endif

//These two pin cannot be modified without modify the HSYNC assembler code
#if defined(__AVR_ATmega2560__)
  #define COLORPIN0 30
  #define COLORPIN1 31
#else
  #define COLORPIN0 6
  #define COLORPIN1 7
#endif

//VSYNC pin used by TIMER1. Can be 9 or 10
#if defined(__AVR_ATmega2560__)
  #define VSYNCPIN 11
#else
  #define VSYNCPIN 9
#endif

//Number of MDA lines to be skipped (black lines), BackPorchLines
/*These lines includes the vertical sync pulse and back porch.

Minimum value must be 35 (calculate from Nick Gammon)
You can modify this value to center the framebuffer vertically, or not*/
#if defined(__AVR_ATmega2560__) && \
(defined(ATMEGA2560_HIGHRES) || defined(ATMEGA2560_MAXRES))
  #define SKIPLINES 30
#else
  #define SKIPLINES 30
#endif

static byte afreq, afreq0;
unsigned long vtimer;

static byte aline, rlinecnt;
static byte vskip, COCK;
byte mdaxfb[MDAX_HEIGHT*MDAX_BWIDTH];

//VSYNC interrupt
ISR(TIMER1_OVF_vect) {
  aline=-1;
  vskip=SKIPLINES;
  vtimer++;
  rlinecnt=0;
}
//HSYNC interrupt
ISR(TIMER2_OVF_vect) {
  /*
  NOTE: I prefer to generate the line here, inside the interrupt.
  Gammon's code generate the line pixels inside main().
  My versin generate the signal using only interrupts, so inside main() function
  you can do anything you want. Your code will be interrupted when MDA signal
  needs to be generated
  */
 

  //check vertical porch
  if (vskip) {
      vskip--;
      return;
  }
  if (rlinecnt<MDAX_HEIGHT) {   
    //interrupt jitter fix (needed to keep signal stable)
    //code from https://github.com/cnlohr/avrcraft/tree/master/terminal
    //modified from 4 nop align to 8 nop align
    #define DEJITTER_OFFSET 17
    #define DEJITTER_SYNC 2
    asm volatile(
      "     lds r16, %[timer0]    \n\t" //
      #if defined(__AVR_ATmega2560__)
      "     add r16, %[toffset]   \n\t" //
      #endif
      "     subi r16, %[tsync]    \n\t" //
      "     andi r16, 7           \n\t" //
      "     call TL               \n\t" //
      "TL:                        \n\t" //
      #if defined(__AVR_ATmega2560__)
      "     pop r17               \n\t" //ATMEGA2560 has a 22bit PC!
      #endif
      "     pop r31               \n\t" //
      "     pop r30               \n\t" //
      "     adiw r30, (LW-TL-5)   \n\t" //
      "     add r30, r16          \n\t" //
      //"   adc r31, __zero_reg__ \n\t" //
      "     ijmp                  \n\t" //
      "LW:                        \n\t" //
      "     nop                   \n\t" //
      "     nop                   \n\t" //
      "     nop                   \n\t" //
      "     nop                   \n\t" //
     "     nop                   \n\t" //
     "     nop                   \n\t" //
      "     nop                   \n\t" //         
      "     nop                   \n\t" //
    "     nop                   \n\t" //
      "LBEND:                     \n\t" //
    :
    : [timer0] "i" (&TCNT0),
      [toffset] "i" ((uint8_t)DEJITTER_OFFSET),
      [tsync] "i" ((uint8_t)DEJITTER_SYNC)
    : "r30", "r31", "r16", "r17");
    /*
    Output all pixels.

    NOTE: My trick here is to unpack 4 pixels and shift them before writing to
    PORTD.

    Pixels are packed as 0b11223344 because the first pixel write have no time
    to perform a shift (ld, out) and must be prealigned to the two upper bits 
    of PORTD, where the two wires of the MDA DSUB are connected. The second, 
    the third and the forth pixels are shifted left using mul opcode instead 
    of a left shift opcode. Shift opcodes are slow and can shift only 1 bit at
    a time, using 1 clock cycle. mul is faster.

    Instead of using a loop i use the .rept assembler directive to generate an 
    unrolled loop of 30 iterations.
    */
    asm volatile (
   
     ".rept 80   \n\t" // Front pourch
        "    nop  \n\t" //
        ".endr    \n\t" //

      "    ldi r20, 4       \n\t" //const for <<2bit
      #ifdef MDAX_DEV_DEPRECATED
      ".rept 1           \n\t" //center line
      "    nop              \n\t" //
      ".endr                \n\t" //
      #endif
      ".rept 30             \n\t" //output 4 pixels for each iteration
      "    ld r16, Z+       \n\t" //
      "    out %[port], r16 \n\t" //write pixel 1
      "    nop              \n\t" //
      "    nop              \n\t" //
      "    mul r16, r20     \n\t" //<<2
      "    out %[port], r0  \n\t" //write pixel 2
      "    nop              \n\t" //
      "    nop              \n\t" //
      "    mul r0, r20      \n\t" //<<4
      "    out %[port], r0  \n\t" //write pixel 3
      "    nop              \n\t" //
      "    nop              \n\t" //
      "    nop              \n\t" //
      "    mul r0, r20      \n\t" //<<6
      "    out %[port], r0  \n\t" //write pixel 4
      "    nop              \n\t" //
      "    nop              \n\t" //
      "    nop              \n\t" //
      ".endr                \n\t" //
      "    nop              \n\t" //expand last pixel
    
      "    ldi r16, 0       \n\t" //
      "    out %[port], r16 \n\t" //write black for next pixels
    :
    #if defined(__AVR_ATmega2560__)
    : [port] "I" (_SFR_IO_ADDR(PORTC)),
    #else
    : [port] "I" (_SFR_IO_ADDR(PORTD)),
    #endif
      "z" "I" (/*rline*/(byte*)mdaxfb + rlinecnt*MDAX_BWIDTH)
    : "r16", "r17", "r20", "r21", "memory");

    //increment framebuffer line counter after 6 MDA lines
    #if defined(__AVR_ATmega2560__) && defined(ATMEGA2560_MAXRES)
      #define CLONED_LINES (1-1)//was (2-1)
    #else
      #define CLONED_LINES (6-1) //was (6-1)
    #endif
    if (++aline==CLONED_LINES) { 
      aline=-1;
      rlinecnt++;
    } else {
      #ifdef MDAX_DEV_DEPRECATED
      //small delay to keep the line signal aligned
      asm volatile(
        ".rept 17 \n\t" //
        "    nop  \n\t" //
        ".endr    \n\t" //
      :::);
      #endif
    }
  } 
}
void MDAX::begin(bool enableTone) {
  //Timers setup code, modified version of the Nick Gammon's MDA sketch
  cli();

  //disable TIMER0 interrupt
  TIMSK0=0;
  TCCR0A=0;
  TCCR0B=(1 << CS00); //enable 16MHz counter (used to fix the HSYNC interrupt jitter)
  OCR0A=0;
  OCR0B=0;
  TCNT0=0;
  
//TIMER1 - vertical sync pulses
  pinMode(VSYNCPIN, OUTPUT);
  #if VSYNCPIN==10 //ATMEGA328 PIN 10
  TCCR1A=bit(WGM10) | bit(WGM11) | bit(COM1B1);
  TCCR1B=bit(WGM12) | bit(WGM13) | bit(CS12) | bit(CS10); //1024 prescaler
   OCR1A=311; //20000 / 64 uS=312 (less one)
  OCR1B=0; //64 / 64 uS=1 (less one)
  TIFR1=bit(TOV1); //clear overflow flag
  TIMSK1=bit(TOIE1); //interrupt on overflow on TIMER1
  #else //ATMEGA328 PIN 9 or ATMEGA2560 PIN 11
  TCCR1A=bit(WGM11) | bit(COM1A1);
  TCCR1B=bit(WGM12) | bit(WGM13) | bit(CS12) | bit(CS10); //1024 prescaler
   ICR1=350; // 20000 / 64 uS = 312 (less one)
  OCR1A=0; //64 / 64 uS=1 (less one)
  TIFR1=bit(TOV1); //clear overflow flag
  TIMSK1=bit(TOIE1); //interrupt on overflow on TIMER1
  #endif

  //TIMER2 - horizontal sync pulses
  pinMode(HSYNCPIN, OUTPUT);
  TCCR2A=bit(WGM20) | bit(WGM21) | bit(COM2B1); //pin3=COM2B1
  TCCR2B=bit(WGM22) | bit(CS21); //8 prescaler

  OCR2A=107; // 54 / 0.5 uS =  (less one) scan line?
  OCR2B=7; //4 / 0.5 uS=8 (less one) Sync puls?
  TIFR2=bit(TOV2); //clear overflow flag
  TIMSK2=bit(TOIE2); //interrupt on overflow on TIMER2
  //pins for outputting the colour information
  pinMode(COLORPIN0, OUTPUT);
  pinMode(COLORPIN1, OUTPUT);  
  sei();
}
void MDAX::end() {
  //disable TIMER0
  TCCR0A=0;
  TCCR0B=0;
  //disable TIMER1
  TCCR1A=0;
  TCCR1B=0;
  //disable TIMER2
  TCCR2A=0;
  TCCR2B=0;
}
void MDAX::clear(byte color) {
  register byte c=color;
  c&=3;
  register byte c0=(c*4) | c;
  c0|=c0*16;
  memset(mdaxfb, c0, MDAX_BSIZE);
}
void MDAX::copy(byte *src) {
  byte *o=(byte*)mdaxfb;
  unsigned cnt=MDAX_BSIZE;
  while (cnt--)
    *o++=pgm_read_byte(src++);
}
void MDAX::fillrect(byte x, byte y, byte width, byte height, byte color) {
  byte rh=height;
  while (rh--) {
    byte rw=width, rx=x;
    while (rw--) {
      if (rx<MDAX_WIDTH && y<MDAX_HEIGHT)
        putpixel(rx, y, color);
      rx++;
    }
    y++;
  }
}


void MDAX::delay(int msec) {
  while (msec--) {
    unsigned cnt=205; //TODO: use a more precise way to calculate cnt
    while (cnt--)
      asm volatile("nop\nnop\nnop\nnop\n");
  }
}
