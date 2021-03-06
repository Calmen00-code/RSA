#ifndef MATH_OPERATION
#define MATH_OPERATION

#include <gmp.h> /* For large numbers computation */

void extendedEuclidean( mpz_t gcd, mpz_t a, mpz_t b, mpz_t x, mpz_t y );

#endif
