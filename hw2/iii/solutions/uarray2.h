typedef struct UArray2_T *UArray2_T;

/*
* Width = number of columns
* Height = number of rows
*/

/* UArray2_new returns a new Uarray */
UArray2_T UArray2_new(int width, int height, int size);

/* 
* This function maps apply() to all elements in the array,
* using the col major order
*/
void UArray2_map_col_major(UArray2_T the_array, 
        void apply(int col, int row, UArray2_T a, 
        void *curr_val, void *cl), void *cl);

/* 
* This function maps apply() to all elements in the array,
* using the row major order
*/
void UArray2_map_row_major(UArray2_T the_array, 
        void apply(int col, int row, UArray2_T a, 
        void *curr_val, void *cl), void *cl);

/* This function returns a pointer to the value at the given indices*/
void *UArray2_at(UArray2_T the_array, int col, int row);

/* This function returns the width of the array */
int UArray2_width(UArray2_T the_array);

/* This function returns the height of the array*/
int UArray2_height(UArray2_T the_array);    

/* This function returns the size of each element in the array*/
int UArray2_size(UArray2_T the_array);

/* This function frees space in the array*/
void UArray2_free(UArray2_T *the_array);
