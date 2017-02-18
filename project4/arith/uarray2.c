//#line 50 "www/solutions/uarray2.nw"
#include "assert.h"
#include "mem.h"
#include "uarray.h"
#include "uarray2.h"

#define T UArray2_T

struct T {
        int width, height;
        int size;
        UArray_T rows; /* UArray_T of 'height' UArray_Ts,
                          each of length 'width' and size 'size' */
        // Element (i, j) in the world of ideas maps to
        //   rows[j][i] where the square brackets stand for access
        //   to a Hanson UArray_T
};
//#line 77 "www/solutions/uarray2.nw"
static inline UArray_T row(T a, int j)
{
        UArray_T *prow = UArray_at(a->rows, j); // Ramsey idiom
        return *prow;
}
//#line 90 "www/solutions/uarray2.nw"
static int is_ok(T a)
{
        return a && UArray_length(a->rows) == a->height &&
               UArray_size(a->rows) == sizeof(UArray_T) &&
               (a->height == 0 || (UArray_length(row(a, 0)) == a->width
                                   && UArray_size  (row(a, 0)) == a->size));
}
//#line 107 "www/solutions/uarray2.nw"
T UArray2_new(int width, int height, int size)
{
        int i;  /* interates over row number */
        T array;
        NEW(array);
        array->width  = width;
        array->height = height;
        array->size   = size;
        array->rows   = UArray_new(height, sizeof(UArray_T));
        for (i = 0; i < height; i++) {
                UArray_T *rowp = UArray_at(array->rows, i);
                *rowp = UArray_new(width, size);
        }
        assert(is_ok(array));
        return array;
}
//#line 129 "www/solutions/uarray2.nw"
void UArray2_free(T *array2)
{
        int i;
        assert(array2 && *array2);
        for (i = 0; i < (*array2)->height; i++) {
                UArray_T p = row(*array2, i);
                UArray_free(&p);
        }
        UArray_free(&(*array2)->rows);
        FREE(*array2);
}
//#line 149 "www/solutions/uarray2.nw"
void *UArray2_at(T array2, int i, int j)
{
        assert(array2);
        return UArray_at(row(array2, j), i);
}
//#line 160 "www/solutions/uarray2.nw"
int UArray2_height(T array2)
{
        assert(array2);
        return array2->height;
}

int UArray2_width(T array2)
{
        assert(array2);
        return array2->width;
}

int UArray2_size(T array2)
{
        assert(array2);
        return array2->size;
}
//#line 191 "www/solutions/uarray2.nw"
void UArray2_map_row_major(T array2, 
                           void apply(int i, int j, T array2, 
                                      void *elem, void *cl), 
                           void *cl)
{
        assert(array2);
        int h = array2->height;  // keeping height and width in registers 
        int w = array2->width;   // avoids extra memory traffic
        for (int j = 0; j < h; j++) {
                // don't want row/UArray_at in inner loop
                UArray_T thisrow = row(array2, j); 
                for (int i = 0; i < w; i++)
                        apply(i, j, array2, UArray_at(thisrow, i), cl);
        }
}
//#line 209 "www/solutions/uarray2.nw"
void UArray2_map_col_major(T array2, 
                           void apply(int i, int j, T array2, 
                                      void *elem, void *cl), 
                           void *cl)
{
        assert(array2);
        int h = array2->height;  // keeping height and width in registers 
        int w = array2->width;   // avoids extra memory traffic
        for (int i = 0; i < w; i++)
                for (int j = 0; j < h; j++)
                        apply(i, j, array2, UArray_at(row(array2, j), i), cl);
}
