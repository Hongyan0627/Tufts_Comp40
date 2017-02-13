#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <seq.h>

typedef uint32_t Um_word;

/* make Seq_T into a stack of integers */
static void push(Seq_T values, Um_word word) 
{
        assert(sizeof(Um_word) <= sizeof(uintptr_t));
        Seq_addhi(values, (void *)(uintptr_t) word);
}

static Um_word pop(Seq_T values)
{
        return (Um_word)(uintptr_t) Seq_remhi(values);
}

static Um_word get(Seq_T values, int i)
{
        return (Um_word)(uintptr_t) Seq_get(values, i);
}

/*
 * return true iff sequence has at least n elements
 * when returning false, writes an error message about stack underflow
 */
static bool has(Seq_T sequence, int n);

/*
 * implement binary operator.  Macro needed because OPERATOR is not a C value
 */
#define BINARY(OPERATOR) \
  do { \
          if (has(values, 2)) {                 \
                  Um_word y = pop(values);      \
                  Um_word x = pop(values);      \
                  push(values, x OPERATOR y);   \
          }                                     \
  } while (false)

/*
 * and similarly for unary operator
 */
#define UNARY(OPERATOR) \
  do { \
          if (has(values, 1)) {                 \
                  Um_word x = pop(values);      \
                  push(values, OPERATOR x);     \
          }                                     \
  } while (false)


static void run(Seq_T values)
{
        int c; /* character from standard input */
waiting:
        /*
         * if we are not entering a number, we are here,
         * awaiting instructions
         */
        c = getchar();

waiting_with_character:
        switch (c) {
        case EOF: return;
                /* push a number */
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
                push(values, c - '0');
                goto entering;
                /* unary and binary operators */
        case '+': BINARY(+); goto waiting;
        case '-': BINARY(-); goto waiting;
        case '*': BINARY(*); goto waiting;
        case '&': BINARY(&); goto waiting;
        case '|': BINARY(|); goto waiting;
        case '~' : UNARY(~); goto waiting;
        case 'c' : UNARY(-); goto waiting; /* "change sign" */
        case '/': 
                if (has(values, 2)) {
                        Um_word y = pop(values);
                        Um_word x = pop(values);
                        if (y == 0) {
                                printf("Division by zero\n");
                                push(values, x);
                                push(values, y);
                        } else if ((int32_t) x < 0) {
                                if ((int32_t) y < 0) {
                                        x = -(int32_t)x;
                                        y = -(int32_t)y;
                                        push(values, x / y);
                                } else {
                                        x = -(int32_t)x;
                                        Um_word q = x / y;
                                        push(values, -(int32_t)q);
                                }
                        } else if ((int32_t) y < 0) {
                                y = -(int32_t) y;
                                Um_word q = x / y;
                                push(values, -(int32_t)q);
                        } else {
                                push(values, x / y);
                        }
                }
                goto waiting;

        case 's':  /* swap top two values */
                if (has(values, 2)) {
                        Um_word y = pop(values);
                        Um_word x = pop(values);
                        push(values, y);
                        push(values, x);
                }
                goto waiting;
        case 'd': /* duplicate top value */
                if (has(values, 1)) {
                        Um_word x = pop(values);
                        push(values, x);
                        push(values, x);
                }
                goto waiting;
        case 'p': /* pop the value stack */
                if (has(values, 1))
                        pop(values);
                goto waiting;
        case '\n': /* print the value stack */
                for (int i = Seq_length(values); i > 0; i--)
                        printf(">>> %d\n", get(values, i - 1));
                goto waiting;
        case 'z': /* clear (zero out) the value stack by popping all elements */
                while (Seq_length(values) > 0)
                        Seq_remlo(values);
                goto waiting;
        default:
                if (!isspace(c))
                        printf("Unknown character '%c'\n", c);
                goto waiting;
        }
entering:
        /* we are in the middle of entering a number */
        c = getchar();
        switch (c) {
                /* if we see a digit, add it to number on top of the stack */
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
                assert(has(values, 1));
                Um_word w = pop(values);
                push(values, 10 * w + c - '0');
                goto entering;

                // if we see anything else, behave as if waiting
        default:
                goto waiting_with_character;
        }
}

int main() 
{
        Seq_T values = Seq_new(10);
        run(values);
        Seq_free(&values);
        return EXIT_SUCCESS;
}

static bool has(Seq_T sequence, int n)
{
        if (Seq_length(sequence) >= n)
                return true;
        else {
                printf("Stack underflow---expected at least %d element%s\n",
                       n,
                       n == 1 ? "" : "s");
                return false;
        }
}
