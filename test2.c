#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include "header.h"

int getArraySize( char str[] )
{
    int i, size;

    size = 0;
    for ( i = 0; str[i] != '\0'; ++i ) {
        if ( str[i] == ' ' )
            ++size;
    }
    ++size;
    return size;
}

int main()
{
    char str[STR];
    char *token;
    int *arr, arrSize, i;

    strcpy(str, "073032 077032 032083 085068 078084 073032 079077 032070 079077 077065 065089 073065");
    arrSize = getArraySize( str );
    arr = calloc( sizeof(int*), arrSize );
    
    token = strtok(str, " ");
    i = 0;
    while ( token != NULL ) {
        arr[i] = atoi(token);
        printf("%d\n", arr[i]);
        token = strtok(NULL, " ");
        ++i;
    }

    printf("\n");
    for ( i = 0; i < arrSize; ++i )
        printf("%d ", arr[i]);
    printf("\n");
    free(arr); arr = NULL;
    return 0;
}

/*
    mpz_t e, fi, gcdVal, invOne, invTwo;
    char str[1024];

    mpz_init(e); mpz_set_ui(e, 3);
    mpz_init(fi); mpz_set_ui(fi, 153532);
    mpz_init(gcdVal); mpz_set_ui(gcdVal, 0);
    mpz_init(invOne); mpz_set_ui(invOne, 0);
    mpz_init(invTwo); mpz_set_ui(invTwo, 0);
*/
    /* strcpy(str, "4781771649437227274200346715662813109220916734356822826663428804568955772066210724078708923314063541257323472325758763137170447840544451043861130756484401625181933735897457565405406535326289883951463929824347586034330580573579204757522995494697945536872800470726616142255078344408097938426527459065018595707864667930235718292023737041194457882412866731117381646717673567460687664870549296764781512823083223037852238975848503003972016662571520084755470998007479973368347745533145993480250622275480677047047998197540734647655559652379636600135303940343206682074532437326710143463160554057441882677052685355292534349761"); */
/*
    mpz_set_str(fi, str, 10);

    mpz_gcdext(gcdVal, invOne, invTwo, e, fi);
    printf("gcd: ");
    mpz_out_str(stdout, 10, gcdVal);
    printf("\n");

    printf("invOne: ");
    mpz_out_str(stdout, 10, invOne);
    printf("\n");

    printf("invTwo: ");
    mpz_out_str(stdout, 10, invTwo);
    printf("\n");

    printf("e: ");
    mpz_out_str(stdout, 10, e);
    printf("\n");

    printf("fi: ");
    mpz_out_str(stdout, 10, fi);
    printf("\n");
*/
