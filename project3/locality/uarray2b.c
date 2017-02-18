/*
 *     filename: uarray2b.c
 *     partner 1 name: Peter Vondras       Login: peter
 *     partner 2 name: Hongyan Wang        Login: hwang10
 *     date: February 25th, 2016
 *     assignment: hw3
 *
 *     summary: This file implements a unboxed polymorphic 2D array. It does
 *              this by storing information in a UArray2 of blocks of data. 
 *              Within each block is a UArray of data stored in row major order.
 *                      
 */


#include <uarray2b.h>
#include <uarray2.h>
#include <uarray.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mem.h"

#define T UArray2b_T

static double MAX_BLOCK_SIZE = 64000;

/* Main structure for uarray2b */
struct T {
        UArray2_T uarray2;
        int width;
        int height;
        int blockWidth;
        int blockHeight;
        int blocksize;
        int size;
};

/* 
 * new blocked 2d array
 * blocksize = square root of # of cells in block. 
 * blocksize < 1 is a checked runtime error
 */
T UArray2b_new(int width, int height, int size, int blocksize)
{
        assert(blocksize >= 1 && width >= 0 && height >= 0);

        T blockarray; 
        UArray_T *anArray_p;       

        NEW(blockarray); 

        /* Set blockwidth and blockheight with extra block for edges */
        blockarray->blockWidth   = width / blocksize;
        blockarray->blockWidth  += (width % blocksize > 0) ? 1 : 0;
        blockarray->blockHeight  = height / blocksize;
        blockarray->blockHeight += (height % blocksize > 0) ? 1 : 0;

        /* update structure values */
        blockarray->width        = width;
        blockarray->height       = height;
        blockarray->blocksize    = blocksize;
        blockarray->size         = size;
        blockarray->uarray2      = UArray2_new(blockarray->blockWidth,
                                               blockarray->blockHeight,
                                               sizeof(UArray_T));
 
        /* put a UArray_T in each block */
        for (int row = 0; row < blockarray->blockHeight; row++)
        {
                for (int col = 0; col < blockarray->blockWidth; col++)
                {  
                        anArray_p = UArray2_at(blockarray->uarray2, col, row);
                        *anArray_p = UArray_new(blocksize * blocksize, size);
                }
        }
        
        return blockarray;
}

/* 
 * new blocked 2d array: blocksize as large as possible provided
 * block occupies at most 64KB (if possible)
 */
T UArray2b_new_64K_block(int width, int height, int size)
{      
        T myArray;
        int blocksize;

        blocksize = (int)sqrt(MAX_BLOCK_SIZE / size);
        myArray = UArray2b_new(width, height, size, blocksize);
        return myArray;
}

/* free memory in each block and UArray2b */
void UArray2b_free  (T *blockarray_p)
{
        assert( blockarray_p != NULL);
        assert(*blockarray_p != NULL);
        UArray_T *anArray_p; 

        /* free UArrays in each block */
        for (int row = 0; row < (*blockarray_p)->blockHeight; row++)
        {
                for (int col = 0; col < (*blockarray_p)->blockWidth; col++)
                {  
                        anArray_p = UArray2_at((*blockarray_p)->uarray2, col,
                                               row);
                        UArray_free(anArray_p);
                }
        }
        UArray2_free( &((*blockarray_p)->uarray2) );
        FREE(*blockarray_p);
        *blockarray_p = NULL;
}

int UArray2b_width (T array2b)
{
        assert(array2b != NULL);
        return array2b->width;
}

int UArray2b_height(T array2b)
{
        assert(array2b != NULL);
        return array2b->height;
}

int UArray2b_size  (T array2b)
{
        assert(array2b != NULL);
        return array2b->size;
}

int UArray2b_blocksize(T array2b)
{
        assert(array2b != NULL);
        return array2b->blocksize;
}

/* 
 * return a pointer to the cell in column i, row j;
 * index out of range is a checked run-time error
 */
void *UArray2b_at(T array2b, int col, int row)
{       
        UArray_T *anArray_p;
        int local_index;

        /* retrieve correct block */
        anArray_p = UArray2_at(array2b->uarray2, col/array2b->blocksize,
                                 row/array2b->blocksize);
        /* find correct index within the block */
        local_index = array2b->blocksize * (row % array2b->blocksize) +
                      (col % array2b->blocksize);
        
        return UArray_at(*anArray_p, local_index);
}

/* visits every cell in one block before moving to another block */
void UArray2b_map(T blockarray, void apply(int i, int j, T array2b,
                                        void *elem, void *cl), void *cl)
{       
        assert(blockarray != NULL);
        UArray_T *anArray_p; 
        int col, row;
        
        /* for every row */
        for (int block_row = 0; block_row < blockarray->blockHeight;
                                block_row++)
        {
                /* for every col */
                for (int block_col = 0; block_col < blockarray->blockWidth;
                                        block_col++)
                {  
                        /* for every location in block */
                        anArray_p = UArray2_at(blockarray->uarray2,
                                               block_col, block_row);
                        for (int i = 0; i < UArray_length(*anArray_p); i++)
                        {
                                /* convert from local to global coordinates */
                                col = (block_col * blockarray->blocksize) + 
                                      (i % blockarray->blocksize);
                                row = (block_row * blockarray->blocksize) + 
                                      (i / blockarray->blocksize);
                                /* do not use "empty" edge memory locations */
                                if (col >= blockarray->width ||
                                    row >= blockarray->height)
                                        continue;

                                /* call apply function on this cell */
                                apply(col, row, blockarray, 
                                           UArray_at(*anArray_p, i), cl);
                        }
                }
        }
        
}
