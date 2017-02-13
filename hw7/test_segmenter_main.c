/*
 *     filename: test_segmenter_main.c
 *     partner 1 name: Peter Vondras       Login: peter
 *     partner 2 name: Hongyan Wang        Login: hwang10
 *     date: April 6th, 2016
 *     assignment: hw6
 *
 *     summary: Tester runs tests for segmenter module.
 */

#include "segmenter_tester.h"
#include "seg.h"
#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;

        map_and_unmap();
                printf("map_and_unmap.................PASSED\n");

        if (no_duplicate_segment_IDs() == true)
                printf("no_duplicate_segment_IDs......PASSED\n");
        else
                printf("no_duplicate_segment_IDs......FAILED\n");

        if (segment_integrity() == true)
                printf("segment_integrity.............PASSED\n");
        else
                printf("segment_integrity.............FAILED\n");

        // infinite_mapping();

        if (test_map_zero() == true)
                printf("test_map_zero.................PASSED\n");
        else
                printf("test_map_zero.................FAILED\n");

        if (test_segment_size() == true)
                printf("test_segment_size.............PASSED\n");
        else
                printf("test_segment_size.............FAILED\n");
        
        return 0;
}
