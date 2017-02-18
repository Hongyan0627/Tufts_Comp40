/*
 *     filename: seg.c
 *     partner 1 name: Peter Vondras       Login: peter
 *     partner 2 name: Hongyan Wang        Login: hwang10
 *     date: April 10th, 2016
 *     assignment: hw6
 *
 *     summary: Implementation for segmenter. The segmenter handles the mapping
 *              of segment ID's to pointers to memory of actual segments along
 *              with memory allocation, deallocation and size initialization.
 */

#include <stdlib.h>
#include <mem.h>
#include <assert.h>
#include "seg.h"

static const int HINT = 1; /* sequence start size */

/* 
 * Seg_T contains a sequence to keep track of segment ID's that have been mapped
 * which will point to heap allocated memory, unless they are unmapped. The
 * second sequence is used as a stack to recycle previously used segment ID's
 */
struct Seg_T {
        uint32_t **tracked_IDs;
        uint32_t *unmapped_IDs;
        uint32_t maxID;
        uint32_t stack_loc;
        uint32_t tracked_size;
        uint32_t unmapped_size;
};

/* used to free all segments at the end of sequences use */
static void free_all_segments(Seg_T seg);

/*
 * Creates and returns a new Seg_T which is allocated on the heap.
 */
Seg_T Seg_new()
{
        Seg_T seg;
        NEW(seg);

        /* create new sequences for mapping memory to segment ID */
        seg->tracked_IDs   = calloc(sizeof(uint32_t*), HINT);
        seg->unmapped_IDs  = malloc(sizeof(uint32_t) * HINT);
        seg->maxID         = 0;
        seg->stack_loc     = 0;
        seg->tracked_size  = HINT;
        seg->unmapped_size = HINT;

        return seg;
}

/*
 * Frees all heap allocated memory of segment. It is a checked runtime error to
 * send a freed segmenter as a parameter.
 */
void Seg_free(Seg_T *seg_p)
{
        assert(seg_p != NULL); /* it is a checked runtime error to free NULL */
        Seg_T segment = *seg_p;
        
        /* free all segments which are not already freed */      
        free_all_segments(segment);

        /* free Sequences in Seg_T */
        free( segment->tracked_IDs );
        free( segment->unmapped_IDs );
        FREE(segment);  /* free segment and set to NULL */
}

/* 
 * Walks through tracked_IDs and frees all that are not set to NULL. 
 * It is an unchecked runtime error for a freed segment to not be set to NULL.
 */
static void free_all_segments(Seg_T seg)
{
        uint32_t *toFree, **tracked_IDs;
        uint32_t len = seg->maxID;
        tracked_IDs = seg->tracked_IDs;

        for (uint32_t i = 0; i < len; i++) {
                toFree = tracked_IDs[i];
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
        uint32_t **tracked_IDs = seg->tracked_IDs;
        /* if there was an old program, free it */
        uint32_t *oldProgram = *tracked_IDs;
        if (oldProgram != NULL) {
                free(oldProgram);
                oldProgram = NULL;
        }

        /* allocate memory and initialize to all 0's */
        uint32_t *newSegment = calloc( (size + 1), sizeof(uint32_t) );
        assert(newSegment != NULL); /* ensure memory was allocated */

        /* set seg 0 pointer in tracked_IDs and write size into index 0 */
        *tracked_IDs = newSegment;
        *newSegment  = size;

        /* the location of the size information is obscured */
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
        uint32_t stack_loc = seg->stack_loc;

        /* if there an unmapped ID available */
        if (stack_loc != 0) {
                /* storing ID numbers instead of pointers */
                nextID = seg->unmapped_IDs[stack_loc - 1];
                seg->tracked_IDs[nextID] = newSegment;
                seg->stack_loc--;
        }
        else { /* assign an ID that has not been used before */
                nextID = seg->maxID + 1;
                uint32_t tracked_size = seg->tracked_size;
                if (nextID == tracked_size) {
                        uint32_t **old_tracked = seg->tracked_IDs;
                        uint32_t new_tracked_size = tracked_size * 2;
                        uint32_t **new_tracked = realloc(old_tracked, 
                            new_tracked_size * sizeof(uint32_t*));
                        for (uint32_t i = nextID; i < new_tracked_size; i++) {
                                new_tracked[i] = NULL;
                        }
                        seg->tracked_size = new_tracked_size;
                        seg->tracked_IDs = new_tracked;
                }
                seg->tracked_IDs[nextID] = newSegment;
                seg->maxID++;
        }

        /* set size at index 0 and return the segment's ID */
        *newSegment = size;
        return nextID;
}

/*
 * Deallocates requested segment ID.
 * It is a checked runtime error to unmap a segment which is not currently 
 * mapped. In this case the the program will EXIT_FAILURE.
 */
void Seg_unmap(Seg_T seg, uint32_t ID)
{
        /* free allocated memory */
        uint32_t *segment = seg->tracked_IDs[ID];
        if (segment != NULL)
                free(segment);
        // else 
        //         exit(EXIT_FAILURE);

        /* 
         * mark this segment ID as freed and add to the tracked unmmaped_IDs 
         * stack.
         */
        segment = NULL;
        seg->tracked_IDs[ID] = NULL;

        if (seg->stack_loc == seg->unmapped_size) {
                uint32_t *old_unmapped = seg->unmapped_IDs;
                uint32_t new_unmapped_size = seg->unmapped_size * 2;
                uint32_t *new_unmapped = realloc(old_unmapped, 
                    new_unmapped_size * sizeof(uint32_t));
                seg->unmapped_size = new_unmapped_size;
                seg->unmapped_IDs = new_unmapped;
        }

        seg->unmapped_IDs[seg->stack_loc++] = ID;
}

/*
 * Given a segment ID, returns the memory address of that segment.
 * It is an unchecked runtime error to request the ID of an unmapped segment.
 */
uint32_t *Seg_get_address(Seg_T seg, uint32_t ID)
{
        /* add one to memory location of segment to obscure segment size */
        return seg->tracked_IDs[ID] + 1;
}

/* returns size of segment in number of instructions */
uint32_t Seg_length(Seg_T seg, uint32_t ID)
{
        uint32_t *segment = seg->tracked_IDs[ID];

        if (segment == NULL)
                return 0;
        else
                return *segment;
}