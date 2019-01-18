/*******************************************************************
* Copyright (c) www.shujuzhou.com
* File: LinearRegression.cpp
* Author: xjzhou@shujuzhou.com
* Date Created: 12/10/2018 17:39
* Date Revised: 12/10/2018 17:39
* Desc: 参考 https://blog.csdn.net/robin_xu_shuai/article/details/52878257
* Usage: 
********************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int feature_size;
int data_size;
char filename[20];
double** feature;
double* theta;
double* theta_new;

void readData()
{
    FILE* fread;
    if( NULL == (fread = fopen(filename,"r")) )
    {
        printf("open file error");
        exit(0);
    }
    if( !(feature = (double**)malloc(sizeof(double*) * data_size)) )
    {
        printf("feature** malloc error");
        exit(0);
    }
    int i;
    for( i = 0; i < data_size; i++ )
    {
        if( !(feature[i] = (double*)malloc(sizeof(double) * (feature_size + 2))) )
        {
            printf("feature[%d]* malloc error", i);
            exit(0);
        }
    }
    int j;
    for( i = 0; i < data_size; i++ )
    {
        feature[i][0] = 1.0;
        for( j = 1; j <= feature_size + 1; j++ )
        {
            if( 1 != fscanf(fread, " %lf ", &feature[i][j]) )
            {
                printf("fscanf error %d %d", i, j);
                exit(0);
            }
        }
    }
    for( i = 0; i < data_size; i++ )
    {
        for( j = 0; j <= feature_size + 1; j++ )
        {
            printf("%lf\t", feature[i][j]);
        }
        printf("\n");
    }
}
void StochasticGradientDescent()
{
    int i, j, k, conv;
    if( !(theta = (double*)malloc(sizeof(double) * (feature_size + 1))) )
    {
        printf("theta* malloc error");
        exit(0);
    }
    if( !(theta_new = (double*)malloc(sizeof(double) * (feature_size + 1))) )
    {
        printf("theta_new* malloc error");
        exit(0);
    }
    for( i = 0; i <= feature_size; i++ )
        theta[i] = theta_new[i] = 0.0;

    double diff, alpha = 0.00001;

    while(1)
    {
        for( i = 0; i < data_size; i++ )
        {
            diff = 0.0;
            for( k = 0; k <= feature_size; k++ )
            {
                diff += theta[k] * feature[i][k];
            }
            diff -= feature[i][feature_size + 1];
            for( j = 0; j <= feature_size; j++ )
            {
                diff *= feature[i][j];
                theta_new[j] = theta[j] - alpha * diff;
            }
        }

        for( i = 0; i <= feature_size; i++ )
            printf("%lf ", theta_new[i]);
        printf("\n");

        for( conv = 1, i = 0; i <= feature_size; i++ )
        {
            if( fabs(theta_new[i] - theta[i]) > 0.0002 )
            {
                conv = 0;
                break;
            }
        }
        if( 1 == conv )
        {
            break;
        }else
        {
            for( i = 0; i <= feature_size; i++ )
            {
                theta[i] = theta_new[i];
            }
        }
    }
}

int main(int argc, char** argv)
{
    if( argc != 4 )
    {
        printf("1.feature_size:\n"
            "2.data_size\n"
            "3.filename\n");
        exit(0);
    }

    feature_size = atoi(argv[1]);
    data_size = atoi(argv[2]);
    strcat(filename, argv[3]);
    printf("feature_size:%d, data_size:%d, filename: %s\n", feature_size, data_size,filename);

    readData();
    StochasticGradientDescent();
    return 0;
}

