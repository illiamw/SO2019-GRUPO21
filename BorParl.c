#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gmp.h>
#include <pthread.h>
#include <semaphore.h>


sem_t buffer_full, buffer_empty;
pthread_mutex_t mutex;

struct parametros_y {
   mpf_t *y;
   mpf_t *prox_Y;
};
typedef struct parametros_y Y_param;

struct parametros_a{
   mpf_t *a;
   mpf_t *prox_Y;
   int *i;
   mpf_t *prox_A;
};
typedef struct parametros_a A_param;

void* data_Y (void *arg_y);
void* data_A (void *arg_a);
void BoParl(int intN, mpf_t *pi);

int main() {
    mpf_t pi;
    mpf_init(pi);
    BoParl(100000, &pi);
    printf("%lf\n", mpf_get_d (pi));
    mpf_clear(pi);
    return 0;
}




//data_Y é o produtor
void* data_Y (void *arg_y) {
    mpf_t aX_Y2, num, den;
    Y_param *my_data;
    my_data =  (Y_param *) arg_y;
    mpf_init(aX_Y2);
    mpf_init(num);
    mpf_init(den);
   
    //prox_Y = (1-pow((1-pow(y,4)),0.25))/(1+pow((1-pow(y,4)),0.25));
      
    mpf_pow_ui(aX_Y2, *(my_data->y), 4);
    mpf_ui_sub (aX_Y2, 1, aX_Y2);
    mpf_sqrt(aX_Y2, aX_Y2);
    mpf_sqrt(aX_Y2, aX_Y2);
    mpf_ui_sub (num, 1, aX_Y2);
    mpf_add_ui(den, aX_Y2, 1);
    sem_wait(&buffer_full);
    //pthread_mutex_lock e pthread_mutex_unlock protegem o acesso de prox_Y à região crítica
    pthread_mutex_lock(&mutex); 
    mpf_div(*(my_data->prox_Y), num, den);
    pthread_mutex_unlock(&mutex); 
    sem_post(&buffer_empty);

    mpf_clear(aX_Y2);
    mpf_clear(num);
    mpf_clear(den);

    pthread_exit(NULL);
}

//data_A é o consumidor
void* data_A (void *arg_a) {
    double aux4;  
    mpf_t aX_A2, aX_A3;
    
    A_param *my_data;
    my_data =  (A_param *) arg_a;
    mpf_init(aX_A2);
    mpf_init(aX_A3);
    //prox_A = a*pow((1+prox_Y),4)    -     pow(2,(2*i+3))*prox_Y*(1+prox_Y+prox_Y*prox_Y);

    mpf_t ynext;
    mpf_init(ynext);
    sem_wait(&buffer_empty);
    pthread_mutex_lock(&mutex); 
    mpf_set(ynext, *(my_data->prox_Y));
    pthread_mutex_unlock(&mutex);
    sem_post(&buffer_full);
              
    
    mpf_add_ui(aX_A2,ynext , 1);
    mpf_pow_ui(aX_A2, aX_A2, 4);
    mpf_mul(aX_A2, *(my_data->a), aX_A2);
    aux4 = pow(2,(2* (*(my_data->i))+3));
    mpf_pow_ui(aX_A3, ynext, 2);
    mpf_add_ui(aX_A3, aX_A3, 1);
    mpf_add(aX_A3, aX_A3, ynext);
    mpf_mul(aX_A3, aX_A3, ynext);
    mpf_mul_ui(aX_A3, aX_A3, aux4);
    mpf_sub(*(my_data->prox_A), aX_A2, aX_A3);
    mpf_clear(aX_A2);
    mpf_clear(aX_A3);

    pthread_exit(NULL);
}

 
void BoParl(int intN, mpf_t *pi) {
    //inicializações da precisão da estrutura mpf, posteriores
    mpf_set_default_prec (pow(10, 5));

    double aX_A = 6-4*sqrt(2);
    mpf_t a;
    mpf_init_set_d(a, aX_A);

    double aX_Y = sqrt(2)-1;
    mpf_t y;
    mpf_init_set_d(y, aX_Y);

    mpf_t prox_A, prox_Y;
    mpf_init(prox_A);
    mpf_init(prox_Y);
     
    int i;
    Y_param obj1;
    A_param obj2;
    pthread_t id1;
    pthread_t id2;

    sem_init(&buffer_full, 0, 1);
    sem_init(&buffer_empty, 0, 0); 
    pthread_mutex_init (&mutex,NULL);
 
    obj1.y=&y;
    obj1.prox_Y=&prox_Y;
    obj2.a=&a;
    obj2.prox_Y=&prox_Y;
    obj2.i=&i;
    obj2.prox_A=&prox_A;
 

    for(i = 0; i < intN; i++){
        //printf("Iteração: %d\n", i);
 
        //Cria as threads

        pthread_create(&id1, NULL, data_Y, &obj1);

        pthread_create(&id2, NULL, data_A, &obj2);

        //Aguardar o fim da execucao das threads
	    pthread_join(id1, NULL);
	    pthread_join(id2, NULL);
        
	    //a = prox_A;
        mpf_set(a, prox_A);
        //y = prox_Y;
        mpf_set(y, prox_Y);
    }

    mpf_ui_div(*pi, 1, a);

    mpf_clear(a);
    mpf_clear(y);
    mpf_clear(prox_A);
    mpf_clear(prox_Y);

}

