#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assert.h"
#include "fmt.h"
#include "seq.h"

extern void Um_write_sequence(FILE *output, Seq_T instructions);

extern void emit_halt_test(Seq_T instructions);
extern void emit_verbose_halt_test(Seq_T instructions);
extern void emit_add_two_numbers(Seq_T instructions);
extern void emit_print_six(Seq_T instructions);
extern void emit_test1(Seq_T stream);
extern void emit_load_a_program(Seq_T instructions);
extern void emit_load_out(Seq_T stream);
extern void emit_in_out(Seq_T stream);
extern void emit_math(Seq_T stream);
extern void emit_set_map_unmap(Seq_T stream);
extern void emit_seg_store_load(Seq_T stream);
extern void emit_cond(Seq_T stream);
extern void emit_nand(Seq_T stream);

static struct test_info {
        const char *name;
        const char *test_input;          /* NULL means no input needed */
        const char *expected_output;
        /* writes instructions into sequence */
        void (*emit_test)(Seq_T stream);
} tests[] = {
        { "1_halt",           NULL, "", emit_halt_test },
        { "halt-verbose",   NULL, "", emit_verbose_halt_test },
        { "add",            NULL, "", emit_add_two_numbers },
        { "print-six",      NULL, "6", emit_print_six },
        { "test1",          NULL, "", emit_test1 },
        { "load-a-program", NULL, "PASSED!", emit_load_a_program },
        { "2_load_out_halt", NULL, "01234567", emit_load_out},
        { "3_in_out_halt", "hello,world!", "hello,wo", emit_in_out},
        { "4_math", NULL, "77", emit_math},
        { "5_map_unmap", NULL, "P", emit_set_map_unmap},
        { "6_store_load", NULL, "0123456701234567", emit_seg_store_load},
        { "7_cond", NULL, "112", emit_cond},
        { "8_nand", NULL, "6", emit_nand}
};
  
#define NTESTS (sizeof(tests)/sizeof(tests[0]))

/*
 * open file 'path' for writing, then free the pathname;
 * if anything fails, checked runtime error
 */
static FILE *open_and_free_pathname(char *path);

/*
 * if contents is NULL or empty, remove the given 'path', 
 * otherwise write 'contents' into 'path'.  Either way, free 'path'.
 */
static void write_or_remove_file(char *path, const char *contents);

static void write_test_files(struct test_info *test)
{
        FILE *binary = open_and_free_pathname(Fmt_string("%s.um", test->name));
        Seq_T instructions = Seq_new(0);
        test->emit_test(instructions);
        Um_write_sequence(binary, instructions);
        Seq_free(&instructions);
        fclose(binary);

        write_or_remove_file(Fmt_string("%s.0", test->name),
                             test->test_input);
        write_or_remove_file(Fmt_string("%s.1", test->name),
                             test->expected_output);
}

int main (int argc, char *argv[])
{
        bool failed = false;
        if (argc == 1)
                for (unsigned i = 0; i < NTESTS; i++) {
                        printf("***** Writing test '%s'.\n", tests[i].name);
                        write_test_files(&tests[i]);
                }
        else
                for (int j = 1; j < argc; j++) {
                        bool tested = false;
                        for (unsigned i = 0; i < NTESTS; i++)
                                if (!strcmp(tests[i].name, argv[j])) {
                                        tested = true;
                                        write_test_files(&tests[i]);
                                }
                        if (!tested) {
                                failed = true;
                                fprintf(stderr,
                                        "***** No test named %s *****\n",
                                        argv[j]);
                        }
                }
        return failed; /* failed nonzero == exit nonzero == failure */
}


static void write_or_remove_file(char *path, const char *contents)
{
        if (contents == NULL || *contents == '\0') {
                remove(path);
        } else {
                FILE *input = fopen(path, "wb");
                assert(input != NULL);

                fputs(contents, input);
                fclose(input);
        }
        free(path);
}

static FILE *open_and_free_pathname(char *path)
{
        FILE *fp = fopen(path, "wb");
        assert(fp != NULL);

        free(path);
        return fp;
}
