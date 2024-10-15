#include <stdio.h>
#include <stdlib.h>
#include "estrutura.h"
#include <string.h>
#include "radix.h"
#include <math.h>

//precisa trocar de posição as duas colunas;
void swap(item **it1, item **it2) {
    item *tmp = *it1; 
    *it1 = *it2;       
    *it2 = tmp;       
}

void stooge_sort (item **naipes, int menor, int maior, int exp){
    if (menor >= maior){
        return;
    }

    if (naipes[menor][exp].chave > naipes[maior][exp].chave){
        swap (&naipes[menor], &naipes[maior]);
    }

    if (1+menor >= maior){
        return;
    }else{//se há mais de 3 elementos no vetor, chamar recursão;
        int y = (int)((maior - menor + 1) / 3);
        stooge_sort (naipes, menor, maior - y, exp);
        stooge_sort (naipes, menor + y, maior, exp);
        stooge_sort (naipes, menor, maior - y, exp);
    }
}

void stooge (item **naipes, int size_cartas, int num_bar){
    for (int h = size_cartas; h >= 0; h--){
        stooge_sort (naipes, 0, num_bar-1, h);
    }

    for (int p = 0; p < num_bar; p++){//printando os elementos após o stooge estar concluido;
        for (int l = 0; l < size_cartas + 1; l++){
                if (l == 0){
                    char *hell = item_naipe (&(naipes[p][l]));
                    printf ("%s ", hell);
                }else{
                    printf ("%c", naipes[p][l].simbolo);
                }
            }
            printf(";");
        }
    printf ("\n");
}