/**
 * Program: conversion.c
 * Purpose: Handling all conversion from a type to another
 */

#include <stdio.h>
#include <stdlib.h>
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
