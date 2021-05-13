/**
 * Program: rsa.c
 * Purpose: Handling all function related to the RSA
 */

#include <gmp.h> /* For large number computation */

void random( mpz_t result, mpz_t lower, mpz_t upper )
{
    mpz_t randUpper, randLower;
    gmp_randstate_t state;

    /* Initialising state for random */
    gmp_randinit_default(state);    

    /* Generating mpz random number */
    mpz_urandomm(randLower, state, lower);
    mpz_urandomm(randUpper, state, upper);

    /* Performs substraction so we can randomised
       value in the range of >= lower and <= upper */
    mpz_sub(result, randUpper, randLower);
}
