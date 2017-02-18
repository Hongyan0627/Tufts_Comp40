#ifndef PNM_INCLUDED
#define PNM_INCLUDED
#include <stdio.h>
#include <stdint.h>

#include <except.h>

#include <a2methods.h>

/*
 * functions in this interface use only the 'new', 'free',
 * 'cell', and 'map_default' methods
 *
 * every function in this interface uses the (x, y) coordinate system,
 * which is the same as the (col, row) or (width, height) system.
 *
 */

/* colored pixel (scaled integers) */
typedef struct Pnm_rgb {
        unsigned red, green, blue;
} *Pnm_rgb;

/*
 * clients may read 'methods, but to mutate 'methods' or any 
 * field of 'methods' is an UNCHECKED run-time error
 */
typedef struct Pnm_ppm {
        unsigned width, height, denominator;
        A2Methods_UArray2 pixels;          /* 2D array with
                                            * element type 'struct Pnm_rgb' 
                                            */
        const struct A2Methods_T *methods; /* to operate on 'pixels' field */
} *Pnm_ppm;

/* raised by ppmread when not a pnm file */
extern const Except_T Pnm_Badformat;

/* Read a file using the given methods and return a pixmap
 * containing a 2D array of the type returned by 'methods->new'.
 * 'methods' field of the result is the same as the argument.
 * Raises Pnm_Badformat if not given a proper PNM file.  Methods
 * are not copied, so caller must ensure they live as long as the pixmap.
 */
Pnm_ppm Pnm_ppmread(FILE *fp, A2Methods_T methods);

/* 
 * Write 'pixmap' to a file.  If 'pixmap' is empty, it's a checked 
 * run-time error. 
 */
void Pnm_ppmwrite(FILE *fp, Pnm_ppm pixmap);

/* Free pixmap pointed to by ppmp. Does not free methods. */
void Pnm_ppmfree(Pnm_ppm *ppmp);

#endif
