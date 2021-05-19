/**
 * Program: rsa.c
 * Purpose: Handling all function related to the RSA
 */

#include <stdlib.h>
#include <string.h>
#include <gmp.h>    /* Use to compute large integer */
#include <time.h>
#include "lehmann.h"
#include "euclidean.h"
#include "rsa.h"
#include "maths.h"
#include "header.h"

/**
 * This function will call all the function 
 * responsible for RSA Encryption
 */
void Encryption( char asciiMsg[], char ciphertext[], 
                 mpz_t n, mpz_t e )
{
    int i;
    int *asciiArr, arrSize;
    mpz_t c, x;
    char cipher[STR];

    /* Initialising mpz structure */
    mpz_init(c); mpz_set_ui(c, 0);
    mpz_init(x); mpz_set_ui(x, 0);

    /* Allocating asciiArr */
    arrSize = getArraySize( asciiMsg );
    asciiArr = calloc(sizeof(int), arrSize);

    /* Parsed asciiMsg into integer array 
       to allow integer computation */
    getIntArray( asciiMsg, asciiArr );

    for ( i = 0; i < arrSize - 1; ++i ) {
        mpz_set_ui(x, asciiArr[i]);
        fastExp( c, x, e, n );

        mpz_get_str( cipher, 10, c );
        strcat( ciphertext, cipher );
        strcat( ciphertext, " " );
    }
    free(asciiArr); asciiArr = NULL;
    /* Deallocating mpz */
    mpz_clear(c); mpz_clear(x);
}

/**
 * Decrypt ciphtertext back to plaintext using d as private key
 */
void Decryption( char ciphertext[], char **plaintext,
                 mpz_t d, mpz_t n )
{
    int i;
    int *cipherArr, arrSize;
    char plain[STR];
    mpz_t m, c;

    /* Initialising mpz structure */
    mpz_init(c); mpz_set_ui(c, 0);
    mpz_init(m); mpz_set_ui(m, 0);

    /* Allocating cipherArr and plaintext */
    arrSize = getArraySize( ciphertext );
    cipherArr = calloc(sizeof(int), arrSize);

    /* Parsed asciiMsg into integer array 
       to allow integer computation */
    getIntArray( ciphertext, cipherArr );

    for ( i = 0; i < arrSize - 1; ++i ) {
        mpz_set_ui(c, cipherArr[i]);
        fastExp( m, c, d, n );
        mpz_get_str( plain, 10, m );
        strcpy( plaintext[i], plain );
    }
    free(cipherArr); cipherArr = NULL;
    /* Deallocating mpz */
    mpz_clear(m); mpz_clear(c);
} 

/**
 * Parsed each of the asciiMsg separated by ' '
 * and store them into every entry of asciiArr
 */
void getIntArray( char text[], int *arr )
{
    char str[STR], *token;
    int i;

    strcpy(str, text);

    /* Get the first token */
    token = strtok(str, " ");
    i = 0;
    while ( token != NULL ) {
        arr[i] = atoi(token);
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

/* FIXME
void randomGenerator( mpz_t result, mpz_t range, 
                      gmp_randstate_t state )
{
*/
    /* Generating random number within range */ 
/*
    mpz_add(result, result, lower);
}
*/

/**
 * Used by generateKey to get p and q
 *
 * Call random function to generate random numbers
 * and return the randomised prime numbers
 */
void generateRandomPrime( mpz_t randNum, mpz_t range,
                          gmp_randstate_t state ) 
{
    int stop = FALSE; 
 
    /* Iterate until prime is acquired */
    while ( stop == FALSE ) {
        mpz_urandomm(randNum, state, range);
        /* Primality Test */
        if ( lehmann( randNum ) == TRUE )
            stop = TRUE;
    }
}

/**
 * Generating keys value for the RSA
 *
 * Public Key: n, e
 * Private Key: d
 */
void generateKey( mpz_t e, mpz_t n, mpz_t d )
{
    mpz_t range, base;
    mpz_t p, q, fi, fiP, fiQ;
    mpz_t modInvOne, modInvTwo;
    mpz_t mulInvOne, mulInvTwo;
    mpz_t gcdRes, invOne, invTwo;
    gmp_randstate_t state;

    /* Initialising lower and upper */
    mpz_init(range); mpz_set_ui(range, 0);
    mpz_init(base); mpz_set_ui(base, 2);
    mpz_init(p); mpz_set_ui(p, 0);
    mpz_init(q); mpz_set_ui(q, 0);
    mpz_init(fi); mpz_set_ui(fi, 0);
    mpz_init(fiP); mpz_set_ui(fiP, 0);
    mpz_init(fiQ); mpz_set_ui(fiQ, 0);
    mpz_init(invOne); mpz_set_ui(invOne, 0);
    mpz_init(invTwo); mpz_set_ui(invTwo, 0);
    mpz_init(modInvOne); mpz_set_ui(modInvOne, 0);
    mpz_init(modInvTwo); mpz_set_ui(modInvTwo, 0);
    mpz_init(mulInvOne); mpz_set_ui(mulInvOne, 0);
    mpz_init(mulInvTwo); mpz_set_ui(mulInvTwo, 0);
    mpz_init(gcdRes); mpz_set_ui(gcdRes, 0);

    /* Taking key of bits between 24 */
    mpz_pow_ui(range, base, 24);

    /* Initialising random seed */
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, time(NULL));

    /* Generates prime for p and q */
    generateRandomPrime( p, range, state );
    generateRandomPrime( q, range, state );

    /* Computing n */
    mpz_mul(n, p, q);

    /* Computing fi */
    mpz_sub_ui(fiP, p, 1); mpz_sub_ui(fiQ, q, 1);
    mpz_mul(fi, fiP, fiQ);

    /* Finding e */
    findE(e, fi);

    /* Finding d */
    mpz_gcdext( gcdRes, invOne, invTwo, e, fi );

    if ( mpz_cmp_ui( invOne, 0 ) > 0 ) {
        mpz_mul(mulInvOne, invOne, e);
        mpz_mod(modInvOne, mulInvOne, fi);
        /* Accept if the mod result is 1 */
        if ( mpz_cmp_ui( modInvOne, 1 ) == 0 )
            mpz_set(d, invOne);
        else {
            mpz_mul(mulInvOne, invOne, fi);
            mpz_mod(modInvOne, mulInvOne, fi);
            /* Accept the second possibilities */
            if ( mpz_cmp_ui( modInvOne, 1 ) == 0 )
                mpz_set(d, invOne);
            else {
                /* Add with fi if negative */
                if ( mpz_cmp_ui( invTwo, 0 ) < 0 )
                    mpz_add(d, invTwo, fi );
                else /* Otherwise just assign */
                    mpz_set(d, invTwo);
            }
        }
    }
    else if ( mpz_cmp_ui( invTwo, 0 ) > 0 ) {
        mpz_mul(mulInvTwo, invTwo, e);
        mpz_mod(modInvTwo, mulInvTwo, fi);
        /* Accept if the mod result is 1 */
        if ( mpz_cmp_ui( modInvTwo, 1 ) == 0 )
            mpz_set(d, invTwo);
        else {
            mpz_mul(mulInvTwo, invTwo, fi);
            mpz_mod(modInvTwo, mulInvTwo, fi);
            /* Accept the second possibilities */
            if ( mpz_cmp_ui( modInvTwo, 1 ) == 0 )
                mpz_set(d, invTwo);
            else {
                /* Add with fi if negative */
                if ( mpz_cmp_ui( invOne, 0 ) < 0 )
                    mpz_add(d, invOne, fi );
                else /* Otherwise just assign */
                    mpz_set(d, invOne);
            }
        }
    }
 
    /* Deallocating the structure */
    mpz_clear(range); 
    mpz_clear(base); mpz_clear(p);
    mpz_clear(q); mpz_clear(fi);
    mpz_clear(fiP); mpz_clear(fiQ);
    mpz_clear(invOne); mpz_clear(invTwo);
    mpz_clear(gcdRes); mpz_clear(modInvOne); 
    mpz_clear(modInvTwo); gmp_randclear(state);
    mpz_clear(mulInvOne); mpz_clear(mulInvTwo); 
}

/**
 * Find the public exponent (e) 
 * e = { 1, 2, ..., fi-1 } such that 
 * gcd (e, fi) = 1
 */
void findE( mpz_t e, mpz_t fi )
{
    mpz_t i, gcdRes;
    int stop = FALSE;

    mpz_init(gcdRes); mpz_set_ui(gcdRes, 0);

    /*
     * i is not set to 1 as e = 1 is 
     * cryptographically unsafe
     */
    mpz_init(i); mpz_set_ui(i, 2);

    /* In Standard C: i < fi */
    while ( mpz_cmp(i, fi) < 0 && stop == FALSE ) {
        /* Setting e = i */
        mpz_set(e, i);
        mpz_gcd( gcdRes, e, fi );
        /* In Standard C: gcdRes == 1 */
        if ( mpz_cmp_ui(gcdRes, 1) == 0 )
            stop = TRUE;
        mpz_add_ui(i, i, 1);
    }
}

int checkPrime ( mpz_t prime ) 
{
    mpz_t i; mpz_t m, remainder, mod; 
    int isPrime = TRUE;

    /* Allocation of mpz struct */
    mpz_init(i); mpz_set_ui(i, 2);
    mpz_init(m); mpz_set_ui(m, 0);
    mpz_init(remainder); mpz_set_ui(remainder, 0);
    mpz_init(mod); mpz_set_ui(mod, 0);

    /* m = prime / 2 */
    mpz_tdiv_qr_ui(m, remainder, prime, 2);

    while ( mpz_cmp(i, m) <= 0 && isPrime == TRUE ) {
        mpz_mod( mod, prime, i );
        if ( mpz_cmp_ui( mod, 0 ) == 0 )
            isPrime = FALSE;
        mpz_add_ui(i, i, 1); /* ++i */
    }

    mpz_clear(i); mpz_clear(m);
    mpz_clear(remainder); mpz_clear(mod);
    return isPrime;
}
