/****************************************************************
 *
 *                         cputiming.h
 *
 *                   Author: Noah Mendelsohn
 *
 *       Interface to functions implementing type CPUTime_T,
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

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
 *                   Type definitions
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

typedef struct CPU_Time *CPUTime_T;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
 *              Functions implementing the CPUTime interface
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */



CPUTime_T CPUTime_New();

void CPUTime_Free(CPUTime_T *startTimepp);

void CPUTime_Start(CPUTime_T StartTimep) ;

double CPUTime_Stop(CPUTime_T startTimep) ;

