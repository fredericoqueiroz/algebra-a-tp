#include <stdio.h>
#include <gmp.h>

// Computa x, y e g tais que mdc(a,b) = g e ax + by = g
void mdc_estendido(mpz_t g, mpz_t x, mpz_t y, const mpz_t a, const mpz_t b){

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
int inverso_modular(mpz_t r, const mpz_t a, const mpz_t n){
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

int main(){

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

    return 0;
}
