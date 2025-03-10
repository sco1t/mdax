/*
based on the smaffer, Sandro Maffiodo VGAx code that was
based on the "VGA color video generation" by Nick Gammon:
  http://www.gammon.com.au/forum/?id=11608.
inspired from the work of Peten Paja:
  http://petenpaja.blogspot.fi/2013/11/toorums-quest-ii-retro-video-game.html
AVR interrupt dejitter from Charles CNLOHR:
  https://github.com/cnlohr/avrcraft/tree/master/terminal

HERE you can find some inline documentation about the MDAX library class 
*/
#ifndef __MDAX_library__
#define __MDAX_library__

#define MDA_VERSION "1.0.0"

#ifdef ARDUINO
#include <Arduino.h>
#endif
#include <avr/pgmspace.h>

//uncomment ATMEGA2560_HIGHRES to use 120x90px 80px? squared pixels
//#define ATMEGA2560_HIGHRES 

//uncomment ATMEGA2560_MAXRES to use 120x240px rectangular pixels
//#define ATMEGA2560_MAXRES

#if defined(__AVR_ATmega2560__) && defined(ATMEGA2560_MAXRES)
  #define MDAX_HEIGHT 240 //number of lines
#elif defined(__AVR_ATmega2560__) && defined(ATMEGA2560_HIGHRES)
  #define MDAX_HEIGHT 80 //number of lines
#else
  #define MDAX_HEIGHT 60 //number of lines
#endif
#define MDAX_BWIDTH 30 //number of bytes in a row
#define MDAX_WIDTH (MDAX_BWIDTH*4) //number of pixels in a row
#define MDAX_BSIZE (MDAX_BWIDTH*MDAX_HEIGHT) //size of framebuffer in bytes
#define MDAX_SIZE (MDAX_WIDTH*MDAX_HEIGHT) //size of framebuffer in pixels

//framebuffer. if you want you can write directly to this array. its safe
extern byte mdaxfb[MDAX_HEIGHT*MDAX_BWIDTH];

//clock replacement. this is increment in the VSYNC interrupt, so run at 50Hz
extern unsigned long vtimer;

//MDAX class. This is a static class. Multiple instances will not work
class MDAX {
public:
  /*
   * begin()
   * end()
   *    NOTES: begin() method reconfigure TIMER0 TIMER1 and TIMER2.
   *    If you need to shutdown this library, you need to call end() and
   *    reconfigure all the three timers by yourself. The lib will not
   *    restore the previous timers configuration
   */
  static void begin(bool enableTone=true);
  static void end();
  /*
   * putpixel(x, y, color)
   *    x: horizontal pixel coordinate. Must be less than MDAX_WIDTH
   *    y: vertical pixel coordinate. Must be less than MDAX_HEIGHT
   *    color: 2bit color. you must use only these values: 0 1 2 3
   */
  static inline void putpixel(byte x, byte y, byte color) {
    byte *p = mdaxfb + y*MDAX_BWIDTH + (x>>2);
    byte bitpos=6-(x & 3)*2;
    *p=(*p & ~(3 <<bitpos)) | color <<bitpos;
  }
  /*
   * getpixel(x, y)
   *    x: horizontal pixel coordinate. Must be less than MDAX_WIDTH
   *    y: vertical pixel coordinate. Must be less than MDAX_HEIGHT
   *    return: 2bit color at <x,y> coordinate
   */
  static inline byte getpixel(byte x, byte y) {
    byte p=mdaxfb[y*MDAX_BWIDTH + (x>>2)], bitpos=6-(x & 3)*2;
    return (p >> bitpos) & 3;
  }
  /*
   * putpixel4(B, y, color)
   *    bx: horizontal BYTE coordinate. Must be less than MDAX_BWIDTH
   *    y: vertical pixel coordinate. Must be less than MDAX_HEIGHT
   *    fourpixels: four 2bit pixels in a byte.
   *      The four pixels must be packed in this order: highest 2bit of the byte
   *      are the first, left-most, pixel:
   *                      +---+---+---+---+---+---+---+---+
   *      highest bit --> | 1 | 1 | 2 | 2 | 3 | 3 | 4 | 4 | <-- lowest bit
   *                      +---+---+---+---+---+---+---+---+
   *      For example, if you want to set the first pixel (the left-most pixel)
   *      to 3 and the fourth pixel (right-most) to 1:
   *                      +---+---+---+---+---+---+---+---+
   *      highest bit --> | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 1 | <-- lowest bit
   *                      +---+---+---+---+---+---+---+---+
   *      This byte is 193 in decimal and 0xC1 in hexadecimal
   */
  static inline void putpixel4(byte bx, byte y, byte fourpixels) {
    mdaxfb[y*MDAX_BWIDTH + bx]=fourpixels;
  }
  /*
   * getpixel4(bx, y)
   *    bx: horizontal BYTE coordinate. Must be less than MDAX_BWIDTH
   *    y: vertical pixel coordinate. Must be less than MDAX_HEIGHT
   *    return: four 2bit pixels packed in a byte
   */
  static inline byte getpixel4(byte bx, byte y) {
    return mdaxfb[y*MDAX_BWIDTH + bx];
  }
  /*
   * clear(color)
   *    color: 2bit color to clear the framebuffer
   */
  static void clear(byte color);
  /*
   * copy(src)
   *    src: source data. src size must be equal to framebuffer
   */
  static void copy(byte *src);
  /*
   * bitblit(src, swidth, sheight, dx, dy, color)
   *    src: source data. each byte hold 8 pixels. higher bit (0b10000000) will
   *      be blitted first. Bits set as 1 are opaque, 0 are transparent
   *    swidth: source width in pixels. This is the number of horizontal bits
   *      to be blitted and can be not a multiple of 8
   *    sheight: source height in pixels
   *    dx: destination x coordinate in pixels. supported range: -127,+127
   *    dy: destination y coordinate in pixels. supported range: -127,+127
   *    color: 2bit color use for opaque pixels (with bits set to 1)
   */
  static void bitblit(byte *src, byte swidth, byte sheight, char dx, char dy,
                byte color);
  /*
   * blit(src, sx, sy, swidth, sheight, dx, dy)
   *    src: source data
   *    swidth: source width in pixels
   *    sheight: source height in pixels
   *    dx: destination x coordinate in pixels. supported range: -127,+127
   *    dy: destination y coordinate in pixels. supported range: -127,+127
   *
   * blit[N] versions are optimized for swidth=[N] cases
   */
  static void blit(byte *src, byte swidth, byte sheight, char dx, char dy);
  static void blit4(byte *src, byte sheight, char dx, char dy);
  static void blit8(byte *src, byte sheight, char dx, char dy);
  /*
   * blitwmask(src, mask, sx, sy, swidth, sheight, dx, dy)
   *    src: source data. transparent pixels must be set to 0
   *    mask: source mask. pixel format is the same as src (2bit per pixel).
   *      value of 3 mean transparent pixel, value 0 mean opaque
   *    swidth: source width in pixels
   *    sheight: source height in pixels
   *    dx: destination x coordinate in pixels. supported range: -127,+127
   *    dy: destination y coordinate in pixels. supported range: -127,+127
   *
   * Masked blit is implemented using AND+OR raster operation, like described
   * here: http://en.wikipedia.org/wiki/Bit_blit
   *
   * blit[N]wmask versions are optimized for swidth=[N] cases
   */
  static void blitwmask(byte *src, byte *mask, byte swidth, byte sheight,
                char dx, char dy);
  static void blit8wmask(byte *src, byte *mask, byte sheight, char dx, char dy);
  /*
   * blit[N]aligned(src, sheight, dbx, dy)
   *    src: source data
   *    sheight: source height in pixels
   *    dbx: destination x coordinate in BYTES. supported range: 0,MDAX_BWIDTH
   *    dy: destination y coordinate in pixels. supported range: 0,MDAX_HEIGHT
   *
   * These methods does not perform any clipping. coordinates must point inside
   * framebuffer
   */
  static void blit4aligned(byte *src, byte sheight, byte dbx, byte dy);
  static void blit8aligned(byte *src, byte sheight, byte dbx, byte dy);
  /*
   * fillrect(x, y, width, height, color)
   *    x: destination x coordinate in pixels
   *    y: destination y coordinate in pixels
   *    width: width of the rect in pixels
   *    height: height of the rect in pixels
   *    color: color of the rect
   */
  static void fillrect(byte x, byte y, byte width, byte height, byte color);
  /*
   * print(fnt, glyphscount, fntheight, hspace, vspace, str, dx, dy, color)
   *    fnt: font definition, generated from 2BITFONT tool
   *    glyphscount: number of symbols inside font definition (generated from
   *      2BITFONT tool)
   *    fntheight: font height (generated from 2BITFONT tool)
   *    hspace: horizontal space between each printed symbol
   *    vspace: vertical space between each printed symbol
   *    str: string to be printed. The string is readed from PROGMEM (FLASH)
   *    dx: destination x coordinate in pixels
   *    dy: destination y coordinate in pixels
   *    color: color of the text
   */
  static void printPROGMEM(byte *fnt, byte glyphscount, byte fntheight, 
                byte hspace, byte vspace, const char *str, char dx, char dy, 
                byte color);
  /*
   * printSRAM(...)
   *    same as printPROGMEM but read from SRAM
   */
  static void printSRAM(byte *fnt, byte glyphscount, byte fntheight, 
                byte hspace, byte vspace, const char *str, char dx, char dy, 
                byte color);
  /*
   * delay(msec)
   *    msec: number of milliseconds to wait
   */
  static void delay(int msec);

 


  /*
   * millis()
   *    return the number of milliseconds ellapsed
  
  static inline unsigned long millis() {
    return vtimer*16;
  }
  
   * micros()
   *    return the number of microseconds ellapsed  
  
  static inline unsigned long micros() {
    return vtimer*16000;
  }

 */

};
#endif

