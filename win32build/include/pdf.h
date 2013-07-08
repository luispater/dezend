/* pdf.h
 * Copyright (C) 1997-98 Thomas Merz. All rights reserved.
 *
 * PDFlib public declarations and definitions
 */

#ifndef PDF_H
#define PDF_H

#include <stdio.h>
#include <stdarg.h>

#include "p_port.h"

#ifdef USE_TIFF
#include "tiffio.h"
#endif

#define PDFLIB_VERSION	"PDFlib V0.6 (C) Thomas Merz 1997-98"

/* default path to font and AFM directory */
#ifndef PDF_DEFAULT_FONT_PATH
#define PDF_DEFAULT_FONT_PATH	"./fonts"
#endif

/* Data types and defines */

typedef unsigned char byte;

#define false	0
#define true	1

/* Error and warning levels */
#define PDF_INFO	1
#define PDF_WARN	2
#define PDF_FATAL	3
#define PDF_INTERNAL	4

/* PDF version compatiblity modes */
typedef enum { PDF1_0, PDF1_1, PDF1_2 } PDF_compat_mode;

typedef enum {
    builtin, pdfdoc, macroman, macexpert, winansi, encoding_count
} PDF_encoding;

typedef char *PDF_encodingvector[256];

typedef enum {
    none, lzw, runlength, ccitt, dct, flate, compression_count
} PDF_compression;

typedef enum {
    trans_none, trans_split, trans_blinds, trans_box, 
    trans_wipe, trans_dissolve, trans_glitter, trans_replace,
    transition_count
} PDF_transition;

typedef enum {
    DeviceGray, DeviceRGB, DeviceCMYK, 
    CalGray, CalRGB, Lab, 
    Indexed, Pattern, Separation,
    colorspace_count
} PDF_colorspace;

typedef byte pdf_colormap[256][3];

typedef struct PDF_s PDF;

typedef struct {
    float width, height;
} PDF_pagesize;

/* Predefine some useful paper formats */
extern PDF_pagesize
a0, a1, a2, a3, a4, a5, a6, b5, letter, legal, ledger, p11x17;

typedef struct {
	/* general stuff */
	bool		binary_mode;
	PDF_compat_mode	required_compatibility;
	void
	    (*error_handler)(int level, const char* fmt, va_list ap);

	/* PDF Info dictionary entries */
	char		*Keywords;
	char		*Subject;
	char		*ModDate;
	char		*Title;
	char		*CreationDate;
	char		*Creator;
	const char	*Producer;
	char		*Author;

	/* path to font directory */
	char		*fontpath;
} PDF_info;

typedef struct { float a, b, c, d, e, f; } PDF_matrix;

/* not currently used */
/* typedef struct { float x, y; } PDF_point; */

typedef struct PDF_data_source_s PDF_data_source;

struct PDF_data_source_s {
    byte 		*next_byte;
    size_t		bytes_available;
    void		(*init)(PDF *, PDF_data_source *src);
    bool		(*fill)(PDF *, PDF_data_source *src);
    void		(*terminate)(PDF *, PDF_data_source *src);

    byte		*buffer_start;
    size_t		buffer_length;
    byte		*private_data;
};

struct PDF_image_t;

typedef struct PDF_image_t {
    FILE		*fp;		/* image file pointer */
    char		*filename;	/* image file name */
    unsigned int	width;		/* image width in pixels */
    unsigned int	height;		/* image height in pixels */
    int			bpc;		/* bits per color component */
    unsigned int	components;	/* number of color components */
    PDF_compression	compression;	/* image compression type */
    PDF_colorspace	colorspace;	/* image color space */
    bool		indexed; /* image contains colormap (palette) */

    unsigned int	BitPixel;	/* HACK: use bpc instead */
    pdf_colormap 	colormap;

    /* JPEG specific stuff */
    bool		adobe;		/* JPEG image with Adobe marker */
    long		startpos;	/* start of image data in file */
    float    		dpi;		/* image resolution in dots per inch */

#ifdef USE_TIFF
    /* TIFF specific stuff */
    TIFF		*tif;		/* pointer to TIFF data structure */
    uint32		*raster;	/* frame buffer */
    int			cur_line;	/* current image line */
#endif

    /* GIF specific stuff */
    /*unsigned int	ColorResolution;*/
    unsigned int	Background;
    /*unsigned int	AspectRatio;*/

    int			transparent;
    int			delayTime;
    int			inputFlag;
    int			disposal;

    int			useGlobalColormap;
    unsigned int	bitPixel;

    bool		interlace;
    int			imageno;

    int			no;		/* PDF image number */
    PDF_data_source	src;
    void		(*closefunc)(PDF *p, struct PDF_image_t *image);
} PDF_image;

/* 
 * ----------------------------------------
 * Method prototypes, sorted by source file
 * ----------------------------------------
 */

/* p_basic.c */
PDF_info *PDF_get_info(void);
PDF *PDF_open(FILE *fp, PDF_info *info);
void PDF_close(PDF *p);
void PDF_begin_page(PDF *p, float height, float width);
void PDF_end_page(PDF *p);
void PDF_set_transition(PDF *p, PDF_transition t);
void PDF_set_duration(PDF *p, float t);
void *PDF_malloc(size_t size, char *caller);
void PDF_free(void *mem);

/* p_text.c */
void PDF_show(PDF *p, char *text);
void PDF_show_xy(PDF *p, char *text, float x, float y);
void PDF_set_font(PDF *p, char *fontname, float fontsize, PDF_encoding enc);
void PDF_set_leading(PDF *p, float l);
void PDF_set_text_rise(PDF *p, float rise);
void PDF_set_horiz_scaling(PDF *p, float scale);
void PDF_set_text_rendering(PDF *p, byte mode);
void PDF_set_text_matrix(PDF *p, PDF_matrix m);
void PDF_set_text_pos(PDF *p, float x, float y);
void PDF_set_char_spacing(PDF *p, float spacing);
void PDF_set_word_spacing(PDF *p, float spacing);
void PDF_continue_text(PDF *p, char *text);

/* p_gstate.c */
void PDF_save(PDF *p);
void PDF_restore(PDF *p);
void PDF_translate(PDF *p, float tx, float ty);
void PDF_scale(PDF *p, float sx, float sy);
void PDF_rotate(PDF *p, float phi);

void PDF_setdash(PDF *p, float d1, float d2);
void PDF_setpolydash(PDF *p, float *darray, int length);
void PDF_setflat(PDF *p, float flat);
void PDF_setlinejoin(PDF *p, byte join);
void PDF_setlinecap(PDF *p, byte cap);
void PDF_setmiterlimit(PDF *p, float miter);
void PDF_setlinewidth(PDF *p, float width);

/* p_color.c */
/* do not use color operators within path objects */
void PDF_setgray_fill(PDF *p, float g);
void PDF_setgray_stroke(PDF *p, float g);
void PDF_setgray(PDF *p, float g);
void PDF_setrgbcolor_fill(PDF *p, float red, float green, float blue);
void PDF_setrgbcolor_stroke(PDF *p, float red, float green, float blue);
void PDF_setrgbcolor(PDF *p, float red, float green, float blue);

/* p_draw.c */
void PDF_moveto(PDF *p, float x, float y);
void PDF_lineto(PDF *p, float x, float y);
void PDF_curveto(PDF *p, float x1, float y1, float x2, float y2, float x3, float y3);
void PDF_circle(PDF *p, float x, float y, float r);
void PDF_arc(PDF *p, float x, float y, float r, float alpha1, float alpha2);
void PDF_rect(PDF *p, float x, float y, float width, float height);
void PDF_closepath(PDF *p);

void PDF_stroke(PDF *p);
void PDF_closepath_stroke(PDF *p);
void PDF_fill(PDF *p);
void PDF_fill_stroke(PDF *p);
void PDF_closepath_fill_stroke(PDF *p);
void PDF_endpath(PDF *p);

void PDF_clip(PDF *p);

/* p_image.c */
void PDF_place_image(PDF *p, PDF_image *image, float x, float y, float scale);
void PDF_place_inline_image(PDF *p, PDF_image *image, float x, float y, float scale);
void PDF_put_image(PDF *p, PDF_image *image);
void PDF_execute_image(PDF *p, PDF_image *image, float x, float y, float scale);
void PDF_close_image(PDF *p, PDF_image *image);

/* p_jpeg.c */
PDF_image *PDF_open_JPEG(PDF *p, char *filename);
void PDF_close_JPEG(PDF *p, PDF_image *image);

/* p_tiff.c */
PDF_image *PDF_open_TIFF(PDF *p, char *filename);
void PDF_close_TIFF(PDF *p, PDF_image *image);

/* p_gif.c */
PDF_image *PDF_open_GIF(PDF *p, char *filename);
void PDF_close_GIF(PDF *p, PDF_image *image);

/* p_filter.c */
void PDF_data_source_from_buf(PDF *p, PDF_data_source *src, byte *buffer, long len);

/* p_font.c */
float PDF_stringwidth(PDF *p, byte *text);

/* p_hyper.c */
void PDF_add_outline(PDF *p, char *text);

#endif				/* PDF_H */
