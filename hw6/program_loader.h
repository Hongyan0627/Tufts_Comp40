/*
 *     filename: program_loader.h
 *     partner 1 name: Peter Vondras       Login: peter
 *     partner 2 name: Hongyan Wang        Login: hwang10
 *     date: April 8th, 2016
 *     assignment: hw6
 *
 *     summary: Interface for loader for UM 
 */

#ifndef PROGRAM_LOADER_H_INCLUDED
#define PROGRAM_LOADER_H_INCLUDED

#include <stdint.h>
#include "seg.h"
#include "stddef.h"
#include <stdio.h>

Seg_T initial_load_program(FILE *fp, uint32_t numWords);

#endif


