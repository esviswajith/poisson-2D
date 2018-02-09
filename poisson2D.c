#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void plot();

void main(void){
    
FILE *out;
    out = fopen("p2dout.dat","w");
    
    int i,j,k,count;
    double difference,phi[100][100],newphi[100][100],rho[100][100];
    difference = 1.0;
    for (i=0;i<100;i++){
        phi[i][0]=50.0;
        for(j=1;j<100;j++){
            phi[i][j] = 0.0;
            newphi[i][j] = 0.0;
            rho[i][j] = 0.0;
        }
    }
    
    rho[50][50]=0.0;
    count = 0;
    do{
        difference = 0.0;
        for(i=1;i<99;i++){
            for(j=1;j<99;j++){
                newphi[i][j] = 0.25*(phi[i-1][j]+phi[i+1][j]+phi[i][j-1]+phi[i][j+1]+rho[i][j]);
                difference += fabs(newphi[i][j]-phi[i][j]);
                phi[i][j] = newphi[i][j];
            }
        }
        count+=1;
    }while(difference>0.0001);
    
    printf("%d",count);
    for (i=0;i<100;i++){
        for(j=1;j<100;j++){
            fprintf(out,"%d %d %lf %lf\n",i,j,phi[i][j],difference);
        }
    }
    
    plot();
    
}

void plot(void){
    
    FILE *commandfile;
    commandfile = fopen("gnuscript.txt","w");
    fprintf(commandfile, "splot 'p2dout.dat' u 1:2:3 w d\n");
    fclose(commandfile);
    system("gnuplot --persist gnuscript.txt");
    
}
