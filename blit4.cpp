#include "MDAX.h"

void MDAX::blit4aligned(byte *src, byte sheight, byte dbx, byte dy) {
  byte *sptr=src;
  byte *dptr=(byte*)mdaxfb+MDAX_BWIDTH*dy+dbx;
  while (sheight--) {
    *dptr=pgm_read_byte(sptr++);
    dptr+=MDAX_BWIDTH;
  }
}
void MDAX::blit4(byte *src, byte sheight, char dx, char dy) {
  byte *sptr=src;
  if (dy<0) {
    if (dy<-4)
      return;
    sheight+=dy;
    sptr+=(-dy)*2;
    dy=0;
  }
  if (dy>=MDAX_HEIGHT)
    return;
  char yout=dy+sheight-MDAX_HEIGHT;
  if (yout>0)
    sheight-=yout;
  byte *dptr=(byte*)mdaxfb+MDAX_BWIDTH*dy+(dx>>2);
  if (dx<0) {
    if (dx<=-4)
      return;
    switch (dx & 3) {
    case 1:
      //3 pixels unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        dptr[1]&=0x3f;
        dptr[1]|=b0<<6;
        dptr+=MDAX_BWIDTH;
      }
      break;
    case 2:
      //2 pixels unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        dptr[1]&=0x0f;
        dptr[1]|=b0<<4;
        dptr+=MDAX_BWIDTH;
      }
      break;
    case 3:
      //1 pixel unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        dptr[1]&=0x03;
        dptr[1]|=b0<<2;
        dptr+=MDAX_BWIDTH;
      }
      break;
    }
  } else if (dx>MDAX_WIDTH-4) {
    if (dx>=MDAX_WIDTH)
      return;
    switch (dx & 3) {
    case 1:
      //3 pixels unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        dptr[0]&=0xc0;
        dptr[0]|=b0>>2;
        dptr+=MDAX_BWIDTH;
      }
      break;
    case 2:
      //2 pixels unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        dptr[0]&=0xf0;
        dptr[0]|=b0>>4;
        dptr+=MDAX_BWIDTH;
      }
      break;
    case 3:
      //1 pixel unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        dptr[0]&=0xfc;
        dptr[0]|=b0>>6;
        dptr+=MDAX_BWIDTH;
      }
      break;
    }
  } else {
    switch (dx & 3) {
    case 1:
      //3 pixels unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        dptr[0]&=0xc0;
        dptr[0]|=b0>>2;
        dptr[1]&=0x3f;
        dptr[1]|=b0<<6;
        dptr+=MDAX_BWIDTH;
      }
      break;
    case 2:
      //2 pixels unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        dptr[0]&=0xf0;
        dptr[0]|=b0>>4;
        dptr[1]&=0x0f;
        dptr[1]|=b0<<4;
        dptr+=MDAX_BWIDTH;
      }
      break;
    case 3:
      //1 pixel unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        dptr[0]&=0xfc;
        dptr[0]|=b0>>6;
        dptr[1]&=0x03;
        dptr[1]|=b0<<2;
        dptr+=MDAX_BWIDTH;
      }
      break;
    case 0:
      //0 pixel unaligned. blit is byte aligned!
      while (sheight--) {
        *dptr=pgm_read_byte(sptr++);
        dptr+=MDAX_BWIDTH;
      }
      break;
    }
  }
}
