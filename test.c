#include <stdio.h>
#include <gmp.h>
#include "rsa.h"

int main()
{
    int i;
    mpz_t lower, upper, result;
    gmp_randstate_t state;

    mpz_init(lower); mpz_set_ui(lower, 1);
    mpz_init(upper); mpz_set_ui(upper, 5);
    mpz_init(result); mpz_set_ui(result, 0);
 
    /* Initialising state for random */
    gmp_randinit_default(state);    

    for ( i = 0; i < 5; ++i ) {
        random( result, lower, upper, state );
        mpz_out_str( stdout, 10, result );
        printf("\n");
    }
    return 0;
}
