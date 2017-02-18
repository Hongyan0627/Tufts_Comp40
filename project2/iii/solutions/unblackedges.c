/*
* unblackedges.c
* purpose: to unblacken the edges of a portable graymap file
* and output the result
* by: Derick Yang and Hongyan Wang
* date: February 15, 2016
*/
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <pnmrdr.h>
#include <seq.h>
#include <except.h>
#include "bit2.h"

extern const Except_T Pnmrdr_Badformat;
Except_T Not_pbm = {"Input file is pbm file."};

/*
* bitPoint is a struct to hold a location within the bitmap
*/
struct bitPoint {
        int col;
        int row;
};

/* clean_blackedges cleans the edges and prints the result. */
void clean_blackedges(FILE *fp);
/* write_bitmap writes the input from the file/stdin to an Bit2_T */
void write_bitmap(Bit2_T bitmap, Pnmrdr_T reader, int width, int height);
/* print_output prints a bitmap. */
void print_output(Bit2_T bitmap);
/* check_edges checks the edges for black bits. */
void check_edges(Bit2_T bitmap);
/* expand_pixel checks all neighboring pixels of an black edge pixel. */
void expand_pixel(Bit2_T bitmap, Bit2_T visited, struct bitPoint *bp);
/* enqueue adds a location to the queue. */
void enqueue(Bit2_T bitmap, Bit2_T visited, Seq_T queue, int col, int row);
/* create_bp allocates memory and initializes a new bitPoint. */
struct bitPoint *create_bp(int col, int row);
/* initializes a in a bitmap to 0. */
void init_zeros(int col, int row, Bit2_T bitmap, int curr_val, void *cl);

/*
* The unblackedges program unblackens the edges of a file given on
* stdin or with a filename, and outputs the result.
*/
int main (int argc, char *argv[]) {
        FILE *fp;
        
        if (argc > 2) { /* handle too many inputs */
                fprintf(stderr, "Too many inputs.\n");
                exit(1);
        } else if (argc == 2) { /* read from file */
                fp = fopen(argv[1], "r");
                if (fp == NULL) {
                        fprintf(stderr, "Fail to open file.\n");
                        exit(1);
                }
                clean_blackedges(fp);
                fclose(fp);
        } else { /* read from stdin */
                clean_blackedges(stdin);
        }
        return 0;
}

/* 
* clean_blackedges() takes a file pointer and prints the
* unblackened version.
*/
void clean_blackedges(FILE *fp) {
        Pnmrdr_T reader; 
        Pnmrdr_mapdata data;
        Bit2_T bitmap;
        /* Catch exceptions with try-catch block */
        TRY        
                reader = Pnmrdr_new(fp);
                data = Pnmrdr_data(reader);

                if (data.type != Pnmrdr_bit) {
                        RAISE(Not_pbm);
                }

                /* everything ok, start removing edges */
                bitmap = Bit2_new(data.width, data.height);
                write_bitmap(bitmap, reader, (int) data.width, 
                        (int) data.height);
                check_edges(bitmap);
                print_output(bitmap);
                Bit2_free(&bitmap);
                Pnmrdr_free(&reader);

        EXCEPT(Pnmrdr_Badformat)
                fclose(fp);
                fprintf(stderr, "%s\n", "Input not valid format.");
                exit(1);
        EXCEPT(Not_pbm)
                fclose(fp);
                Pnmrdr_free(&reader);
                fprintf(stderr, "%s\n", "Input file is not pbm file.");
                exit(1);
        END_TRY;
}

/* 
* write_bitmap() writes a file to a Bit2_T map.
* args: the bitmap to write to, a reader, the width of the
* map, and the height of the map.
*/
void write_bitmap(Bit2_T bitmap, Pnmrdr_T reader, int width, int height) {
        for (int row = 0; row < height; row++) {
                for (int col = 0; col < width; col++) {
                        Bit2_put(bitmap, col, row, Pnmrdr_get(reader));
                }
        }
}

/*
* print_output() prints the resulting file to stdout.
* args: the bitmap to print out.
*/
void print_output(Bit2_T bitmap) {
        int width = Bit2_width(bitmap);
        int height = Bit2_height(bitmap);
        printf("P1\n");
        printf("%d %d\n", width, height);

        for (int row = 0; row < height; row++) {
                for (int col = 0; col < width; col++) {
                        printf("%d", Bit2_get(bitmap, col, row));
        
                        if (col % 70 == 0 && col > 0) {
                                printf("\n");
                        }
        
                }
                printf("\n");
        }
}

/*
* check_edges() checks each pixel on the edge of the bitmap, 
* and whiten the black edge pixel's neighbors.
* args: the bitmap to check.
*/
void check_edges(Bit2_T bitmap) {
        Bit2_T visited = Bit2_new(Bit2_width(bitmap), Bit2_height(bitmap));
        Bit2_map_row_major(visited, init_zeros, NULL);

        for (int row = 0; row < Bit2_height(bitmap); row++) {
                if (row == 0 || row == (Bit2_height(bitmap) - 1)) {
                        for (int col = 0; col < Bit2_width(bitmap); col++) {

                                if (Bit2_get(bitmap, col, row) == 1) {
                                        struct bitPoint *bp = 
                                                create_bp(col, row);
                                        expand_pixel(bitmap, visited, bp);
                                }

                        }
                } else {

                        if (Bit2_get(bitmap, 0, row) == 1) {
                                struct bitPoint *bp1 = create_bp(0, row);
                                expand_pixel(bitmap, visited, bp1);
                        }

                        if (Bit2_get(bitmap, 
                                Bit2_width(bitmap) - 1, row) == 1) {
                                struct bitPoint *bp2 = 
                                        create_bp(Bit2_width(bitmap)-1, row);
                                expand_pixel(bitmap, visited, bp2);
                        }

                }
        }
        Bit2_free(&visited);
}

/*
* init_zeros() initializes a pixel in a bitmap to 0
*/
void init_zeros(int col, int row, Bit2_T bitmap, int curr_val, void *cl) {
        (void) curr_val; (void) cl;
        Bit2_put(bitmap, col, row, 0);
}

/*
* expand_pixel() utilizes a queue to whiten all the neighboring
* pixels of an edge pixel.
* args: the bitmap, the array of visited pixels,
* the coordinates of an edge point that is black.
*/
void expand_pixel(Bit2_T bitmap, Bit2_T visited, struct bitPoint *bp) {
        Seq_T queue = Seq_new(0);
        Seq_addhi(queue, bp);
        Bit2_put(visited, bp->col, bp->row, 1);

        while (Seq_length(queue) > 0) {
                struct bitPoint *curr = (struct bitPoint *) Seq_remlo(queue);
                /* try enqueueing all neighbors */
                enqueue(bitmap, visited, queue, curr->col, curr->row - 1);
                enqueue(bitmap, visited, queue, curr->col, curr->row + 1);
                enqueue(bitmap, visited, queue, curr->col - 1, curr->row);
                enqueue(bitmap, visited, queue, curr->col + 1, curr->row);
                Bit2_put(bitmap, curr->col, curr->row, 0);
        
                if (curr != NULL) {
                        free(curr);
                        curr = NULL;
                }
        }

        Seq_free(&queue);
}

/*
* enqueue() checks if the cell at the given coordinates should
* be put in the queue, and then puts it in the queue if necessary
* args: the bitmap, the array of visited pixels, a queue to add to, 
* and the coordinates of the point to add.
*/
void enqueue(Bit2_T bitmap, Bit2_T visited, Seq_T queue, int col, int row) {
        if (col < 0 || col >= Bit2_width(visited) || row < 0 || 
                row >= Bit2_height(visited) || 
                Bit2_get(bitmap, col, row) == 0 ||
                Bit2_get(visited, col, row) == 1) {
                return;
        } else {
                struct bitPoint *bp_nb = 
                        (struct bitPoint *) malloc(sizeof(*bp_nb));
                assert(bp_nb != NULL);
                bp_nb->col = col;
                bp_nb->row = row;
                Seq_addhi(queue, bp_nb);
                Bit2_put(visited, col, row, 1);
        }
}

/*
* create_bp() allocates and assigns coordinates to a bitPoint.
* args: the coordinates of the point to create
* rets: a pointer to a bitPoint on the heap.
*/
struct bitPoint *create_bp(int col, int row) {
        struct bitPoint *bp = 
                (struct bitPoint *) malloc(sizeof(*bp));
        assert(bp != NULL);
        bp->col = col;
        bp->row = row;
        return bp;
}
