/*
* readaline.c
* purpose: to read a line and store it in a pointer
* by: Derick Yang and Hongyan Wang
* date: January 28, 2016
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
* readaline takes a file pointer of the current
* point in the file, and a pointer to a string
* to update.
* It returns the length of the line that was read in,
* and updates the string pointer to the line that was
* read in.
*/
size_t readaline(FILE *inputfp, char **datap) {
    /*assert whether the inputs are null*/
    assert(inputfp != NULL);
    assert(datap != NULL);

    /*initial size of char array is max 200 chars*/
    size_t n = 200;
    char *theline = (char *) calloc(n, sizeof(char));
    assert(theline != NULL);

    /*index of the current character*/
    size_t num_chars = 0;
    int value;

    while (!feof(inputfp)) {
        value = fgetc(inputfp);
        if (value == '\n' || value == EOF) {
            break;
        }
        /*Expansion for long lines here.
        We use n - 2 because we need room for the end of 
        line character and the null character*/
        if (num_chars > (n - 2)) {
            n = n * 2;
            char *temp = (char *) calloc(n, sizeof(char));
            assert(temp != NULL);
            memcpy(temp, theline, strlen(theline) * sizeof(char));
            free(theline);
            theline = temp;
        }
        theline[num_chars++] = value;
    }
    
    theline[num_chars] = 0;
    /*assign the passed pointer*/
    *datap = theline;
    assert(ferror(inputfp) == 0);
    return num_chars;
}