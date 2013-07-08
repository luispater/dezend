#ifndef GD_H
#define GD_H 1

/* gd.h: declarations file for the gifdraw module.

	Written by Tom Boutell, 5/94.
	Copyright 1994, Cold Spring Harbor Labs.
	Permission granted to use this code in any fashion provided
	that this notice is retained and any alterations are
	labeled as such. It is requested, but not required, that
	you share extensions to this module with us so that we
	can incorporate them into new versions. */

/* stdio is needed for file I/O. */
#include <stdio.h>

/* This can't be changed, it's part of the GIF specification. */

#define gdMaxColors 256

/* structure to contain globals and static vars */

#define        MAX_LWZ_BITS            12

struct gdImageGlobals{
	/* real globals */
	 int Width, Height;
	 int curx, cury;
	 long CountDown;
	 int Pass;
	 int Interlace;
	 int rl_pixel;
	 int rl_basecode;
	 int rl_count;
	 int rl_table_pixel;
	 int rl_table_max;
	 int just_cleared;
	 int out_bits;
	 int out_bits_init;
	 int out_count;
	 int out_bump;
	 int out_bump_init;
	 int out_clear;
	 int out_clear_init;
	 int max_ocodes;
	 int code_clear;
	 int code_eof;
	 unsigned int obuf;
	 int obits;
	 FILE *ofile;
	 unsigned char oblock[256];
	 int oblen;

	 int a_count;
	 char accum[ 256 ];
	int ZeroDataBlock;
	struct {
       int     transparent;
       int     delayTime;
       int     inputFlag;
       int     disposal;
	} Gif89;

	/* static vars in functions */
	 /* binformat() */
	 char bufs[8][64];
	 int bhand;

	/* DoExtension */
	unsigned char     DoExtension_buf[256];

	/* GetCode_ */
	unsigned char    GetCode_buf[280];
	int              curbit, lastbit, done, last_byte;

	/* LWZReadByte */
	int      fresh;
	int      code_size, set_code_size;
	int      max_code, max_code_size;
	int      firstcode, oldcode;
	int      clear_code, end_code;
	int      table[2][(1<< MAX_LWZ_BITS)];
	int      stack[(1<<(MAX_LWZ_BITS))*2], *sp;
};

/* Image type. See functions below; you will not need to change
	the elements directly. Use the provided macros to
	access sx, sy, the color table, and colorsTotal for 
	read-only purposes. */

typedef struct gdImageStruct {
	unsigned char ** pixels;
	int sx;
	int sy;
	int colorsTotal;
	int red[gdMaxColors];
	int green[gdMaxColors];
	int blue[gdMaxColors]; 
	int open[gdMaxColors];
	int transparent;
	int *polyInts;
	int polyAllocated;
	struct gdImageStruct *brush;
	struct gdImageStruct *tile;	
	int brushColorMap[gdMaxColors];
	int tileColorMap[gdMaxColors];
	int styleLength;
	int stylePos;
	int *style;
	int interlace;

	/* add the globals here, now we don't have to change api at all*/
	struct gdImageGlobals globals;
} gdImage;

typedef gdImage * gdImagePtr;

typedef struct {
	/* # of characters in font */
	int nchars;
	/* First character is numbered... (usually 32 = space) */
	int offset;
	/* Character width and height */
	int w;
	int h;
	/* Font data; array of characters, one row after another.
		Easily included in code, also easily loaded from
		data files. */
	char *data;
} gdFont;

/* Text functions take these. */
typedef gdFont *gdFontPtr;

/* For backwards compatibility only. Use gdImageSetStyle()
	for MUCH more flexible line drawing. Also see
	gdImageSetBrush(). */
#define gdDashSize 4

/* Special colors. */

#define gdStyled (-2)
#define gdBrushed (-3)
#define gdStyledBrushed (-4)
#define gdTiled (-5)

/* NOT the same as the transparent color index.
	This is used in line styles only. */
#define gdTransparent (-6)

/* Functions to manipulate images. */

gdImagePtr gdImageCreate(int sx, int sy);
gdImagePtr gdImageCreateFromGif(FILE *fd);
gdImagePtr gdImageCreateFromGd(FILE *in);
gdImagePtr gdImageCreateFromXbm(FILE *fd);
void gdImageDestroy(gdImagePtr im);
void gdImageSetPixel(gdImagePtr im, int x, int y, int color);
int gdImageGetPixel(gdImagePtr im, int x, int y);
void gdImageLine(gdImagePtr im, int x1, int y1, int x2, int y2, int color);
/* For backwards compatibility only. Use gdImageSetStyle()
	for much more flexible line drawing. */
void gdImageDashedLine(gdImagePtr im, int x1, int y1, int x2, int y2, int color);
/* Corners specified (not width and height). Upper left first, lower right
 	second. */
void gdImageRectangle(gdImagePtr im, int x1, int y1, int x2, int y2, int color);
/* Solid bar. Upper left corner first, lower right corner second. */
void gdImageFilledRectangle(gdImagePtr im, int x1, int y1, int x2, int y2, int color);
int gdImageBoundsSafe(gdImagePtr im, int x, int y);
void gdImageChar(gdImagePtr im, gdFontPtr f, int x, int y, int c, int color);
void gdImageCharUp(gdImagePtr im, gdFontPtr f, int x, int y, int c, int color);
void gdImageString(gdImagePtr im, gdFontPtr f, int x, int y, unsigned char *s, int color);
void gdImageStringUp(gdImagePtr im, gdFontPtr f, int x, int y, unsigned char *s, int color);
void gdImageString16(gdImagePtr im, gdFontPtr f, int x, int y, unsigned short *s, int color);
void gdImageStringUp16(gdImagePtr im, gdFontPtr f, int x, int y, unsigned short *s, int color);

/* Point type for use in polygon drawing. */

typedef struct {
	int x, y;
} gdPoint, *gdPointPtr;

void gdImagePolygon(gdImagePtr im, gdPointPtr p, int n, int c);
void gdImageFilledPolygon(gdImagePtr im, gdPointPtr p, int n, int c);

int gdImageColorAllocate(gdImagePtr im, int r, int g, int b);
int gdImageColorClosest(gdImagePtr im, int r, int g, int b);
int gdImageColorExact(gdImagePtr im, int r, int g, int b);
void gdImageColorDeallocate(gdImagePtr im, int color);
void gdImageColorTransparent(gdImagePtr im, int color);
void gdImageGif(gdImagePtr im, FILE *out);
void gdImageGd(gdImagePtr im, FILE *out);
void gdImageArc(gdImagePtr im, int cx, int cy, int w, int h, int s, int e, int color);
void gdImageFillToBorder(gdImagePtr im, int x, int y, int border, int color);
void gdImageFill(gdImagePtr im, int x, int y, int color);
void gdImageCopy(gdImagePtr dst, gdImagePtr src, int dstX, int dstY, int srcX, int srcY, int w, int h);
/* Stretches or shrinks to fit, as needed */
void gdImageCopyResized(gdImagePtr dst, gdImagePtr src, int dstX, int dstY, int srcX, int srcY, int dstW, int dstH, int srcW, int srcH);
void gdImageSetBrush(gdImagePtr im, gdImagePtr brush);
void gdImageSetTile(gdImagePtr im, gdImagePtr tile);
void gdImageSetStyle(gdImagePtr im, int *style, int noOfPixels);
/* On or off (1 or 0) */
void gdImageInterlace(gdImagePtr im, int interlaceArg);

/* Macros to access information about images. READ ONLY. Changing
	these values will NOT have the desired result. */
#define gdImageSX(im) ((im)->sx)
#define gdImageSY(im) ((im)->sy)
#define gdImageColorsTotal(im) ((im)->colorsTotal)
#define gdImageRed(im, c) ((im)->red[(c)])
#define gdImageGreen(im, c) ((im)->green[(c)])
#define gdImageBlue(im, c) ((im)->blue[(c)])
#define gdImageGetTransparent(im) ((im)->transparent)
#define gdImageGetInterlaced(im) ((im)->interlace)
#endif
