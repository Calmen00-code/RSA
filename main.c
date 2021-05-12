/**
 * Program: main.c
 * Purpose: Driver for the RSA Algorithm
 */

#include <stdio.h>
#include "header.h"
#include "lehmann.h"
#include "file.h"

int main(int argc, char* argv[])
{
    int i, j;
    int num;
    char **content;

    num = readFileSize( argv[1] );
    content = read( argv[1] );
    
    for ( i = 0; i < num; ++i ) {
        for ( j = 0; content[i][j] != '\0'; ++j )
            printf("%c", content[i][j]);
    }
    return 0;
}
