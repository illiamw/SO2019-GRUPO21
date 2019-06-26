#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gmp.h>

void Borw(int n);

void main(){
    int n=100000;
    Borw(n);
}

void Borw(int n){ 

    //Variavies de Borwein Convergência quártica 
    //double a, y;    

    //Iterações valor K somatórias
    //int i=0;

    //valores iniciais
    //a = 2*pow((sqrt(2)-1),2);
    
    //y = sqrt(2)-1;
    

    
    //iterações 
    //for(i=0;i<n-1;i++){
    //    y = (1- pow( (1-pow(y,4)), 0.25)) / (1+ pow( (1-pow(y,4)), 0.25));
    //    a = (a*pow( (1 + y), 4) - pow(2, ((2*i)+3) )*y*(1 + y + pow(y,2)));
    //}   
    

    //return (1/a);

    /////////////////////////////////
    // Convertendo formula de Math >>> GMP
    //
    /////////////////////////////////

    //Ajustando a precisão da estrutura
    mpf_set_default_prec(pow(10,5));

    //Ponteiros correspondente as flutuantes do da biblioteca
    mpf_t a, y;

    //Setando os valores inicias de A0 e Y0
    mpf_init_set_d(a, 2*pow((sqrt(2)-1),2));
    mpf_init_set_d(y, sqrt(2)-1);

    //Variaveis acumulativas para iteração
    mpf_t a1, y1, a2, y2, a3;
    mpf_init(a1);
    mpf_init(y1);
    mpf_init(a2);
    mpf_init(y2);
    mpf_init(a3);
    int i;

    //iteração correspondente a formula
    for (i = 0; i < n-1; i++){

        //Operações do Y
        mpf_pow_ui(y1,y,4);
        mpf_ui_sub(y1,1,y1);
        mpf_sqrt(y1, y1);
        mpf_sqrt(y1, y1);
        mpf_add_ui(y2,y1,1);
        mpf_ui_sub(y1,1,y1);        

        mpf_div(y,y1,y2);

        //Operações do A
        mpf_add_ui(a1,y,1);
        mpf_pow_ui(a1,a1,4);
        mpf_mul(a1,a1,a);

        mpf_mul_ui(a2,y,(pow(2, ((2*i)+3)) ));
        mpf_pow_ui(a3,y,2);
        mpf_add(a3, y, a3);
        mpf_add_ui(a3,a3,1);
        mpf_mul(a2, a2, a3);

        mpf_sub(a, a1, a2);    
    }

    mpf_t pi;
    mpf_init(pi);
    mpf_ui_div(pi,1,a);

    printf("%lf\n", mpf_get_d (pi));
    
    //Limpando memória

    mpf_clear(a);
    mpf_clear(y);
    mpf_clear(a1);
    mpf_clear(a2);
    mpf_clear(a3);
    mpf_clear(y1);
    mpf_clear(y2);
    mpf_clear(pi);

}