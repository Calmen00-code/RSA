#include <stdio.h>
#include <gmp.h>
#include "lehmann.h"
#include "header.h"
#include "rsa.h"

int main()
{

/*
    int i;
    mpz_t lower, upper, result;
    gmp_randstate_t state;

    mpz_init(lower); mpz_set_ui(lower, 200);
    mpz_init(upper); mpz_set_ui(upper, 500);
    mpz_init(result); mpz_set_ui(result, 0);
*/
 
    /* Initialising state for random */
/*
    gmp_randinit_default(state);    

    for ( i = 0; i < 10; ++i ) {
        random( result, lower, upper, state );
        mpz_out_str( stdout, 10, result );
        printf("\n");
    }
*/

    int j;
    mpz_t rop;

    mpz_init(rop);
    mpz_set_ui(rop, 0);

    for ( j = 1; j <= 101; ++j ) {
        mpz_set_ui(rop, j);
        if ( lehmann( rop ) == TRUE )
            printf("%d\n", j);
    }
    mpz_clear(rop);
    return 0;
}
