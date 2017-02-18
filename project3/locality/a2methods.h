#ifndef A2METHODS_INCLUDED
#define A2METHODS_INCLUDED

#define A2 A2Methods_UArray2

typedef void *A2;               /* unknown type that represents a 
                                 * 2D array of 'cells'
                                 */

typedef void A2Methods_Object;  /* an unknown sequence of bytes in memory
                                 * (element of an array)
                                 */

typedef void A2Methods_applyfun(int i, int j, A2 array2,
                                A2Methods_Object *ptr, void *cl);
typedef void A2Methods_mapfun(A2 array2, A2Methods_applyfun apply, void *cl);

typedef void A2Methods_smallapplyfun(A2Methods_Object *ptr, void *cl);
typedef void A2Methods_smallmapfun(A2 a2, A2Methods_smallapplyfun f, void *cl);

/* operations on 2D arrays */

/* 
 * it is a checked run-time error to pass a NULL 2D array to any function,
 * and except as noted, a NULL function pointer is an *unchecked* r. e.
 */
typedef struct A2Methods_T {
        /* creates a distinct 2D array of memory cells, 
         * each of the given 'size'
         *
         * each cell is uninitialized
         * if the array is blocked, uses a default block size
         */
        A2(*new)(int width, int height, int size);

        /* creates a distinct 2D array of memory cells,
         * each of the given 'size'
         *
         * each cell is uninitialized
         * if array is blocked, the block size given is the number of cells
         *    along one side of a block; otherwise 'blocksize' is ignored
         */
        A2(*new_with_blocksize)(int width, int height, int size,
                                int blocksize);

        /* frees *array2p and overwrites the pointer with NULL */
        void (*free)(A2 *array2p);


        /* observe properties of the array */
        int (*width)    (A2 array2);
        int (*height)   (A2 array2);
        int (*size)     (A2 array2);
        int (*blocksize)(A2 array2);   /* for unblocked array, returns 1 */

        /* returns a pointer to the object in column i, row j
         * (checked runtime error if i or j is out of bounds)
         */
        A2Methods_Object *(*at)(A2 array2, int i, int j);

        /* mapping functions */
        /* each mapping function visits every cell in array2, and for each
         * cell it calls 'apply' with these arguments:
         *    i, the column index of the cell
         *    j, the row index of the cell
         *    array2, the array passed to the mapping function
         *    cell, a pointer to the cell
         *    cl, the closure pointer passed to the mapping function
         *
         * These functions differ only in the *order* they visit cells:
         *   - row_major visits each row before the next, in order of
         *     increasing row index; within a row, column numbers increase
         *   - col_major visits each column before the next, in order of
         *     increasing column index; within a column, row numbers increase
         *   - block_major visits each block before the next; order of
         *     blocks and order of cells within a block is not specified
         *   - map_default uses a default order that has good locality
         *
         * In any record, map_block_major may be NULL provided that
         * map_row_major and map_col_major are not NULL, and vice versa.
         */
        void (*map_row_major)(A2 array2, A2Methods_applyfun apply, void *cl);
        void (*map_col_major)(A2 array2, A2Methods_applyfun apply, void *cl);
        void (*map_block_major)(A2 array2, A2Methods_applyfun apply,
                                void *cl);
        void (*map_default)(A2 array2, A2Methods_applyfun apply, void *cl);

        /* 
         * alternative mapping functions that pass only 
         * cell pointer and closure
         */
        void (*small_map_row_major)  (A2 a2, A2Methods_smallapplyfun apply,
                                      void *cl);
        void (*small_map_col_major)  (A2 a2, A2Methods_smallapplyfun apply,
                                      void *cl);
        void (*small_map_block_major)(A2 a2, A2Methods_smallapplyfun apply,
                                      void *cl);
        void (*small_map_default)    (A2 a2, A2Methods_smallapplyfun apply,
                                      void *cl);

} *A2Methods_T;

#undef A2

#endif
