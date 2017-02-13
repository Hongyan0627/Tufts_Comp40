/*
 *     filename: UM.c
 *     partner 1 name: Peter Vondras       Login: peter
 *     partner 2 name: Hongyan Wang        Login: hwang10
 *     date: April 8th, 2016
 *     assignment: hw6
 *
 *     summary: Implementation for Universal Machine
 */

#include "program_loader.h"
#include "UM.h"
#include <stdio.h>
#include "code_extractor.h"
#include <stdlib.h>
#include <inttypes.h>

typedef uint32_t Um_instruction;

typedef struct runtime_info{
	uint32_t 	registers[8];
	Seg_T   	program;
	Um_instruction *seg0;
	uint32_t        program_counter;
	uint32_t        program_length;
	unsigned    	ra;
	unsigned 	rb;
	unsigned 	rc;
	uint32_t 	val;
} runtime_info;

static void execute_instruction(runtime_info *runtime, Um_instruction instruction);

static inline void cond_move 	 (runtime_info *runtime);
static inline void seg_load 	 (runtime_info *runtime);
static inline void seg_store 	 (runtime_info *runtime);
static inline void add      	 (runtime_info *runtime);
static inline void multiply 	 (runtime_info *runtime);
static inline void divide   	 (runtime_info *runtime);
static inline void nand     	 (runtime_info *runtime);
static inline void halt 	     (runtime_info *runtime);
static inline void map_seg  	 (runtime_info *runtime);
static inline void unmap_seg 	 (runtime_info *runtime);
static inline void output   	 (runtime_info *runtime);
static inline void input    	 (runtime_info *runtime);
static inline void load_program  (runtime_info *runtime);
static inline void load_val      (runtime_info *runtime);

enum opcode { COND_MOVE = 0, SEG_LOAD, SEG_STORE, ADD, MULTIPLY, DIVIDE,
        NAND, HALT, MAP_SEG, UNMAP_SEG, OUTPUT, INPUT, LOAD_PROGRAM, LOAD_VAL};

int run_um(Seg_T program)
{
	(void)program;
	// uint32_t program_counter, program_length;
	Um_instruction instruction;
	// uint32_t *seg0;
	// uint32_t registers[8] = { 0 };

	runtime_info runtime;

	/* initialize Seg_T with our program and registers to all '0' */
	runtime.program = program;
	for (int i = 0; i < 8; i++) {
		runtime.registers[i] = 0;
	}
	

	runtime.seg0 = Seg_get_address(program, 0);
	runtime.program_length = Seg_length(program, 0);

	/* for every instruction in seg0 */
	for (runtime.program_counter = 0;
	     runtime.program_counter < runtime.program_length; 
	     runtime.program_counter++) {
	     	/* get instruction */
		instruction = runtime.seg0[runtime.program_counter];
		// printf("Instructions: %0x\n" PRIu32, instruction);
		execute_instruction(&runtime, instruction);
	}

	/* what if they did not halt? ***************************************************/
	halt(&runtime);

	return 1;
}

static void execute_instruction(runtime_info *runtime, Um_instruction instruction)
{
	switch(get_opcode(instruction)) {

	case COND_MOVE:
		set_ra_rb_rc(instruction, &(runtime->ra), &(runtime->rb), &(runtime->rc));
		cond_move(runtime);
		break;
	
	case SEG_LOAD:
		set_ra_rb_rc(instruction, &(runtime->ra), &(runtime->rb), &(runtime->rc));
		seg_load(runtime);
		break;

	case SEG_STORE:
		set_ra_rb_rc(instruction, &(runtime->ra), &(runtime->rb), &(runtime->rc));
		seg_store(runtime);
		break;

	case ADD:
		set_ra_rb_rc(instruction, &(runtime->ra), &(runtime->rb), &(runtime->rc));
		add(runtime);
		break;

	case MULTIPLY:
		set_ra_rb_rc(instruction, &(runtime->ra), &(runtime->rb), &(runtime->rc));
		multiply(runtime);
		break;

	case DIVIDE:
		set_ra_rb_rc(instruction, &(runtime->ra), &(runtime->rb), &(runtime->rc));
		divide(runtime);
		break;

	case NAND:
		set_ra_rb_rc(instruction, &(runtime->ra), &(runtime->rb), &(runtime->rc));
		nand(runtime);
		break;

	case HALT:
		halt(runtime);
		exit(EXIT_SUCCESS);
		break;

	case MAP_SEG:
		set_ra_rb_rc(instruction, &(runtime->ra), &(runtime->rb), &(runtime->rc));
		map_seg(runtime);
		break;

	case UNMAP_SEG:
		set_ra_rb_rc(instruction, &(runtime->ra), &(runtime->rb), &(runtime->rc));
		unmap_seg(runtime);
		break;

	case OUTPUT:
		set_ra_rb_rc(instruction, &(runtime->ra), &(runtime->rb), &(runtime->rc));
		output(runtime);
		break;

	case INPUT:
		set_ra_rb_rc(instruction, &(runtime->ra), &(runtime->rb), &(runtime->rc));
		input(runtime);
		break;

	case LOAD_PROGRAM:
		set_ra_rb_rc(instruction, &(runtime->ra), &(runtime->rb), &(runtime->rc));
		load_program(runtime);
		break;

	case LOAD_VAL:
		set_ra_val(instruction, &(runtime->ra), &(runtime->val));
		load_val(runtime);
		break;
  
	/* you can have any number of case statements */
	default : /* Optional */
		fprintf(stderr, "Improper instruction requested\n");
		halt(runtime);
	}	
}

static inline void cond_move(runtime_info *runtime)
{
        if (runtime->registers[runtime->rc] != 0)
        	runtime->registers[runtime->ra] = runtime->registers[runtime->rb];
}

static inline void seg_load(runtime_info *runtime)
{
	/* get address of segment */
	uint32_t *address= Seg_get_address(runtime->program, runtime->registers[runtime->rb]);
	/* 
	 * get user value in segment at index requested + 1. First index holds
	 * the size of the segment.
	 */ 
	runtime->registers[runtime->ra] = address[runtime->rc];
}

static inline void seg_store(runtime_info *runtime)
{
	/* get address of segment */
	uint32_t *address= Seg_get_address(runtime->program, runtime->registers[runtime->ra]); 
	/* 
	 * store user value in segment at index requested + 1. First index holds
	 * the size of the segment.
	 */
	address[runtime->rb] = runtime->registers[runtime->rc];
}

static inline void add(runtime_info *runtime)
{
	runtime->registers[runtime->ra] = runtime->registers[runtime->rb] + runtime->registers[runtime->rc];
}

static inline void multiply(runtime_info *runtime)
{
	runtime->registers[runtime->ra] = runtime->registers[runtime->rb] * runtime->registers[runtime->rc];
}

static inline void divide(runtime_info *runtime)
{
	runtime->registers[runtime->ra] = runtime->registers[runtime->rb] / runtime->registers[runtime->rc];
}

static inline void nand(runtime_info *runtime)
{
	uint32_t valB, valC;
	valB = runtime->registers[runtime->rb];
	valC = runtime->registers[runtime->rc];

	runtime->registers[runtime->ra] = ~(valB & valC);
}

static inline void halt(runtime_info *runtime) 
{
	Seg_free(&(runtime->program));
}

static inline void map_seg(runtime_info *runtime)
{
	runtime->registers[runtime->rb] = Seg_map(runtime->program, runtime->registers[runtime->rc]);
}

static inline void unmap_seg(runtime_info *runtime)
{
	Seg_unmap(runtime->program, runtime->registers[runtime->rc]);
}

static inline void output(runtime_info *runtime)
{
	putchar(runtime->registers[runtime->rc]);
}

static inline void input(runtime_info *runtime)
{
	int c =  getchar();

	if (c == EOF)
		runtime->registers[runtime->rc] = ~(uint32_t)0;
	else
		runtime->registers[runtime->rc] = c;
}

static inline void load_program(runtime_info *runtime)
{
	uint32_t *new_segment_0, *loadThis;
	uint32_t len, ID;

	if (runtime->registers[runtime->rb] != 0) {
		/* ID of loadThis segment */
		ID = runtime->registers[runtime->rb];

		/* get address of segment */
		loadThis = Seg_get_address(runtime->program, ID);

		/* allocate memory for new program */
		len 	      = Seg_length(runtime->program, ID);
		new_segment_0 = Seg_map_zero(runtime->program, len);

		/* copy requested program into new segment 0 */
		for (uint32_t i = 0; i < len; i++) {
			new_segment_0[i] = loadThis[i];
		}

		/* reset program counter and length */
		runtime->program_length  = len;
	}

	runtime->program_counter = runtime->registers[runtime->rc];
}

static inline void load_val(runtime_info *runtime)
{
	runtime->registers[runtime->ra] = runtime->val;
}