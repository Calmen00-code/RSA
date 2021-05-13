#ifndef RSA_H
#define RSA_H

#include <gmp.h>

void random( mpz_t result, mpz_t lower, mpz_t upper, gmp_randstate_t state );

#endif
