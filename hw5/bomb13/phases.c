/* 
        phases.c
        By: Hongyan Wang and Josie Barth
        Date: March 18th 2016
        
        Purpose: C code that represents our best guess as the fuction might
                 be implemented for each phase
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *TARGET_1 = "This is actually not an entirely terrible idea.";
static char *TARGET_5 = "giants";
static char *PARSE_5 = "isrveawhobpnutfg";

/*returns true (1) if strings are not equal, otherwise returns false (0)*/
extern int strings_not_equal(char *input1, char *input2);

/* takes a char * and returns the length of the string as an int */
extern int string_length(char *input);

extern void explode_bomb();
extern void read_line(char **input);
extern void phase_defused();

struct node {
        long value;
        struct node *next;
};

struct node node_9 = {
        158,
        NULL
};

struct node node_8 = {
        862,
        &node_9
};

struct node node_7 = {
        599,
        &node_8
};

struct node node_6 = {
        246,
        &node_7
};

struct node node_5 = {
        480,
        &node_6
};

struct node node_4 = {
        781,
        &node_5
};

struct node node_3 = {
        888,
        &node_4
};

struct node node_2 = {
        655,
        &node_3
};

struct node node_1 = {
        722,
        &node_2
};

struct BST_node {
        long value;
        struct BST_node *left, *right;
};

/* see README for general structure of the BST */
extern struct BST_node *BST;



void fun_6(struct node *root);

/* compare 2 strings.  See if input string is equal to: 
  "This is actually not an entirely terrible idea."*/
void phase_1(char *input)
{
        int answer;
        
        /* in strings_not_equal, compares the input with the string:
           "This is actually not an entirely terrible idea." */
        answer = strings_not_equal(input, TARGET_1);
        
        /* if strings are not equal */
        if (answer == 1) {
                explode_bomb();
        } 
        
        /* else strings are equal: (answer == 0) so we defused phase 1*/   
        return;
}

/* read six numbers and see if they follow the pattern: 
   x, x+5, x+10, x+15, x+20, x+ 25 */
void phase_2(char *input)
{
        int arr[6];
        int read;
        int i;
        
        read = sscanf(input, "%d %d %d %d %d %d", &arr[0], &arr[1], &arr[2],
                                                  &arr[3], &arr[4], &arr[5]);
                                              
         /* if you read in less than 6 numbers, explode bomb */
        if (read <= 5) {
                explode_bomb();
        }
       
        for (i = 1; i < 6; i++) {
                if (arr[i] != (arr[i-1] + 5)) {
                        explode_bomb();
                }
        }
        /* if you make it here without any explosions, then you have 6 numbers
        that follow the pattern: x, x+5, x+10, x+15, x+20, x+ 255.  Good job!*/
        return;
}

/* enter a value that correponds with a switch statement 0-7 */
void phase_3(char *input) 
{
        int switch_num;
        int value;
        int switch_val;
        int read;
        
        read = sscanf(input, "%d %d", &switch_num, &value);
        
        /* if you read less than 2 numbers, explode bomb */
        if (read <= 1)
                explode_bomb();
        
        /* if you give an invalid switch case number (a number greater than 7),
           explode bomb */
        if (switch_num > 7) {
                explode_bomb();
                switch_val = 0;
        }
        else {
                switch(switch_num) {
                        case 0 : switch_val = 0x1a8; break;
                        case 2 : switch_val = 0x206; break;
                        case 3 : switch_val = 0x1e6; break;
                        case 4 : switch_val = 0x17d; break;
                        case 5 : switch_val = 0x1aa; break;
                        case 6 : switch_val = 0x28b; break;
                        case 7 : switch_val = 0x11c; break;
                        default : switch_val = 0x1c7;
                }
        } 
        if (value != switch_val)
                explode_bomb();
        return;
}

/* recursively cacluates the factorial of a given number */
int func4(int fact) 
{
        if (fact <= 1)
                return 1;
        else 
                return (fact * func4(fact - 1));
}

/* compute 7 factorial */
void phase_4(char *input)
{
        int factorial;
        int compute_fact;
        int read;
        
        read = sscanf(input, "%d", &factorial);
        
        if (read != 1)
                explode_bomb();
        
        if (factorial <= 0)
                explode_bomb();
        
        compute_fact = func4(factorial);
        
        /*checks if computed factorial equal 7! = 5040 */
        if (compute_fact != 5040)
                explode_bomb();
        
        return;
}


/* Takes an input string and computes a new string from a global parsed string.
   The result should match the target string "giants" */
void phase_5(char *input)
{
        int i;
        int index;
        int result;
        
        if (string_length(input) != 6)
                explode_bomb();
        
        for (i = 0; i < 6; i++) {
                
                /* calcuates index of global parse string from input string */
                index = (input[i] % 16); 
                
                input[i] = PARSE_5[index]; 
        }
        
        result = strings_not_equal(input, TARGET_5);
        
        if (result != 0)
                explode_bomb();
        
        return;
}

void fun_6(struct node *root)
{
        if (root == NULL)
                return;
        
        root->next = &node_1;
        
        struct node *flag;
        struct node *curr;
        long temp;
       
        flag = root;
        curr = flag->next;
        
        /* bubble sort the linked list */
        while (flag->next != NULL) {
        
                while (curr != NULL) {
                        if (curr->value > flag->value) { 
                                temp = curr->value;
                                curr->value = flag->value;
                                flag->value = temp;
                        }
                        curr = curr->next;       
                }
                flag = flag->next;
        }
        return;
}

/* insert a number into the 4th index of a linked list (0-based indexing);
   the 5th node in the list*/
void phase_6(char *input)
{
        long num;
        struct node node_0;
        int i;
        
        num = strtol(input, NULL, 10);
        
        node_0.value = num;
        
        fun_6(&node_0);
        
        struct node *curr = &node_0;
        
        /*get to the 4th index of the linked list (0-based indexing);
          the 5th node in the list*/
        for (i = 0; i < 5; i++)
                curr = curr->next; 
        
        if (curr->value != num)
                explode_bomb();
        
        return;
         
}

long fun_7(long num, struct BST_node *BST)
{
        if (num >= BST->value) {
                
                if (num == BST->value)
                        return 0;
                else 
                        return (2 * fun_7(num, BST->right) + 1);
        }
        else
                return (2 * fun_7(num, BST->left));
}

void secret_phase()
{
        char *input;
        long num;
        long result;

        read_line(&input);
        num = strtol(input, NULL, 10);
        
        if (num > 1001)
                explode_bomb();
        
        result = fun_7(num, BST);
        
        if (result != 6)
                explode_bomb();
        
        phase_defused();
        return;
}



