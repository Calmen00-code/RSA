/**
 * Program: file.c
 * Purpose: Reading the content of the file and store into 2-D Array
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"
#include "file.h"

/**
 * Reading the filename into content
 */
char** read( char filename[] )
{
    FILE *readPtr = NULL;
    char **content = NULL;
    int numLine = 0;
    int i;
    char str[STR] = "";

    readPtr = fopen( filename, "r" );
    if ( readPtr == NULL ) {
        perror("Error while reading file");
        exit(1);
    } else {        
        numLine = readFileSize( filename );
        content = calloc(numLine, sizeof(char*));

        for ( i = 0; i < numLine; ++i ) {
            content[i] = calloc(STR, sizeof(char));
            fgets(str, STR, readPtr);
            strcpy(content[i], str);
        }
        fclose(readPtr); readPtr = NULL;
    }
    return content;
}

/**
 * Read the number of lines in a file
 */
int readFileSize( char filename[] )
{
    FILE *readPtr = NULL;
    int line = 0;
    char str[STR];

    readPtr = fopen(filename, "r");
    if ( readPtr == NULL ) {
        perror("Error while reading file");
    }
    else {
        /* Reading stops when the pointer reaches the end of file */
        while ( fgets( str, STR, readPtr ) != NULL )
            ++line;
        fclose(readPtr); readPtr = NULL;
    }
    return line;
}

/**
 * Write the text outcome into the file
 */
void writeToFile( char text[], char filename[] )
{
    int i;
    FILE *writePtr = NULL;

    writePtr = fopen(filename, "w");
    if ( writePtr == NULL ) {
        perror("Error while writing to file");
    } else {
        for ( i = 0; text[i] != '\0'; ++i ) {
            printf("%c", text[i]);
            fprintf( writePtr, "%c", text[i] );
        }
        fclose(writePtr); writePtr = NULL;
    }
}
