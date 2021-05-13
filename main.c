/**
 * Program: main.c
 * Purpose: Driver for the RSA Algorithm
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gmp.h>
#include "header.h"
#include "lehmann.h"
#include "file.h"

/**
 * Check if the current character of 
 * content has a pairing partner
 */
int hasPair( char content[], char i, char j )
{
    int pair = TRUE;

    if ( content[j+1] == '\0' )
        pair = FALSE;
    return pair;
}

/**
 * Writing the ascii so that it can be paired
 * with the next ascii value (so that it is 2 pairs) 
 */
void asciiWrite( char *asciiStr, int ascii )
{
    if ( ascii < 100 ) /* Add 0 at front */
        sprintf( asciiStr, "0%d", ascii );
    else               /* Just parsed as normal */
        sprintf( asciiStr, "%d", ascii );
}
   
int main(int argc, char* argv[])
{
    int i, j, k;
    int size;
    char **content;
    char asciiStr[STR], asciiMsg[STR];
    int ascii;

    if ( argc != 2 ) {
        printf("To run the program,\n");
        printf("\t  ./rsa [filename.txt]\n");
    } else {
        size = readFileSize( argv[1] );
        content = read( argv[1] );
        
        for ( i = 0; i < size; ++i ) {
            for ( j = 0; content[i][j] != '\0'; ++j ) {
                /* No padding required */
                if ( hasPair( content[i], i, j ) == TRUE ) {                    
                    /* Iteration fixed at 2 times (2 ASCII chars is a pair) */
                    for ( k = 0; k < CHAR_GAP; ++k ) {
                        ascii = (int)content[i][j];
                        asciiWrite( asciiStr, ascii );
                        strcat( asciiMsg, asciiStr );
                        ++j;  /* Increment j to move to the next character */
                    }
                } else { /* Padding required */
                    strcpy( asciiStr, "000" );
                    ascii = (int)content[i][j];
                    asciiWrite( asciiStr, ascii );
                    strcat( asciiMsg, asciiStr );
                }
                strcat( asciiMsg, " " ); /* Adding white spaces to asciiMsg */
                memset(asciiStr, 0, sizeof(asciiStr));  /* Empty the string */
            }
        }
        printf("%s\n", asciiMsg);

        /* Free the dynamic allocation created from read */
        free(content); content = NULL;
    }
    return 0;
}
