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
#include "rsa.h"
#include "conversion.h"

/**
 * Check if the current character of 
 * content has a pairing partner
 */
int hasPair( char content[], int j )
{
    int pair = FALSE;

    /* Standard keyboard character in ASCII */
    if ( content[j+1] >= 32 &&
         content[j+1] <= 126 ) {
        pair = TRUE;
    }
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
    int *cipherArr, arrSize, size;
    char **content;
    char asciiStr[STR] = "", asciiMsg[STR] = "", hexacipher[STR] = "";
    char ciphertext[STR] = "", **plaintext;
    int ascii;
    mpz_t n, e, d;

    if ( argc != 2 ) {
        printf("To run the program,\n");
        printf("\t  ./rsa [filename.txt]\n");
    } else {
        mpz_init(n); mpz_set_ui(n, 0);
        mpz_init(e); mpz_set_ui(e, 0);
        mpz_init(d); mpz_set_ui(d, 0);

        size = readFileSize( argv[1] );
        content = read( argv[1] );
 
        for ( i = 0; i < size; ++i ) {
            for ( j = 0; content[i][j] != '\0'; ++j ) {
                /* No padding required */
                if ( hasPair( content[i], j ) == TRUE ) {
                    /* Iteration fixed at 2 times (2 ASCII chars is a pair) */
                    for ( k = 0; k < CHAR_GAP; ++k ) {
                        ascii = (int)content[i][j];
                        asciiWrite( asciiStr, ascii );
                        strcat( asciiMsg, asciiStr );
                        ++j;  /* Increment j to move to the next character */
                    }
                    --j; /* revert j by 1 as it is being added 1 in 
                            addition to stop the loop above */
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
        generateKey( e, n, d );
        printf("e: ");
        mpz_out_str(stdout, 10, e);
        printf("\n");
        printf("n: ");
        mpz_out_str(stdout, 10, n);
        printf("\n");
        printf("d: ");
        mpz_out_str(stdout, 10, d);
        printf("\n\n");

        /**** ENCRYPTION ****/
        Encryption( asciiMsg, ciphertext, n, e );    /* Public Key = n, e */
        arrSize = getArraySize( ciphertext );
        cipherArr = calloc(sizeof(int), arrSize);
        getIntArray( ciphertext, cipherArr );
        decToHex( cipherArr, arrSize, hexacipher );
        writeToFile( hexacipher, "ciphertext.txt" );
        printf("Encryption Result: ciphertext.txt\n");

        /***** DECRYPTION *****/
        plaintext = calloc(sizeof(char*), arrSize);
        for ( i = 0; i < arrSize; ++i )
            plaintext[i] = calloc(sizeof(char), STR);
        Decryption( ciphertext, plaintext, d, n );

        char tmpStr[STR] = "";
        for ( i = 0; i < arrSize; ++i ) {
            for ( j = 0; plaintext[i][j] != '\0'; ++j ) {
                /* Do padding if length of ascii string is not
                   equivalent to 2 pairs of character */
                if ( strlen(plaintext[i]) < 6 ) {
                    strcpy( tmpStr, plaintext[i] );
                    sprintf( plaintext[i], "0%s", tmpStr );
                }
            }
        }

        char charStr[STR] = "", convert[STR] = "";
        char cVal;
        int count = 1;
        for ( i = 0; i < arrSize; ++i ) {
            for ( j = 0; plaintext[i][j] != '\0'; ++j ) {
                if ( count == 3 ) {
                    cVal = toChar( plaintext[i], j, 2 );
                    sprintf( charStr, "%c", cVal );
                    strcat( convert, charStr );
                    count = 1;
                } else
                    ++count;
            }
        }
        printf("Decryption Result: plaintext.txt\n");
        writeToFile( convert, "plaintext.txt" );

        /* Free the dynamic allocation created from read */
        for ( i = 0; i < size; ++i ) {
            free(content[i]); 
            content[i] = NULL;
        }
        for ( i = 0; i < arrSize; ++i ) {
            free(plaintext[i]); 
            plaintext[i] = NULL;
        }
        free(plaintext); plaintext = NULL;
        free(content); content = NULL;
        free(cipherArr); cipherArr = NULL;

        /* Deallocating mpz */
        mpz_clear(n); mpz_clear(e); mpz_clear(d);
    }
    return 0;
}
