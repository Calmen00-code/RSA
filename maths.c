/**
 * Program: maths.c
 * Purpose: Handling the mathematical operation in this program
 */

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
