#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include <pthread.h>

struct parametros_a {
   mpf_t *a;
   mpf_t *b;
   mpf_t *prox_A;
};
typedef struct parametros_a a_data;

struct parametros_b {
   mpf_t *a;
   mpf_t *b;
   mpf_t *prox_B;
};
typedef struct parametros_b b_data;

void* a_Novo(void* arg_a) ;
void* b_Novo(void* arg_b);
void t_Novo(mpf_t a, mpf_t prox_A, mpf_t t, mpf_t *prox_T, mpf_t *p, mpf_t aX);
void GlParl(int intN, mpf_t*pi);


int main() {
    mpf_t pi;
    mpf_init(pi);
    GlParl(100000, &pi);
    printf("%lf\n", mpf_get_d (pi));
    mpf_clear(pi);
    return 0;
}


void* a_Novo(void* arg_a) {
    a_data *iDados;
    iDados =  (a_data*) arg_a;
    mpf_add(*(iDados->prox_A), *(iDados->a), *(iDados->b));
    mpf_div_ui(*(iDados->prox_A), *(iDados->prox_A), 2);
    pthread_exit(NULL);
}

void* b_Novo(void* arg_b) {
    b_data *iDados;
    iDados =  (b_data *) arg_b;
    mpf_mul(*(iDados->prox_B), *(iDados->a), *(iDados->b));
    mpf_sqrt (*(iDados->prox_B), *(iDados->prox_B));
    pthread_exit(NULL);
}

void t_Novo(mpf_t a, mpf_t prox_A, mpf_t t, mpf_t *prox_T, mpf_t *p, mpf_t aX) {
    //aX = a - prox_A; //evita o uso de pow(a, 2)
    mpf_sub(aX, a, prox_A);
    //prox_T = t - p * aX * aX;
    mpf_pow_ui(aX, aX, 2);
    mpf_mul(aX, aX, *p);
    mpf_sub(*prox_T, t, aX);
    //p = 2 * p;
    mpf_mul_ui(*p, *p, 2);
}
//Calcula numericamente o valor de PI
void GlParl(int intN, mpf_t*pi){
    //double a = 1;
    //double b = sqrt(2)/2;
    //double t = 0.25;
    //double p = 1;

    //double prox_A, prox_B, prox_T, aX;

    //for(i = 0; i < intN; i++){
        //prox_A = (a + b)/2;
        //a = prox_A;
        //b = prox_B;
        //t = prox_T;
    //}
    //aX = (a + b)/2; //evita o uso de pow(a, 2) 
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

    
    mpf_t prox_A, prox_B, prox_T, aX;
    mpf_init(prox_A);
    mpf_init(prox_B);
    mpf_init(prox_T);
    mpf_init(aX);
    
    int i;
    for(i = 0; i < intN; i++){
        //prox_A = (a + b)/2;
        a_data obj1;
        b_data obj2;

        pthread_t id1;
        pthread_t id2;
        obj1.a=&a;
        obj1.b=&b;
        obj1.prox_A= &prox_A;
        obj2.a=&a;
        obj2.b=&b;
        obj2.prox_B=&prox_B;
        pthread_create(&id1, NULL, a_Novo, &obj1);
        pthread_create(&id2, NULL, b_Novo, &obj2);
        pthread_join(id1,NULL);
        pthread_join(id2,NULL);
        
        t_Novo(a, prox_A, t, &prox_T, &p, aX); 
        
        //a = prox_A;
        mpf_set(a, prox_A);
        //b = prox_B;
        mpf_set(b, prox_B);
        //t = prox_T;
        mpf_set(t, prox_T);
    }
    //aX = (a + b)/2; //evita o uso de pow(a, 2)
    mpf_add(aX, a, b);
    mpf_div_ui(aX, aX, 2);
    mpf_mul(aX, aX, aX);
    mpf_div(*pi, aX, t);
    
}
