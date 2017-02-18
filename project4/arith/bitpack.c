/*
 *     Filename: bitpack.c
 *     Partner 1 name: Hongyan Wang       Login: hwang10
 *     Partner 2 name: Ryan Schneiderman  Login: rschne01 
 *     Date: March 10th, 2016
 *     Assignment: hw4
 *
 *     Summary: this file contains implementations of Bitpack interface. 
 *              Width-test functions: Bitpack_fitsu and Bitpack_fitss will test
 *                                   if an integer can be represented in k bits.
 *              Field-extraction functions: Bitpack_getu and Bitpack_gets will 
 *                                          extract values from a word. 
 *              Field-update functions: Bitpack_newu and Bitpack_news will 
 *                                      change a field in a word. Note that 
 *                                      these functions not mutate the original
 *                                      word but instead returns a new one. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <except.h>
#include <stdint.h>
#include "bitpack.h"
#include <inttypes.h>

/* Assume the width is always less than or equal to 64.*/
#define MAX_WIDTH 64

/* The exception Bitpack Overflow is raised in the field-update functions if 
 * the given value can not fit in given bits. */
Except_T Bitpack_Overflow = { "Overflow packing bits" };


/* Helper function for shift uint64_t integer to left. */
static inline uint64_t shift_leftu(uint64_t n, unsigned width)
{
        /* If we shift an integer to left 64 bits, we should get 0. */
    if(width == MAX_WIDTH) return 0;

    uint64_t result = n << width;
    return result;
} 

/* Helper function for shift uint64_t integer to right. */
static inline uint64_t shift_rightu(uint64_t n, unsigned width)
{
        /* If we shift an integer to right 64 bits, we should get 0. */
    if(width == MAX_WIDTH) return 0;

    uint64_t result = n >> width;
    return result;
} 

/* Helper function for shift int64_t integer to left. */
static inline int64_t shift_lefts(int64_t n, unsigned width)
{
    /* If we shift an integer to left 64 bits, we should get 0. */
    if(width == MAX_WIDTH) return 0;

    int64_t result = n << width;
    return result;
} 


/* Test whether unsigned integer n can be represented in width bits. 
 * input: uint64_t integer n, width is the number of bits. 
 * output: return true if width bits can represent uint64_t n. Otherwise 
 *         false.*/
bool Bitpack_fitsu(uint64_t n, unsigned width) 
{
        /* If the number of bits is greater than or equal to 64, it should 
         * always return true.*/
        if (width >= MAX_WIDTH) return true;
        
        /* unsigned integer range of width bits should be from 0 to (2 ** width 
         * - 1)*/
        uint64_t max_val = shift_leftu(1, width);
        return (n < max_val);
}

/* Test whether signed integer n can be represented in width bits. 
 * input: int64_t integer n, width is the number of bits. 
 * output: return true if width bits can represent int64_t n. Otherwise 
 *         false.*/
bool Bitpack_fitss(int64_t n, unsigned width) 
{
        /* If we have more than 64 bits, it should always return true.*/
        if (width >= MAX_WIDTH) return true;

        /* If we have only one bit, it should always return false.*/
        if (width == 0)                 return false;

        /* use the Bitpack_fitsu interface to check whether width bits can 
         * represent n. */
        bool flag = false;
        if (n >= 0){
                flag = Bitpack_fitsu(2 * n, width);
        } else {
                flag = Bitpack_fitsu((~(n-1)) * 2 - 1, width);
        }

        return flag;
}

/* Extract unsigned value from a word. 
 * input: uint64_t integer word, field width, field lsb. 
 * output: unsigned field value at specific position. */
uint64_t Bitpack_getu(uint64_t word, unsigned width, unsigned lsb) 
{        
        /* It should be a checked run-time error if width does not satisfy 
         * 0 ≤ w ≤ 64.
         * It should be a checked run-time error to width and lsb do not 
         * satisfy w + lsb ≤ 64.*/
        assert(width <= MAX_WIDTH);
        assert((width + lsb) <= MAX_WIDTH);

        /* Fields of width zero are defined to contain the value zero. */
        if (width == 0) return 0;

        /* Create mask for extracting field. */
        uint64_t mask = shift_leftu(1, width) - 1;
        mask = shift_leftu(mask, lsb);

        uint64_t result = (word & mask);
        result = shift_rightu(result, lsb);

        return result;
}

/* Extract signed value from a word. 
 * input: uint64_t integer word, field width, field lsb. 
 * output: signed field value at specific position. */
int64_t Bitpack_gets(uint64_t word, unsigned width, unsigned lsb) {

        /* It should be a checked run-time error if width does not satisfy 
         * 0 ≤ w ≤ 64.
         * It should be a checked run-time error to width and lsb do not 
         * satisfy w + lsb ≤ 64.*/
        assert(width <= MAX_WIDTH);
        assert((width + lsb) <= MAX_WIDTH);

        /* Fields of width zero are defined to contain the value zero. */
        if (width == 0) return 0;

        int64_t result;

        /* Use the Bitpack_getu interface to get the unsigned field value. */
        uint64_t u_result = Bitpack_getu(word, width, lsb);
        uint64_t upper_bound = shift_leftu(1, width - 1) - 1;

        /* Check whether the field value is negative. If it's negative, 
         * transfer it to negative values. */
        if (u_result <= upper_bound) {
                result = (int64_t)u_result;
        } else {
                result = (int64_t)(u_result - shift_leftu(1,width));
        }

        return result;
}

/* Change a unsigned field in a word, return the new word. 
 * Input: uint64_t word, field width, field lsb and new unsigned field value.
 * Output: a new word  which is identical to the input word, except that the 
 * field of width with least significant bit at lsb will have been replaced by 
 * a width-bit representation of unsigned value. */
uint64_t Bitpack_newu(uint64_t word, unsigned width, unsigned lsb, 
                                                              uint64_t value) 
{
        /* It should be a checked run-time error if width does not satisfy 
         * 0 ≤ w ≤ 64.
         * It should be a checked run-time error to width and lsb do not 
         * satisfy w + lsb ≤ 64.*/
        assert(width <= MAX_WIDTH);
        assert((width + lsb) <= MAX_WIDTH);

        /* If given unsigned value does not fit in width signed bits, it must 
         * raise the exception Bitpack Overflow. */
        if (Bitpack_fitsu(value, width) != true) {
                RAISE(Bitpack_Overflow);
                assert(0);
        }

        /* Create the mask. */
        uint64_t left_field = shift_leftu(1, MAX_WIDTH - width - lsb) - 1;;
        left_field = shift_leftu(left_field, width + lsb);
        uint64_t right_field = shift_leftu(1, lsb) - 1;
        uint64_t mask = left_field + right_field;
        
        /* Use mask to get the new word. */
        uint64_t result = (word & mask) | shift_leftu(value, lsb);

        return result;                          
}

/* Change a signed field in a word, return the new word. 
 * Input: uint64_t word, field width, field lsb and new signed field value.
 * Output: a new word  which is identical to the input word, except that the 
 * field of width with least significant bit at lsb will have been replaced by 
 * a width-bit representation of signed value. */
uint64_t Bitpack_news(uint64_t word, unsigned width, unsigned lsb, 
                                                               int64_t value) 
{
        /* It should be a checked run-time error if width does not satisfy 
         * 0 ≤ w ≤ 64.
         * It should be a checked run-time error to width and lsb do not 
         * satisfy w + lsb ≤ 64.*/
        assert(width <= 64);
        assert((width + lsb) <= MAX_WIDTH);
        
        /* If given unsigned value does not fit in width signed bits, it must 
         * raise the exception Bitpack Overflow. */
        if (Bitpack_fitss(value, width) != true) {
                RAISE(Bitpack_Overflow);
                assert(0);
        }

        /* Create the mask. */
        uint64_t left_field = shift_leftu(1, MAX_WIDTH - width - lsb) - 1;
        left_field = shift_leftu(left_field, width + lsb);
        uint64_t right_field = shift_leftu(1, lsb) - 1;
        uint64_t mask = left_field + right_field;

        /* transfer the signed value to unsigned value. */
        uint64_t value_field = value;
        value_field = shift_leftu(value_field, MAX_WIDTH - width);
        value_field = shift_rightu(value_field, MAX_WIDTH - width - lsb);
        
        /*replace the field, get the new word. */
        uint64_t result = (word & mask);
        result = (result | value_field);
        return result;
}