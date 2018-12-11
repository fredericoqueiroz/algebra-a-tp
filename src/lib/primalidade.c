#include <stdlib.h>
#include <gmp.h>
#include "primalidade.h"
#include "aritmetica.h"

// Verifica se n passa no teste de Miller Rabin com base a
int talvez_primo(const mpz_t a,
                 const mpz_t n,
                 const mpz_t n1,
                 unsigned int t,
                 const mpz_t q)
{
    mpz_t r;
    mpz_init(r);
    unsigned int i = 1;
    int result = 0;

    mpz_mod(r, a, n);
    if(mpz_cmp_ui(r, 0) == 0){
        result = 1;
        goto end;
    }

    exp_binaria(r, a, q, n);
    if(mpz_cmp_ui(r, 1) == 0){
        result = 1;
        goto end;
    }

    while(i < t){
        mpz_mul(r, r, r);
        mpz_mod(r, r, n);
        if(mpz_cmp(r, n1) == 0){
            result = 1;
            goto end;
        }
        i++;
    }

    end:
        mpz_clear(r);
        return result;

}

// Computa um numero aleatorio r, no intervalo [1,n]
void numero_aleatorio(mpz_t r,
                      const mpz_t n,
                      gmp_randstate_t rnd)
{
    mp_bitcnt_t num_bits = mpz_sizeinbase(n, 2);
    do{
        mpz_urandomb(r, rnd, num_bits);
    } while (!(mpz_cmp_ui(r, 1) >= 0 && mpz_cmp(r, n) <= 0));
}

// 0 se 'n' eh definitivamente composto
// 1 se 'n' eh provavelmente primo
int provavelmente_primo(const mpz_t n,
                        unsigned int iter,
                        gmp_randstate_t rnd)
{
    mpz_t base, q, n1;
    unsigned int i, t = 0;
    int result = 1;

    mpz_init(base);
    mpz_init(q);
    mpz_init(n1);

    mpz_sub_ui(n1, n, 1);

    // encontra 't' e 'q' tal que n-1 = 2^t * q
    mpz_set(q, n1);
    while(mpz_cmp_ui(q, 0) != 0 && mpz_even_p(q)){
        mpz_div_ui(q, q, 2);
        t++;
    }

    for(i=0; i<iter; i++){
        do{
            numero_aleatorio(base, n, rnd);
        } while(mpz_cmp_ui(base, 2) < 0);

        if(talvez_primo(base, n, n1, t, q) == 0){
            result = 0;
            goto end;
        }
    }

    end:
        mpz_clear(base);
        mpz_clear(q);
        mpz_clear(n1);
        return result;
}

// Computa um primo aleatorio r no intervalo [2,2^b)
void primo_aleatorio(mpz_t r,
                     unsigned int b,
                     gmp_randstate_t rnd)
{
    do{
        mpz_urandomb(r, rnd, b);
    } while(mpz_cmp_ui(r, 2) < 0 || !provavelmente_primo(r, 10, rnd));
}