/*
 *     filename: segmenter_tester.h
 *     partner 1 name: Peter Vondras       Login: peter
 *     partner 2 name: Hongyan Wang        Login: hwang10
 *     date: April 6th, 2016
 *     assignment: hw6
 *
 *     summary: Tester module for segmenter module               
 */

#ifndef SEGMENTER_TESTER_H_INCLUDED
#define SEGMENTER_TESTER_H_INCLUDED

#include "seg.h"
#include <stdbool.h>

/*
 * Map 100 or so segments. Unmap 50 of them. Map 51 segments and ensure that no
 * new (not previously used) are given out until the 51st ID which would 
 * affectively be the 101st.
 */
bool no_duplicate_segment_IDs();

/*
 * run valgrind after unmap to ensure heap allocated memory has been freed.
 */
void map_and_unmap();

/*
 * Map 100 segments of size x. Write a string of words filling the segment in
 * each. Request the address of each segment and ensure that it is still
 * intact.
*/
bool segment_integrity();

/*
 * Map and unmap a segment of size 0 2^33 times which should result in NO
 * problems as the same ID space will be recycled.
*/
void infinite_mapping();

/*
 * test ability to map segment zero
 */
bool test_map_zero();

/* 
 * test segment size is the size requested.
 */
 bool test_segment_size();

#endif
