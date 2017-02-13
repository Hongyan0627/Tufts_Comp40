#include "rgb_cv_trans.h"

/* We can try different denominators when we create Pnm_ppm image. */
#define DENOMINATOR 255

/* helper function to make float numbers within range [0, 1]. */
static float set_Range(float val) 
{
        if (val < 0) return 0.0;
        if (val > 1) return 1.0;
        return val;
}

/* This function will convert the pixel from RGB color space to component video
 * color space. 
 * input: Pnm_ppm image, map function and methods.
 * output: 2D array, each element is component video color pixel. */
A2Methods_UArray2 rgbImage_to_cvImage(Pnm_ppm rgb_image, 
                        A2Methods_mapfun *map, A2Methods_T methods)
{
        int width = rgb_image->width;
        int height = rgb_image->height;

        /* create a new 2D array to save component video color pixels. */
        A2Methods_UArray2 cvImage = methods->new(width, height, 
                        sizeof(struct Pnm_ybr));

        /* closure contains 2D array, methods and denominator. */
        struct a2_closure_with_denominator *my_cl = malloc(sizeof(*my_cl));
        my_cl->methods = methods;
        my_cl->array2 = cvImage;
        my_cl->denominator = rgb_image->denominator;

        /* cal map function to transfer each pixel from RGB color to component 
         * video color. */
        map(rgb_image->pixels, apply_rgb_to_cv, my_cl);

        /* free the closure. */
        if(my_cl != NULL){
                free(my_cl);
                my_cl = NULL;
        }

        return cvImage;
}

/* This apply function will transfer each RGB color pixel to component video 
 * color pixel. */
void apply_rgb_to_cv(int col, int row, A2Methods_UArray2 
                        arr2, void *elem, void *cl)
{
        (void) arr2;
        struct a2_closure_with_denominator *mcl = cl;

        /* make sure the width and height match when we transfer RGB image to 
         * component video color image. */
        if ((col > mcl->methods->width(mcl->array2)) || 
                (row > mcl->methods->height(mcl->array2))){
                return;
        }

        Pnm_ybr ybr_pixel = mcl->methods->at(mcl->array2, col, row);
        Pnm_rgb rgb_pixel = elem;

        /* transfer RGB integers to float representations. */
        float r = (rgb_pixel->red * 1.0)/(mcl->denominator);
        float g = (rgb_pixel->green * 1.0)/(mcl->denominator);
        float b = (rgb_pixel->blue * 1.0)/(mcl->denominator);

        /* compute the y, Pb, Pr values in component video color pixel. */
        ybr_pixel->y  =   0.299    * r + 0.587    * g + 0.114    * b;
        ybr_pixel->pb = - 0.168736 * r - 0.331264 * g + 0.5      * b;
        ybr_pixel->pr  =  0.5      * r - 0.418688 * g - 0.081312 * b;

}

/* This function will convert the pixel from component video color space to RGB
 * color space. 
 * input: 2D array with component video color pixel as element, map 
 *        function and methods. 
 * output: Pnm_ppm image. */
Pnm_ppm cvImage_to_rgbImage(A2Methods_UArray2 cv_image, A2Methods_mapfun *map,
                        A2Methods_T methods)
{
        int width = (methods->width(cv_image));
        int height = (methods->height(cv_image));
        /* set denominator by ourself. We can try different denominator 
         * values. */
        unsigned denominator = DENOMINATOR;
        /* allocate memory for Pnm_ppm image. */
        Pnm_ppm rgb_image;
        NEW(rgb_image);

        /* set members values of Pnm_ppm image. */
        rgb_image->width  = width;
        rgb_image->height = height;
        rgb_image->denominator = denominator;
        rgb_image->methods = methods;
        rgb_image->pixels = methods->new(width, height, 
                                        sizeof(struct Pnm_rgb));
        
        /* closure for apply function contains 2D RGB pixels, methods and 
         * denominator. */      
        struct a2_closure_with_denominator *my_cl = malloc(sizeof(*my_cl));
        my_cl->methods = methods;
        my_cl->array2 = rgb_image->pixels;
        my_cl->denominator = denominator;

        /* use the map function to transfer each component video color pixel 
         * to RGB color pixel. */
        map(cv_image, apply_cv_to_rgb, my_cl);
        /* free the closure. */
        if(my_cl != NULL){
                free(my_cl);
                my_cl = NULL;
        }

        return rgb_image;
}

/* This apply function will transfer each component video color pixel to RGB 
 * color pixel. */
void apply_cv_to_rgb(int col, int row, A2Methods_UArray2 arr2, void *elem, 
                     void *cl)
{
        (void) arr2;
        struct a2_closure_with_denominator *mcl = cl;

        Pnm_ybr ybr_pixel = elem;
        Pnm_rgb rgb_pixel = mcl->methods->at(mcl->array2, col, row);
        /* compute red, green, blue integers based on y, Pb, Pr values. */
        rgb_pixel->red =   (unsigned)((mcl->denominator) * 
                               set_Range(1.0 * (ybr_pixel->y) + 0.0 * 
                               (ybr_pixel->pb) + 1.402 * (ybr_pixel->pr)));

        rgb_pixel->green = (unsigned)((mcl->denominator) * 
                               set_Range(1.0 * (ybr_pixel->y) - 0.344136 * 
                               (ybr_pixel->pb) - 0.714136 * (ybr_pixel->pr)));
        rgb_pixel->blue =  (unsigned)((mcl->denominator) * 
                               set_Range(1.0 * (ybr_pixel->y) + 1.772 * 
                               (ybr_pixel->pb) + 0.0 * (ybr_pixel->pr)));
}