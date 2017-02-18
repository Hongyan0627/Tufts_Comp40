
/*
#include "uarray2b.h"

int main()
{
        UArray2b_T test;
        test = UArray2b_new(5, 5, 1, 2);




        UArray2b_free(&test);
        return 0;
}*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "uarray2b.h"

typedef long number;

const int DIM1 = 5;
const int DIM2 = 7;
const int ELEMENT_SIZE = sizeof(number);
const int MARKER = 99;

void
check_and_print(int i, int j, UArray2b_T a, void *p1, void *p2) 
{
        number *entry_p = p1;

        *((bool *)p2) &= UArray2b_at(a, i, j) == entry_p;

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

        UArray2b_T test_array;
        bool OK = true;

        test_array = UArray2b_new(DIM1, DIM2, ELEMENT_SIZE, 2);


        OK &= (UArray2b_width(test_array) == DIM1);
        OK &= (UArray2b_height(test_array) == DIM2);
        OK &= (UArray2b_size(test_array) == ELEMENT_SIZE);

        printf("calling at once\n");
        /* Note: we are only setting a value on the corner of the array */
        *((number *)UArray2b_at(test_array, DIM1-1, DIM2-1)) = MARKER;
        printf("Trying block map\n");
        UArray2b_map(test_array, check_and_print, &OK);

        printf("free!\n");
        UArray2b_free(&test_array);

        printf("The array is %sOK!\n", (OK ? "" : "NOT "));

}
