#include <bitpack.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <seq.h>

// This is the code from the lab handout
typedef uint32_t Um_instruction;
typedef uint32_t Um_opcode;

Um_instruction three_register(Um_opcode op, int ra, int rb, int rc);
Um_instruction loadval(uint32_t ra, uint32_t val);
extern void Um_write_sequence(FILE *output, Seq_T stream);

static inline Um_instruction cond_move(uint32_t ra, uint32_t rb, uint32_t rc);
static inline Um_instruction seg_load (uint32_t ra, uint32_t rb, uint32_t rc);
static inline Um_instruction seg_store(uint32_t ra, uint32_t rb, uint32_t rc);
static inline Um_instruction add      (uint32_t ra, uint32_t rb, uint32_t rc);
static inline Um_instruction multiply (uint32_t ra, uint32_t rb, uint32_t rc);
static inline Um_instruction divide   (uint32_t ra, uint32_t rb, uint32_t rc);
static inline Um_instruction nand     (uint32_t ra, uint32_t rb, uint32_t rc);
static inline Um_instruction halt();
static inline Um_instruction map_seg  (uint32_t rb, uint32_t rc);
static inline Um_instruction unmap_seg(uint32_t rc);
static inline Um_instruction output   (uint32_t rc);
static inline Um_instruction input    (uint32_t rc);
static inline Um_instruction load_program(uint32_t rb, uint32_t rc);


/* Create instruction functions */

enum opcode { COND_MOVE = 0, SEG_LOAD, SEG_STORE, ADD, MULTIPLY, DIVIDE,
        NAND, HALT, MAP_SEG, UNMAP_SEG, OUTPUT, INPUT, LOAD_PROGRAM};

static inline Um_instruction cond_move(uint32_t ra, uint32_t rb, uint32_t rc)
{
        return three_register(COND_MOVE, ra, rb, rc);
}

static inline Um_instruction seg_load(uint32_t ra, uint32_t rb, uint32_t rc)
{
        return three_register(SEG_LOAD, ra, rb, rc);
}

static inline Um_instruction seg_store(uint32_t ra, uint32_t rb, uint32_t rc)
{
        return three_register(SEG_STORE, ra, rb, rc);
}

static inline Um_instruction add(uint32_t ra, uint32_t rb, uint32_t rc)
{
        return three_register(ADD, ra, rb, rc);
}

static inline Um_instruction multiply(uint32_t ra, uint32_t rb, uint32_t rc)
{
        return three_register(MULTIPLY, ra, rb, rc);
}

static inline Um_instruction divide(uint32_t ra, uint32_t rb, uint32_t rc)
{
        return three_register(DIVIDE, ra, rb, rc);
}

static inline Um_instruction nand(uint32_t ra, uint32_t rb, uint32_t rc)
{
        return three_register(NAND, ra, rb, rc);
}

static inline Um_instruction halt(void) 
{
        return three_register(HALT, 0, 0, 0);
}

static inline Um_instruction map_seg(uint32_t rb, uint32_t rc)
{
        return three_register(MAP_SEG, 0, rb, rc);
}

static inline Um_instruction unmap_seg(uint32_t rc)
{
        return three_register(UNMAP_SEG, 0, 0, rc);
}

static inline Um_instruction output(uint32_t rc)
{
        return three_register(OUTPUT, 0, 0, rc);
}

static inline Um_instruction input(uint32_t rc)
{
        return three_register(INPUT, 0, 0, rc);
}

static inline Um_instruction load_program(uint32_t rb, uint32_t rc)
{
        return three_register(LOAD_PROGRAM, 0, rb, rc);
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

Um_instruction loadval(uint32_t ra, uint32_t val)
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

void emit_test1(Seq_T stream)
{
        /* load values to add and output */
        emit(stream, loadval(r7, 'T'));
        emit(stream, output(r7));
        emit(stream, loadval(r7, 'e'));
        emit(stream, output(r7));
        emit(stream, loadval(r7, 's'));
        emit(stream, output(r7));
        emit(stream, loadval(r7, 't'));
        emit(stream, output(r7));
        emit(stream, loadval(r7, ' '));
        emit(stream, output(r7));
        emit(stream, loadval(r7, '1'));
        emit(stream, output(r7));
        emit(stream, loadval(r7, '\n'));
        emit(stream, output(r7));

        // Test add and multiplication 
        emit(stream, loadval(r1, 6782));
        emit(stream, loadval(r2, 1218));
        emit(stream, add(r0, r1, r2));

        emit(stream, loadval(r2, 4000));
        emit(stream, divide(r0, r0, r2));

        emit(stream, loadval(r2, 48));
        emit(stream, add(r0, r0, r2));
        emit(stream, output(r0));
        emit(stream, loadval(r7, '\n'));
        emit(stream, output(r7));

        emit(stream, loadval(r7, 'T'));
        emit(stream, output(r7));
        emit(stream, loadval(r7, 'e'));
        emit(stream, output(r7));
        emit(stream, loadval(r7, 's'));
        emit(stream, output(r7));
        emit(stream, loadval(r7, 't'));
        emit(stream, output(r7));
        emit(stream, loadval(r7, ' '));
        emit(stream, output(r7));
        emit(stream, loadval(r7, '2'));
        emit(stream, output(r7));
        emit(stream, loadval(r7, '\n'));
        emit(stream, output(r7));

        emit(stream, loadval(r2, 0));
        emit(stream, loadval(r3, 2));

        emit(stream, loadval(r6, 7));        
        emit(stream, map_seg(r5,r6));

        emit(stream, loadval(r3, 0));
        emit(stream, loadval(r2, 0));
        emit(stream, seg_load(r4, r3, r2));
        emit(stream, seg_store(r5, r2, r4));

        emit(stream, loadval(r2, 1));
        emit(stream, seg_load(r4, r3, r2));
        emit(stream, seg_store(r5, r2, r4));

        emit(stream, loadval(r2, 2));
        emit(stream, seg_load(r4, r3, r2));
        emit(stream, seg_store(r5, r2, r4));

        emit(stream, loadval(r2, 3));
        emit(stream, seg_load(r4, r3, r2));
        emit(stream, seg_store(r5, r2, r4));

        emit(stream, loadval(r2, 4));
        emit(stream, seg_load(r4, r3, r2));
        emit(stream, seg_store(r5, r2, r4));

        emit(stream, loadval(r2, 5));
        emit(stream, seg_load(r4, r3, r2));
        emit(stream, seg_store(r5, r2, r4));

        emit(stream, loadval(r2, 6));
        emit(stream, seg_load(r4, r3, r2));
        emit(stream, seg_store(r5, r2, r4));

        emit(stream, loadval(r3, 0));
        emit(stream, load_program(r5, r3));
        emit(stream, halt());
}

void emit_load_a_program(Seq_T stream)
{
        /* create segment of size 15 */
        emit(stream, loadval(r5, 3));  /* declare size */
        emit(stream, map_seg(r7, r5)); /* map seg of size 15 */
        emit(stream, loadval(r3, 1));  /* load a one for incrementing */
        emit(stream, loadval(r2, 18));  /* load a one for incrementing */

        /* copy data below to new segment */
        emit(stream, seg_load(r4, r0, r2));
        emit(stream, seg_store(r7, r1, r4));
        emit(stream, add(r2, r2, r3));  /* add 1 to index value */
        emit(stream, add(r1, r1, r3));  /* add 1 to index value */
        emit(stream, seg_load(r4, r0, r2));
        emit(stream, seg_store(r7, r1, r4));
        emit(stream, add(r2, r2, r3));  /* add 1 to index value */
        emit(stream, add(r1, r1, r3));  /* add 1 to index value */
        emit(stream, seg_load(r4, r0, r2));
        emit(stream, seg_store(r7, r1, r4));
        emit(stream, add(r2, r2, r3));  /* add 1 to index value */
        emit(stream, add(r1, r1, r3));  /* add 1 to index value */

        emit(stream, load_program(r7, r0));

        /* data to load as new program */
        emit(stream, halt());
        emit(stream, loadval(r1, 'P'));
        emit(stream, output(r1));
        emit(stream, halt());
}

void emit_load_out(Seq_T stream)
{
        emit(stream, loadval(r0, 48));
        emit(stream, loadval(r1, 49));
        emit(stream, loadval(r2, 50));
        emit(stream, loadval(r3, 51));
        emit(stream, loadval(r4, 52));
        emit(stream, loadval(r5, 53));
        emit(stream, loadval(r6, 54));
        emit(stream, loadval(r7, 55));
        emit(stream, output(r0));
        emit(stream, output(r1));
        emit(stream, output(r2));
        emit(stream, output(r3));
        emit(stream, output(r4));
        emit(stream, output(r5));
        emit(stream, output(r6));
        emit(stream, output(r7));
        emit(stream, halt());
}

void emit_in_out(Seq_T stream)
{
        emit(stream, input(r0));
        emit(stream, output(r0));
        emit(stream, input(r1));
        emit(stream, output(r1));
        emit(stream, input(r2));
        emit(stream, output(r2));
        emit(stream, input(r3));
        emit(stream, output(r3));
        emit(stream, input(r4));
        emit(stream, output(r4));
        emit(stream, input(r5));
        emit(stream, output(r5));
        emit(stream, input(r6));
        emit(stream, output(r6));
        emit(stream, input(r7));
        emit(stream, output(r7));
        emit(stream, halt());
}

void emit_math(Seq_T stream)
{
        emit(stream, loadval(r0, 11));
        emit(stream, loadval(r1, 44));
        emit(stream, loadval(r2, 10));
        emit(stream, loadval(r3, 8));
        emit(stream, loadval(r4, (1 << 25) - 1));
        emit(stream, loadval(r5, 1 << 24));
        emit(stream, add(r7, r0, r1));
        emit(stream, output(r7));
        emit(stream, multiply(r7, r1, r2));
        emit(stream, divide(r7, r7, r3));
        emit(stream, output(r7));
        emit(stream, halt());
}

void emit_set_map_unmap(Seq_T stream)
{
        emit(stream, loadval(r6, 1000));
        emit(stream, loadval(r7, 100));
        emit(stream, loadval(r4, 'P'));
        emit(stream, loadval(r5, 'F'));

        emit(stream, map_seg(r1, r6));
        emit(stream, unmap_seg(r1));
        emit(stream, map_seg(r2, r7));

        emit(stream, nand(r3, r1, r2));
        emit(stream, add(r3, r3, r1));
        emit(stream, nand(r3, r3, r3));
        emit(stream, cond_move(r4, r5, r3));

        emit(stream, output(r4));

        emit(stream, halt());
}

void emit_seg_store_load(Seq_T stream)
{
        emit(stream, loadval(r0, 48));
        emit(stream, loadval(r1, 49));
        emit(stream, loadval(r2, 50));
        emit(stream, loadval(r3, 51));
        emit(stream, loadval(r4, 52));
        emit(stream, loadval(r5, 53));
        emit(stream, loadval(r6, 54));
        emit(stream, loadval(r7, 55));
        emit(stream, output(r0));
        emit(stream, output(r1));
        emit(stream, output(r2));
        emit(stream, output(r3));
        emit(stream, output(r4));
        emit(stream, output(r5));
        emit(stream, output(r6));
        emit(stream, output(r7));

        emit(stream, loadval(r6, 10000));        
        emit(stream, map_seg(r1,r6));

        emit(stream, loadval(r2, 0));
        emit(stream, loadval(r3, 0));
        emit(stream, seg_load(r4, r2, r3));
        emit(stream, loadval(r6, 100));
        emit(stream, multiply(r5, r3, r6));
        emit(stream, seg_store(r1, r5, r4));

        emit(stream, loadval(r2, 0));
        emit(stream, loadval(r3, 1));
        emit(stream, seg_load(r4, r2, r3));
        emit(stream, loadval(r6, 100));
        emit(stream, multiply(r5, r3, r6));
        emit(stream, seg_store(r1, r5, r4));

        emit(stream, loadval(r2, 0));
        emit(stream, loadval(r3, 2));
        emit(stream, seg_load(r4, r2, r3));
        emit(stream, loadval(r6, 100));
        emit(stream, multiply(r5, r3, r6));
        emit(stream, seg_store(r1, r5, r4));

        emit(stream, loadval(r2, 0));
        emit(stream, loadval(r3, 3));
        emit(stream, seg_load(r4, r2, r3));
        emit(stream, loadval(r6, 100));
        emit(stream, multiply(r5, r3, r6));
        emit(stream, seg_store(r1, r5, r4));

        emit(stream, loadval(r2, 0));
        emit(stream, loadval(r3, 4));
        emit(stream, seg_load(r4, r2, r3));
        emit(stream, loadval(r6, 100));
        emit(stream, multiply(r5, r3, r6));
        emit(stream, seg_store(r1, r5, r4));

        emit(stream, loadval(r2, 0));
        emit(stream, loadval(r3, 5));
        emit(stream, seg_load(r4, r2, r3));
        emit(stream, loadval(r6, 100));
        emit(stream, multiply(r5, r3, r6));
        emit(stream, seg_store(r1, r5, r4));

        emit(stream, loadval(r2, 0));
        emit(stream, loadval(r3, 6));
        emit(stream, seg_load(r4, r2, r3));
        emit(stream, loadval(r6, 100));
        emit(stream, multiply(r5, r3, r6));
        emit(stream, seg_store(r1, r5, r4));

        emit(stream, loadval(r2, 0));
        emit(stream, loadval(r3, 7));
        emit(stream, seg_load(r4, r2, r3));
        emit(stream, loadval(r6, 100));
        emit(stream, multiply(r5, r3, r6));
        emit(stream, seg_store(r1, r5, r4));

        emit(stream, loadval(r2, 0));
        emit(stream, loadval(r3, 8));
        emit(stream, seg_load(r4, r2, r3));
        emit(stream, loadval(r6, 100));
        emit(stream, multiply(r5, r3, r6));
        emit(stream, seg_store(r1, r5, r4));

        emit(stream, loadval(r2, 0));
        emit(stream, loadval(r3, 9));
        emit(stream, seg_load(r4, r2, r3));
        emit(stream, loadval(r6, 100));
        emit(stream, multiply(r5, r3, r6));
        emit(stream, seg_store(r1, r5, r4));

        emit(stream, loadval(r2, 0));
        emit(stream, loadval(r3, 10));
        emit(stream, seg_load(r4, r2, r3));
        emit(stream, loadval(r6, 100));
        emit(stream, multiply(r5, r3, r6));
        emit(stream, seg_store(r1, r5, r4));

        emit(stream, loadval(r2, 0));
        emit(stream, loadval(r3, 11));
        emit(stream, seg_load(r4, r2, r3));
        emit(stream, loadval(r6, 100));
        emit(stream, multiply(r5, r3, r6));
        emit(stream, seg_store(r1, r5, r4));

        emit(stream, loadval(r2, 0));
        emit(stream, loadval(r3, 12));
        emit(stream, seg_load(r4, r2, r3));
        emit(stream, loadval(r6, 100));
        emit(stream, multiply(r5, r3, r6));
        emit(stream, seg_store(r1, r5, r4));

        emit(stream, loadval(r2, 0));
        emit(stream, loadval(r3, 13));
        emit(stream, seg_load(r4, r2, r3));
        emit(stream, loadval(r6, 100));
        emit(stream, multiply(r5, r3, r6));
        emit(stream, seg_store(r1, r5, r4));

        emit(stream, loadval(r2, 0));
        emit(stream, loadval(r3, 14));
        emit(stream, seg_load(r4, r2, r3));
        emit(stream, loadval(r6, 100));
        emit(stream, multiply(r5, r3, r6));
        emit(stream, seg_store(r1, r5, r4));

        emit(stream, loadval(r2, 0));
        emit(stream, loadval(r3, 15));
        emit(stream, seg_load(r4, r2, r3));
        emit(stream, loadval(r6, 100));
        emit(stream, multiply(r5, r3, r6));
        emit(stream, seg_store(r1, r5, r4));


        emit(stream, loadval(r7, 0));
        emit(stream, load_program(r1, r7));

        emit(stream, halt());
}

void emit_cond(Seq_T stream)
{
        emit(stream, loadval(r1, 0));
        emit(stream, loadval(r2, 1));
        emit(stream, loadval(r3, 2));
        emit(stream, loadval(r7, 48));
        emit(stream, add(r6, r2, r7));
        emit(stream, output(r6));
        
        emit(stream,cond_move(r2, r3, r1));
        emit(stream, add(r6, r2, r7));
        emit(stream, output(r6));

        emit(stream, loadval(r1, 1));
        emit(stream,cond_move(r2, r3, r1));
        emit(stream, add(r6, r2, r7));
        emit(stream, output(r6));

        emit(stream, halt());
}

void emit_nand(Seq_T stream)
{
        /*16777215 is 0xffffff*/
        emit(stream, loadval(r1, 16777215));
        emit(stream, loadval(r2, 1 << 8));
        emit(stream, multiply(r1, r1, r2));
        emit(stream, loadval(r2, 255));
        emit(stream, add(r1, r1, r2));

        emit(stream, loadval(r3, 16777215));
        emit(stream, loadval(r2, 1 << 8));
        emit(stream, multiply(r3, r3, r2));
        emit(stream, loadval(r2, 241));
        emit(stream, add(r3, r3, r2));

        emit(stream, nand(r0, r1, r3));
        
        emit(stream, loadval(r2, 40));
        emit(stream, add(r0, r0, r2));
        emit(stream, output(r0));

        emit(stream, halt());
}