/****************************************************************
 *
 *                         cputiming.c
 *
 *                   Author: Noah Mendelsohn
 *
 *       This source file implements the type CPUTime_T,
 *       which is used to timely execution of program code.
 *
 *       The overall pattern of function names follows Hanson's
 *       conventions for _New, _Free, etc., which are not
 *       re-explained in detail here.
 * 
 *       Usage:
 * 
 *       CPUTime_t timer = CPUTime_new();
 *       CPUTime_Start(timer);
 *         ... Do work to be timed here
 *       double cputime = CPUTime_Stop(timer);
 *
 *       cputime will be set to the CPY time in nanoseconds taken
 *       taken for the execution of the work being timed. This is 
 *       always an integer value stored in a double. For timings up to
 *       several million seconds, no precision should be lost.
 *
 *       Note that printf format %.0f is typically a reasonable way to
 *       print such integers.
 *
 *****************************************************************/

#include <stdlib.h>
#include <time.h>
#include "assert.h"
#include "cputiming_impl.h"

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
 *              Forward declaration of functions/
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


static int timespec_subtract (struct timespec *result, struct timespec *x, 
                              struct timespec *y);

static double timespec_to_double(struct timespec *x);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
 *              Functions implementing the CPUTime interface
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


CPUTime_T CPUTime_New(){
        CPUTime_T startTimep = malloc(sizeof(*startTimep));
        assert (startTimep != NULL);
        return startTimep;
}

void CPUTime_Free(CPUTime_T *startTimepp){
        assert(startTimepp != NULL);
        assert(*startTimepp != NULL);
        free(*startTimepp);
        *startTimepp = NULL;
        return;
}

void CPUTime_Start(CPUTime_T startTimep) {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &(startTimep->time));
        return;
}

double CPUTime_Stop(CPUTime_T startTimep) {
        struct timespec stop, time_used;
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
        assert(timespec_subtract(&time_used, &stop, &(startTimep->time)) == 0);
        return timespec_to_double(&time_used);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
 *     Utility functions called internally
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
 *  timespec_subtract
 * 
 *  *result = *x - *y
 *
 *  Adapted from timeval_subtract at:
 *
 *  http://www.gnu.org/software/libc/manual/html_node/Elapsed-Time.html
 */
static int
timespec_subtract (result, x, y)
struct timespec *result, *x, *y;
{
        int nsec;
        /* Perform the carry for the later subtraction by updating y. */
        if (x->tv_nsec < y->tv_nsec) {
                nsec = (y->tv_nsec - x->tv_nsec) / 1000000000 + 1;
                y->tv_nsec -= 1000000000 * nsec;
                y->tv_sec += nsec;
        }
        if (x->tv_nsec - y->tv_nsec > 1000000000) {
                nsec = (x->tv_nsec - y->tv_nsec) / 1000000000;
                y->tv_nsec += 1000000000 * nsec;
                y->tv_sec -= nsec;
        }

        /* Compute the time remaining to wait.
           tv_nsec is certainly positive. */
        result->tv_sec = x->tv_sec - y->tv_sec;
        result->tv_nsec = x->tv_nsec - y->tv_nsec;

        /* Assert added by Noah */
        assert(result->tv_nsec < 1000000000);

        /* Return 1 if result is negative. */
        return x->tv_sec < y->tv_sec;
}


/*
 *                 timespec_to_long
 *
 *     A timespec structure consists of two longs, one with seconds
 *     and one with nanoseconds. This function combines them
 *     into a single value counting nanoseconds, returned as a double
 *     just in case the result is too large to fit a long (approximately
 *     4 seconds). Note that the double can hold 53 bits, which is
 *     many millions of seconds without losing accuracy, and can of 
 *     course store much larger values with some loss of precision.
 */

static double
timespec_to_double(struct timespec *ts) {
        return ((double)(ts->tv_sec) * 1000000000) +
                        ts->tv_nsec;

}
