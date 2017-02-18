/*
 *                      useuarray2.c
 *
 *         This program illustrates the use of the uarray2 interface.
 *
 *         Although it will catch some errors in some uarray2 implementations
 *         it is NOT a thorough test program.
 *
 *         NOTE: this program is commented sparsely, as figuring out
 *         what this program does and why the tests it makes matter is
 *         part of the homework assignment.
 *
 *         Author: Noah Mendelsohn
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "uarray2.h"

typedef long number;

const int DIM1 = 5;
const int DIM2 = 7;
const int ELEMENT_SIZE = sizeof(number);
const int MARKER = 99;

void
check_and_print(int i, int j, UArray2_T a, void *p1, void *p2) 
{
        number *entry_p = p1;

        *((bool *)p2) &= UArray2_at(a, i, j) == entry_p;

        if ( (i == (DIM1 -1) ) && (j == (DIM2 - 1) ) ) {
                /* we got the corner */
                *((bool *)p2) &= (*entry_p == MARKER);
        }

        printf("ar[%d,%d]\n", i, j);
}

int
main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;

        UArray2_T test_array;
        bool OK = true;
        number mark = 1;

        test_array = UArray2_new(DIM1, DIM2, ELEMENT_SIZE);

        OK &= (UArray2_width(test_array) == DIM1);
        OK &= (UArray2_height(test_array) == DIM2);
        OK &= (UArray2_size(test_array) == ELEMENT_SIZE);


        /* Note: we are only setting a value on the corner of the array */
        *((number *)UArray2_at(test_array, DIM1-1, DIM2-1)) = MARKER;
        
        printf("Trying column major\n");
        // UArray2_map_col_major(test_array, check_and_print, &OK);
        UArray2_map_col_major(test_array, check_and_print, &mark);

        printf("Trying row major\n");
        // UArray2_map_row_major(test_array, check_and_print, &OK);
        UArray2_map_row_major(test_array, check_and_print, &mark);

        UArray2_free(&test_array);

        printf("The array is %sOK!\n", (OK ? "" : "NOT "));

}
