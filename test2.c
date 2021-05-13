#include <stdio.h>
#include <gmp.h>

int main()
{
    mpz_t a, b, p;

    mpz_init(a); mpz_set_ui(a, 3);
    mpz_init(b); mpz_set_ui(b, 2);
    mpz_init(p); mpz_set_ui(p, 0);

    mpz_gcd(p, a, b);
    mpz_out_str(stdout, 10, p);

    return 0;
}
