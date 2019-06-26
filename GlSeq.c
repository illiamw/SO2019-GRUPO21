#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>

void GL(int n);

int main() {
	int n=100000;
	GL(n);
}

//Calcula numericamente o valor de PI
void GL(int n){
    //double a = 1;
    //double b = sqrt(2)/2;

    //double t = 0.25;

    //double p = 1;

    //double a_next, b_next, t_next, aux;

    //for(i = 0; i < n-1; i++){
        //a_next = (a + b)/2;

        //b_next = sqrt(a * b);

        //aux = a - a_next; //evita o uso de pow(a, 2)

        //t_next = t - p * aux * aux
         
        //atualização das variáveis
        //p = 2 * p;
        //a = a_next;
        //b = b_next;
        //t = t_next;
    //}
    //aux = (a + b)/2; //evita o uso de pow(a, 2)

    /////////////////////////////////
    // Convertendo formula de Math >>> GMP
    //
    /////////////////////////////////


    //inicializações
    mpf_set_default_prec (pow(10, 5));

    
    mpf_t a;
    mpf_init_set_d(a, 1.0);
    
    double raiz = sqrt(0.5);
    mpf_t b;
    mpf_init_set_d(b, raiz);
    
    mpf_t t;
    mpf_init_set_d(t, 0.25);
    
    mpf_t p;
    mpf_init_set_d(p, 1.0);

    
    mpf_t a_next, b_next, t_next, aux;
    mpf_init(a_next);
    mpf_init(b_next);
    mpf_init(t_next);
    mpf_init(aux);
     
    int i; 
    mpf_t rop;
    mpf_init(rop); 
    mpf_t rop2;
    mpf_init(rop2);
    for(i = 0; i < n-1; i++){
        mpf_add(rop, a, b);
        mpf_div_ui(a_next, rop, 2);

        mpf_mul(rop2, a, b);
        mpf_sqrt (b_next, rop2);

        mpf_sub(aux, a, a_next);

        mpf_pow_ui(aux, aux, 2);
        mpf_mul(aux, aux, p);
        mpf_sub(t_next, t, aux);
         
        mpf_mul_ui(p, p, 2);
        mpf_set(a, a_next);
        mpf_set(b, b_next);
        mpf_set(t, t_next);
    }

    mpf_add(aux, a, b);
    mpf_div_ui(aux, aux, 2);
    mpf_mul(aux, aux, aux);

    mpf_t pi;
    mpf_init(pi);

    mpf_div(pi, aux, t);
    
    printf("%lf\n", mpf_get_d (pi));

    mpf_clear(a);
    mpf_clear(b);
    mpf_clear(t);
    mpf_clear(p);
    mpf_clear (a_next);
    mpf_clear (b_next);
    mpf_clear (t_next);
    mpf_clear(aux);
    mpf_clear(rop);
    mpf_clear(rop2);


}

