/*
 *     Filename: compress40.c
 *     Partner 1 name: Hongyan Wang       Login: hwang10
 *     Partner 2 name: Ryan Schneiderman  Login: rschne01
 *     Date: March 10th, 2016
 *     Assignment: hw4
 *
 *     Summary: this file contains two functions: compress40 and decompress40.
 *              These two functions will be called in 40image.c files based on 
 *              the input argument '-c' or 'd'.
 *              Compress40 read in Pnm_ppm image, then transfer it to component 
 *                         video color image, then pack each 2 by 2 blocks, then
 *                         compress it to binary image.
 *              Decompress40 read in binary image, then unpack the codeword, 
 *                          then transfer it to component video color image, 
 *                          then transfer it to Pnm_ppm image and write it to 
 *                          standard output.
 */

#include "compress40.h"
#include "arith40.h"
#include "image_io.h"
#include "cv_codeword_trans.h"
#include "rgb_cv_trans.h"

void compress40(FILE *input)
{   
        /* Use UArray2 methods as default methods*/
        A2Methods_T methods = uarray2_methods_plain;  
        assert(methods);

        /* Use default map function*/
        A2Methods_mapfun *map = methods->map_default;
        assert(map);

        /* Read the Pnm_ppm image and trim the the last row and/or column of 
         * the image such that both width and height are even numbers. */
        Pnm_ppm rgb_image = readPpmImage(input, methods);

       /* Convert the pixel from RGB color space to component video color space. 
        * input: Pnm_ppm image, map function and methods.
        * output: 2D array, each element is component video color pixel. */
        A2Methods_UArray2 cv_image = rgbImage_to_cvImage(rgb_image, map, 
                                                                methods);

       /* Convert the pixel from component video color space to a, b, c, d, pb, 
        * pr. 
        * input: 2D array with component video color pixel as element, map 
        *        function and methods. 
        * output: 2D array with structure of a, b, c, d, pb, pr as element. 
        * Note: both width and height of the output 2D array is equal to half 
        * of the width and height of input 2D array. */
        A2Methods_UArray2 compressed_image = cvImage_to_wordImage(cv_image, 
                                                                map, methods);

        /* Convert the pixel from a, b, c, d, pb, pr to codeword. 
         * input: 2D array with structure of a, b, c, d, pb, pr as element, map 
         *        function and methods. 
         * output: 2D array with codeword as element. */
        A2Methods_UArray2 codeword_array = wordImage_to_codewordImage(
                                                compressed_image, map, methods);
    
        /* Write a compressed binary image to standard output.
         * Note the codewords are written to disk in big-endian order*/
        printBinImage(codeword_array, methods);

        /* Free all the memories on heap*/
        methods->free(&cv_image);
        methods->free(&compressed_image);
        methods->free(&codeword_array);
        Pnm_ppmfree(&rgb_image);
}

void decompress40(FILE *input)
{

    /* Use UArray2 methods as default methods*/
        A2Methods_T methods = uarray2_methods_plain;  
    assert(methods);

    /* Use default map function*/
    A2Methods_mapfun *map = methods->map_default;
    assert(map);

    /* Read the header of the binary image, get all codewords in 2D array. 
     * input: binary image file pointer, map function and methods. 
     * output: 2D array with codeword as element. */
    A2Methods_UArray2 codeword_array = readBinImage(input, map, methods);

    /* Unpack the codeword, get a, b, c, d, pb, pr as pixels. 
     * input: 2D array with codeword as element, map function, methods.
     * output: 2D array with structure of a, b, c, d, pb, pr as element.*/
    A2Methods_UArray2 compressed_image = codewordImage_to_wordImage(
                                                codeword_array, map, methods);

    /* Convert the pixel from a, b, c, d, pb, pr to component video color 
     * space.
     * input: 2D array with structure of a, b, c, d, pb, pr as element, map 
     *         function, methods. 
     * output: 2D array with component video color pixel as element. 
     * Note: both the width and height of the output 2D array are double of the
     *       width and height of input 2D array. */
    A2Methods_UArray2 cv_image = wordImage_to_cvImage(compressed_image, map, 
                                                methods);

    /* Convert the pixel from component video color space to RGB color space. 
     * input: 2D array with component video color pixel as element, map 
     *        function and methods. 
     * output: Pnm_ppm image. */
    Pnm_ppm rgb_image = cvImage_to_rgbImage(cv_image, map, methods);

    /* Free the memories for 2D arrays on heap*/
    methods->free(&codeword_array);
    methods->free(&compressed_image);
    methods->free(&cv_image);

    /* Write the uncompressed image to standard output*/
    Pnm_ppmwrite(stdout, rgb_image);

    /* Free the Pnm_ppm image*/
    Pnm_ppmfree(&rgb_image);
}


