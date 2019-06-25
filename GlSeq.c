#include <stdlib.h>
#include <stdio.h>
#include <math.h>


double a(int n);
double b(int n);
double t(int n);
double p(int n);
double pi(int n);
void GlSeq();


int main() {
    GlSeq();
    return 0;
}



double a(int n){
    if(n == 0){
        return 1;
    }else{
        return (a(n - 1) + b(n - 1))/2;
    }
}

double b(int n){
    if(n == 0){
        return 1/sqrt(2);
    }else{
        return sqrt(a(n - 1) * b(n - 1));
    }
}

double t(int n){
    if(n == 0){
        return 0.25;
    }else{
        return t(n - 1) - p(n - 1) * pow(a(n - 1) - a(n), 2);
    }
}

double p(int n){
    if(n == 0){
        return 1;
    }else{
        return 2 * p(n - 1);
    }
}

double pi(int n){
    return pow(a(n) + b(n), 2)/(4 * t(n));
}

void GlSeq(){
    int n;
    scanf("%d", &n);
    printf("%.6lf \n", pi(n));
}