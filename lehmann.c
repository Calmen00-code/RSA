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

int lehmann( mpz_t prime )
{
    int i;
    int is_prime = TRUE;
    mpz_t powVal, base, a, r, exp, tmp, mod, remainder;
    gmp_randstate_t state;
    
    /* Initialising mpz data structure */
    mpz_init(powVal); mpz_set_ui(powVal, 0);
    mpz_init(base); mpz_set_ui(base, 0);
    mpz_init(a); mpz_set_ui(a, 0);
    mpz_init(r); mpz_set_ui(r, 0);
    mpz_init(exp); mpz_set_ui(exp, 0);
    mpz_init(tmp); mpz_set_ui(tmp, 0);
    mpz_init(remainder); mpz_set_ui(remainder, 0);
    mpz_init(mod); mpz_set_ui(mod, 0);

    /* Initialising the time seed for Random */
    gmp_randinit_default(state);

    /* tmp = prime - 1 */
    mpz_sub_ui(tmp, prime, 1);
    /* exp = tmp / 2 */
    mpz_tdiv_qr_ui(exp, remainder, tmp, 2);

    mpz_urandomm(a, state, prime);          /* Randomised a */

    i = 0;
    while ( i < NREPEATS_LEHMANN && is_prime == TRUE ) {
        mpz_pow_ui(powVal, a, mpz_get_ui(exp)); /* Raise a to exp */
        mpz_mod(r, powVal, prime);              /* r = powVal % prime number */

        mpz_mod(mod, r, prime);
        if ( mpz_cmp_d(mod, 1) == 0 || mpz_cmp(mod, tmp) == 0 ) {
            mpz_urandomm(a, state, prime);          /* Randomised a */
            ++i;
        } else
            is_prime = FALSE;
    }

    /* Deallocating the structure */
    mpz_clear(powVal); mpz_clear(base); 
    mpz_clear(a); mpz_clear(r);
    mpz_clear(exp); mpz_clear(tmp);
    mpz_clear(remainder); gmp_randclear(state);

    return is_prime;
}
