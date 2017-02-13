/*
 *     filename: universal_machine.c
 *     partner 1 name: Peter Vondras       Login: peter
 *     partner 2 name: Hongyan Wang        Login: hwang10
 *     date: April 10th, 2016
 *     assignment: hw6
 *
 *     summary: Universal machine main ensures proper input, requests loading
 *              program and calls the UM to run.            
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "program_loader.h"
#include "UM.h"

int main(int argc, char *argv[])
{
        size_t size = 1;
        struct stat statistics;
        FILE *input;

        if (argc != 2) {
                fprintf(stderr, "Improper input\n");
                return EXIT_FAILURE;
        } else {
                /* query filesize */
                if (stat(argv[1], &statistics) == 0)
                        size = statistics.st_size;
                /* only run programs with number of bytes divisible by 4 */
                if (size % 4 == 0) {
                        input = fopen(argv[1], "r");
                        if (input == NULL)
                                fprintf(stderr, "Improper input\n");
                        Seg_T program = initial_load_program(input, 
                                (uint32_t)(size / 4));
                        fclose(input);
                        return run_um(program);
                }
                fprintf(stderr, "Improper input\n");
                return EXIT_FAILURE;
        }
}
