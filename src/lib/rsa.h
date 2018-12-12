#include <gmp.h>

#ifndef _RSA
#define _RSA

void gera_chaves(mpz_t n,
                 mpz_t e,
                 mpz_t d,
                 gmp_randstate_t rnd);

void codifica(mpz_t r, const char *str);

char *decodifica(const mpz_t n);

void criptografa(mpz_t C,
                 const mpz_t M,
                 const mpz_t n,
                 const mpz_t e);

void descriptografa(mpz_t M,
                    const mpz_t C,
                    const mpz_t n,
                    const mpz_t d);

#endif
