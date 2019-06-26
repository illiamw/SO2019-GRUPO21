#define Nthreads 4
#define ITERA 1000000000 //número de ITERAções
#define RANDOM_MAX 	(0x80000000 - 1) //Definindo valor 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gmp.h>
#include <pthread.h>

int variar(int* r);//Função randomica com alta precisão de varabilidade
void manageThreads(int itera, mpf_t *pi);//Função do calculo de PI
void* monte_carlo_thread(void* corretos_void);//Função de paralelização

int main(int argc, char const *argv[])
{

    srand(time(NULL));
    mpf_t pi;
    mpf_init(pi);
    
    manageThreads(ITERA, &pi);
    printf("%lf\n", mpf_get_d (pi));
    mpf_clear(pi);

	return 0;
}
//Função de paralela associadas a threads
void* monte_carlo_thread(void* corretos_void) {
	// Variaveis dos pontos no plano para o calculo de acertos
    double x;
	double y;
    //r - rand(), *corretos-numeros de acertos, i - ITERAções de loop
    int r;
	int *corretos;
	int i;
	
    //Passando o ponteiro recebido pela threads apos paraleliza-la
    corretos = (int*)corretos_void;
    *corretos = 0;
    
    //Numero randomico
    r = rand();	

    //Função Monte Carlo, Chamada por cada thread
	for (i = 0; i < ITERA/Nthreads; i++)
	{
		x = (double) variar(&r)/RANDOM_MAX;
		y = (double) variar(&r)/RANDOM_MAX;
		if(x*x+y*y < 1) {
			*corretos += 1;
		}
	}
	pthread_exit(NULL);
}

//Gerenciamento de Threads
void manageThreads(int itera, mpf_t *pi) {
    //Zera a refrencia de time utilizado para gerar o numero randomico
	srand(time(NULL));
    //Variaveis ITERAtivas
	int i, corretos_total = 0;

    //Auxiliares da estrutura gmp
	mpf_t aux;
	mpf_init(aux);

    //Vetor de gerenciamento 
	pthread_t id_threads[Nthreads];
	int corretos[Nthreads];

	//Cria as threads 
    // Parametros >>> pthread_create(id da thread, NULL (opção default), função a ser paralelizada, parametro de ITERAção viculada ao gerenciador de threads
	for(i = 0; i < Nthreads; i++) {
		pthread_create(&id_threads[i], NULL, monte_carlo_thread, &corretos[i]);
	}
	
	//Espera as threads realizarem suas intruções
	for(i = 0; i < Nthreads; i++) {
		pthread_join(id_threads[i], NULL);
	}

    //Sincronização das threads
	for(i = 0; i < Nthreads; i++) {
		corretos_total += corretos[i];
	}

	//pi = 4.0*corretos/ITERA;
	mpf_set_d(aux, corretos_total);
	mpf_mul_ui(aux, aux, 4.0);
	mpf_div_ui(*pi, aux, itera);
	mpf_clear(aux);
	
}

//função responsável por gerar um número pseudo-aleatório
int variar(int* r){
	return *r = (1103515245*(*r)+ 12345) % 0x80000000;
}