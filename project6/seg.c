

#include "seg.h"
#include <stdlib.h>
#include <seq.h>
#include <mem.h>
#include <stdio.h>
#include <assert.h>

static const int HINT = 0;

/* 
 * Seg_T contains a sequence to keep track of segment ID's that have been mapped
 * which will point to heap allocated memory, unless they are unmapped. The
 * second sequence is used as a stack to recycle previously used segment ID's
 */

struct Seg_T {
        Seq_T tracked_IDs;
        Seq_T unmapped_IDs;
        uint32_t maxID;
};

/* used to free all segments at the end of sequences use */
static void free_all_segments(Seq_T tracked_IDs);

/*
 * Creates and returns a new Seg_T which is allocated on the heap.
 */
Seg_T Seg_new()
{
        Seg_T seg;
        NEW(seg);

        /* create new sequences for mapping memory to segment ID */
        seg->tracked_IDs   = Seq_new(HINT);
        seg->unmapped_IDs  = Seq_new(HINT);
        seg->maxID         = 0;

        /* push index zero for program onto tracked_IDs */
        Seq_addhi(seg->tracked_IDs, NULL);

        return seg;
}

/*
 * Frees all heap allocated memory of segment. It is a checked runtime error to
 * send a freed segmenter as a parameter.
 */
void Seg_free(Seg_T *seg_p)
{
        assert(seg_p != NULL);
        Seg_T segment = *seg_p;
      
        free_all_segments(segment->tracked_IDs);

        Seq_free( &((segment)->tracked_IDs) );
        Seq_free( &((segment)->unmapped_IDs) );
        FREE(segment);
}

static void free_all_segments(Seq_T tracked_IDs)
{
        uint32_t *toFree;
        uint32_t len = Seq_length(tracked_IDs);

        for (uint32_t i = 0; i < len; i++) {
                toFree = Seq_get(tracked_IDs, i);
                if (toFree != NULL) {
                        free(toFree);
                }
        }
}

/*
 * Allocates segment 0 of size "size" and returns pointer to heap allocated
 * memory.
 */
uint32_t *Seg_map_zero(Seg_T seg, uint32_t size)
{
        /* if there was an old program, free it */
        uint32_t *oldProgram = Seq_get(seg->tracked_IDs, 0);
        if (oldProgram != NULL)
                free(oldProgram);

        uint32_t *newSegment = calloc( (size + 1), sizeof(uint32_t) );
        assert(newSegment != NULL);

        /* set seg 0 pointer in tracked_IDs and write size into index 0 */
        Seq_put(seg->tracked_IDs, 0, newSegment);
        *newSegment = size;

        return newSegment + 1;
}

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
uint32_t Seg_map(Seg_T seg, uint32_t size)
{
        uint32_t nextID;
        uint32_t *newSegment = calloc( (size + 1), sizeof(uint32_t) );
        assert(newSegment != NULL);

        /* if there an unmapped ID available */
        if (Seq_length(seg->unmapped_IDs) != 0) {
                /* storing ID numbers instead of pointers */
                nextID = (uint32_t)(uintptr_t)Seq_remhi(seg->unmapped_IDs);
                Seq_put(seg->tracked_IDs, nextID, newSegment);
        }
        else { /* assign an ID that has not been used before */
                nextID = seg->maxID + 1;
                Seq_addhi(seg->tracked_IDs, newSegment);
                seg->maxID++;
        }

        *newSegment = size;
        return nextID;
}

/*
 * Deallocates requested segment ID.
 * It is an unchecked runtime error to unmap a segment which is not currently 
 * mapped.
 */
void Seg_unmap(Seg_T seg, uint32_t ID)
{
        uint32_t *segment = Seq_get(seg->tracked_IDs, ID);
        free(segment);
        segment = NULL;
        Seq_put(seg->tracked_IDs, ID, NULL);
        Seq_addhi(seg->unmapped_IDs, (void*)(uintptr_t)ID);
}

/*
 * Given a segment ID, returns the memory address of that segment.
 * It is an unchecked runtime error to request the ID of an unmapped segment.
 */
uint32_t *Seg_get_address(Seg_T seg, uint32_t ID)
{
        return (uint32_t*)Seq_get(seg->tracked_IDs, ID) + 1;
}

/* returns capacity of segment in number of words */
uint32_t Seg_length(Seg_T seg, uint32_t ID)
{
        return *(uint32_t*)Seq_get(seg->tracked_IDs, ID);
}