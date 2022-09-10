# MDA monochrome graphics Library for Arduino UNO and MEGA

The text below needs updated for MDAx


Based on VGAx By Sandro Maffiodo  
[smaffer@gmail.com](mailto:smaffer@gmail.com)  
[http://www.sandromaffiodo.com](http://www.sandromaffiodo.com)

## What is MDAx?

This is a MDA library for Arduino UNO and Arduino MEGA.  
To use this library you need only 3 resistors and one DSUB15 connector.  
This library require an ATMega328 MCU (or higher) MCU. Does not work with ATTINY family or ATMega168.

## Credits
Baced on [VGAx] (https://github.com/smaffer/vgax ) by By Sandro Maffiodo  
Based on the [VGA color video generation](http://www.gammon.com.au/forum/?id=11608) by [Nick Gammon](http://www.gammon.com.au).  
Inspired from the game [Toorums Quest](http://petenpaja.blogspot.fi/2013/11/toorums-quest-ii-retro-video-game.html) by [Peten Paja](http://petenpaja.blogspot.fi).  
AVR [interrupt dejitter](https://github.com/cnlohr/avrcraft/tree/master/terminal) from [Charles CNLOHR](https://github.com/cnlohr).  
Thanks to Roberto Melzi [RobCai](https://www.youtube.com/channel/UCgQK0QAMUV5L4OT6y7HsryQ) for developing the first game that uses this library: [Arduino Bomber](https://www.youtube.com/watch?v=dtfNhh6GZ-s). 

## Audio

It's gone. all gone. If you use code for VGAX you will need to remove all reference to sound. 

## Wiring

You need:

- 1x 470ohm resistors
- 2x 68ohm resistors 
- 1x DSUB15 female connector

Then connect them like the following schema.  
*NOTE: The DSUB15 connector is shown from rear view*

![wire0.png](docs/wire0.png)
![wire1.png](docs/wire1.png)


Pin 6 and pin 7 on Arduino MEGA must be changed to pin 30 and pin 31 but the same logic of choosing colors can be applyed on MEGA.

## PIN and PORT

Video generation is implemented using PORTD, so **you cannot use any of the
PORTD pins**.

The vertical synchronization signal is generated on pin 9. Gammon's version use
the pin 10 but i prefer to keep pins 10 11 12 13 free for common SPI usage.

On Arduino MEGA PORTD is substituted to PORTA, vertical sync is pin 11 and horizontal pin is 9.

## Interrupt

MDAx library generate the video signal using only interrupts, so, inside main() function, you can do anything you want. Your code will be interrupted when VGA signal needs to be generated.


**WARNING: You cannot add other interrupts or the MDA signal generation will be broken.**

## Timers

This library uses **all the 3 timers** of ATMega328 MCU. On ATMega2560 there are more unused timers.

*TIMER1* and *TIMER2* are configured to generate HSYNC and VSYNC pulses.
The setup code for these two timers has been [created by Nick Gammon](http://www.gammon.com.au/forum/?id=11608).
I have only made some modifications to use pin 9 instead of pin 10. On ATMega2560 HSYNC and VSYNC are different.

*TIMER0* is used to fix the interrupt jitter. I have modified an assembler trick
originally writen by [Charles CNLOHR](https://github.com/cnlohr/avrcraft/tree/master/terminal).

By default the *TIMER0* is used by Arduino to implement these functions:

	unsigned millis();
	unsigned long micros();
	void delay(ms); 
	void delayMicroseconds(us);

Instead of using these functions, you should use the alternative versions
provided by my library.

## Library usage

To use the VGAX library you need to include its header

    #include <MDAX.h>

VGAX class is static, so you can use the class without create an instance of it:

    void setup() {
      MDAX::begin();
    }

Or, if you prefer, you can create your instance, but keep in mind that cannot be
more than one VGAX instance at a time:

    MDAX mda;

    void setup() {
      mda.begin();
    }

### Pixel

This is a simple example of putpixel4 function. The putpixel4 function put 4
pixels at a time. The following code create a pattern of colors in the setup
function:

	 #include <VGAX.h>

    VGAX vga;

    void setup() {
      vga.begin();
      vga.clear(11);
      for (int y=0; y!=VGAX_HEIGHT; y++) {
        for (int x=0; x!=VGAX_BWIDTH; x++) {
          vga.putpixel4(x, y, y%2 ? 27 : 228);
        }
      }
    }
    void loop() {
    }
    


### Fonts

You can use my 2bitfont tool to create your fonts. I have designed two super small fonts that can be used with VGAX or with others projects. Here they are:

**ufont.png**: ![ufont.png](docs/ufont.png)

**ufont2.png**: ![ufont2.png](docs/ufont2.png)

The following example use the first font.

    #include <VGAX.h>

    //font generated from 2BITFONT - by Sandro Maffiodo
    #define FNT_UFONT_HEIGHT 6
    #define FNT_UFONT_SYMBOLS_COUNT 95
    //data size=570 bytes
    const unsigned char fnt_ufont_data[FNT_UFONT_SYMBOLS_COUNT][1+FNT_UFONT_HEIGHT] PROGMEM={
    { 1, 128, 128, 128,   0, 128,   0, }, //glyph '!' code=0
    { 3, 160, 160,   0,   0,   0,   0, }, //glyph '"' code=1
    { 5,  80, 248,  80, 248,  80,   0, }, //glyph '#' code=2
    { 5, 120, 160, 112,  40, 240,   0, }, //glyph '$' code=3
    { 5, 136,  16,  32,  64, 136,   0, }, //glyph '%' code=4
    { 5,  96, 144, 104, 144, 104,   0, }, //glyph '&' code=5
    { 2, 128,  64,   0,   0,   0,   0, }, //glyph ''' code=6
    { 2,  64, 128, 128, 128,  64,   0, }, //glyph '(' code=7
    { 2, 128,  64,  64,  64, 128,   0, }, //glyph ')' code=8
    { 3,   0, 160,  64, 160,   0,   0, }, //glyph '*' code=9
    { 3,   0,  64, 224,  64,   0,   0, }, //glyph '+' code=10
    { 2,   0,   0,   0,   0, 128,  64, }, //glyph ',' code=11
    { 3,   0,   0, 224,   0,   0,   0, }, //glyph '-' code=12
    { 1,   0,   0,   0,   0, 128,   0, }, //glyph '.' code=13
    { 5,   8,  16,  32,  64, 128,   0, }, //glyph '/' code=14
    { 4,  96, 144, 144, 144,  96,   0, }, //glyph '0' code=15
    { 3,  64, 192,  64,  64, 224,   0, }, //glyph '1' code=16
    { 4, 224,  16,  96, 128, 240,   0, }, //glyph '2' code=17
    { 4, 224,  16,  96,  16, 224,   0, }, //glyph '3' code=18
    { 4, 144, 144, 240,  16,  16,   0, }, //glyph '4' code=19
    { 4, 240, 128, 224,  16, 224,   0, }, //glyph '5' code=20
    { 4,  96, 128, 224, 144,  96,   0, }, //glyph '6' code=21
    { 4, 240,  16,  32,  64,  64,   0, }, //glyph '7' code=22
    { 4,  96, 144,  96, 144,  96,   0, }, //glyph '8' code=23
    { 4,  96, 144, 112,  16,  96,   0, }, //glyph '9' code=24
    { 1,   0, 128,   0, 128,   0,   0, }, //glyph ':' code=25
    { 2,   0, 128,   0,   0, 128,  64, }, //glyph ';' code=26
    { 3,  32,  64, 128,  64,  32,   0, }, //glyph '<' code=27
    { 3,   0, 224,   0, 224,   0,   0, }, //glyph '=' code=28
    { 3, 128,  64,  32,  64, 128,   0, }, //glyph '>' code=29
    { 4, 224,  16,  96,   0,  64,   0, }, //glyph '?' code=30
    { 4,  96, 144, 176, 128, 112,   0, }, //glyph '@' code=31
    { 4,  96, 144, 240, 144, 144,   0, }, //glyph 'A' code=32
    { 4, 224, 144, 224, 144, 224,   0, }, //glyph 'B' code=33
    { 4, 112, 128, 128, 128, 112,   0, }, //glyph 'C' code=34
    { 4, 224, 144, 144, 144, 224,   0, }, //glyph 'D' code=35
    { 4, 240, 128, 224, 128, 240,   0, }, //glyph 'E' code=36
    { 4, 240, 128, 224, 128, 128,   0, }, //glyph 'F' code=37
    { 4, 112, 128, 176, 144, 112,   0, }, //glyph 'G' code=38
    { 4, 144, 144, 240, 144, 144,   0, }, //glyph 'H' code=39
    { 3, 224,  64,  64,  64, 224,   0, }, //glyph 'I' code=40
    { 4, 240,  16,  16, 144,  96,   0, }, //glyph 'J' code=41
    { 4, 144, 160, 192, 160, 144,   0, }, //glyph 'K' code=42
    { 4, 128, 128, 128, 128, 240,   0, }, //glyph 'L' code=43
    { 5, 136, 216, 168, 136, 136,   0, }, //glyph 'M' code=44
    { 4, 144, 208, 176, 144, 144,   0, }, //glyph 'N' code=45
    { 4,  96, 144, 144, 144,  96,   0, }, //glyph 'O' code=46
    { 4, 224, 144, 224, 128, 128,   0, }, //glyph 'P' code=47
    { 4,  96, 144, 144, 144,  96,  16, }, //glyph 'Q' code=48
    { 4, 224, 144, 224, 160, 144,   0, }, //glyph 'R' code=49
    { 4, 112, 128,  96,  16, 224,   0, }, //glyph 'S' code=50
    { 3, 224,  64,  64,  64,  64,   0, }, //glyph 'T' code=51
    { 4, 144, 144, 144, 144,  96,   0, }, //glyph 'U' code=52
    { 3, 160, 160, 160, 160,  64,   0, }, //glyph 'V' code=53
    { 5, 136, 168, 168, 168,  80,   0, }, //glyph 'W' code=54
    { 4, 144, 144,  96, 144, 144,   0, }, //glyph 'X' code=55
    { 3, 160, 160,  64,  64,  64,   0, }, //glyph 'Y' code=56
    { 4, 240,  16,  96, 128, 240,   0, }, //glyph 'Z' code=57
    { 2, 192, 128, 128, 128, 192,   0, }, //glyph '[' code=58
    { 5, 128,  64,  32,  16,   8,   0, }, //glyph '\' code=59
    { 2, 192,  64,  64,  64, 192,   0, }, //glyph ']' code=60
    { 5,  32,  80, 136,   0,   0,   0, }, //glyph '^' code=61
    { 4,   0,   0,   0,   0, 240,   0, }, //glyph '_' code=62
    { 2, 128,  64,   0,   0,   0,   0, }, //glyph '`' code=63
    { 3,   0, 224,  32, 224, 224,   0, }, //glyph 'a' code=64
    { 3, 128, 224, 160, 160, 224,   0, }, //glyph 'b' code=65
    { 3,   0, 224, 128, 128, 224,   0, }, //glyph 'c' code=66
    { 3,  32, 224, 160, 160, 224,   0, }, //glyph 'd' code=67
    { 3,   0, 224, 224, 128, 224,   0, }, //glyph 'e' code=68
    { 2,  64, 128, 192, 128, 128,   0, }, //glyph 'f' code=69
    { 3,   0, 224, 160, 224,  32, 224, }, //glyph 'g' code=70
    { 3, 128, 224, 160, 160, 160,   0, }, //glyph 'h' code=71
    { 1, 128,   0,   128, 128, 128, 0, }, //glyph 'i' code=72
    { 2,   0, 192,  64,  64,  64, 128, }, //glyph 'j' code=73
    { 3, 128, 160, 192, 160, 160,   0, }, //glyph 'k' code=74
    { 1, 128, 128, 128, 128, 128,   0, }, //glyph 'l' code=75
    { 5,   0, 248, 168, 168, 168,   0, }, //glyph 'm' code=76
    { 3,   0, 224, 160, 160, 160,   0, }, //glyph 'n' code=77
    { 3,   0, 224, 160, 160, 224,   0, }, //glyph 'o' code=78
    { 3,   0, 224, 160, 160, 224, 128, }, //glyph 'p' code=79
    { 3,   0, 224, 160, 160, 224,  32, }, //glyph 'q' code=80
    { 3,   0, 224, 128, 128, 128,   0, }, //glyph 'r' code=81
    { 2,   0, 192, 128,  64, 192,   0, }, //glyph 's' code=82
    { 3,  64, 224,  64,  64,  64,   0, }, //glyph 't' code=83
    { 3,   0, 160, 160, 160, 224,   0, }, //glyph 'u' code=84
    { 3,   0, 160, 160, 160,  64,   0, }, //glyph 'v' code=85
    { 5,   0, 168, 168, 168,  80,   0, }, //glyph 'w' code=86
    { 3,   0, 160,  64, 160, 160,   0, }, //glyph 'x' code=87
    { 3,   0, 160, 160, 224,  32, 224, }, //glyph 'y' code=88
    { 2,   0, 192,  64, 128, 192,   0, }, //glyph 'z' code=89
    { 3,  96,  64, 192,  64,  96,   0, }, //glyph '{' code=90
    { 1, 128, 128, 128, 128, 128,   0, }, //glyph '|' code=91
    { 3, 192,  64,  96,  64, 192,   0, }, //glyph '}' code=92
    { 3,  96, 192,   0,   0,   0,   0, }, //glyph '~' code=93
    { 4,  48,  64, 224,  64, 240,   0, }, //glyph '£' code=94
    };
    VGAX vga;

    void setup() {
      static const char str0[] PROGMEM="VGAX Hello World!";
      vga.begin();
      vga.clear(11);
      vga.printPROGMEM((byte*)fnt_ufont_data, FNT_UFONT_SYMBOLS_COUNT, FNT_UFONT_HEIGHT, 3, 1, str0, 10, 10, 1);
    }
    void loop() {
    }


### 2bitimage

![2bitimage](docs/2bitimage.png)

To convert an image to the VGAX format (2bit per pixel) i wrote a simple webapp that reads an image and create a C/C++ source file to be used with VGAX.

The image that you can use as a source must use only the colours that you are generating with your hardware. For example if you use the red and green pins, you must convert your image using another tool so your image should only use these four colors: red, green, yellow and black. 2bitimage packs them in the 2bit format used by VGAX but not perform any color convertion.

The source file of the webapp is inside the tools directory. You can open 2bitimage.html with your webbrowser and run it locally. I use Google Chrome, dunno if works with other webbrowsers.

### 2bitfont

![2bitfont](docs/2bitfont.png)

With 2bitfont you can create your fonts from a single image and convert them to be used with VGAX library. The tool reads an image that contains all font's glyphs are separated from a vertical blank line. All glyphs are extracted and converted to a C/C++ source file.

2bitfont is a webapp, like 2bitimage, that can run locally on your webbrowser.
    
## FAQ

  (1 mean A0, 2 mean A1, 4 mean A3, 8 mean A4 and so on)
- How can i prevent screen flickering? At this time there is no one mechanism to prevent the flickering. The right way to prevent flicker is to use a double (frame)buffer but there isn't enought free memory to do that.

