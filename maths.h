#ifndef MATHS_H
#define MATHS_H

#include <gmp.h> /* For large numbers computation */

int power( int num, int exp );
void gcd( mpz_t res, mpz_t a, mpz_t b );
int decToBin( int *arr, int n );
void fastExp( int *res, int x, int h, int n );

#endif
