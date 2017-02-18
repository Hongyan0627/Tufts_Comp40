/*
 *     filename: seg.h
 *     partner 1 name: Peter Vondras       Login: peter
 *     partner 2 name: Hongyan Wang        Login: hwang10
 *     date: April 6th, 2016
 *     assignment: hw6
 *
 *     summary: Interface for segmenter. The segmenter handles the mapping of 
 *              segment ID's to pointers to memory of actual segments along
 *              with memory allocation, deallocation and size initialization.
 */

#ifndef SEG_H_INCLUDED
#define SEG_H_INCLUDED

#include <stdint.h>

typedef struct Seg_T *Seg_T;

/*
 * Creates and returns a Seg_T
 */
Seg_T Seg_new();

/*
 * Frees all heap allocated memory of segment. It is a checked runtime error to
 * send a freed segmenter as a parameter.
 */
void Seg_free(Seg_T *seg_p);

/*
 * Allocates segment 0 of size "size" and returns pointer to heap allocated
 * memory.
 */
uint32_t *Seg_map_zero(Seg_T seg, uint32_t size);

/*
 * maps a segment and returns a segment ID. A checked runtime error will be 
 * thrown if resources are not able to be allocated. It is a checked runtime 
 * error to map more than 2^33-2 segments. Note the -2 accounts for the program
 * being loaded at segment 0. It is a checked runtime error to request a segment
 * of negative size.
 * 
 * The first index location in a segment will be the uint32_t size value which 
 * does not include its own size.
 */
uint32_t Seg_map(Seg_T seg, uint32_t size); 


/*
 * Deallocates requested segment ID.
 * It is an unchecked runtime error to unmap a segment which is not currently 
 * mapped.
 */
void Seg_unmap(Seg_T seg, uint32_t ID);

/*
 * Given a segment ID, returns the memory address of that segment.
 * It is an unchecked runtime error to request the ID of an unmapped segment.
 */
uint32_t *Seg_get_address(Seg_T seg, uint32_t ID); 

/* returns capacity of segment in number of words */
uint32_t Seg_length(Seg_T seg, uint32_t ID);

#endif


