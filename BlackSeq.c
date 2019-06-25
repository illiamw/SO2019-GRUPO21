#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include<time.h>

double media(double *trials, int m);
double desvio(double *trials, int m);
void BlackSeq();


int main() {
    BlackSeq();
    return 0;
}


// funções necessarias para o calculo do Black Scholes
double media(double *trials, int m){
    int i;
    double aux=0.0;
    for (i=0;i<m;i++){
        aux =trials[i] +aux;
    }
    aux = (aux/( (double)m ));
    return aux;
}

double desvio(double *trials, int m){
    int i;
    double med = media(trials,m);
    double desv= 0.0;
    double aux= 0.0;
    for (i = 0; i < m ; i++) {
        aux =aux + pow((trials[i] - med),2);
    }
    aux = (aux/( (double)m ));
    desv = sqrt(aux);
    return desv;

}

void BlackSeq(){
    double S; // Valor da acao
    double E; // Preco de exercicio da opçao
    double r; // Taxa de juros livre de risco(SELIC)
    double o; // Volatilidade da acao
    double T; // Tempo de validade da acao
    int M, i; // Numero de interacoes
    double temp;
    //variaveis para as outras funcoes
    double *trials, mean,stddev,intConf,intConfMax, intConfMin;
    // sem arquivos:
    scanf("%lf", &S);
    scanf("%lf", &E);
    scanf("%lf", &r);
    scanf("%lf", &o);
    scanf("%lf", &T);
    scanf("%d", &M);
    // alocando a memoria
    trials = (double*)malloc(M* sizeof(double));
    assert(trials);
    srand(time(NULL));
    for (i = 0; i <M ; i++) {
        temp= S*exp( ((r - ((1/2)*pow(o,2)))*T) + (o*sqrt(T)*rand()/RAND_MAX));
        trials[i] = exp(-r*T)*fmax((temp-E), 0);
    }
    mean = media(trials, M);
    stddev = desvio(trials, M);
    intConf= (1.96*(stddev/M));
    intConfMax = (mean + intConf);
    intConfMin = (mean - intConf);
    // fim do programa:
    printf("%lf\n", S);
    printf("%lf\n", E);
    printf("%lf\n", r);
    printf("%lf\n", o);
    printf("%lf\n", T);
    printf("%d\n", M);
    printf("Confidence interval: (%.6lf, %.6lf)", intConfMin, intConfMax);

    free(trials);
    exit(0);

}