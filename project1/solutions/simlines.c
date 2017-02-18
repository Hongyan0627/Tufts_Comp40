/*
* simlines.c
* purpose: to detect similar lines amongst multiple files
* by: Derick Yang and Hongyan Wang
* date: January 28, 2016
*/

#include <stdlib.h>
#include <stdio.h>
#include "readaline.h"
#include <table.h>
#include <string.h>
#include <atom.h>
#include <seq.h>
#include <assert.h>
#include <mem.h>

/*
* struct Occurrence is a data type to story each
* occurrence of a line. It contains a filename and
* a line number. We store Occurrences in Sequences
* that we print in our print function.
*/
struct Occurrence{
    const char *filename;
    int line_num;
};

/*helper function for main to process each file*/
void process_file(FILE *curr_file, 
    char* filename, Table_T all_lines);
/*sanitizes each line for easy key values*/
char *clean_line(const char* line, int line_len);
/*checks if a character is valid in a line*/
int isValidChar(char c);
/*inserts an instance into the table*/
void insert(const char *key, const char *filename, 
    int line_num, Table_T all_lines);
/*inserts an occurrence into the corresponding sequence*/
void insert_occ(const char* filename, int line_num, Seq_T seq);
/*counts the number of match groups*/
void count_groups(const void *key, void **value, void *cl);
/*prints match group in the correct format*/
void print_simlines(const void *key, void **value, void *cl);


/*
* main takes command line arguments and analyzes files
* for similar lines, and then prints instances of similar
* lines
* args: command line args
*/
int main(int argc, char *argv[]) {
    /*too few arguments, return with a message*/
    if (argc < 2) {
        fprintf(stderr, "No files found.\n");
        exit(EXIT_FAILURE);
    }

    /*initialize table*/
    Table_T all_lines = Table_new(0, NULL, NULL);
    FILE *curr_file = NULL;
    for (int i = 1; i < argc; i++) {
        process_file(curr_file, argv[i], all_lines);
    }
    /* 
    * count the number of match groups that we have,
    * in order to determine which ones to have a newline after
    */
    int *num_groups = malloc(sizeof(int));
    assert(num_groups != NULL);
    *num_groups = 0;
    /*count the number of match groups that we have*/
    Table_map(all_lines, count_groups, num_groups);
    Table_map(all_lines, print_simlines, num_groups);

    if (num_groups != NULL) {
        free(num_groups);
        num_groups = NULL;
    }
    Table_free(&all_lines);
    exit(EXIT_SUCCESS);
}

/*
* process_file() helps main process each file, reading in all
* the lines in the file and inserting into the table.
* args: FILE *curr_file, the file we want to read from
*       char *filename, the name of the file,
*       Table_T all_lines, the table to store match groups
* byref: all_lines is a call by ref parameter that we update to
*       include lines from the file (not actually returned)
*/
void process_file(FILE *curr_file, 
    char* filename, Table_T all_lines) {
    char *curr_line = NULL;
    /*start counting line number*/
    int line_num = 0;
    size_t line_len;
    /*open file*/
    curr_file = fopen(filename, "r");
    assert(curr_file != NULL);
    /*read lines until end of file*/
    while(!feof(curr_file)) {
        char *prekey = NULL;
        if (curr_line != NULL) {
            free(curr_line);
            curr_line = NULL;
        }
        line_len = readaline(curr_file, &curr_line);
        line_num++;
        prekey = clean_line(curr_line, line_len);
        if (strlen(prekey) > 0) {
            /*create a key and insert the pair in table*/
            const char *realkey = Atom_string(prekey);
            insert(realkey, filename, line_num, all_lines);
        }
        if (prekey != NULL) {
            free(prekey);
            prekey = NULL;
        }
    }
    /*free line*/
    if (curr_line != NULL) {
        free(curr_line);
        curr_line = NULL;
    }
    fclose(curr_file);
}

/*
* clean_line() does pstring processing, cleaning it of any
* characters that should not be counted as parts of a word
* args: char *line, the line to clean,
*       int line_len, the length of that line
* rets: char *, the clean line
*/
char *clean_line(const char *line, int line_len) {
    char *newline = (char *) malloc(sizeof(char) * (line_len + 1));
    assert(newline != NULL);
    
    /* flag tells if we are done with a word (2), at the beginning 
    of a line (0), or still inside a word (1)*/
    int oldctr = 0, newctr = 0, flag = 0;
    while (line[oldctr] != '\0') {
        if (isValidChar(line[oldctr])) {
            flag = 1;
            newline[newctr++] = line[oldctr];
        } else {
            if (flag == 1) {
                newline[newctr++] = ' ';
                flag = 2;
            }
        }
        oldctr++;
    }

    /*terminate the string*/
    if (newctr > 0 && newline[newctr - 1] == ' ') {
        newline[newctr - 1] = '\0';
    } else {
        newline[newctr] = '\0';
    }

    return newline;
}

/*
* isValidChar() determines if a character is a valid word character
* args: char c, the char to check
* rets: int, 0 if invalid.
*/
int isValidChar(char c) {
    return ((c >= '0' && c <= '9') ||
        (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        (c == '_'));
}

/*
* insert() inserts an instance into the table
* args: char *key, the key
*       char *filename, the name of the files
*       int line_num, the line num we encountered the line
*       Table_T all_lines, the table to update
* byref: all_lines is a call by ref parameter that we update
*       (not actually returned).
*/
void insert(const char *key, const char *filename, 
    int line_num, Table_T all_lines) {
    Seq_T existing_seq = (Seq_T) Table_get(all_lines, key);
    if (existing_seq == NULL) {
        Seq_T new_seq = Seq_new(0);
        insert_occ(filename, line_num, new_seq);
        Seq_T double_check = (Seq_T)Table_put(all_lines, key, new_seq);
        assert(double_check == NULL);
    } else {
        insert_occ(filename, line_num, existing_seq);
    }

}

/*
* insert_occ() inserts an Occurrence into the correct sequence
* args: char *filename, the name of the file
*       int line_num, the line number
*       Seq_T seq, the sequence to update
* byref: seq is a call by reference parameter that we update
*       (not actually returned)
*/
void insert_occ(const char* filename, int line_num, Seq_T seq) {
    struct Occurrence *oc = 
            (struct Occurrence *) malloc(sizeof(struct Occurrence)); 
    assert(oc != NULL);
    oc->filename = filename;
    oc->line_num = line_num;
    Seq_addhi(seq, oc);
}

/*
* count_groups() counts the number of match groups found
* Passed as a parameter to the Hanson Table_map function.
* args(all void): char *key, the key, Seq_T **value, ptr to value, and
*       int *cl, which keeps track of the number of match groups
* byref: after Table_map runs this function through the entire map,
*          *cl should contain the number of match groups in the table
*/
void count_groups(const void *key, void **value, void *cl) {
    Seq_T the_seq = (Seq_T)*value;
    int seq_size = Seq_length(the_seq);
    int *count = (int *) cl;
    (void) key;
    /*count the number of match groups*/
    if (seq_size > 1) {
        (*count)++;
    }
}

/*
* print_simlines() prints each match group. Passed as a
* parameter to the Hanson Table_map function.
* args(all void): char *key, the key, void **value, ptr to value, and
*        int *cl, the number of groups left to print
*/
void print_simlines(const void *key, void **value, void *cl) {
    /*unvoid variables*/
    int *count = (int *) cl;
    Seq_T the_seq = (Seq_T)*value;
    int seq_size = Seq_length(the_seq);
    struct Occurrence* curr_ocurr = NULL;
    if (seq_size > 1) { /*we have a match group*/
        printf("%s\n", (const char*) key);
        /*print each occurrence formatted*/
        for (int i = 0; i < seq_size; i++) {
            curr_ocurr = (struct Occurrence*) Seq_get(the_seq, i);
            printf("%-20s %7d\n", curr_ocurr->filename, curr_ocurr->line_num);
            if (curr_ocurr != NULL) {
                free(curr_ocurr);
                curr_ocurr = NULL;
            }
        }
        /*count down the number of groups left to print*/
        if (((*count)--) > 1) { /*last group*/
            printf("\n");
        }
    } else {
        curr_ocurr = (struct Occurrence*) Seq_get(the_seq, 0);
        /*free space*/
        if (curr_ocurr != NULL) {
            free(curr_ocurr);
            curr_ocurr = NULL;
        }
    }
    Seq_free(&the_seq);
}
