/*
 *     filename: segmenter_tester.c
 *     partner 1 name: Peter Vondras       Login: peter
 *     partner 2 name: Hongyan Wang        Login: hwang10
 *     date: April 6th, 2016
 *     assignment: hw6
 *
 *     summary: Tester module for segmenter module               
 */

#include "segmenter_tester.h"

/*
 * Map 1000 or so segments. Unmap 500 of them. Map 501 segments and ensure that
 * no new (not previously used) are given out until the 51st ID which would 
 * affectively be the 101st.
 */
bool no_duplicate_segment_IDs()
{
        Seg_T seg = Seg_new();
        uint32_t table [ 1001 ] = { 0 };
        bool testFlag = true;
        uint32_t ID, i;

        /* 0 segment reserved for program */
        table[0] = 1;
        /* map segments 1 - 999 */
        for (i = 0; i < 999; i++) {
                ID = Seg_map(seg, 0);
                if (table[ID] != 0) {
                        testFlag = false;
                        break;
                }
                table[ID] = 1;
        }

        /* unmap 500 in the middle */
        for (i = 250; i < 750; i++)
                Seg_unmap(seg, i);
        /* map 501 segments */
        for (i = 250; i < 751; i++)
                ID = Seg_map(seg, 0);
        /* last segment mapped should be segment 1000 */
        if (ID != 1000)
                testFlag = false;

        Seg_free(&seg);

        return testFlag;
}

/*
 * run valgrind after unmap to ensure heap allocated memory has been freed.
 */
void map_and_unmap()
{
        Seg_T seg = Seg_new();
        uint32_t i;

        /* map segments 1 - 1000 */
        for (i = 1; i <= 100; i++)
                Seg_map(seg, 0);

        /* unmap all */
        for (i = 1; i <= 100; i++)
                Seg_unmap(seg, i);

        Seg_free(&seg);
}

/*
 * Map 100 segments of size x. Write a string of words filling the segment in
 * each. Request the address of each segment and ensure that it is still
 * intact.
 */
bool segment_integrity()
{
        Seg_T seg = Seg_new();
        uint32_t i, j, ID;
        uint32_t *address;
        bool testFlag = true;

        /* map segments 1 - 999 and set 10 words with unique sequence*/
        for (i = 1; i < 100; i++) {
                ID = Seg_map(seg, 10);
                address = Seg_get_address(seg, ID);
                for (j = 0; j < 10; j++)
                address[j] = i;
        }

        /* test sequences */
        for (i = 1; i < 100; i++) {
                address = Seg_get_address(seg, i);
                for (j = 0; j < 10; j++) {
                if (address[j] != i)
                        testFlag = false;
                }
                Seg_unmap(seg, i);
        }

        Seg_free(&seg);
        return testFlag;
}

/*
 * Map and unmap a segment of size 0 2^33 times which should result in NO
 * problems as the same ID space will be recycled.
*/
void infinite_mapping()
{
        Seg_T seg = Seg_new();
        unsigned long i;
        uint32_t ID;

        /* map more segments than would fit in a uint32_t */
        for (i = 0; i < 4294967296; i++) {
                ID = Seg_map(seg, 0);
                Seg_unmap(seg, ID);
        }

        Seg_free(&seg);
}

/* tests the ability to map segment 0 */
bool test_map_zero()
{
        uint32_t i;
        uint32_t *zero;
        bool testFlag = true;
        Seg_T seg     = Seg_new();
        uint32_t len;

        /* checking size of segment */
        zero = Seg_map_zero(seg, 10);
        len = Seg_length(seg, 0);
        if (len != 10)
                testFlag = false;

        /* putting unique string of numbers into segment */
        for (i = 0; i < 10; i++) {
                zero[i] = i;
        }

        /* checking segment is intact */
        for (i = 0; i < 10; i++) {
                if (zero[i] != i)
                        testFlag = false;
        }        

        Seg_unmap(seg, 0);
        Seg_free(&seg);

        return testFlag;
}

/* 
 * test segment size is the size requested.
 */
 bool test_segment_size()
{
        Seg_T seg = Seg_new();
        unsigned long i;
        uint32_t ID, size;
        bool testFlag = true;

        /* check size label in each segment matches requested size */
        for (i = 1; i < 50; i++) {
                ID = Seg_map(seg, i);
                size = Seg_length(seg, ID);
                if (size != i)
                        testFlag = false;

                Seg_unmap(seg, ID);
        }

        Seg_free(&seg);
        return testFlag;
}
