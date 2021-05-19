/**
 * Program: conversion.c
 * Purpose: Handling all conversion from a type to another
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

/**
 * Taking the plaintext in ascii and convert the 
 * ascii value which represented each ascii character
 */
char toChar( char plaintext[], int end, int nSteps )
{
    char tmp[STR] = "";
    char cVal;
    int i, iVal, start;

    start = end - nSteps;
    for ( i = 0; i <= nSteps; ++i ) {
        tmp[i] = plaintext[start];
        ++start;
    }
    iVal = atoi(tmp);
    cVal = (char)iVal;
    return cVal;
}

/**
 * Convertion decimal in string into hexa in text
 */
void decToHex( char dectext[], char hexatext[] )
{
    int i, dec;
    char hex[STR] = "";

    for ( i = 0; dectext[i] != '\0'; ++i ) {
        dec = atoi( dectext[i] );
        sprintf( hex, "%X", dec );
        strcpy( hexatext, hex );
    }
}
