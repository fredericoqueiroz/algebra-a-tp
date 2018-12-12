#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "aritmetica.h"
#include "primalidade.h"

void gera_chaves(mpz_t n,
                 mpz_t e,
                 mpz_t d,
                 gmp_randstate_t rnd)
{
    mpz_t p, q, fi_p, fi_q, fi_n;

    mpz_init(p);
    //Gera um primo aleatorio p no intervalo [2,2^2048)
    primo_aleatorio(p, 2048, rnd);

    mpz_init(q);
    //Gera um primo aleatorio q no intervalo [2,2^2048)
    primo_aleatorio(q, 2048, rnd);

    // n = p * q
    mpz_mul(n, p, q);

    mpz_init(fi_p);
    mpz_sub_ui(fi_p, p, 1); // fi_p = p-1

    mpz_init(fi_q);
    mpz_sub_ui(fi_q, q, 1); // fi_q = q-1

    mpz_init(fi_n);
    mpz_mul(fi_n, fi_p, fi_q); // fi_n = (p-1)*(q-1)

    mpz_set_ui(e, 65537);
    // Encontra d que eh o inverso de e (mod fi_n)
    inverso_modular(d, e, fi_n);

    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(fi_p);
    mpz_clear(fi_q);
    mpz_clear(fi_n);
}

// Codifica uma string *str em base 256
void codifica(mpz_t r, const char *str)
{
    mpz_t b, aux;
    char c;
    int ascii, i = 0;

    mpz_init(b);
    mpz_init(aux);

    mpz_set_ui(b, 1);
    mpz_set_ui(r, 0);

    while(str[i] != '\0'){
        c = str[i];
        ascii = (int)c;
        mpz_mul_ui(aux, b, ascii);
        mpz_add(r, r, aux);
        mpz_mul_ui(b, b, 256);
        i++;
    }

    mpz_clear(b);
    mpz_clear(aux);
}

// Desfaz a funcao codifica, retornando um char*
char *decodifica(const mpz_t n)
{
    char *str = (char *) malloc(501 * sizeof(char));

    mpz_t x, ascii;
    int i = -1;
    char c;

    mpz_init(x);
    mpz_init(ascii);

    mpz_set(x, n);

    do{
        i++;
        mpz_mod_ui(ascii, x, 256);
        mpz_sub(x, x, ascii);
        mpz_div_ui(x, x, 256);

        c = (char)mpz_get_ui(ascii);
        str[i] = c;
    } while(str[i] != '\0');

    mpz_clear(x);
    mpz_clear(ascii);

    return str;
}

void criptografa(mpz_t C,
                 const mpz_t M,
                 const mpz_t n,
                 const mpz_t e)
{
    exp_binaria(C, M, e, n);
}

void descriptografa(mpz_t M,
                    const mpz_t C,
                    const mpz_t n,
                    const mpz_t d)
{
    exp_binaria(M, C, d, n);
}