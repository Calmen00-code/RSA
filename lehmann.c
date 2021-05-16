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
#include <math.h>
#include "maths.h"
#include "lehmann.h"
#include "header.h"

int lehmann( mpz_t prime )
{
    int i;
    int isPrime = TRUE;
    double probPrime = 0.0;
    mpz_t res, a, e, base, mod, tmp, remainder;
    gmp_randstate_t state;

    /* Allocating mpz struct */
    mpz_init(res); mpz_set_ui(res, 0);
    mpz_init(a); mpz_set_ui(a, 0);
    mpz_init(e); mpz_set_ui(e, 0);
    mpz_init(base); mpz_set_ui(base, 2);
    mpz_init(mod); mpz_set_ui(mod, 0);
    mpz_init(remainder); mpz_set_ui(remainder, 0);
    mpz_init(tmp); mpz_set_ui(tmp, 0);

    /* Initialising the time seed for Random */
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));

    /* Computing range of mod */
    mpz_pow_ui(mod, base, 1025);

    /* Computing e */
    mpz_sub_ui(e, prime, 1);            /* e = prime - 1*/
    mpz_tdiv_qr_ui(e, remainder, e, 2); /* e = e / 2 */
    /* printf("e: %lf\n", e); printf("\n"); */

    /* First randomised of a */
    mpz_urandomm(a, state, prime);
    mpz_add_ui(a, a, 2);
    /* printf("a: "); mpz_out_str(stdout, 10, a); printf("\n"); */

    i = 0;
    while ( i < NREPEATS_LEHMANN && isPrime == TRUE ) {
        mpz_powm(res, a, e, mod);           /* Compute res = a^e */
        /* printf("a^e: "); mpz_out_str(stdout, 10, res); printf("\n"); */
        mpz_mod(res, res, prime);           /* Computer res mod prime */
        /* printf("res: "); mpz_out_str(stdout, 10, res); printf("\n"); */

        mpz_sub_ui(tmp, prime, 1);
        if ( mpz_cmp_ui(res, 1) == 0 ) {
            mpz_urandomm(a, state, prime);
            if ( i == 0 )
                probPrime = 0.5;
            /* mpz_add_ui(a, a, 2); */
            /* printf("a: "); mpz_out_str(stdout, 10, a); printf("\n"); */
            ++i;
        } else if ( mpz_cmp(res, tmp) == 0 ) {
            mpz_urandomm(a, state, prime);
            if ( i > 0 )
                probPrime = 1 - (1/pow(2,i));
            ++i;
        } else
            isPrime = FALSE;
    }
    if ( probPrime > 0.5 )
        isPrime = TRUE;
    return isPrime;
}
