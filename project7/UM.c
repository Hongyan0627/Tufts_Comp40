/*
 *     filename: UM.c
 *     partner 1 name: Peter Vondras       Login: peter
 *     partner 2 name: Hongyan Wang        Login: hwang10
 *     date: April 8th, 2016
 *     assignment: hw6
 *
 *     summary: Implementation for Universal Machine
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "UM.h"
#include "code_extractor.h"

typedef uint32_t Um_instruction;

/* defines what instruction type is being requested */
enum opcode { COND_MOVE = 0, SEG_LOAD, SEG_STORE, ADD, MULTIPLY, DIVIDE,
              NAND, HALT, MAP_SEG, UNMAP_SEG, OUTPUT, INPUT, LOAD_PROGRAM, 
              LOAD_VAL };

/* Runs the UM through every instruction */
int run_um(Seg_T program)
{
        Um_instruction instruction;
        // runtime_info runtime;
        uint32_t        registers[8];
        Um_instruction *seg0;
        uint32_t        program_counter;
        unsigned        ra;
        unsigned        rb;
        unsigned        rc;
        uint32_t        val;
        uint32_t *address;
        int c;

        assert( program != NULL );

        /* initialize Seg_T with our program and registers to all '0' */
        // runtime.program = program;
        for (int i = 0; i < 8; i++) {
                registers[i] = 0;
        }
        
        /* set seg0 pointer and program length */
        seg0 = Seg_get_address(program, 0);
        // runtime.program_length = Seg_length(program, 0);

        /* for every instruction in seg0 */
        for (program_counter = 0; ; program_counter++) {
                /* get instruction */
                instruction = seg0[program_counter];
                // execute_instruction(&runtime, instruction);
                switch(get_opcode(instruction)) {

                        case COND_MOVE:
                                ra = get_ra(instruction);
                                rb = get_rb(instruction);
                                rc = get_rc(instruction);
                                if (registers[rc] != 0)
                                        registers[ra] = 
                                                registers[rb];
                                break;
                        
                        case SEG_LOAD:
                                ra = get_ra(instruction);
                                rb = get_rb(instruction);
                                rc = get_rc(instruction);
                                /* get address of segment */
                                address = Seg_get_address(program, 
                                        registers[rb]);
                                /* 
                                 * get user value in segment at index requested
                                 * + 1. First index holds
                                 * the size of the segment.
                                 */ 
                                registers[ra] = address[registers[rc]];
                                break;

                        case SEG_STORE:
                                ra = get_ra(instruction);
                                rb = get_rb(instruction);
                                rc = get_rc(instruction);
                                /* get address of segment */
                                address = Seg_get_address(program, 
                                        registers[ra]); 

                                /* 
                                 * store user value in segment at index 
                                 * requested + 1. First index holds
                                 * the size of the segment.
                                 */
                                address[registers[rb]] = registers[rc];
                                break;

                        case ADD:
                                ra = get_ra(instruction);
                                rb = get_rb(instruction);
                                rc = get_rc(instruction);
                                registers[ra] = registers[rb] + registers[rc];
                                break;

                        case MULTIPLY:
                                ra = get_ra(instruction);
                                rb = get_rb(instruction);
                                rc = get_rc(instruction);
                                registers[ra] = registers[rb] * registers[rc];
                                break;

                        case DIVIDE:
                                ra = get_ra(instruction);
                                rb = get_rb(instruction);
                                rc = get_rc(instruction);
                                registers[ra] = registers[rb] / registers[rc];
                                break;

                        case NAND:
                                ra = get_ra(instruction);
                                rb = get_rb(instruction);
                                rc = get_rc(instruction);
                                registers[ra] = ~(registers[rb] & 
                                        registers[rc]);
                                break;

                        case HALT:
                                Seg_free(&(program));
                                exit(EXIT_SUCCESS);
                                break;

                        case MAP_SEG:
                                rb = get_rb(instruction);
                                rc = get_rc(instruction);
                                registers[rb] = 
                                        Seg_map(program, registers[rc]);
                                break;

                        case UNMAP_SEG:
                                rb = get_rb(instruction);
                                rc = get_rc(instruction);
                                Seg_unmap(program, registers[rc]);
                                break;

                        case OUTPUT:
                                rc = get_rc(instruction);
                                putchar(registers[rc]);
                                break;

                        case INPUT:
                                rc = get_rc(instruction);
                                c =  getchar();
                                if (c == EOF)
                                        registers[rc] = ~(uint32_t)0;
                                else
                                        registers[rc] = c;
                                break;

                        case LOAD_PROGRAM:
                                rb = get_rb(instruction);
                                rc = get_rc(instruction);
                                uint32_t *new_segment_0, *loadThis;
                                uint32_t len, ID;

                                /* 
                                 * skip duplication if request is to load 
                                 * segment 0
                                 */
                                if (registers[rb] != 0) {
                                        /* get ID of loadThis segment */
                                        ID = registers[rb];
                                        /* get address of segment */
                                        loadThis = Seg_get_address(program, ID);

                                        /* allocate memory for new program */
                                        len           = Seg_length(program, ID);
                                        new_segment_0 = Seg_map_zero(program, 
                                                len + 1);
                                        seg0 = new_segment_0;

                                        uint32_t i = 0;
                                        /* 
                                         * copy requested program into new 
                                         * segment 0 
                                         */
                                        for (; i < len; i++) {
                                                new_segment_0[i] = loadThis[i];
                                        }
                                        new_segment_0[i] = 0x70000000;


                                        /* reset program length */
                                        // program_length  = len + 1;
                                }

                                /* 
                                 * Reset program counter. One is subtracted 
                                 * from the instruction number
                                 * requested because the value will be 
                                 * incremented by one before it is
                                 * executed.
                                 */
                                program_counter = registers[rc] - 1;
                                break;

                        case LOAD_VAL:
                                ra = get_ra_2(instruction);
                                val = get_val(instruction);
                                registers[ra] = val;
                                break;
                  
                        default : /* Improper opcode detected */
                                fprintf(stderr, 
                                        "Improper instruction requested\n");
                                Seg_free(&(program));
                }
        }

        /* clean up when client fails to halt */
        Seg_free(&(program));
        return EXIT_FAILURE;
}




