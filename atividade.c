#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "operacoes.h"

char* multiplicacao(const char* str1, const char* str2);

char* no_meio (char *str, unsigned long meio) {
    char *tmp = (char *)malloc(meio);

    
}

char* karatsuba(char* str1, char* str2){
        if (strlen(str1) <= 2 || strlen(str2) <= 2) {
        return ;
    }

    unsigned long maior_meio = max ( strlen(str1), strlen(str2));
    unsigned long meio = maior_meio/2;

    char *metade_superior1 = no_meio(str1, meio);
    char *metade_inferior1 = no_meio();
    char *metade_superior2 = no_meio();
    char *metade_inferior2 = no_meio();
}

int main() {
    // Inicialização

    // Entrada (2 números inteiros positivos de até 10000 dígitos)

    // Execução de multiplicação convencional e medição de tempo

    // Execução de Karatsuba e medição de tempo
}
