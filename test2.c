#include <stdio.h>
#include <gmp.h>

int main()
{
    mpz_t a, b, p, invOne, invTwo;

    mpz_init(a); mpz_set_ui(a, 3);
    mpz_init(b); mpz_set_ui(b, 20);
    mpz_init(p); mpz_set_ui(p, 0);
    mpz_init(invOne); mpz_set_ui(invOne, 0);
    mpz_init(invTwo); mpz_set_ui(invTwo, 0);

    mpz_gcdext(p, invOne, invTwo, a, b);
    printf("gcd: ");
    mpz_out_str(stdout, 10, p);
    printf("\n");

    printf("invOne: ");
    mpz_out_str(stdout, 10, invOne);
    printf("\n");

    printf("invTwo: ");
    mpz_out_str(stdout, 10, invTwo);
    printf("\n");

    printf("a: ");
    mpz_out_str(stdout, 10, a);
    printf("\n");

    printf("b: ");
    mpz_out_str(stdout, 10, b);
    printf("\n");

    return 0;
}
