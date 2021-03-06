/*
* brightness.c
* calculate the average brightness of a pnm file
* by: Derick Yang and Hongyan Wang
* date: January 25, 2016 
*/
#include <stdlib.h>
#include <stdio.h>
#include <pnmrdr.h>
#include <assert.h>

int print_avg (FILE * img);

/* 
* Main takes either 0 or 1 arguments. If 0 arguments, handles stdin
* otherwise, handles a filename. If arguments are invalid, prints an 
* error message and returns failure.
*/
int main (int argc, char *argv[]) {
    FILE * img;
    assert(argc <= 2);
    if (argc == 2) {
        img = fopen(argv[1], "rb");
        print_avg(img);
    } else { /* argc == 1*/
        print_avg(stdin);
    }
}

/* print_avg takes a pointer to a FILE stream and determines whether
* it is in the correct format. It then calculates the average brightness
* among the pixels in the image*/
int print_avg (FILE * img) {
    /* fopen() returned null, file not found*/
    if (img == NULL) { 
        fprintf(stderr, "File not found.\n");
        exit(EXIT_FAILURE);
    } else { /* file found, determine filetype */
        Pnmrdr_T reader = Pnmrdr_new(img);
        Pnmrdr_mapdata data = Pnmrdr_data(reader);
        /* if the format is wrong, exit with an error message */
        if (data.type != Pnmrdr_gray) {
            fprintf(stderr, "Wrong file format.\n");
            Pnmrdr_free(&reader);
            fclose(img);
            exit(EXIT_FAILURE);
        }
        /* everything good so far, calculate average */
        int num_pix = data.width * data.height;
        int sum = 0;
        for (int i = 0; i < num_pix; i++) {
            sum += Pnmrdr_get(reader);
        }
        double avg = 1.0 * sum / num_pix;
        avg = avg / data.denominator;
        /* print average and clean up*/
        printf("%4.3f\n", avg);
        Pnmrdr_free(&reader);
        fclose(img);
        exit(EXIT_SUCCESS);
    }
}