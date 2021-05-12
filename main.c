/**
 * Program: main.c
 * Purpose: Driver for the RSA Algorithm
 */

#include <stdio.h>
#include "header.h"
#include "lehmann.h"

int main(int argc, char* argv[])
{
    int i;
    int status;
    for ( i = 1; i <= 101; ++i ) {
        status = lehmann( i );
        if ( status == TRUE )
            printf("%d: TRUE\n", i);
        else
            printf("%d: FALSE\n", i);
    }
    
    return 0;
}
