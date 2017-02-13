#include "cv_codeword_trans.h"

#define A_MUL 63
#define BCD_MUL 103
#define A_WIDTH 6
#define BCD_WIDTH 6
#define PRB_WIDTH 4

/* helper function to transfer float a to integer a*/
static uint64_t a_float_to_int (float val, uint64_t mul) {
        return round(val * mul);
} 

/* helper function to transfer float b, c, d to integer b, c, d. 
 * Note: b, c, d range is fixed to be 0.3. */
static int64_t bcd_float_to_int (float val, uint64_t mul) {
        if (val >=  BCD_RANGE)  val =  BCD_RANGE;
        if (val <= -BCD_RANGE)  val = -BCD_RANGE;
   
        return (int64_t)(round(val * mul));
} 

/* helper function to transfer integer a to float a. */
static float a_int_to_float (uint64_t val, uint64_t mul) {
        return (val * 1.0)/mul;
}  

/* helper function to transfer integer b, c, d to float b, c, d. */
static float bcd_int_to_float (int64_t val, uint64_t mul) {
        return (val * 1.0)/mul;
} 

/* helper function to make float values are in range [0, 1]. */
static float set_Range(float val) 
{
        if (val < 0) return 0.0;
        if (val > 1) return 1.0;
        return val;
}

/* This function will convert the pixel from component video color space to a,
 * b, c, d, pb, pr. 
 * input: 2D array with component video color pixel as element, map function 
 * and methods. 
 * output: 2D array with structure of a, b, c, d, pb, pr as element. 
 * Note: both width and height of the output 2D array is equal to half of the 
 * width and height of input 2D array. */
A2Methods_UArray2 cvImage_to_wordImage(A2Methods_UArray2 cv_image, 
                      A2Methods_mapfun *map, A2Methods_T methods)
{
        int width  = (methods->width(cv_image))/2;
        int height = (methods->height(cv_image))/2;

        /* create a new 2D array with compressed_word structure as elements. */
        A2Methods_UArray2 compressed_image = methods->new(width, height, 
                      sizeof(struct compressed_word));

        /* closure for apply function with methods and 2D array as members. */
        struct a2_closure *my_cl = malloc(sizeof(*my_cl));
        my_cl->methods = methods;
        my_cl->array2 = cv_image;
        
        /* use map function to transfer 4 component video color pixels to a 
         * compressed_word structure. */
        map(compressed_image, apply_cv_to_word, my_cl);
        
        /* free the closure. */
        if(my_cl != NULL){
                free(my_cl);
                my_cl = NULL;
        }

        return compressed_image;
}

/* This apply function will transfer 4 component video color pixels in a 2 by 2
 * block to a compressed_word structure. */
void apply_cv_to_word(int col, int row, A2Methods_UArray2 arr2, 
                        void *elem, void *cl)
{
        (void) arr2;
        int index_col, index_row;
        struct a2_closure *mcl;
        Pnm_ybr pixel1, pixel2, pixel3, pixel4;
        float avg_pb, avg_pr, float_a, float_b, float_c, float_d;
        
        /* one word corresponds to 4 pixels. */
        index_col = 2 * col;
        index_row = 2 * row;
        mcl = cl; 
        
        /* get pointers to 4 component video color pixels. */
        pixel1 = mcl->methods->at(mcl->array2, index_col, index_row);
        pixel2 = mcl->methods->at(mcl->array2, index_col + 1, index_row);
        pixel3 = mcl->methods->at(mcl->array2, index_col, index_row + 1);
        pixel4 = mcl->methods->at(mcl->array2, index_col + 1, index_row + 1);
        
        compressed_word word_elem = elem;

        /* compute float a, b, c, d, Pb, Pr values from 4 component video color
         * pixels. */
        avg_pb = (pixel1->pb + pixel2->pb + pixel3->pb + pixel4->pb)/4.0;
        avg_pr = (pixel1->pr + pixel2->pr + pixel3->pr + pixel4->pr)/4.0;
        float_a = (pixel4->y + pixel3->y + pixel2->y + pixel1->y)/4.0;
        float_b = (pixel4->y + pixel3->y - pixel2->y - pixel1->y)/4.0;
        float_c = (pixel4->y - pixel3->y + pixel2->y - pixel1->y)/4.0;
        float_d = (pixel4->y - pixel3->y - pixel2->y + pixel1->y)/4.0;

        /* set compressed_word structure members. Transfer float a, b, c, d, 
         * Pb, Pr to integers a, b, c, d, Pb, Pr. */
        word_elem->pb = (uint64_t)(Arith40_index_of_chroma(avg_pb));
        word_elem->pr = (uint64_t)(Arith40_index_of_chroma(avg_pr));
        word_elem->a = a_float_to_int(float_a, A_MUL);
        word_elem->b = bcd_float_to_int(float_b, BCD_MUL);
        word_elem->c = bcd_float_to_int(float_c, BCD_MUL);
        word_elem->d = bcd_float_to_int(float_d, BCD_MUL);
}

/* This function will convert the pixel from a, b, c, d, pb, pr to codeword. 
 * input: 2D array with structure of a, b, c, d, pb, pr as element, map 
 * function and methods. 
 * output: 2D array with codeword as element. */
A2Methods_UArray2 wordImage_to_cvImage(A2Methods_UArray2 compressed_image, 
                A2Methods_mapfun *map, A2Methods_T methods)
{
        int width  = (methods->width(compressed_image)) * 2;
        int height = (methods->height(compressed_image)) * 2;

        /* create a new 2D array with to save component video color pixels. */
        A2Methods_UArray2 cv_image = methods->new(width, height, 
                        sizeof(struct Pnm_ybr));

        /* closure for apply function contains new 2D array and methods. */
        struct a2_closure *my_cl = malloc(sizeof(*my_cl));
        my_cl->methods = methods;
        my_cl->array2 = cv_image;

        /* use map function to transfer each compressed_word structure to 4 
         * component video color pixels. save as a 2 by 2 block in the new 2D 
         * array. */
        map(compressed_image, apply_word_to_cv, my_cl);

        /* free the closure. */
        if(my_cl != NULL){
                free(my_cl);
                my_cl = NULL;
        }

        return cv_image;

}

/* This apply function will transfer a compressed_word structure to 4 component
 * video color pixels and set these four pixels as a 2 by 2 block in the output
 * 2D array. */
void apply_word_to_cv(int col, int row, A2Methods_UArray2 arr2, void *elem, 
                                                                void *cl)
{
        (void) arr2;
        float avg_pb, avg_pr, a, b, c, d;
        
        Pnm_ybr pixel1, pixel2, pixel3, pixel4;
        compressed_word word_block = elem;
        struct a2_closure *mcl = cl;

        /* get pointers to 4 component video color pixels. */
        pixel1 = mcl->methods->at(mcl->array2, 2 * col, 2 * row);
        pixel2 = mcl->methods->at(mcl->array2, 2 * col + 1, 2 * row);
        pixel3 = mcl->methods->at(mcl->array2, 2 * col, 2 * row + 1);
        pixel4 = mcl->methods->at(mcl->array2, 2 * col + 1, 2 * row + 1);

        /* compute the average float Pb, Pr values. */
        avg_pb = Arith40_chroma_of_index(word_block->pb);
        avg_pr = Arith40_chroma_of_index(word_block->pr);

        /* transfer float a, b, c, d to integer a, b, c, d.*/
        a = a_int_to_float(word_block->a, A_MUL);
        b = bcd_int_to_float(word_block->b, BCD_MUL);
        c = bcd_int_to_float(word_block->c, BCD_MUL);
        d = bcd_int_to_float(word_block->d, BCD_MUL);

        /* set Pb, Pr values for 4 component video color pixels to be average 
         * Pb, Pr values. */
        pixel1->pb = avg_pb;
        pixel2->pb = avg_pb;
        pixel3->pb = avg_pb;
        pixel4->pb = avg_pb;

        pixel1->pr = avg_pr;
        pixel2->pr = avg_pr;
        pixel3->pr = avg_pr;
        pixel4->pr = avg_pr;

        /* compute 4 y values for 4 pixels. Make sure float y values are in 
         * range [0, 1]. */
        pixel1->y = set_Range(a - b - c + d);
        pixel2->y = set_Range(a - b + c - d);
        pixel3->y = set_Range(a + b - c - d);
        pixel4->y = set_Range(a + b + c + d);

}


/* This function will convert the pixel from a, b, c, d, pb, pr to codeword. 
 * input: 2D array with structure of a, b, c, d, pb, pr as element, map 
 * function and methods. 
 * output: 2D array with codeword as element. */
A2Methods_UArray2 wordImage_to_codewordImage(A2Methods_UArray2 
        compressed_image, A2Methods_mapfun *map, A2Methods_T methods)
{
        int width = methods->width(compressed_image);
        int height = methods->height(compressed_image);

        /* create a new 2D array to save packed codeword. */
        A2Methods_UArray2 codeword_array = methods->new(width, height, 
                                                    sizeof(uint64_t));

        /* closure for apply functions with new 2D array and methods. */
        struct a2_closure *my_cl = malloc(sizeof(*my_cl));
        my_cl->methods = methods;
        my_cl->array2 = codeword_array;

        /* use map function to transfer compressed_word structure to packed 
         * codeword. */
        map(compressed_image, apply_pack_word, my_cl);

        /* free the closure. */
        if(my_cl != NULL){
                free(my_cl);
                my_cl = NULL;
        }

        return codeword_array;

}

/* This apply function will pack a compressed_word structure into one codeword
 * by the interface in bitpack.h. */
void apply_pack_word(int col, int row, A2Methods_UArray2 arr2, 
                                                 void *elem, void *cl)
{
        (void) arr2;

        struct a2_closure *mcl = cl;
        compressed_word old_word = elem;

        uint64_t temp_word = 0;
        uint64_t *new_word = mcl->methods->at(mcl->array2, col, row);

        /* use bitpack.c interfaces to pack a, b, c, d, Pb, Pr integer values
         * into a 64-bit codeword. */
        temp_word = Bitpack_newu(temp_word, PRB_WIDTH, 0,  old_word->pr);
        temp_word = Bitpack_newu(temp_word, PRB_WIDTH, PRB_WIDTH, 
                                                old_word->pb);
        temp_word = Bitpack_news(temp_word, BCD_WIDTH, 2 * PRB_WIDTH, 
                                                old_word->d);
        temp_word = Bitpack_news(temp_word, BCD_WIDTH, BCD_WIDTH + 
                                                2 * PRB_WIDTH, old_word->c);
        temp_word = Bitpack_news(temp_word, BCD_WIDTH, 
                        2 * BCD_WIDTH + 2 * PRB_WIDTH, old_word->b);
        temp_word = Bitpack_newu(temp_word, A_WIDTH, 
                        3 * BCD_WIDTH + 2 * PRB_WIDTH, old_word->a);

        *new_word = temp_word;
}

/* This function will unpack the codeword, get a, b, c, d, pb, pr as pixels. 
 * input: 2D array with codeword as element, map function, methods.
 * output: 2D array with structure of a, b, c, d, pb, pr as element.*/
A2Methods_UArray2 codewordImage_to_wordImage(A2Methods_UArray2 codeword_array,
                        A2Methods_mapfun *map, A2Methods_T methods)
{
        int width =  methods->width(codeword_array);
        int height = methods->height(codeword_array);

        /* create a new 2D array to save compressed_word structure. */
        A2Methods_UArray2 compressed_image = methods->new(width, height, 
                        sizeof(struct compressed_word));

        /* closure for apply function with new 2D array and methods as 
         * members. */
        struct a2_closure *my_cl = malloc(sizeof(*my_cl));
        my_cl->methods = methods;
        my_cl->array2 = compressed_image;

        /* use map function to transfer each codeword to a compressed_word 
         * structure. */
        map(codeword_array, apply_unpack_word, my_cl);

        /* free the closure. */
        if(my_cl != NULL){
                free(my_cl);
                my_cl = NULL;
        }

        return compressed_image;
}

/* This apply function will unpack each codeword by the interface in bitpack.h
 * and create a compressed_word structure with a, b, c, d, pb, pr as members.*/
void apply_unpack_word(int col, int row, A2Methods_UArray2 arr2, 
                        void *elem, void *cl)
{
        (void) arr2;    
        struct a2_closure *mcl = cl;
        uint64_t codeword = *((uint64_t *)elem);
        compressed_word word_block = mcl->methods->at(mcl->array2, col, row);

        /* use the interfaces in bitpack.c to unpack each codeword. */
        word_block->a  = Bitpack_getu(codeword, A_WIDTH, 
                                3 * BCD_WIDTH + 2 * PRB_WIDTH);
        word_block->b  = Bitpack_gets(codeword, BCD_WIDTH, 
                                2 * BCD_WIDTH + 2 * PRB_WIDTH);
        word_block->c  = Bitpack_gets(codeword, BCD_WIDTH, 
                                BCD_WIDTH + 2 * PRB_WIDTH);
        word_block->d  = Bitpack_gets(codeword, BCD_WIDTH, 2 * PRB_WIDTH);
        word_block->pb = Bitpack_getu(codeword, PRB_WIDTH, PRB_WIDTH);
        word_block->pr = Bitpack_getu(codeword, PRB_WIDTH, 0);
}