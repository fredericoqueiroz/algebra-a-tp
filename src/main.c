#include <stdlib.h>
#include "lib/aritmetica.h"


int main(){

    /*  Teste da funcao inverso_modular
    mpz_t a, n, r, r1;
    mpz_init(a);
    mpz_init(n);
    mpz_init(r);
    mpz_init(r1);
    int inv, inv2;
    
    gmp_scanf("%Zd %Zd", a, n);
    
    inv = inverso_modular(r, a, n);
    inv2 = mpz_invert(r1, a, n);
    
    if(inv)
        gmp_printf("%Zd * %Zd = 1 (mod %Zd)\n", a, r, n);
    else
        gmp_printf("%Zd nao possui inverso modulo %Zd\n", a, n);
    
    if(inv2)
        gmp_printf("%Zd * %Zd = 1 (mod %Zd)\n", a, r1, n);
    else
        gmp_printf("%Zd nao possui inverso modulo %Zd\n", a, n);

    mpz_clear(a);
    mpz_clear(n);
    mpz_clear(r);
    mpz_clear(r1);
    */

    /* Teste da funcao exp_binaria
    mpz_t r, b, e, n;
    mpz_init(r);
    mpz_init(b);
    mpz_init(e);
    mpz_init(n);
    
    gmp_scanf("%Zd %Zd %Zd", b, e, n);
    
    exp_binaria(r, b, e, n);
    
    gmp_printf("%Zd ^ %Zd = %Zd (mod %Zd)\n", b, e, r, n);
    
    mpz_clear(r);
    mpz_clear(b);
    mpz_clear(e);
    mpz_clear(n);
    */

    return 0;
}
