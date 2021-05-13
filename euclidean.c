#include <gmp.h>
#include "euclidean.h"

void extendedEuclidean( mpz_t gcd, mpz_t a, mpz_t b, 
                        mpz_t x, mpz_t y )
{
    mpz_t mod, subRes, mulRes, divRes, remainder;
    mpz_t x1, y1; /* Store the result of the recursive x and y */

    /* Initialising x1 and y1 */
    mpz_init(mod); mpz_set_ui(mod, 0);
    mpz_init(subRes); mpz_set_ui(subRes, 0);
    mpz_init(mulRes); mpz_set_ui(mulRes, 0);
    mpz_init(divRes); mpz_set_ui(divRes, 0);
    mpz_init(remainder); mpz_set_ui(remainder, 0);
    mpz_init(x1); mpz_set_ui(x1, 0);
    mpz_init(y1); mpz_set_ui(y1, 0);

    /* Base Case: a = 0 when gcd was found (gcd = b) */
    if ( mpz_cmp_d(a, 0) != 0 )
    {
        /* x1 and y1 will be updated in the recursive case */
        mpz_mod( mod, b, a );
        extendedEuclidean( gcd, mod, a, x1, y1 );
        /* In Standard C: *x = y1 - ((b/a) * x1) */
        mpz_tdiv_qr(divRes, remainder, b, a);
        mpz_mul(mulRes, divRes, x1);
        mpz_sub(x, y1, mulRes);
        /* In Standard C: *y = x1 */
        mpz_set(y, x1);
    }
    else
    {   /** According to ax + by = gcd(a,b) **/
        /** When gcd = b, a must be 0 */ 

        /* According to the equation above ... */
        mpz_set_ui(x, 0); /* x must be 0 for a = 0 */
        mpz_set_ui(y, 1); /* y must be 1 for b = gcd, because (b*y) */
        mpz_set(gcd, b);
    }
    mpz_clear(mod); mpz_clear(subRes); 
    mpz_clear(mulRes); mpz_clear(divRes); 
    mpz_clear(remainder); mpz_clear(x1); mpz_clear(y1); 
}
