#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define ERRO 1E-15

void BorSeq();


int main() {
    BorSeq();
    return 0;
}


void BorSeq(){
    int i,n=1000000000, conv = 0;
    double a, b, p, pi, pi_ant;
    double a_tmp, b_tmp, p_tmp;

    //scanf("%d", &n);
    //Valores iniciais
    a = sqrt(2.0);
    b = 0.0;
    p = 2.0 + sqrt(2.0);
    conv = 0;
    pi = 0.0;

    //itera n vezes ou ate convergir para calcular pi
    for (i = 0; (i < n) && (conv == 0); i++) {
        pi_ant = pi;

        a_tmp = ( sqrt(a) + (1 / sqrt(a)) ) / 2.0;
        b_tmp = ( (1 + b) * sqrt(a) ) / (a + b);
        p_tmp = ( (1 + a_tmp) * p * b_tmp) / (1 + b_tmp);

        //Atualiza variaveis
        a = a_tmp;
        b = b_tmp;
        p = p_tmp;
        pi = p;

        conv = (fabs(pi - pi_ant) < ERRO) ? 1 : 0;		//analisar a convergencia
    }

    //Retorna valor de pi
    printf("\n%.6f",pi);

}