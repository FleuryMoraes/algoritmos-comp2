#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "operacoes.h"
#include <math.h>
#include <string.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

 void reverse(char s[]){
     int i, j;
     char c;
     for (i = 0, j = strlen(s)-1; i<j; i++, j--){
        c = s[i];
        s[i] = s[j];
        s[j] = c;
     }
 }

 void itoa(int n, char s[]){
     int i, sign;
     if ((sign = n) < 0) 
         n = -n;          
     i = 0;
     do {       
         s[i++] = n % 10 + '0';    
     } while ((n /= 10) > 0);     
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
} 

char* multiplicacao(const char* str1, const char* str2){
    //testar a multiplicação antes de meter no katsuraba;
    int tam1, tam2;
    tam1 = strlen (str1);
    tam2 = strlen (str2);
    int strfn = 0;
    char *strf;
    //aqui escrevemos uma string que recebe a multiplicação;
    strf = (char*) malloc (1 + max (strlen(str1), strlen(str2)) * 2);
    //atoi recebe apenas char*, entao eu tenho que criar o arr;
    char arr[2];
    arr[1] = '\0';
    for (int i = 0; i < tam1; i++){
        arr[0] = str1[i];
        int num1 = atoi (arr);
        num1 = num1 * pow (10, tam1-i-1);
        for (int j = 0; j< tam2; j++){
            arr[0] = str2[j];
            int num2 = atoi (arr);
            num2 = num2 * num1;
            num2 = num2 * pow (10, tam2-j-1);
            strfn += num2;
        }
    }
    //transformando o resultado da multiplicação pra string;
    itoa (strfn, strf);
    return strf;
}

int main() {
    char str1[3] = "24";
    char str2[3] = "30";
    char *strf = multiplicacao (str1, str2);
    printf ("%s\n", strf);

    // Inicialização

    // Entrada (2 números inteiros positivos de até 10000 dígitos)

    // Execução de multiplicação convencional e medição de tempo

    // Execução de Karatsuba e medição de tempo
}
