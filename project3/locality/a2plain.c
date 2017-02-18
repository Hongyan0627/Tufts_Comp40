/*
 *     filename: a2plain.c
 *     partner 1 name: Peter Vondras       Login: peter
 *     partner 2 name: Hongyan Wang        Login: hwang10
 *     date: February 25th, 2016
 *     assignment: hw3
 *
 *     summary: implementation of A2Methods which uses UArray2
 *                      
 */

#include <stdlib.h>
#include <a2plain.h>
#include "uarray2.h"

typedef A2Methods_UArray2 A2;   /* private abbreviation */

static A2 new(int width, int height, int size)
{
        return UArray2_new(width, height, size);
}

static A2Methods_UArray2 new_with_blocksize(int width, int height, int size,
                                            int blocksize)
{
        (void)blocksize;
        return UArray2_new(width, height, size);
}

static void a2free(A2 * array2_p)
{
    UArray2_free((UArray2_T *) array2_p);
}

static int width(A2 array2)
{
    return UArray2_width(array2);
}

static int height(A2 array2)
{
    return UArray2_height(array2);
}

static int size(A2 array2)
{
    return UArray2_size(array2);
}

static int blocksize(A2 array2)
{
    (void) array2;
    return 0;
}

static A2Methods_Object *at(A2 array2, int i, int j)
{
    return UArray2_at(array2, i, j);
}

/* function type for UArray2T */
typedef void applyfun(int i, int j, UArray2_T arrayb, void *elem, void *cl);

static void map_row_major(A2 array2, A2Methods_applyfun apply, void *cl)
{
    UArray2_map_row_major(array2, (applyfun *) apply, cl);
}

static void map_col_major(A2 array2, A2Methods_applyfun apply, void *cl)
{
    UArray2_map_col_major(array2, (applyfun *) apply, cl);
}

/* holds the limited information version of mapping function details */
struct small_closure {
    A2Methods_smallapplyfun *apply;
    void *cl;
};

/* 
 * provides a mapping function which does not allow access to other cells in
 * the array. This would be useful for acting on individual cells when no other
 * cell information is needed.
 */
static void apply_small(int i, int j, UArray2_T array2, void *elem, void *vcl)
{
    struct small_closure *cl = vcl;
    (void)i;
    (void)j;
    (void)array2;
    cl->apply(elem, cl->cl);
}

/* 
 * provides a mapping function which does not allow access to other cells in
 * the array. This would be useful for acting on individual cells when no other
 * cell information is needed.
 */
static void small_map_row_major(A2 a2, A2Methods_smallapplyfun apply,
                  void *cl)
{
    struct small_closure mycl = { apply, cl };
    UArray2_map_row_major(a2, apply_small, &mycl);
}

/* 
 * provides a mapping function which does not allow access to other cells in
 * the array. This would be useful for acting on individual cells when no other
 * cell information is needed.
 */
static void small_map_col_major(A2 a2, A2Methods_smallapplyfun apply,
                  void *cl)
{
    struct small_closure mycl = { apply, cl };
    UArray2_map_col_major(a2, apply_small, &mycl);
}

/* method suite of function pointers */
static struct A2Methods_T uarray2_methods_plain_struct = {
    new,
    new_with_blocksize,
    a2free,
    width,
    height,
    size,
    blocksize,
    at,
    map_row_major,
    map_col_major,
    NULL,                   /* map_block_major       */
    map_row_major,          /* map_default           */
    small_map_row_major,
    small_map_col_major,
    NULL,                   /* small_map_block_major */
    small_map_row_major,    /* small_map_default     */
};

        /* exported pointer to the struct */
        A2Methods_T uarray2_methods_plain = &uarray2_methods_plain_struct;
