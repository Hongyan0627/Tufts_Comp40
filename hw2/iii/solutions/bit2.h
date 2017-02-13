typedef struct Bit2_T *Bit2_T;


/*
* Width = number of columns
* Height = number of rows
*/

/* Bit2_new returns a new Bit2 array */
Bit2_T Bit2_new(int width, int height);

/* 
* This function maps apply() to all elements in the array,
* using the col major order
*/
void Bit2_map_col_major(Bit2_T the_array, 
        void apply(int col, int row, Bit2_T a, 
        int curr_val, void *cl), void *cl);

/* 
* This function maps apply() to all elements in the array,
* using the row major order
*/
void Bit2_map_row_major(Bit2_T the_array, 
        void apply(int col, int row, Bit2_T a, 
        int curr_val, void *cl), void *cl);

/* 
* This function replaces the marker at the given pair of indicesto
* the marker. Returns the previous value
*/
int Bit2_put(Bit2_T the_array, int col, int row, int marker);

/*
* This function returns the value of the map at the 
* given pair of indices.
*/
int Bit2_get(Bit2_T the_array, int col, int row);

/* This function returns the width of the array */
int Bit2_width(Bit2_T the_array);

/* This function returns the height of the array*/
int Bit2_height(Bit2_T the_array);   

/* This function frees space in the array*/
void Bit2_free(Bit2_T *the_array);
