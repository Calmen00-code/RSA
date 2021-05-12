#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <gmp.h>

int main()
{
    char str[1024];
    int flag;
    long long int a;

    /* Using standard C data */
/*
    printf("Standard C Integer:\n");
    scanf("%s", str);
    sscanf(str, "%lld", &a);
    printf("%lld\n", a);
    printf("\n");
*/

    /* Using GMP Data Structure */
/*
    mpz_t n;
    printf("GMP Integer:\n");
    scanf("%s", str);
    mpz_init(n);
    mpz_set_ui(n, 0); 
    flag = mpz_set_str(n,str,10);
    assert(!flag);
    mpz_add_ui(n,n,1);
    mpz_out_str(stdout,10,n);
    mpz_clear(n);
    printf("\n");
*/
/* 1000000000000000000000000000000000000000000000000 */


/*
    mpz_t rop;
    mpz_init(rop);
    mpz_set_ui(rop, 0);

    mpz_t base;
    mpz_init(base);
    mpz_set_ui(base, 8);

    mpz_pow_ui(rop, base, 100);
    mpz_out_str(stdout, 10,rop);
    printf("\n");
*/

    mpz_t randomVal;
    mpz_init(randomVal);
    mpz_set_ui(randomVal, 0);

    mpz_t n;
    mpz_init(n);
    mpz_set_ui(n, 5);

    gmp_randstate_t state;
    gmp_randinit_default(state);

    for ( int i = 0; i < 5; ++i ) {
        mpz_urandomm(randomVal, state, n);
        mpz_out_str(stdout, 10,randomVal);
        printf("\n");
    }
    return 0;
}
