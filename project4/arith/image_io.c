#include "image_io.h"

/* Each codeword contains 4 bytes. */
#define BYTE_SIZE 8
#define START_POS 24

/* This function will read the Pnm_ppm image and trim the the last row and/or 
 * column of the image such that both width and height are even numbers. 
 * input: binary image file pointer fp, methods. 
 * output: standard Pnm_ppm image. */
Pnm_ppm readPpmImage(FILE *fp, A2Methods_T methods)
{
        /* Read Pnm_ppm image by the service in Pnm.h. */
        Pnm_ppm initial_image = Pnm_ppmread(fp, methods);

        /* Mark whether we need to trim the image. */
        bool need_trim = false;

        /* Trim the last column if original width is not even. */
        if (initial_image->width % 2 != 0)      {
                (initial_image->width)--;
                need_trim = true;
        }
        
        /* Trim the last row if original height is not even. */
        if (initial_image->height % 2 != 0) {
                (initial_image->height)--;
                need_trim = true;
        }

        if (need_trim == false){
                /* If we didn't trim the image, just return the original 
                 * Pnm_ppm image.*/
                return initial_image;
        } else {

                /* If we trim the image, create a new 2D array with new width 
                 * and new height. */
                A2Methods_UArray2 new_pixels = methods->new(
                        initial_image->width, initial_image->height, 
                                                      sizeof(struct Pnm_rgb));
                for(unsigned row = 0; row < (initial_image->height);row++){
                        for(unsigned col = 0; col < (initial_image->width); 
                                                                       col++){
                                Pnm_rgb new_pixel = methods->at(new_pixels, 
                                                                col, row);
                                Pnm_rgb old_pixel = methods->at(
                                        initial_image->pixels, col, row);
                                new_pixel->red = old_pixel->red;
                                new_pixel->green = old_pixel->green;
                                new_pixel->blue = old_pixel->blue;
                        }
                }

                /* Free the original 2D array. */
                methods->free(&(initial_image->pixels));

                /* Set Pnm_ppm image pixels to be new 2D array. */
                initial_image->pixels = new_pixels;
                return initial_image;
        }
}

/* This function will write a compressed binary image to standard output.
 * Note: the codewords are written to disk in big-endian order*/
void printBinImage(A2Methods_UArray2 codeword_array, A2Methods_T methods)
{
        int width, height, col, row, w;

        /*original width and height are double of the input 2D array width and
         * height.*/
        width  = (methods->width(codeword_array)) * 2;
        height = (methods->height(codeword_array)) * 2;

        /* write the header. */
        printf("COMP40 Compressed image format 2\n%u %u", width, height);
        printf("\n");

        /* write each codeword as row-major order. */
        for (row = 0; row < (height/2); row++){
            for (col = 0; col < (width/2); col++){
                /* cast each codeword into 32-bit. */
                uint64_t *word = methods->at(codeword_array, col, row);
                uint32_t codeword = (uint32_t)(*word);
                /* write each codeword to disk byte by byte in big-endian 
                 * order.*/
                for(w = START_POS; w >= 0; w = w - BYTE_SIZE){
                        unsigned char one_byte = (codeword >> w);
                        putchar(one_byte);
                }
            }
        }
}

/* This function will read the header of the binary image, get all codewords in
 * 2D array. 
 * input: binary image file pointer, map function and methods. 
 * output: 2D array with codeword as element. */
A2Methods_UArray2 readBinImage(FILE *fp, A2Methods_mapfun *map, 
                                                        A2Methods_T methods)
{
        unsigned width, height;
        /* read the header, save the width and height. */
        int read = fscanf(fp, "COMP40 Compressed image format 2\n%u %u", 
                                                        &width, &height);
        /* assert the binary image file format is correct. */
        assert(read == 2);
        int c = getc(fp);
        assert(c == '\n');

        /* The decompressed image width and height should be double of the 
         * read-in width and height. */
        width  =  width /2;
        height =  height/2;

        /* create a 2D array to save codewords at each element.*/
        A2Methods_UArray2 codeword_array = methods->new(width, height,
                                                             sizeof(uint64_t));
        /* use the map function and apply the function apply_readCodeWord to 
         * each element of 2D array. */
        map(codeword_array, apply_readCodeWord, fp);
        return codeword_array;
}

/* This apply function will be called to read in bytes and create a codeword 
 * from 4 bytes. Set each element of 2D array to be the codeword. */
void apply_readCodeWord(int col, int row, A2Methods_UArray2 arr2, 
                                                          void *elem, void *cl)
{
        (void) col;
        (void) row;
        (void) arr2;

        /* Binary image file pointer. */
        FILE *fp = cl;
        assert(fp);

        uint64_t *codeword = elem;

        uint64_t temp_word = 0;
        uint64_t one_byte;

        /*Bytes are written to the disk in big-endian order.*/
        for (int w = START_POS; w >= 0; w = w - BYTE_SIZE){
                one_byte = getc(fp);
                one_byte = one_byte << w;
                temp_word = temp_word | one_byte;
        }
        
        *codeword = temp_word;
}