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

#include <stdint.h>
#include "seg.h"
#include "stddef.h"

int run_um(Seg_T program);

#endif