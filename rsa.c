/**
 * Program: rsa.c
 * Purpose: Handling all function related to the RSA
 */

#include <stdio.h> /* FIXME: Remove after testing */
#include <stdlib.h>
#include <string.h>
#include <gmp.h>    /* Use to compute large integer */
#include <time.h>
#include "euclidean.h"
#include "rsa.h"
#include "lehmann.h"
#include "maths.h"
#include "header.h"

/**
 * This function will call all the function 
 * responsible for RSA Encryption
 */
void Encryption( char asciiMsg[], char ciphertext[] )
{
    int i, c;
    int *asciiArr, arrSize;
    mpz_t n, e, d;
    char cipher[STR];

    /* Initialising mpz structure */
    mpz_init(n); mpz_set_ui(n, 0);
    mpz_init(e); mpz_set_ui(e, 0);
    mpz_init(d); mpz_set_ui(d, 0);

    /* Generating public key */
    generateKey( e, n, d );

    /* Allocating asciiArr */
    arrSize = getArraySize( asciiMsg );
    asciiArr = calloc(sizeof(int), arrSize);

    /* Parsed asciiMsg into integer array 
       to allow integer computation */
    getAsciiArray( asciiMsg, asciiArr );

    for ( i = 0; i < arrSize - 1; ++i ) {
        fastExp( &c, asciiArr[i], 
            mpz_get_ui(e), mpz_get_ui(n) );
        printf("c: %d\n", c);
        sprintf( cipher, "%d", c );
        strcat( ciphertext, cipher );
        strcat( ciphertext, " " );
    }
}

/* void Decryption( char cipherText[] ) */

/**
 * Parsed each of the asciiMsg separated by ' '
 * and store them into every entry of asciiArr
 */
void getAsciiArray( char asciiMsg[], int *asciiArr )
{
    char str[STR], *token;
    int i;

    strcpy(str, asciiMsg);

    /* Get the first token */
    token = strtok(str, " ");
    i = 0;
    while ( token != NULL ) {
        asciiArr[i] = atoi(token);
        token = strtok(NULL, " ");
        ++i;
    }
} 

/**
 * Return the correct size for the asciiArr
 */
int getArraySize( char str[] )
{
    int i, size;

    size = 0;
    for ( i = 0; str[i] != '\0'; ++i ) {
        if ( str[i] == ' ' )
            ++size;
    }
    ++size;
    return size;
}

void randomGenerator( mpz_t result, mpz_t lower, 
             mpz_t upper, gmp_randstate_t state )
{
    /* mpz_t randNum, range; */
    mpz_t range;

    /* Initialising randUpper and randLower */
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
void generateRandomPrime( mpz_t randNum, mpz_t lower, 
                          mpz_t upper )
{
    int stop = FALSE; 
    gmp_randstate_t state;

    /* Initialising random seed */
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, time(NULL));
 
    /* Iterate until prime is acquired */
    while ( stop == FALSE ) {
        randomGenerator( randNum, lower, upper, state );
        /* Primality Test */
        if ( lehmann( randNum ) == TRUE )
            stop = TRUE;
    }
    gmp_randclear(state);
}

/**
 * Generating keys value for the RSA
 *
 * Public Key: n, e
 * Private Key: d
 */
void generateKey( mpz_t e, mpz_t n, mpz_t d )
{
    mpz_t lower, upper, base;
    mpz_t p, q, fi, fiP, fiQ;
    mpz_t gcdRes, invOne, invTwo;

    /* Initialising lower and upper */
    mpz_init(lower); mpz_set_ui(lower, 0);
    mpz_init(upper); mpz_set_ui(upper, 0);
    mpz_init(base); mpz_set_ui(base, 2);
    mpz_init(p); mpz_set_ui(p, 0);
    mpz_init(q); mpz_set_ui(q, 0);
    mpz_init(fi); mpz_set_ui(fi, 0);
    mpz_init(fiP); mpz_set_ui(fiP, 0);
    mpz_init(fiQ); mpz_set_ui(fiQ, 0);
    mpz_init(invOne); mpz_set_ui(invOne, 0);
    mpz_init(invTwo); mpz_set_ui(invTwo, 0);
    mpz_init(gcdRes); mpz_set_ui(gcdRes, 0);

    /* Taking key of bits between 64 to 1024 */
    mpz_pow_ui(lower, base, 64);
    mpz_pow_ui(upper, base, 1024);

    /* Generates prime for p and q */
    generateRandomPrime( p, lower, upper );
    generateRandomPrime( q, lower, upper );

    /* Computing n */
    mpz_mul(n, p, q);

    /* Computing fi */
    mpz_sub_ui(fiP, p, 1); mpz_sub_ui(fiQ, q, 1);
    mpz_mul(fi, fiP, fiQ);

    /* Finding e */
    findE(e, fi); 

    /* Finding d */
    mpz_gcdext( gcdRes, invOne, invTwo, e, fi );

    /* Assign the positive numbers to d */
    if ( mpz_cmp_ui( invOne, 0 ) > 0 )
        mpz_set(d, invOne);
    else
        mpz_set(d, invTwo);
    
    /* Deallocating the structure */
    mpz_clear(lower); mpz_clear(upper);
    mpz_clear(base); mpz_clear(p);
    mpz_clear(q); mpz_clear(fi);
    mpz_clear(fiP); mpz_clear(fiQ);
    mpz_clear(invOne); mpz_clear(invTwo);
    mpz_clear(gcdRes);
}

/**
 * Find the public exponent (e) 
 * e = { 1, 2, ..., fi-1 } such that 
 * gcd (e, fi) = 1
 */
void findE( mpz_t e, mpz_t fi )
{
    mpz_t i, gcdRes, invOne, invTwo;
    int stop = FALSE;

    mpz_init(gcdRes); mpz_set_ui(gcdRes, 0);
    mpz_init(invOne); mpz_set_ui(invOne, 0);
    mpz_init(invTwo); mpz_set_ui(invTwo, 0);

    /*
     * i is not set to 1 as e = 1 is 
     * cryptographically unsafe
     */
    mpz_init(i); mpz_set_ui(i, 2);

    /* In Standard C: i < fi */
    while ( mpz_cmp(i, fi) < 0 && stop == FALSE ) {
        /* Setting e = i */
        mpz_set(e, i);
        mpz_gcdext( gcdRes, invOne, invTwo, e, fi );
        /* In Standard C: gcdRes == 1 */
        if ( mpz_cmp_ui(gcdRes, 1) == 0 )
            stop = TRUE;
        mpz_add_ui(i, i, 1);
    }
}
