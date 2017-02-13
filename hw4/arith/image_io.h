#ifndef IMAGE_IO_INCLUDED
#define IMAGE_IO_INCLUDED

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include "arith40.h"
#include "pnm.h"
#include "a2plain.h"
#include "a2blocked.h"
#include "a2methods.h"
#include "bitpack.h"
#include "mem.h"
#include "assert.h"

/* This function will read the Pnm_ppm image and trim the the last row and/or 
 * column of the image such that both width and height are even numbers. */
extern Pnm_ppm readPpmImage(FILE *fp, A2Methods_T methods);

/* This function will write a compressed binary image to standard output.
 * Note: the codewords are written to disk in big-endian order*/
extern void printBinImage(A2Methods_UArray2 codeword_array, 
                                                        A2Methods_T methods);

/* This function will read the header of the binary image, get all codewords in
 * 2D array. 
 * input: binary image file pointer, map function and methods. 
 * output: 2D array with codeword as element. */
extern A2Methods_UArray2 readBinImage(FILE *fp, A2Methods_mapfun *map, 
                                                        A2Methods_T methods);

/* This apply function will read in 4 bytes and create a codeword, then set the
 * codeword at each element. */
extern void apply_readCodeWord(int col, int row, A2Methods_UArray2 arr2, 
                                                        void *elem, void *cl);

#endif