#ifndef CV_CODEWORD_TRANS_INCLUDED
#define CV_CODEWORD_TRANS_INCLUDED

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
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
#include "ybr_pixel.h"

/* make b, c, d in range [-0.3, 0.3]*/
#define BCD_RANGE 0.3

/*helpful structure with 2D array, methods and denominator as members. */
struct a2_closure{
    A2Methods_UArray2 *array2;
    A2Methods_T methods;
};

/*helpful structure with a, b, c, d, Pb, Pr as members. */
typedef struct compressed_word{
        uint64_t a;
        int64_t  b;
        int64_t  c;
        int64_t  d;
        uint64_t pb;
        uint64_t pr;    
} *compressed_word;

/* This function will convert the pixel from component video color space to a,
 * b, c, d, pb, pr. 
 * input: 2D array with component video color pixel as element, map function 
 * and methods. 
 * output: 2D array with structure of a, b, c, d, pb, pr as element. 
 * Note: both width and height of the output 2D array is equal to half of the 
 * width and height of input 2D array. */
extern A2Methods_UArray2 cvImage_to_wordImage(A2Methods_UArray2 cv_image, 
                        A2Methods_mapfun *map, A2Methods_T methods);

/* This apply function will transfer 4 component video color pixels in a 2 by 2
 * block to a compressed_word structure. */
extern void apply_cv_to_word(int col, int row, A2Methods_UArray2 arr2, 
                                        void *elem, void *cl);

/* This function will convert the pixel from a, b, c, d, pb, pr to codeword. 
 * input: 2D array with structure of a, b, c, d, pb, pr as element, map 
 * function and methods. 
 * output: 2D array with codeword as element. */
extern A2Methods_UArray2 wordImage_to_cvImage(A2Methods_UArray2 
                compressed_image, A2Methods_mapfun *map, A2Methods_T methods);

/* This apply function will transfer a compressed_word structure to 4 component
 * video color pixels and set these four pixels as a 2 by 2 block in the output
 * 2D array. */
extern void apply_word_to_cv(int col, int row, A2Methods_UArray2 arr2, 
                        void *elem, void *cl);


/* This function will convert the pixel from a, b, c, d, pb, pr to codeword. 
 * input: 2D array with structure of a, b, c, d, pb, pr as element, map 
 * function and methods. 
 * output: 2D array with codeword as element. */
extern A2Methods_UArray2 wordImage_to_codewordImage(A2Methods_UArray2 
                compressed_image, A2Methods_mapfun *map, A2Methods_T methods);

/* This apply function will pack a compressed_word structure into one codeword
 * by the interface in bitpack.h. */
extern void apply_pack_word(int col, int row, A2Methods_UArray2 arr2, 
                        void *elem, void *cl);

/* This function will unpack the codeword, get a, b, c, d, pb, pr as pixels. 
 * input: 2D array with codeword as element, map function, methods.
 * output: 2D array with structure of a, b, c, d, pb, pr as element.*/
extern A2Methods_UArray2 codewordImage_to_wordImage(A2Methods_UArray2 
                codeword_array, A2Methods_mapfun *map, A2Methods_T methods);

/* This apply function will unpack each codeword by the interface in bitpack.h
 * and create a compressed_word structure with a, b, c, d, pb, pr as members.*/
extern void apply_unpack_word(int col, int row, A2Methods_UArray2 arr2, 
                        void *elem, void *cl);

#endif