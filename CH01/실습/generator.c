/*
    Random text file generator
    based on alphabetic frequency

    Usage : gcc generator.c -o generator
            generator num
    Var : num is used to set how many numbers of alphabet generate 

Frequency : 
E 12.7  T 9.1   A 8.2   O 7.5   I 7.0   N 6.7
S 6.3   H 6.1   R 6.0   D 4.3   L 4.0   C 2.8
U 2.8   M 2.4   W 2.3   F 2.2   G 2.0   Y 2.0
P 1.9   B 1.5   V 1.0   K 0.08  J 0.02  Q 0.01
X 0.01  Z 0.01
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALP_NUM 26
#define SEED 100

char probToChar(double p, double * cdf);

int main(int argc, char *argv[])
{
    FILE * fp;    
    int num, i;
    double freq_ary[ALP_NUM] = {
        8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0, 6.1, 7.0, 0.02,
        0.08, 4.0, 2.4, 6.7, 7.5, 1.9, 0.01, 6.0, 6.3, 9.1,
        2.8, 1.0, 2.3, 0.01, 2.0, 0.01
    }; // Static Array to store frequency of alphabets
    double cdf[ALP_NUM] = {0,}; // cumulative distribution function values
    double sum = 0.0; // sum of frequencies
    double max=32767, temp_prob;
    char temp_char;

    // Input Setting
    if ( argc != 2 || ( strcmp(argv[1], "0") && atoi(argv[1]) == 0) ) {
        fprintf(stderr, "Usage : generator num\n");
        exit(EXIT_FAILURE);
    }

    num = atoi(argv[1]);

    // Calculating sum and cdf
    for (i = 0 ;i < ALP_NUM ; i ++)
        sum += freq_ary[i];
    cdf[0] = freq_ary[0];
    for (i = 1 ;i < ALP_NUM ; i ++) 
        cdf[i] = cdf[i-1] + freq_ary[i];
    


    
    // Writiing
    srand(SEED);
    if ( (fp = fopen("plaintext.txt","w")) == NULL ) {
        fprintf(stderr, "Wrong file name!\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0 ; i < num ;i ++) {
        temp_prob = ((double)rand() / max) * sum;
        temp_char = probToChar(temp_prob, cdf);
        fputc(temp_char, fp);
    }

    fclose(fp);
    printf("Complete\n");

    return EXIT_SUCCESS;
}
char probToChar(double p, double * cdf)
{
    int i;

    for (i = 0 ;i < ALP_NUM ;i ++)
        if (p <= cdf[i]) 
            break;
    
    return 'A' + i;
}