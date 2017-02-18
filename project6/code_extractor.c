/*
 *     filename: code_extractor.c
 *     partner 1 name: Peter Vondras       Login: peter
 *     partner 2 name: Hongyan Wang        Login: hwang10
 *     date: April 8th, 2016
 *     assignment: hw6
 *
 *     summary: Implementation for code_extractor which gets register numbers
 *				and the opcode from a word.
 */

#include <stdint.h>
#include <bitpack.h>

#define REG_WIDTH 3
#define VAL_WIDTH 25

unsigned get_opcode(uint32_t instruction)
{
	return (unsigned)Bitpack_getu(instruction, 4, 28);
}

void set_ra_rb_rc(uint32_t instruction, unsigned *ra, unsigned *rb, 
		  unsigned *rc)
{
	*ra = (unsigned)Bitpack_getu(instruction, REG_WIDTH, 2 * REG_WIDTH);
	*rb = (unsigned)Bitpack_getu(instruction, REG_WIDTH, 1 * REG_WIDTH);
	*rc = (unsigned)Bitpack_getu(instruction, REG_WIDTH, 0 * REG_WIDTH);
}

void set_ra_val(uint32_t instruction, unsigned *ra, uint32_t *val)
{
	*ra  = Bitpack_getu(instruction, REG_WIDTH, VAL_WIDTH);
	*val = Bitpack_getu(instruction, VAL_WIDTH, 0);
}