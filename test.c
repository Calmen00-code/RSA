#include <stdio.h>
#include <gmp.h>
#include "lehmann.h"
#include "header.h"
#include "rsa.h"
#include "euclidean.h"

int main()
{
    mpz_t a, b, x, y, gcd;

    mpz_init(x); mpz_set_ui(x, 0);
    mpz_init(y); mpz_set_ui(y, 0);
    mpz_init(gcd); mpz_set_ui(gcd, 0);

    mpz_init(a); mpz_set_ui(a, 3);
    mpz_init(b); mpz_set_ui(b, 20);

    extendedEuclidean( gcd, a, b, x, y );
    printf("gcd: ");
    mpz_out_str(stdout, 10, gcd);
    printf("\n");

    printf("x = ");
    mpz_out_str(stdout, 10, x);
    printf("\n"); 
    
    printf("y = ");
    mpz_out_str(stdout, 10, y);
    printf("\n"); 

    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(x);
    mpz_clear(y);
    mpz_clear(gcd);
    return 0;
}


/*
------------- Testing for Random number within a range ---------------------
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

/*
--------------------- Testing for lehmann algorithm --------------------
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
*/
