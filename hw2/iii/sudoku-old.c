#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <pnmrdr.h>
#include "uarray2.h"

//const unsigned int 9 = 9;
struct Checker {
    int chk_nine[9];
    bool OK;
};

int check_board(FILE *fp);
bool read_pixel(UArray2_T board, Pnmrdr_T reader, Pnmrdr_mapdata data);
// void check_and_print(int i, int j, UArray2_T a, void *p1, void *p2);
void write_array(int col, int row, UArray2_T board, void *val, void *cl);
void clean_up(FILE *fp, UArray2_T board, UArray2_T board2, Pnmrdr_T reader,
    struct Checker *bdchk);
void check_cat(int col, int row, UArray2_T board, void *val, void *cl);
void realign(int col, int row, UArray2_T board, void *val, void *cl);

int main (int argc, char *argv[]) {
    FILE *fp;
    assert(argc <= 2);
    if (argc == 2) {
        fp = fopen(argv[1], "r");
        return check_board(fp);
    } else { 
        return check_board(stdin);
    }
}

int check_board(FILE *fp) {
    assert(fp != NULL);
    Pnmrdr_T reader = Pnmrdr_new(fp);
    Pnmrdr_mapdata data = Pnmrdr_data(reader);
    assert(data.type == Pnmrdr_gray);
    if (data.denominator != 9 || data.width != 9 
        || data.height != 9) {
        clean_up(fp, NULL, NULL, reader, NULL);
        return 1;
    }

    UArray2_T board = UArray2_new(9, 9, sizeof(int));
    UArray2_map_row_major(board, write_array, reader);

    struct Checker *bdchk = 
        (struct Checker *) malloc(sizeof(struct Checker));
    assert(bdchk != NULL);
    memset(bdchk->chk_nine, 0, sizeof(bdchk->chk_nine));
    bdchk->OK = true;
    UArray2_map_row_major(board, check_cat, bdchk);
    UArray2_map_col_major(board, check_cat, bdchk);
    /* Check the boxes: */
    UArray2_T rearranged_b = UArray2_new(9, 9, sizeof(int));
    UArray2_map_row_major(board, realign, rearranged_b);
    UArray2_map_row_major(rearranged_b, check_cat, bdchk);
    for (int i = 0; i < 9; i++) {
        bdchk->OK &= (bdchk->chk_nine[i] == 1);
    }
    bool good_board = bdchk->OK;
    clean_up(fp, board, rearranged_b, reader, bdchk);
    return !good_board;
//
    // check if bdchk is in ok state here. (OK == true, array all ones)

    // for (int row = 0; row < UArray2_height(board); row++) {
    //     for (int col = 0; col < UArray2_width(board); col++) {
    //         int curr = *((int *)UArray2_at(board, col, row));
    //         if (curr > 9 || curr < 1 || chk_nine[curr - 1] != 0) {
    //             clean_up(fp, board, reader);
    //             return 1;
    //         } 
    //         chk_nine[curr - 1] = 1;
    //     }
    //     memset(chk_nine, 0, sizeof(chk_nine));
    // }
    
    // for (int col = 0; col < UArray2_width(board); col++) {
    //     for (int row = 0; row < UArray2_height(board); row++) {
    //         int curr = *((int *)UArray2_at(board, col, row));
    //         if (curr > 9 || curr < 1 || chk_nine[curr - 1] != 0) {
    //             clean_up(fp, board, reader);
    //             return 1;
    //         } 
    //         chk_nine[curr - 1] = 1;
    //     }
    //     memset(chk_nine, 0, sizeof(chk_nine));
    // }
    
    // for (int box_num = 0; box_num < 9; box_num ++) {
    //     int box_row = box_num / 3;
    //     int box_col = box_num % 3;
    //     for (int count = 0; count < 9; count++) {
    //         int curr = *((int *)UArray2_at(board, 
    //             box_col * 3 + count % 3, box_row * 3 + count / 3));
    //         if (curr > 9 || curr < 1 || chk_nine[curr - 1] != 0) {
    //             clean_up(fp, board, reader);
    //             return 1;
    //         } 
    //         chk_nine[curr - 1] = 1;
    //     }
    //     memset(chk_nine, 0, sizeof(chk_nine));
    // }

}

void check_cat(int col, int row, UArray2_T board, void *val, void *cl) {
    (void) col; (void) row; (void) board;
    struct Checker *bdchk =  (struct Checker *)cl;
    int curr = *((int *)val);
    if (curr > 9 || curr < 1) {
        bdchk->OK = false;
    } else if (bdchk->chk_nine[curr - 1] != 0) {
        for (int i = 0; i < 9; i++) {
            bdchk->OK &= (bdchk->chk_nine[i] == 1);
        }
        memset(bdchk->chk_nine, 0, sizeof(bdchk->chk_nine));
    }
    bdchk->chk_nine[curr - 1] += 1;
}

void realign(int col, int row, UArray2_T board, void *val, void *cl) {
    (void) board;
    int box_num = ((row * 9 + col) / 27) * 3 + (((row * 9 + col) % 9) / 3);
    int count = (row % 3) * 3 + (col % 3);
    UArray2_T new_array = (UArray2_T) cl;
    *((int *) UArray2_at(new_array, count, box_num)) = 
        *((int *) val); 
}

void write_array(int col, int row, UArray2_T board, void *val, void *cl) {
    (void) col; (void) row; (void) board;
    Pnmrdr_T reader = (Pnmrdr_T) cl;
    *((int *)val) = Pnmrdr_get(reader);
}

void clean_up(FILE *fp, UArray2_T board, UArray2_T board2, Pnmrdr_T reader,
    struct Checker *bdcheck) {
    fclose(fp);
    if (bdcheck != NULL) {
        free(bdcheck);
    }
    UArray2_free(&board);
    UArray2_free(&board2);
    Pnmrdr_free(&reader);
}

/*bool read_pixel(UArray2_T board, Pnmrdr_T reader, Pnmrdr_mapdata data) {
    for (int row = 0; row < (int)data.height; row++) {
        for (int col = 0; col < (int)data.width; col++){
            int toAdd = Pnmrdr_get(reader);
            if (toAdd <= 0 || toAdd > 9) {
                return false;
            }
            *((int *)UArray2_at(board, col, row)) = toAdd;
        }
    }
    return true;
}*/


/*void check_and_print(int i, int j, UArray2_T a, void *p1, void *p2) {
    int *entry_p = p1;
    *((bool *)p2) &= UArray2_at(a, i, j) == entry_p;
    printf("ar[%d,%d]: %d\n", i, j, *((int *)p1));
}*/

