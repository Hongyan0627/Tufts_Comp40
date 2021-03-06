#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strings_not_equal(char *input1, char *input2);

int main(int argc, char* argv[]) 
{
      FILE *infile;
      char input1[100] = {0};
      char input2[100] = {0};

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
    
    fgets(input1, 100, infile);
    fgets(input2, 100, infile);
    
    if (strings_not_equal(input1, input2) != 0) {
            printf("bomb exploded!\n");
            exit(EXIT_FAILURE);
    }
    else {
            printf("no explosion!\n");
            exit(EXIT_SUCCESS);  
    }
        
        return 0;
        
}

int strings_not_equal(char *input1, char *input2)
{        
        if (strcmp(input1, input2) != 0) {
                printf("string1: %s is not equal to string2: %s\n", 
                       input1, input2);
                return 1; /* 1 is true */
        }
        else {
            printf("string1: %s is equal to string2: %s\n",
                   input1, input2);
                   return 0; /* 0 is false */
        }
                   

}