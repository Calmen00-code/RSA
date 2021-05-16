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

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include "maths.h"
#include "lehmann.h"
#include "header.h"

        mpz_urandomm(a, state, prime);      /* Randomised a */
        // FIXME mpz_out_str(stdout, 10, a); printf("\n");
        mpz_powm(powVal, a, exp, mod);      /* Raise a to exp */
        mpz_mod(r, powVal, prime);          /* r = powVal % prime number */

        /* DEFINITELY not a prime when this IF fails */
        mpz_sub_ui(tmp, prime, 1);
        if ( mpz_cmp_d(r, 1) == 0 || mpz_cmp(r, tmp) == 0 ) {
            if ( i == 0 )
                prob_prime = 0.5;
            else
                prob_prime = 1.0 - (1.0 / (double)power(2,i));
        } else
            is_prime = FALSE;

int lehmann( mpz_t prime, gmp_randstate_t state )
{
    int i;
    int isPrime = TRUE;
    mpz_t p, res, e;

    p = mpz_get_ui( prime );
    e = (p - 1) / 2;

    i = 0;
    while ( i < NREPEATS_LEHMANN && isPrime == TRUE ) {
        
        ++i;
    }
    printf("\n");

    if ( prob_prime > 0.5 )
        is_prime = TRUE;

    return is_prime;
}
