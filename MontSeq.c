#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

void MontSeq();


int main() {
    MontSeq();
    return 0;
}


void MontSeq(){
    int niter=1000000000;
    double x,y;
    int i,count=0;
    double z;
    double pi;

    //printf("Enter the number of iterations used to estimate pi:");
    //scanf("%d",&niter);

    /* initialize random numbers */
    srand(time(NULL));
    count=0;
    for ( i=0; i<niter; i++) {
        x = (double)rand()/(double)RAND_MAX;
        y = (double)rand()/(double)RAND_MAX;

        z = x*x+y*y;

        if (z<=1) count++;
    }
    pi=(double)count/niter*4;
    printf(" %.7g \n",pi);
}