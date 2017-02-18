/*
 *     filename: UM.h
 *     partner 1 name: Peter Vondras       Login: peter
 *     partner 2 name: Hongyan Wang        Login: hwang10
 *     date: April 8th, 2016
 *     assignment: hw6
 *
 *     summary: Interface for Universal Machine 
 */

#ifndef UM_H_INCLUDED
#define UM_H_INCLUDED

#include "seg.h"

/* 
 * Takes a Seg_T with a program loaded into seg0. Runs program and frees the 
 * Seg_T. It is a checked runtime error to send a NULL pointer to run_um() and
 * an unchecked runtime error to not have a program loaded into segment 0 of the
 * program.
 */
int run_um(Seg_T program);

#endif
