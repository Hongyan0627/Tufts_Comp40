#include <bitpack.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <seq.h>

// This is the code from the lab handout
typedef uint32_t Um_instruction;
typedef uint32_t Um_opcode;

Um_instruction three_register(Um_opcode op, int ra, int rb, int rc);
Um_instruction loadval(unsigned ra, unsigned val);
extern void Um_write_sequence(FILE *output, Seq_T stream);

static inline Um_instruction cond_move(unsigned ra, unsigned rb, unsigned rc);
static inline Um_instruction seg_load (unsigned ra, unsigned rb, unsigned rc);
static inline Um_instruction seg_store(unsigned ra, unsigned rb, unsigned rc);
static inline Um_instruction add      (unsigned ra, unsigned rb, unsigned rc);
static inline Um_instruction multiply (unsigned ra, unsigned rb, unsigned rc);
static inline Um_instruction divide   (unsigned ra, unsigned rb, unsigned rc);
static inline Um_instruction nand     (unsigned ra, unsigned rb, unsigned rc);
static inline Um_instruction halt();
static inline Um_instruction map_seg  (unsigned rb, unsigned rc);
static inline Um_instruction unmap_seg(unsigned rc);
static inline Um_instruction output   (unsigned rc);
static inline Um_instruction input    (unsigned rc);
static inline Um_instruction load_program(unsigned rb, unsigned rc);


/* Create instruction functions */

enum opcode { COND_MOVE = 0, SEG_LOAD, SEG_STORE, ADD, MULTIPLY, DIVIDE,
        NAND, HALT, MAP_SEG, UNMAP_SEG, OUTPUT, INPUT, LOAD_PROGRAM};

static inline Um_instruction cond_move(unsigned ra, unsigned rb, unsigned rc)
{
        return three_register(COND_MOVE, ra, rb, rc);
}

static inline Um_instruction seg_load(unsigned ra, unsigned rb, unsigned rc)
{
        return three_register(SEG_LOAD, ra, rb, rc);
}

static inline Um_instruction seg_store(unsigned ra, unsigned rb, unsigned rc)
{
        return three_register(SEG_STORE, ra, rb, rc);
}

static inline Um_instruction add(unsigned ra, unsigned rb, unsigned rc)
{
        return three_register(ADD, ra, rb, rc);
}

static inline Um_instruction multiply(unsigned ra, unsigned rb, unsigned rc)
{
        return three_register(MULTIPLY, ra, rb, rc);
}

static inline Um_instruction divide(unsigned ra, unsigned rb, unsigned rc)
{
        return three_register(DIVIDE, ra, rb, rc);
}

static inline Um_instruction nand(unsigned ra, unsigned rb, unsigned rc)
{
        return three_register(NAND, ra, rb, rc);
}

static inline Um_instruction halt(void) 
{
        return three_register(HALT, 0, 0, 0);
}

static inline Um_instruction map_seg(unsigned rb, unsigned rc)
{
        return three_register(MAP_SEG, 0, rb, rc);
}

static inline Um_instruction unmap_seg(unsigned rc)
{
        return three_register(UNMAP_SEG, 0, 0, rc);
}

static inline Um_instruction output(unsigned rc)
{
        return three_register(OUTPUT, 0, 0, rc);
}

static inline Um_instruction input(unsigned rc)
{
        return three_register(INPUT, 0, 0, rc);
}

static inline Um_instruction load_program(unsigned rb, unsigned rc)
{
        return three_register(SEG_LOAD, 0, rb, rc);
}


/* sequence modigying functions */

static inline void emit(Seq_T stream, Um_instruction inst)
{
        assert(sizeof(inst) <= sizeof(uintptr_t));
        Seq_addhi(stream, (void *)(uintptr_t)inst);
}

static inline Um_instruction get_inst(Seq_T stream, int i)
{
        assert(sizeof(Um_instruction) <= sizeof(uintptr_t));
        return (Um_instruction)(uintptr_t)(Seq_get(stream, i));
}

static inline void put_inst(Seq_T stream, int i, Um_instruction inst)
{
        assert(sizeof(inst) <= sizeof(uintptr_t));
        Seq_put(stream, i, (void *)(uintptr_t) inst);
}

/* helper functions for instruction building functions */

Um_instruction three_register(Um_opcode op, int ra, int rb, int rc)
{
        uint64_t instruction = 0;

        /* put bits in locations specified */
        instruction = Bitpack_newu(instruction, 4, 28, op);
        instruction = Bitpack_newu(instruction, 3,  6, ra);
        instruction = Bitpack_newu(instruction, 3,  3, rb);
        instruction = Bitpack_newu(instruction, 3,  0, rc);

        return (uint32_t)instruction;
}

Um_instruction loadval(unsigned ra, unsigned val)
{
        uint64_t instruction = 0;

        /* put bits in locations specified */
        instruction = Bitpack_newu(instruction, 4, 28, 13);
        instruction = Bitpack_newu(instruction, 3, 25, ra);
        instruction = Bitpack_newu(instruction, 25, 0, val);

        return (uint32_t)instruction;
}

/* output a test as a file */

extern void Um_write_sequence(FILE *output, Seq_T stream)
{
        int len = Seq_length(stream);
        uint32_t word;
        int c;

        for (int i = 0; i < len; i++) {
                word = (uint32_t)(uintptr_t)Seq_remlo(stream);
                for (int j = sizeof(uint32_t) - 1; j >= 0; j--) {
                        c = (int)Bitpack_getu((uint64_t)word, 8, (j * 8));
                        putc(c, output);
                }
        }

}

/* written tests */

enum regs   { r0 = 0, r1, r2, r3, r4, r5, r6, r7 };

void emit_halt_test(Seq_T stream)
{
        emit(stream, halt());
}

void emit_verbose_halt_test(Seq_T stream)
{
        emit(stream, halt());
        emit(stream, loadval(r1, 'B'));
        emit(stream, output(r1));
        emit(stream, loadval(r1, 'a'));
        emit(stream, output(r1));
        emit(stream, loadval(r1, 'd'));
        emit(stream, output(r1));
        emit(stream, loadval(r1, '!'));
        emit(stream, output(r1));
        emit(stream, loadval(r1, '\n'));
        emit(stream, output(r1));
}

void emit_add_two_numbers(Seq_T stream)
{
        /* add 15 + 30 */
        emit(stream, add(r1, r2, r3));

        emit(stream, halt());
}

void emit_print_six(Seq_T stream)
{
        /* load values to add and output */
        emit(stream, loadval(r1, 48));
        emit(stream, loadval(r2, 6));

        /* 48 + 6 = 54 */
        emit(stream, add(r3, r1, r2));

        /* output result as char */
        emit(stream, output(r3));
        emit(stream, halt());
}

void emit_input_output(Seq_T stream)
{
        
        emit(stream, input(r3));
        /* output result as char */
        emit(stream, output(r3));
        emit(stream, halt());
}