#include <gmp.h>

#ifndef _PRIMALIDADE
#define _PRIMALIDADE

int talvez_primo(const mpz_t a,
                 const mpz_t n,
                 const mpz_t n1,
                 unsigned int t,
                 const mpz_t q);


void numero_aleatorio(mpz_t r,
                      const mpz_t n,
                      gmp_randstate_t rnd);

int provavelmente_primo(const mpz_t n,
                        unsigned int iter,
                        gmp_randstate_t rnd);

void primo_aleatorio(mpz_t r,
                     unsigned int b,
                     gmp_randstate_t rnd);
                     
#endif