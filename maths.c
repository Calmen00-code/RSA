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
void fastExp( int *res, int x, int h, int n )
{
    int *bin, i, y, size;

    /* Binary is at most the value of h */
    bin = calloc(sizeof(int), h);
    setArray( bin, h, -1 );

    size = decToBin( bin, h );
    y = x;

    for ( i = 1; i < size; ++i ) {
        y = ((long long int)pow(y, 2)) % n;
        if ( bin[i] == 1 )
            y = (y * x) % n;
    }
    *res = y;
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
