#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#define qnThreads 4
#define RANDOM_MAX 	(0x80000000 - 1)	

typedef int num_r;
num_r variar(num_r* r);


struct parametros {
	double *S;
	double *E;
	double *r;
	double *o;
	double *T;
	int *M;
	double *trials;
    double *soma;
};
typedef struct parametros data;


double stddev (double *trials, double mean, int tamVec) {
	int i;
	double stddev = 0;
	for (i = 0; i < tamVec; i++)
	{
		stddev = stddev + pow((trials[i]-mean),2);
	}
	return stddev;
}

void* Bp_thread(void* argumentos) {
	num_r r1;
	data *my_data;
	r1 = rand();
	my_data =  (data *) argumentos;
	
    int i;
	double t;
	double max;
	double soma=0;

    for (i = 0; i < (*(my_data->M))/qnThreads; i++)
	{
        double ran = (double) variar(&r1)/RANDOM_MAX;
        //t = S*exp((r-1.0/2*o*o)*T + o*sqrt(T)*ran); 
		t = (*(my_data->S))*exp(((*(my_data->r))-1.0/2*(*(my_data->o))*(*(my_data->o)))*(*(my_data->T)) + (*(my_data->o))*sqrt((*(my_data->T)))*ran); 
		if(t-(*(my_data->E))>0) {
			max = t-(*(my_data->E));
		}
		else {
			max = 0;
		}
        //trials[i] = exp(-r*T)*max; 
		((my_data->trials[i])) = exp(-(*(my_data->r))*(*(my_data->T)))*max;
        soma = soma + (my_data->trials[i]);  
              
	}
    (*my_data->soma)=soma;     
	pthread_exit(NULL);
}


void Bp(double S, double E, double r, double o, double T, int M) {

    pthread_t id_threads[qnThreads];
    data objList[qnThreads];
    int i;
    double somaTotal=0;
    double totalDesvio=0;
    double soma[qnThreads];
	
    //Inicializar os parâmetros
    for(i = 0; i < qnThreads; i++) {
    	objList[i].S=&S;
    	objList[i].E=&E;
    	objList[i].r=&r;
    	objList[i].o=&o;
    	objList[i].T=&T;
    	objList[i].M=&M;
	    //trials = (double *) malloc(M*sizeof(double)); 
        objList[i].trials = (double *) malloc(M/qnThreads*sizeof(double));
        objList[i].soma=&soma[i];
    }	

    //Cria as threads
    for(i = 0; i < qnThreads; i++) {
    	pthread_create(&id_threads[i], NULL, Bp_thread, &(objList[i]));
    }
	
    //Aguardar o fim da execucao das threads
    for(i = 0; i < qnThreads; i++) {
    	pthread_join(id_threads[i], NULL);
    }
    //Calculando mean
    for(i = 0; i < qnThreads; i++) {
    	somaTotal = somaTotal + soma[i];
    }

    double mean = somaTotal/M;
 
    //Calculando stddev
    for(i = 0; i < qnThreads; i++) {
    	totalDesvio = totalDesvio + stddev (objList[i].trials, mean, M/qnThreads);
    }

    double stddev = sqrt(totalDesvio/M);
    double intConf = 1.96*stddev/sqrt(M);
    double intConfMin = (mean - intConf);
    double intConfMax = (mean + intConf);

    printf("Confidence interval: (%.6lf, %.6lf)\n", intConfMin, intConfMax);
}


int main(){
	srand(time(NULL));
	double S, E, r, o, T;
	int M;
	scanf("%lf", &S);
    scanf("%lf", &E);
    scanf("%lf", &r);
    scanf("%lf", &o);
    scanf("%lf", &T);
    scanf("%d", &M);
	printf("%.6lf\n", S);
	printf("%.6lf\n", E);
	printf("%.6lf\n", r);
	printf("%.6lf\n", o);
	printf("%.6lf\n", T);
	printf("%d\n", M);

	Bp(S, E, r, o, T, M);
	return 0;
}

//Gera o proximo numero pseudo-aleatorio e atualiza a variavel r
num_r variar(num_r* r){
	return *r = (1103515245*(*r)+ 12345) % 0x80000000;
}