/**
 * Program: rsa.c
 * Purpose: Handling all function related to the RSA
 */

#include <stdio.h>
#include <gmp.h> /* For large number computation */
#include "rsa.h"

void random( mpz_t result, mpz_t lower, 
             mpz_t upper, gmp_randstate_t state )
{
    /* mpz_t randNum, range; */
    mpz_t range;

    /* Initialising randUpper and randLower */
    /* mpz_init(randNum); mpz_set_ui(randNum, 0); */
    mpz_init(range); mpz_set_ui(range, 0);

    /* Computing range for random number */
    mpz_sub(range, upper, lower);   /* range = upper - lower */
    mpz_add_ui(range, range, 1);    /* range = range + 1 */

    /* Generating random number within range */ 
    mpz_urandomm(result, state, range);
    mpz_add(result, result, lower);
}
