#ifndef RSA_H
#define RSA_H

#include <gmp.h> /* For large number computation structure */

void randomGenerator( mpz_t result, mpz_t lower, mpz_t upper, gmp_randstate_t state );
void getIntArray( char text[], int *arr );
void Encryption( char asciiMsg[], char ciphertext[], mpz_t n, mpz_t e );
void Decryption( char ciphertext[], char plaintext[], mpz_t d, mpz_t n );
int getArraySize( char str[] );
void generateRandomPrime( mpz_t randNum, mpz_t lower, mpz_t upper );
void generateKey( mpz_t e, mpz_t n, mpz_t d );
void findE( mpz_t e, mpz_t fi );

#endif
