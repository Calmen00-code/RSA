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
    mpz_t randLower, randUpper;

    /* Initialising randUpper and randLower */
    mpz_init(randLower); mpz_set_ui(randLower, 0);
    mpz_init(randUpper); mpz_set_ui(randUpper, 0);

    /* Generating mpz random number */
    mpz_urandomm(randLower, state, lower);
    mpz_urandomm(randUpper, state, upper);

   /**
    * Performs substraction so we can randomised
    * value in the range of >= lower and <= upper
    */
    mpz_sub(result, randUpper, randLower);
}
