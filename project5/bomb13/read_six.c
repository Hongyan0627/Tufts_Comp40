#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strings_not_equal(char *input1, char *input2);

int main(int argc, char* argv[]) 
{
      FILE *infile;
      int int1, int2, int3, int4, int5, int6;

    /* Note to self: remember to port this bomb to Windows and put a 
     * fantastic GUI on it. */

    /* When run with no arguments, the bomb reads its input lines 
     * from standard input. */
    if (argc == 1) {  
        infile = stdin;
    } 

    /* When run with one argument <file>, the bomb reads from <file> 
     * until EOF, and then switches to standard input. Thus, as you 
     * defuse each phase, you can add its defusing string to <file> and
     * avoid having to retype it. */
    else if (argc == 2) {
        if (!(infile = fopen(argv[1], "r"))) {
            printf("%s: Error: Couldn't open %s\n", argv[0], argv[1]);
            exit(8);
        }
    }

    /* You can't call the bomb with more than 1 command line argument. */
    else {
        printf("Usage: %s [<input_file>]\n", argv[0]);
        exit(8);
    }
    
    int read = fscanf(infile, "%d %d %d %d %d %d", &int1, &int2, &int3, &int4,
                      &int5, &int6);
    if (read <= 0x5) {
            printf("failure\n");
            exit(1);
    }
    
    return 0;
}