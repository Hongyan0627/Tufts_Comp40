/*
 *     filename: program_loader.c
 *     partner 1 name: Peter Vondras       Login: peter
 *     partner 2 name: Hongyan Wang        Login: hwang10
 *     date: April 8th, 2016
 *     assignment: hw6
 *
 *     summary: Implementation for program loader for UM 
 */

#include "program_loader.h"
#include <inttypes.h>
#include <bitpack.h>

Seg_T initial_load_program(FILE *fp, uint32_t numWords)
{
	uint32_t word;
	uint32_t *seg0;
	uint32_t zero_index = 0;
	int c;

	/* create new Seg_T and map zero segment */
	Seg_T program = Seg_new();
	seg0 = Seg_map_zero(program, numWords);

	/* for every first char of sets of 4 */
	c = getc(fp);
	while (c != EOF) {
		/* get the word */
		word = 0;
		for (int j = sizeof(uint32_t) - 1; j >= 0; j--) {
                        word = (uint32_t)Bitpack_newu((uint64_t)word, 
                        	8, (j * 8), (uint64_t)c);
                        c = getc(fp);
                }
                /* store the word in segment zero */
		seg0[zero_index] = word;
		zero_index++;
	}

	return program;
}