#include "MDAX.h"

void MDAX::blit(byte *src, byte swidth, byte sheight, char dx, char dy) {
  byte sh=sheight;
  byte *srcline=src;
  byte slinesize=swidth>>2;
  if (swidth & 3)
      slinesize++;
  if (dx>-1 && dx+swidth<=MDAX_WIDTH && dy>-1 && dy+sheight<=MDAX_HEIGHT) {
    //inside screen. no clipping
    while (sh--) {
      byte sw=swidth, sx=0;
      char ldx=dx;
      while (sw--) {
        //get sprite pixel
        byte p=pgm_read_byte(srcline + (sx>>2));
        byte bitpos=6-(sx & 3)*2;
        byte spixel=(p >> bitpos);
        //set framebuffer pixel
        putpixel(ldx, dy, spixel);
        sx++;
        ldx++;
      }
      srcline+=slinesize;
      dy++;
    }
  } else {
    //partially clipped out of screen
    while (sh--) {
      if (dy>-1 && dy<MDAX_HEIGHT) {
        byte sw=swidth, sx=0;
        char ldx=dx;
        while (sw--) {
          if (ldx>-1 && ldx<MDAX_WIDTH) {
            //get sprite pixel
            byte p=pgm_read_byte(srcline + (sx>>2));
            byte bitpos=6-(sx & 3)*2;
            byte spixel=(p >> bitpos) & 3;
            //set framebuffer pixel
            putpixel(ldx, dy, spixel);
          }
          sx++;
          ldx++;
        }
      }
      srcline+=slinesize;
      dy++;
    }
  }
}
void MDAX::blitwmask(byte *src, byte *mask, byte swidth, byte sheight, char dx, char dy) {
  byte sh=sheight;
  byte *srcline=src;
  byte *maskline=mask;
  byte linesize=swidth>>2;
  if (swidth & 3)
      linesize++;
  while (sh--) {
    if (dy>-1 && dy<MDAX_HEIGHT) {
      byte sw=swidth, sx=0;
      char ldx=dx;
      while (sw--) {
        if (ldx>-1 && ldx<MDAX_WIDTH) {
          //get mask bit
          byte m=pgm_read_byte(maskline + (sx>>2));
          byte p=pgm_read_byte(srcline  + (sx>>2));
          //get sprite pixel and mask
          byte sbitpos=6-(sx & 3)*2;
          byte spixel=(p >> sbitpos) & 3;
          byte mpixel=(m >> sbitpos) & 3;
          //set framebuffer pixel with AND+OR blit
          byte *pfb=mdaxfb + dy*MDAX_BWIDTH + (ldx>>2);
          byte dbitpos=6-(ldx & 3)*2;
          *pfb &=(mpixel << dbitpos) | ~(3<<dbitpos);
          *pfb |=(spixel << dbitpos);
        }
        sx++;
        ldx++;
      }
    }
    srcline +=linesize;
    maskline+=linesize;
    dy++;
  }
}
