/**
 * Program: lehman.c
 *
 * Purpose: Implementation of the Lehmann's Primality Test 
 *          that will check if a prime is larger than 
 *          the specified natural number
 * 
 * External 
 * Libary  : GMP library from GNU was used here to 
 *           handle large bits of integer when computing
 *           large integer value for 'a'. 
 *           Please refer to the documentation provided in 
 *           report on how to use each function of gmp
 */

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include "maths.h"
#include "lehmann.h"
#include "header.h"

int lehmann( int prime_number )
{
    int i;
    long int exp;
    double prob_prime = 0.0;
    int is_prime = TRUE;
    mpz_t powVal, base, a, p, r;
    gmp_randstate_t state;
    
    /* Initialising mpz data structure */
    mpz_init(powVal); mpz_set_ui(powVal, 0);
    mpz_init(base); mpz_set_ui(base, 0);
    mpz_init(a); mpz_set_ui(a, 0);
    mpz_init(r); mpz_set_ui(r, 0);
    mpz_init(p); mpz_set_ui(p, prime_number);

    /* Initialising the time seed for Random */
    gmp_randinit_default(state);

    exp = (prime_number - 1) / 2;
    i = 0;
    while ( i < NREPEATS_LEHMANN && is_prime == TRUE ) {
        mpz_urandomm(a, state, p);  /* Randomised a */
        mpz_pow_ui(powVal, a, exp); /* Raise a to exp */
        mpz_mod(r, powVal, p);      /* r = powVal % prime number */

        /* DEFINITELY not a prime when this IF fails */
        if ( mpz_cmp_d(r, 1) == 0 || mpz_cmp_d(r, prime_number - 1) == 0 ) {
            if ( i == 0 )
                prob_prime = 0.5;
            else
                prob_prime = 1.0 - (1.0 / (double)power(2,i));
        } else
            is_prime = FALSE;
        ++i;
    }

    if ( prob_prime > 0.5 )
        is_prime = TRUE;

    mpz_clear(powVal); mpz_clear(base); 
    mpz_clear(a); mpz_clear(p); mpz_clear(r);

    return is_prime;
}
