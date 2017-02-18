/*
 *     filename: ppmtrans.c
 *     partner 1 name: Peter Vondras       Login: peter
 *     partner 2 name: Hongyan Wang        Login: hwang10
 *     date: February 25th, 2016
 *     assignment: hw3
 *
 *     summary: This file will facilitate the transformation of an image file
 *              that is provided on stdin or by filename. It will accept the 
 *              arguments:
 *                      -row-major 
 *                      -col-major 
 *                      -block-major 
 *                      -rotate 0
 *                      -rotate 90
 *                      -rotate 180
 *                      -rotate 270
 *                      -flip horizontal
 *                      -flip vertical
 *                      -transpose
 *                      -time <filename to store result>
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mem.h>
#include "cputiming.h"
#include "assert.h"
#include "a2methods.h"
#include "a2plain.h"
#include "a2blocked.h"
#include "pnm.h"

#define SET_METHODS(METHODS, MAP, WHAT) do {                    \
        methods = (METHODS);                                    \
        assert(methods != NULL);                                \
        map = methods->MAP;                                     \
        if (map == NULL) {                                      \
                fprintf(stderr, "%s does not support "          \
                                WHAT "mapping\n",               \
                                argv[0]);                       \
                exit(1);                                        \
        }                                                       \
} while (0)

typedef void ppmtrans_func(int *col, int *row, int width, int height);

/* sent to apply function */
struct transform_cl {
        /* function pointer to transform row and col" */
        ppmtrans_func *transform_row_col;
        Pnm_ppm final_image;
};

void setup_final_image(Pnm_ppm original_image, int rotation, int action,
                       struct transform_cl *mycl_p);

/* each function will transform row and col appropriately */
void rotate0   (int *col, int *row, int width, int height);
void rotate90  (int *col, int *row, int width, int height);
void rotate180 (int *col, int *row, int width, int height);
void rotate270 (int *col, int *row, int width, int height);
void vertical  (int *col, int *row, int width, int height);
void horizontal(int *col, int *row, int width, int height);
void transpose (int *col, int *row, int width, int height);

/* apply function for copying each pixel in image */
void transform_pixel(int col, int row, A2Methods_UArray2 array, void *pixel, 
                     void *final_image);

/* outputs log file */
void save_time(double time_used, Pnm_ppm final_image, char *time_file_name,
               int action, int rotation, char *map_type);
static void usage(const char *progname);

enum actionType {NONE, HORIZONTAL, VERTICAL, TRANSPOSE};

int main(int argc, char *argv[]) 
{
        int rotation, i, size, action;
        double time_used;
        char *map_type, *time_file_name;
        Pnm_ppm original_image, final_image;
        CPUTime_T timer;
        FILE *fp;

        /* declare initial values */
        map_type        = "default";
        time_file_name  = NULL;
        fp              = NULL;
        rotation        = 0;
        action          = NONE; 

        /* default to UArray2 methods */
        A2Methods_T methods = uarray2_methods_plain;  
        assert(methods);

        /* default to best map */
        A2Methods_mapfun *map = methods->map_default; 
        assert(map);

        /* setup for arguments */
        for (i = 1; i < argc; i++) {
                if (strcmp(argv[i], "-row-major") == 0) {
                        map_type = "row-major";
                        SET_METHODS(uarray2_methods_plain, map_row_major,
                                    "row-major");
                } else if (strcmp(argv[i], "-col-major") == 0) {
                        map_type = "col-major";
                        SET_METHODS(uarray2_methods_plain, map_col_major,
                                    "column-major");
                } else if (strcmp(argv[i], "-block-major") == 0) {
                        map_type = "block-major";
                        SET_METHODS(uarray2_methods_blocked, map_block_major,
                                    "block-major");
                } else if (strcmp(argv[i], "-rotate") == 0) {
                        if (!(i + 1 < argc)) {      /* no rotate value */
                                usage(argv[0]);
                        }
                        char *endptr;
                        rotation = strtol(argv[++i], &endptr, 10);
                        if (!(rotation == 0 || rotation == 90 ||
                            rotation == 180 || rotation == 270)) {
                                fprintf(stderr, 
                                        "Rotation must be 0, 90 180 or 270\n");
                                usage(argv[0]);
                        }
                        if (!(*endptr == '\0')) {    /* Not a number */
                                usage(argv[0]);
                        }
                } else if (strcmp(argv[i], "-flip") == 0) {
                        if (strcmp(argv[i + 1], "horizontal") == 0)
                                action = HORIZONTAL;
                        else if (strcmp(argv[i + 1], "vertical") == 0)
                                action = VERTICAL;
                        else {
                                fprintf(stderr, "Wrong arguments\n");
                                usage(argv[0]);
                        }
                        i++;
                } else if (strcmp(argv[i], "-transpose") == 0) {
                        if (action == NONE)
                                action = TRANSPOSE;
                } else if (strcmp(argv[i], "-time") == 0) {
                        time_file_name = argv[++i];
                } else if (*argv[i] == '-') {
                        fprintf(stderr, "%s: unknown option '%s'\n",
                                argv[0], argv[i]);
                } else if (argc - i > 1) {
                        fprintf(stderr, "Too many arguments\n");
                        usage(argv[0]);
                } else if (fp == NULL) {
                        fp = fopen(argv[i], "rb");
                        if (fp == NULL) {
                                fprintf(stderr, "Unable to open file\n");
                                exit(1); 
                        }
                } else {
                        break;
                }
        }

        /* read from stdin */
        if (fp == NULL) fp = stdin;

        /* create original and final images */
        original_image = Pnm_ppmread(fp, methods);
        NEW(final_image);
        struct transform_cl mycl = { rotate0, final_image };
        setup_final_image(original_image, rotation, action, &mycl);
        
        /* initialize final_image values */
        size = methods->size(original_image->pixels);
        final_image->denominator = original_image->denominator;
        final_image->methods = methods;
        final_image->pixels = methods->new(final_image->width,
                                           final_image->height, size);

        /* transform image and time process */
        timer = CPUTime_New();
        CPUTime_Start(timer);
        (*map)(original_image->pixels, transform_pixel, &mycl);
        time_used = CPUTime_Stop(timer);
        save_time(time_used, final_image, time_file_name, action,
                  rotation, map_type);

        /* free memory */
        CPUTime_Free(&timer);
        Pnm_ppmwrite(stdout, final_image);
        Pnm_ppmfree(&original_image);
        Pnm_ppmfree(&final_image);
        fclose(fp); 

        exit(0);
}

/* 
 * provides logic for which type of transformation to do and what size to make
 * the final image. We decided to get this work done in the beginning instead
 * of doing it for every pixel. 
 */
void setup_final_image(Pnm_ppm original_image, int rotation, int action,
                       struct transform_cl *mycl_p)
{     
        mycl_p->final_image->width  = original_image->width;
        mycl_p->final_image->height = original_image->height;

        if (rotation == 90) {
                mycl_p->final_image->width  = original_image->height;
                mycl_p->final_image->height = original_image->width;
                mycl_p->transform_row_col = rotate90;
        } else if (rotation == 180) {
                mycl_p->transform_row_col = rotate180;
        } else if (rotation == 270) {
                mycl_p->final_image->width  = original_image->height;
                mycl_p->final_image->height = original_image->width;
                mycl_p->transform_row_col = rotate270;
        } else if (action == HORIZONTAL) {
                mycl_p->transform_row_col = horizontal;
        } else if (action == VERTICAL) {
                mycl_p->transform_row_col = vertical;
        } else if (action == TRANSPOSE) {
                mycl_p->final_image->width  = original_image->height;
                mycl_p->final_image->height = original_image->width;
                mycl_p->transform_row_col = transpose;
        }
}

/* will copy the pixel to the appropriate location in final_image */
void transform_pixel(int col, int row, A2Methods_UArray2 array,
                     void *pixel, void *vcl)
{
        (void)array;
        struct transform_cl *cl = vcl;
        Pnm_ppm tempImage = cl->final_image;
        Pnm_rgb pixel_original = pixel;
        Pnm_rgb pixel_final;
        
        // convert to new col, row values
        cl->transform_row_col(&col, &row, tempImage->methods->width(array),
                              tempImage->methods->height(array));
        pixel_final = tempImage->methods->at(tempImage->pixels, col, row);

        /* copy pixel */
        *pixel_final = *pixel_original;
}

/* modify col and row for 0 deg rotation */
void rotate0(int *col, int *row, int width, int height)
{
        (void)width;
        (void)height;
        (void)row;
        (void)col;
}

/* modify col and row for 90 deg rotation */
void rotate90(int *col, int *row, int width, int height)
{
        (void)width;
        int row_new;
        row_new = *col;
        *col    = height - *row - 1;
        *row    = row_new;
}

/* modify col and row for 180 deg rotation */
void rotate180(int *col, int *row, int width, int height)
{
        int row_new;
        row_new = height - *row -1;
        *col    = width - *col - 1;
        *row    = row_new;
}

/* modify col and row for 270 deg rotation */
void rotate270(int *col, int *row, int width, int height)
{
        (void)height;
        int row_new;
        row_new = width - *col - 1;
        *col    = *row;
        *row    = row_new;
}

/* modify col and row for horizontal transformation */
void horizontal(int *col, int *row, int width, int height)
{
        (void) height;
        (void) row;
        *col = width - *col - 1;
}

/* modify col and row for vertical transformation */
void vertical(int *col, int *row, int width, int height)
{
        (void)width;
        int row_new;
        row_new = height - *row - 1;
        *col    = *col;
        *row    = row_new;
}

/* modify col and row for transpose transformation */
void transpose(int *col, int *row, int width, int height)
{
        (void)width;
        (void)height;
        int row_new;
        row_new = *col;
        *col    = *row;
        *row    = row_new;
}

/* outputs log data to file */
void save_time(double time_used, Pnm_ppm final_image, char *time_file_name,
               int action, int rotation, char *map_type)
{
        if (time_file_name == NULL) 
                return;

        int numPixels;
        double average;

        numPixels = final_image->width * final_image->height;
        average   = time_used / numPixels;

        FILE *timings_file = fopen(time_file_name, "a");
        fprintf(timings_file, "**********************************\n");
        fprintf(timings_file, "\nAll work done on \"homework server\"\n");
        fprintf(timings_file, "Rotation:             %12d\n", rotation);

        if (action == 1) /* logic for none rotation  transformations */
                fprintf(timings_file, "Transformation:          HORIZONTAL\n");
        else if (action == 2)
                fprintf(timings_file, "Transformation:          VERTICAL\n");
        else if (action == 3)
                fprintf(timings_file, "Transformation:          TRANSPOSE\n");

        fprintf(timings_file, "Map category:            %s\n", map_type);
        fprintf(timings_file, "Number of pixels:     %12d\n", numPixels);
        fprintf(timings_file, "Total Time:           %12.1f\n", time_used);
        fprintf(timings_file, "Time Per Pixel:       %12.1f\n\n", average);
        fclose(timings_file);
}

static void usage(const char *progname)
{
        fprintf(stderr, "Usage: %s [-rotate <angle>] "
                        "[-{row,col,block}-major] [filename]\n",
                        progname);
        exit(1);
}












