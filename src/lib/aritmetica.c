#include <gmp.h>
#include "aritmetica.h"

// Computa x, y e g tais que mdc(a,b) = g e ax + by = g
void mdc_estendido(mpz_t g,
                   mpz_t x,
                   mpz_t y,
                   const mpz_t a,
                   const mpz_t b)
{
    mpz_t r, q, aux;
    mpz_init(r);
    mpz_init(q);
    mpz_init(aux);

    // a = bq + r , 0 <= r < b
    mpz_mod(r, a, b); // r = a % b
    mpz_div(q, a, b); // q = a / b

    // se r == 0 : 
    //  g = b; x = 0; y = 1;
    if(mpz_cmp_ui(r,0) == 0){
        mpz_set_ui(x,0);
        mpz_set_ui(y,1);
        goto end;
    }

    // mdc(a,b) == mdc(b,r) == bx' + ry'
    mdc_estendido(g, x, y, b, r);

    // bx' + ry' == bx' + (a - bq)y' == bx' + ay' - bqy' == ay' + b(x' - qy') == mdc(a,b)
    mpz_mul(aux, q, y);
    mpz_sub(aux, x, aux); // aux = (x' - qy')
    mpz_set(x, y); // x = y'
    mpz_set(y, aux); // y = (x' - qy')

    end:
        // g = ax + by
        mpz_mul(g, a, x);
        mpz_mul(aux, b, y);
        mpz_add(g, g, aux);
        
        mpz_clear(r);
        mpz_clear(q);
        mpz_clear(aux);
}

// Computa, se existir, r tal que a*r = 1 (mod n)
int inverso_modular(mpz_t r,
                    const mpz_t a,
                    const mpz_t n)
{
    mpz_t g, x, y;
    int flag = 0;
    mpz_init(g);
    mpz_init(x);
    mpz_init(y);
    
    mdc_estendido(g, x, y, a, n);
    
    if(mpz_cmp_ui(g,1) == 0){        
        mpz_set(r, x);
        flag = 1;        
    }
    mpz_clear(g);
    mpz_clear(x);
    mpz_clear(y);
    return flag;
}

// Computa r tal que b^e = r (mod n)
void exp_binaria(mpz_t r,
                 const mpz_t b, 
                 const mpz_t e,
                 const mpz_t n)
{
    mpz_t pot, e_aux, aux;
    
    mpz_init(pot);
    mpz_init(e_aux);
    mpz_init(aux);
    
    mpz_mod(pot, b, n);
    mpz_set_ui(r, 1);
    mpz_set(e_aux, e);
    
    
    while(mpz_cmp_ui(e_aux,0) > 0){
        if(mpz_fdiv_ui(e_aux, 2) == 1){
            //r = (r * pot) % n;
            mpz_mul(r, r, pot);
            mpz_mod(r, r, n);
        }
        
        mpz_mul(pot, pot, pot);
        mpz_mod(pot, pot, n);
        
        mpz_fdiv_q_ui(aux, e_aux, 2);
        mpz_set(e_aux, aux);
    }
    
    mpz_clear(pot);
    mpz_clear(e_aux);
    mpz_clear(aux);
}