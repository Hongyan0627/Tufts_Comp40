#ifndef RGB_CV_TRANS_INCLUDED
#define RGB_CV_TRANS_INCLUDED

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

/* helpful structure with 2D array, methods and denominator as members. */
struct a2_closure_with_denominator{
    A2Methods_UArray2 *array2;
    A2Methods_T methods;
    unsigned denominator;
};



/* This function will convert the pixel from RGB color space to component video
 * color space. 
 * input: Pnm_ppm image, map function and methods.
 * output: 2D array, each element is component video color pixel. */
extern A2Methods_UArray2 rgbImage_to_cvImage(Pnm_ppm rgb_image, 
                        A2Methods_mapfun *map, A2Methods_T methods);

/* This apply function will transfer each RGB color pixel to component video 
 * color pixel. */
extern void apply_rgb_to_cv(int col, int row, A2Methods_UArray2 arr2, 
                                        void *elem, void *cl);

/* This function will convert the pixel from component video color space to RGB
 * color space. 
 * input: 2D array with component video color pixel as element, map 
 *        function and methods. 
 * output: Pnm_ppm image. */
extern Pnm_ppm cvImage_to_rgbImage(A2Methods_UArray2 cv_image, 
                        A2Methods_mapfun *map, A2Methods_T methods);

/* This apply function will transfer each component video color pixel to RGB 
 * color pixel. */
extern void apply_cv_to_rgb(int col, int row, A2Methods_UArray2 arr2, 
                                        void *elem, void *cl);

#endif