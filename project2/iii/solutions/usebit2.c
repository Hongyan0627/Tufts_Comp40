/*
 *                      usebit2.c
 *
 *         This program illustrates the use of the bit2 interface.
 *
 *         Although it will catch some errors in some bit2 implementations
 *         it is NOT a thorough test program.
 *
 *         NOTE: this program is intentionally commented sparsely, as 
 *         figuring out what this program does and why the tests it makes
 *         matter is part of the homework assignment.
 *
 *         Author: Noah Mendelsohn
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bit2.h"

const int DIM1 = 5;
const int DIM2 = 7;

const int MARKER = 1;  /* can only be 1 or 0 */

void
check_and_print(int i, int j, Bit2_T a, int b, void *p1) 
{
        if ( (i == (DIM1 -1) ) && (j == (DIM2 - 1) ) ) {
                /* we got the corner */
                *((bool *)p1) &= Bit2_get(a, i, j) == b;
                *((bool *)p1) &= (b == MARKER);
        }

        printf("ar[%d,%d]\n", i, j);
}



int
main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;

        Bit2_T test_array;
        bool OK = true;

        int x;

        test_array = Bit2_new(DIM1, DIM2);

        OK &= (Bit2_width(test_array) == DIM1);
        OK &= (Bit2_height(test_array) == DIM2);


        /* Note: we are only setting a value on the corner of the array */
        Bit2_put(test_array, DIM1-1, DIM2-1, MARKER);
        OK &= (Bit2_get(test_array, DIM1-1, DIM2-1) == MARKER);

        x = Bit2_put(test_array, DIM1-1, DIM2-1, 0);
        OK &= (x == MARKER);     /* hint: put returns previous value */

        Bit2_put(test_array, DIM1-1, DIM2-1, MARKER);  /* for map test */
        printf("Trying column major\n");
        Bit2_map_col_major(test_array, check_and_print, &OK);

        printf("Trying row major\n");
        Bit2_map_row_major(test_array, check_and_print, &OK);

        Bit2_free(&test_array);

        printf("The array is %sOK!\n", (OK ? "" : "NOT "));

}
