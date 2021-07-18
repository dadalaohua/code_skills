#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define Data    20
#define In      1//2
#define Out     1
#define Neuron  3
#define In_A    0//1
#define Out_A   0//21
#define TrainC  20000
#define A  0.2
#define B  0.4
#define a  0.2
#define b  0.3

double d_in[Data][In],d_out[Data][Out];
double w[Neuron][In],o[Neuron],v[Out][Neuron];
double Maxin[In],Minin[In],Maxout[Out],Minout[Out];
double OutputData[Out];
double dv[Out][Neuron],dw[Neuron][In];
double e;


// void writeTest(){
    // FILE *fp1,*fp2;
    // double r1,r2;
    // int i;
    // srand((unsigned)time(NULL)); 
    // if((fp1=fopen("D:\\in.txt","w"))==NULL){
        // printf("can not open the in file\n");
        // exit(0);
    // }
    // if((fp2=fopen("D:\\out.txt","w"))==NULL){
        // printf("can not open the out file\n");
        // exit(0);
    // }


    // for(i=0;i<Data;i++){
        // r1=rand()%1000/100.0;
        // r2=rand()%1000/100.0;
        // fprintf(fp1,"%lf  %lf\n",r1,r2);
        // fprintf(fp2,"%lf \n",r1+r2);
    // }
    // fclose(fp1);
    // fclose(fp2);
// }

void readData(){

    // FILE *fp1,*fp2;
    // int i,j;
    // if((fp1=fopen("D:\\in.txt","r"))==NULL){
        // printf("can not open the in file\n");
        // exit(0);
    // }
    // for(i=0;i<Data;i++)
        // for(j=0; j<In; j++)
            // fscanf(fp1,"%lf",&d_in[i][j]);
    // fclose(fp1);

    // if((fp2=fopen("D:\\out.txt","r"))==NULL){
        // printf("can not open the out file\n");
        // exit(0);
    // }
    // for(i=0;i<Data;i++)
        // for(j=0; j<Out; j++)
            // fscanf(fp1,"%lf",&d_out[i][j]);
    // fclose(fp2);
    
    int i,j;
    double tmp = -20;
    
    
    for(i = 0; i < Data; i++)
        for(j = 0; j < Out; j++)
            d_out[i][j] = tmp + i * 5;
        
    for(i = 0; i < Data; i++)
        for(j = 0; j < In; j++)
            d_in[i][j] = 30 * exp(3950 * ((1 / (d_out[i][0] + 273.15)) - (1 / (25.0 + 273.15))));
        
    for(i = 0; i < Data; i++)
        for(j = 0; j < In; j++)
            printf("d_in[%d][%d] : %f\n", i, j, d_in[i][j]);

    for(i = 0; i < Data; i++)
        for(j = 0; j < Out; j++)
            printf("d_out[%d][%d] : %f\n", i, j, d_out[i][j]);
}

void initBPNework(){

    int i,j;

    for(i=0; i<In; i++){
        Minin[i]=Maxin[i]=d_in[0][i];
        for(j=0; j<Data; j++)
        {
            Maxin[i]=Maxin[i]>d_in[j][i]?Maxin[i]:d_in[j][i];
            Minin[i]=Minin[i]<d_in[j][i]?Minin[i]:d_in[j][i];
        }
    }

    for(i=0; i<Out; i++){
        Minout[i]=Maxout[i]=d_out[0][i];
        for(j=0; j<Data; j++)
        {
            Maxout[i]=Maxout[i]>d_out[j][i]?Maxout[i]:d_out[j][i];
            Minout[i]=Minout[i]<d_out[j][i]?Minout[i]:d_out[j][i];
        }
    }

    for (i = 0; i < In; i++)
        for(j = 0; j < Data; j++)
            d_in[j][i]=(d_in[j][i]-Minin[i]+In_A)/(Maxin[i]-Minin[i]+In_A);

    for (i = 0; i < Out; i++)
        for(j = 0; j < Data; j++)
            d_out[j][i]=(d_out[j][i]-Minout[i]+Out_A)/(Maxout[i]-Minout[i]+Out_A);

    for (i = 0; i < Neuron; ++i)    
        for (j = 0; j < In; ++j){    
            w[i][j]=rand()*2.0/RAND_MAX-1;
            dw[i][j]=0;
        }

        for (i = 0; i < Neuron; ++i)    
            for (j = 0; j < Out; ++j){
                v[j][i]=rand()*2.0/RAND_MAX-1;
                dv[j][i]=0;
            }
}

void computO(int var){

    int i,j;
    double sum;
    for (i = 0; i < Neuron; ++i){
        sum=0;
        for (j = 0; j < In; ++j)
            sum+=w[i][j]*d_in[var][j];
        o[i]=1/(1+exp(-1*sum));
    }

    for (i = 0; i < Out; ++i){
        sum=0;
        for (j = 0; j < Neuron; ++j)
            sum+=v[i][j]*o[j];

        OutputData[i]=sum;
    }    
}

void backUpdate(int var)
{
    int i,j;
    double t;
    for (i = 0; i < Neuron; ++i)
    {
        t=0;
        for (j = 0; j < Out; ++j){
            t+=(OutputData[j]-d_out[var][j])*v[j][i];

            dv[j][i]=A*dv[j][i]+B*(OutputData[j]-d_out[var][j])*o[i];
            v[j][i]-=dv[j][i];
        }

        for (j = 0; j < In; ++j){
            dw[i][j]=a*dw[i][j]+b*t*o[i]*(1-o[i])*d_in[var][j];
            w[i][j]-=dw[i][j];
        }
    }
}

double result(double var1,double var2)
{
    // int i,j;
    // double sum;

    // var1=(var1-Minin[0]+In_A)/(Maxin[0]-Minin[0]+In_A);
    // var2=(var2-Minin[1]+In_A)/(Maxin[1]-Minin[1]+In_A);

    // for (i = 0; i < Neuron; ++i){
        // sum=0;
        // sum=w[i][0]*var1+w[i][1]*var2;
        // o[i]=1/(1+exp(-1*sum));
    // }
    // sum=0;
    // for (j = 0; j < Neuron; ++j)
        // sum+=v[0][j]*o[j];

    // return sum*(Maxout[0]-Minout[0]+Out_A)+Minout[0]-Out_A;
    
    int i,j;
    double sum;

    var1=(var1-Minin[0]+In_A)/(Maxin[0]-Minin[0]+In_A);

    for (i = 0; i < Neuron; ++i){
        sum=0;
        sum=w[i][0]*var1;
        o[i]=1/(1+exp(-1*sum));
    }
    sum=0;
    for (j = 0; j < Neuron; ++j)
        sum+=v[0][j]*o[j];

    return sum*(Maxout[0]-Minout[0]+Out_A)+Minout[0]-Out_A;
}

// void writeNeuron()
// {
    // FILE *fp1;
    // int i,j;
    // if((fp1=fopen("D:\\neuron.txt","w"))==NULL)
    // {
        // printf("can not open the neuron file\n");
        // exit(0);
    // }
    // for (i = 0; i < Neuron; ++i)    
        // for (j = 0; j < In; ++j){
            // fprintf(fp1,"%lf ",w[i][j]);
        // }
    // fprintf(fp1,"\n\n\n\n");

    // for (i = 0; i < Neuron; ++i)    
        // for (j = 0; j < Out; ++j){
            // fprintf(fp1,"%lf ",v[j][i]);
        // }

    // fclose(fp1);
// }

void trainNetwork(void)
{
    int i,c=0,j;
    do{
        e=0;
        for (i = 0; i < Data; ++i){
            computO(i);
            for (j = 0; j < Out; ++j)
                e+=fabs((OutputData[j]-d_out[i][j])/d_out[i][j]);
            backUpdate(i);
        }
        //printf("%d  %lf\n",c,e/Data);
        c++;
    }while(c<TrainC && e/Data>0.01);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    // writeTest();
    readData();
    initBPNework();
    trainNetwork();
    printf("%lf \n",result(5,5));
    printf("%lf \n",result(10,10));
    printf("%lf \n",result(20,20));
    printf("%lf \n",result(30,30));
    printf("%lf \n",result(50,50));
    printf("%lf \n",result(80,80));
    printf("%lf \n",result(100,100));
    printf("%lf \n",result(160,160));
    // printf("%lf \n",result(2.1,7) );
    // printf("%lf \n",result(4.3,8) );
    // writeNeuron();
    
    return 0;
}