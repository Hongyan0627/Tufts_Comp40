#include <uarray.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "uarray2.h"

/*
* Width = number of columns
* Height = number of rows
*/
struct UArray2_T {
        int width;
        int height;
        UArray_T data;  
};


/* UArray2_new returns a new Uarray */
UArray2_T UArray2_new(int width, int height, int size) {
        UArray2_T the2darray = (UArray2_T) malloc(sizeof(*the2darray));
        assert(the2darray != NULL);
        the2darray->width = width;
        the2darray->height = height;
        the2darray->data = UArray_new(width * height, size);
        return the2darray;
}

/* 
* This function maps apply() to all elements in the array,
* using the col major order
* apply params: col is the column of the element, row is the row
* of the element, the_array is the array, val is a pointer to the
* value at the index, and cl is a pointer to a closure variable
*/
void UArray2_map_col_major(UArray2_T the_array, 
        void apply(int col, int row, UArray2_T a, void *curr_val, void *cl), 
                void *cl) {
        assert(the_array != NULL);
        for (int col_num = 0; col_num < the_array->width; col_num++) {
                for (int row_num = 0; row_num < the_array->height; 
                        row_num++) {
                        apply(col_num, row_num, the_array, 
                                UArray_at(the_array->data, col_num + 
                                row_num * the_array->width), cl);
                }
        }
}

/* 
* This function maps apply() to all elements in the array,
* using the row major order
*/
void UArray2_map_row_major(UArray2_T the_array, 
        void apply(int col, int row, UArray2_T a, void *curr_val, 
                void *cl), void *cl) {
        assert(the_array != NULL);
        for (int row_num = 0; row_num < the_array->height; row_num++) {
                for (int col_num = 0; col_num < the_array->width; col_num++) {
                        apply(col_num, row_num, the_array, 
                                UArray_at(the_array->data, 
                                col_num + row_num * the_array->width), cl);
                }
        }
}

/* This function returns a pointer to the value at the given indices*/
void *UArray2_at(UArray2_T the_array, int col, int row) {
        assert(the_array != NULL);
        assert(col < the_array->width && col >= 0);
        assert(row < the_array->height && row >= 0);
        return UArray_at(the_array->data, col + row * the_array->width);
}

/* This function returns the width of the array */
int UArray2_width(UArray2_T the_array) {
        assert(the_array != NULL);
        return the_array->width;
}

/* This function returns the height of the array*/
int UArray2_height(UArray2_T the_array) {
        assert(the_array != NULL);
        return the_array->height;
}   

/* This function returns the size of each element in the array*/
int UArray2_size(UArray2_T the_array) {
        assert(the_array != NULL);
        return UArray_size(the_array->data);
}

/* This function frees space in the array*/
void UArray2_free(UArray2_T *the_array) {
        if (*the_array != NULL) {
                if ((*the_array)->data != NULL) {
                        UArray_free(&((*the_array)->data));
                }
                free(*the_array);
        }
}

