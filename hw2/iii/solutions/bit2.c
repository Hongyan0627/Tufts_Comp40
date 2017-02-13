#include <bit.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bit2.h"

struct Bit2_T {
        int width;
        int height;
        Bit_T data;
};

/*
* Width = number of columns
* Height = number of rows
*/

/* Bit2_new returns a new Bit2 array */
Bit2_T Bit2_new(int width, int height) {
        Bit2_T the2darray = (Bit2_T) malloc(sizeof(*the2darray));
        assert(the2darray != NULL);
        the2darray->width = width;
        the2darray->height = height;
        the2darray->data = Bit_new(width * height);
        return the2darray;
}

/* 
* This function maps apply() to all elements in the array,
* using the col major order
*/
void Bit2_map_col_major(Bit2_T the_array, 
        void apply(int col, int row, Bit2_T a, 
                int curr_val, void *cl), void *cl) {
        assert(the_array != NULL);
        for (int col_num = 0; col_num < the_array->width; col_num++) {
                for (int row_num = 0; row_num < the_array->height; 
                        row_num++) {
                        apply(col_num, row_num, the_array, 
                                Bit_get(the_array->data, 
                                col_num + row_num * the_array->width), cl);
                }
        }
}

/* 
* This function maps apply() to all elements in the array,
* using the row major order
*/
void Bit2_map_row_major(Bit2_T the_array, 
        void apply(int col, int row, Bit2_T a, 
                int curr_val, void *cl), void *cl) {
        assert(the_array != NULL);
         for (int row_num = 0; row_num < the_array->height; row_num++) {
                for (int col_num = 0; col_num < the_array->width; col_num++) {
                        apply(col_num, row_num, the_array, 
                                Bit_get(the_array->data, 
                                col_num + row_num * the_array->width), cl);
                }
        }
}

/* 
* This function replaces the marker at the given pair of indicesto
* the marker. Returns the previous value
*/
int Bit2_put(Bit2_T the_array, int col, int row, int marker) {
        assert(the_array != NULL);
        assert(col < the_array->width && col >= 0);
        assert(row < the_array->height && row >= 0);
        return Bit_put(the_array->data, col + row * the_array->width, marker);
}

/*
* This function returns the value of the map at the 
* given pair of indices.
*/
int Bit2_get(Bit2_T the_array, int col, int row) {
        assert(the_array != NULL);
        assert(col < the_array->width && col >= 0);
        assert(row < the_array->height && row >= 0);
        return Bit_get(the_array->data, col + row * the_array->width);
}

/* This function returns the width of the array */
int Bit2_width(Bit2_T the_array) {
        assert(the_array != NULL);
        return the_array->width;
}

/* This function returns the height of the array*/
int Bit2_height(Bit2_T the_array) {
        assert(the_array != NULL);
        return the_array->height;
}   

/* This function frees space in the array*/
void Bit2_free(Bit2_T *the_array) {
        assert(*the_array != NULL);
        assert((*the_array)->data != NULL);
        Bit_free(&((*the_array)->data));
        free(*the_array);
}

