/**
 * Program: rsa.c
 * Purpose: Handling all function related to the RSA
 */

#include <stdio.h>
#include <gmp.h> /* For large number computation */
#include "rsa.h"
#include "lehmann.h"
#include "header.h"

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

/**
 * Used by generateKey to get p and q
 *
 * Call random function to generate random numbers
 * and return the randomised prime numbers
 */
void generateRandomPrime( mpz_t randNum, 
                          mpz_t lower, mpz_t upper )
{
    gmp_randstate_t state;
    int stop = FALSE; 
    
    /* Initialising random seed */
    gmp_randinit_default(state);

    /* Iterate until prime is acquired */
    while ( stop == FALSE ) {
        random( randNum, lower, upper, state );
        if ( lehmann( randNum ) == TRUE )
            stop = TRUE;
    }
    gmp_randclear(state);
}
/*
    mpz_t lower, upper;
*/

    /* Initialising lower and upper */
/*
    mpz_init(lower); mpz_set_ui(lower, 0);
    mpz_init(upper); mpz_set_ui(upper, 0);
*/
