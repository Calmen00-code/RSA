#ifndef RSA_H
#define RSA_H

#include <gmp.h> /* For large number computation structure */

void randomGenerator( mpz_t result, mpz_t lower, mpz_t upper, gmp_randstate_t state );
void getAsciiArray( char asciiMsg[], int *asciiArr );
void Encryption( char asciiMsg[], char ciphertext[] );
int getArraySize( char str[] );
void generateRandomPrime( mpz_t randNum, mpz_t lower, mpz_t upper );
void generateKey( mpz_t e, mpz_t n, mpz_t d );
void findE( mpz_t e, mpz_t fi );

#endif
