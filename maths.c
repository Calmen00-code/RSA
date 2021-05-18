/**
 * Program: maths.c
 * Purpose: Handling the mathematical operation in this program
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "maths.h"
#include "header.h"

int power( int num, int exp )
{
    int i;
    int total = 1;

    if ( exp == 0 )
        total = 1;
    else
    {
        for ( i = 0; i < exp; ++i )
            total *= num;
    }
    return total;
}

/**
 * Converting n to binary array
 */
int decToBin( int *arr, int n )
{
    int i, size, j;
    int *a;

    a = calloc(sizeof(int), n);
    setArray( a, n, -1 );

    for ( i = 0; n > 0; i++ ) {
        a[i] = n % 2;
        n /= 2;
    }
    size = i;
    --i;
    for ( j = 0; j < size; ++j ) {
        arr[j] = a[i];
        --i;
    }
    free(a); a = NULL;
    return size;
}

/**
 * Performs fast modular exponentiation
 */
void fastExp( mpz_t res, mpz_t x, mpz_t h, mpz_t n )
{
    int *bin, i, size;
    mpz_t y;

    /* Initialising y */
    mpz_init(y); mpz_set_ui(y, 0);

    /* Binary is at most the value of h */
    bin = calloc(sizeof(int), 1000);
    setArray( bin, 1000, -1 );

    size = decToBin( bin, mpz_get_ui(h) );
    mpz_set(y, x);

    for ( i = 1; i < size; ++i ) {
        mpz_pow_ui(y, y, 2);
        mpz_mod(y, y, n);
        if ( bin[i] == 1 ) {
            mpz_mul(y, y, x);
            mpz_mod(y, y, n);
        }
    }
    mpz_set(res, y);

    mpz_clear(y);
    free(bin); bin = NULL;
}

void setArray( int *arr, int size, int val )
{
    int i;
    for ( i = 0; i < size; ++i )
        arr[i] = val;
}

/* FIXME: Remove after testing */
void displayArr( int *arr, int size )
{
    int i;
    for ( i = 0; i < size; ++i ) {
        if ( arr[i] != -1 )
            printf("%d", arr[i]);
    }
    printf("\n");
}
