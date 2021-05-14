/**
 * Program: maths.c
 * Purpose: Handling the mathematical operation in this program
 */

#include <stdio.h>
#include "maths.h"

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

    a = calloc(sizeof(int*), n);

    for ( i = 0; n > 0; i++) {
        a[i] = n % 2;
        n = n / 2;
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
    char binStr[STR];

    /* Binary is at most the value of h */
    bin = calloc(sizeof(int*), h);
    memset(bin, -1, sizeof(bin));

    size = decToBin( bin, h );
    y = x;

    for ( i = 1; i < size; ++i ) {
        y = ((int)pow(y, 2)) % n;
        if ( bin[i] == 1 )
            y = (y * x) % n;
    }
    *res = y;
    free(bin); bin = NULL;
}
