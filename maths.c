/**
 * Program: maths.c
 * Purpose: Handling the mathematical operation in this program
 */

#include <stdio.h>
#include "maths.h"

int power( int num, int exp )
{
    int i;
    int total = 1;

    if ( exp == 0 )
        total = 1;
    else
    {
        for ( i = 0; i < exp; ++i )
            total *= num;
    }
    return total;
}

/**
 * GCD in mpz_t
 */
void gcd( mpz_t res, mpz_t a, mpz_t b )
{
    mpz_t i;

    mpz_init(i); mpz_set_ui(i, 1);

    /* In Standard C: a != b */
    while ( mpz_cmp(a, b) != 0 ) {
        /* In Standard C: a > b */
        printf("Infinite\n");
        if ( mpz_cmp(a, b) > 0 )
            mpz_sub(a, a, b);
        else
            mpz_sub(b, b, a);
    }
    mpz_set(res, a);
    mpz_clear(i);
}

/**
 * Performs fast-modular exponentiation
 */
void fastModularExp( 
