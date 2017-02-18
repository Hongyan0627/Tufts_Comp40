/*
* sudoku.c
* purpose: a program to check the validity of a sudoku board
* input through a filename or stdin.
* bv: Derick Yang and Hongyan Wang
* date: February 15 2016
*/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <pnmrdr.h>
#include <except.h>
#include "uarray2.h"

/* 
* Checker is a struct to pass as the closure for the mapping
* function. It maintains a running checklist for the numbers 1-9,
* and a boolean value representing the validity of the board.
*/
struct Checker {
        /* a checklist, reset at the end of each valid row/col */
        int chk_nine[9]; 
        bool OK;
};

Except_T Reader_failed = {"Reader failed."};

/* check_board() check for a valid sudoku board. */
int check_board(FILE *fp);
/* write_array() writes the file into a UArray2_T. */
void write_array(int col, int row, UArray2_T board, void *val, void *cl);
/* check_cat() checks a certain category for validity: row, col or box. */
void check_cat(int col, int row, UArray2_T board, void *val, void *cl);
/* realign() is used to map boxes to rows in order to use the check_cat func*/
void realign(int col, int row, UArray2_T board, void *val, void *cl);
/* cleanup() frees space before returning. */
void cleanup(FILE *fp, UArray2_T board, UArray2_T board2, Pnmrdr_T reader,
        struct Checker *bdchk);

/* 
* This program reads a pnm file and checks whether it is a valid Sudoku
* board.
*/
int main (int argc, char *argv[]) {
        FILE *fp;
        assert(argc <= 2); /* invalid usage */
        if (argc == 2) { /* read from file */
                fp = fopen(argv[1], "r");
                return check_board(fp);
        } else { /* else, read from stdin */
                return check_board(stdin);
        }
}

/*
* check_board() checks if a sudoku board is valid.
* args: a file pointer, either to stdin or a file that was opened
* rets: an int, 0 if the board is valid, 1 if it is not.
*/
int check_board(FILE *fp) {
        assert(fp != NULL);
        Pnmrdr_T reader;
        Pnmrdr_mapdata data;
        TRY
                reader = Pnmrdr_new(fp);
                data = Pnmrdr_data(reader);
        EXCEPT(Pnmrdr_Badformat)
                fclose(fp);
                fprintf(stderr, "%s\n", "Input not valid format.");
                exit(1);
        END_TRY;

        /* Check for correct sizes/format */
        if (data.type != Pnmrdr_gray) {
                cleanup(fp, NULL, NULL, reader, NULL);
                assert(0);
        } 

        if (data.denominator != 9 || data.width != 9 || data.height != 9) {
                cleanup(fp, NULL, NULL, reader, NULL);
                return 1;
        }
        
        /* Initialize the board and write the file to the board. */
        UArray2_T board = UArray2_new(9, 9, sizeof(int));
        UArray2_map_row_major(board, write_array, reader);
        
        /* Initialize the checker. */
        struct Checker *bdchk = 
                (struct Checker *) malloc(sizeof(struct Checker));
        assert(bdchk != NULL);
        memset(bdchk->chk_nine, 0, sizeof(bdchk->chk_nine));
        bdchk->OK = true;
        
        /* Check rows and columns: */
        UArray2_map_row_major(board, check_cat, bdchk);
        UArray2_map_col_major(board, check_cat, bdchk);
        
        /* Check the boxes (first, map old board to new board): */
        UArray2_T rearranged_b = UArray2_new(9, 9, sizeof(int));
        UArray2_map_row_major(board, realign, rearranged_b);
        UArray2_map_row_major(rearranged_b, check_cat, bdchk);
        
        /* Check that the checklist is full: */
        for (int i = 0; i < 9; i++) {
                bdchk->OK &= (bdchk->chk_nine[i] == 1);
        }
        
        bool good_board = bdchk->OK;
        cleanup(fp, board, rearranged_b, reader, bdchk);
        return !good_board;
}

/*
* check_cat() is a mapped function that will check if a row/col is
* valid or not. Using a zero array of length 9, it checks that each
* number is there. If the category is invalid, it updates the boolean 
* for the entire board to false.
* args: col, row, the board (not used), the value at the index, and
* the closure (which is a Checker struct).
*/
void check_cat(int col, int row, UArray2_T board, void *val, void *cl) {
        (void) col; (void) row; (void) board;
        struct Checker *bdchk =  (struct Checker *)cl;
        int curr = *((int *)val);
        if (curr > 9 || curr < 1) {
                bdchk->OK = false;
        } else if (bdchk->chk_nine[curr - 1] != 0) {
                /* check if we have reached the end of a valid row/col */
                for (int i = 0; i < 9; i++) {
                        bdchk->OK &= (bdchk->chk_nine[i] == 1);
                }
                /* reset the checklist to all unchecked */
                memset(bdchk->chk_nine, 0, sizeof(bdchk->chk_nine));
        }
        bdchk->chk_nine[curr - 1] += 1;
}

/*
* realign() creates a new board to store a each box in a row. We use this
* so that we can use another mapping to check the validity of each box
* args: col, row, the board, the original value, and the closure 
* (which is the UArray2_T we are writing)
*/
void realign(int col, int row, UArray2_T board, void *val, void *cl) {
        (void) board;
        /* calculate the new box num */
        int box_num = ((row * 9 + col) / 27) * 3 
                + (((row * 9 + col) % 9) / 3);
        int count = (row % 3) * 3 + (col % 3);
        UArray2_T new_array = (UArray2_T) cl;
        *((int *) UArray2_at(new_array, count, box_num)) = *((int *) val); 
}

/*
* write_array() is a mapped function that will input values from the file
* into a 2 dimensional array.
* args: col, row, the board (voided), the value at the index, and the 
* closure (which is a Pnmrdr_T)
*/
void write_array(int col, int row, UArray2_T board, void *val, void *cl) {
        (void) col; (void) row; (void) board;
        Pnmrdr_T reader = (Pnmrdr_T) cl;
        *((int *)val) = Pnmrdr_get(reader);
}

/*
* cleanup() cleans up memory so that there are no memory leaks
* args: all the things we want to free
*/
void cleanup(FILE *fp, UArray2_T board, UArray2_T board2, Pnmrdr_T reader,
        struct Checker *bdcheck) {
        fclose(fp);
        if (bdcheck != NULL) {
                free(bdcheck);
        }
        UArray2_free(&board);
        UArray2_free(&board2);
        Pnmrdr_free(&reader);
}