/*
 *     filename: code_extractor.h
 *     partner 1 name: Peter Vondras       Login: peter
 *     partner 2 name: Hongyan Wang        Login: hwang10
 *     date: April 8th, 2016
 *     assignment: hw6
 *
 *     summary: Interface for code_extractor which gets register numbers and 
 *              the opcode from a word.
 */

#ifndef CODE_EXTRACTOR_H_INCLUDED
#define CODE_EXTRACTOR_H_INCLUDED

#define get_opcode(instruction) instruction >> 28 
#define get_ra(instruction) instruction << 23 >> 29
#define get_rb(instruction) instruction << 26 >> 29
#define get_rc(instruction) instruction << 29 >> 29
#define get_ra_2(instruction) instruction << 4 >> 29
#define get_val(instruction) instruction << 7 >> 7

#endif
