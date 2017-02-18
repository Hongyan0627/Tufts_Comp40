#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <a2plain.h>
#include <a2methods.h>
#include <pnm.h>
#include <math.h>
#include <except.h>

double compute_pixel_diff(int col, int row, Pnm_ppm image1, Pnm_ppm image2);

int main(int argc, char *argv[]){

        assert(argc == 3);

        FILE *fp1, *fp2;
        Pnm_ppm image1, image2;
        unsigned int col, row, sum;
        double E;

        A2Methods_T methods = uarray2_methods_plain;
        assert(methods);
        
        fp1 = fopen(argv[1],"rb");
        image1 = Pnm_ppmread(fp1, methods);
        

        fp2 = fopen(argv[2],"rb");
        image2 = Pnm_ppmread(fp2, methods);
          

        printf("image1 width: %u,   height: %u\n", image1->width, 
                image1->height);
        printf("image2 width: %u,   height: %u\n", image2->width, 
                image2->height);
        assert(abs(image1->width - image2->width) <= 1); 
        assert(abs(image1->height - image2->height) <= 1); 
        

        for (row = 0; row < image1->height; row++) {
                if ( row >= image2->height) break;
                for (col = 0; col < image1->width; col++){
                        if (col >= image2->width) break;
                        sum += compute_pixel_diff(col, row, image1, image2);
                }
        }
        
        E = sqrt(1.0 * sum/(3 * (col + 1) * (row + 1)));
        printf("%.4f\n", E);
        Pnm_ppmfree(&image1);
        Pnm_ppmfree(&image2);
        fclose(fp1);
        fclose(fp2);
}

double compute_pixel_diff(int col, int row, Pnm_ppm image1, Pnm_ppm image2){
        Pnm_rgb pixel1, pixel2;
        int rdiff, gdiff, bdiff, sum;
        pixel1 = image1->methods->at(image1->pixels, col, row);
        pixel2 = image2->methods->at(image2->pixels, col, row);
        rdiff = pixel1->red - pixel2->red;
        gdiff = pixel1->green - pixel2->green;
        bdiff = pixel1->blue - pixel2->blue;
        sum = rdiff * rdiff + gdiff * gdiff + bdiff * bdiff;
        return sum;
}