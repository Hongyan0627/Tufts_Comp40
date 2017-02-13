/*
 *     filename: code_extractor.h
 *     partner 1 name: Peter Vondras       Login: peter
 *     partner 2 name: Hongyan Wang        Login: hwang10
 *     date: April 8th, 2016
 *     assignment: hw6
 *
 *     summary: Interface for code_extractor which gets register numbers and 
 *				the opcode from a word.
 */

#ifndef CODE_EXTRACTOR_H_INCLUDED
#define CODE_EXTRACTOR_H_INCLUDED

#include <stdint.h>

unsigned get_opcode(uint32_t instruction);
void set_ra_rb_rc  (uint32_t instruction, unsigned *ra, unsigned *rb,
		    unsigned *rc);
void set_ra_val    (uint32_t instruction, unsigned *ra, uint32_t *val);

#endif


