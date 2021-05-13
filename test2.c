#include <stdio.h>
#include <string.h>
#include <gmp.h>

int main()
{
    mpz_t a, b, p, invOne, invTwo;
    char str[1024];

    mpz_init(a); mpz_set_ui(a, 2);
    mpz_init(b); mpz_set_ui(b, 0);
    mpz_init(p); mpz_set_ui(p, 0);
    mpz_init(invOne); mpz_set_ui(invOne, 0);
    mpz_init(invTwo); mpz_set_ui(invTwo, 0);
    strcpy(str, "4781771649437227274200346715662813109220916734356822826663428804568955772066210724078708923314063541257323472325758763137170447840544451043861130756484401625181933735897457565405406535326289883951463929824347586034330580573579204757522995494697945536872800470726616142255078344408097938426527459065018595708002968640999433852535103647683536585245177244454470815763617951809163245060764271994116931055493135736040172488193937720718832363763392262219451002014222561056550165098652074200302199767572096918573975594544275607298479091524449077110867876254049173999288785105111653990976709671729382896696355707732831157124");
    mpz_set_str(b, str, 10);

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
