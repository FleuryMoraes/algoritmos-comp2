#include <stdio.h>
#include <stdlib.h>
#include "estrutura.h"

//cria a chave pra ordenação com base no símbolo de input (ATUALIZAR P/NAIPE); 
void set_chave (item *elemento){
    switch (elemento->simbolo){
        case '4':
            elemento->chave = 0;
            break;
        case '5':
            elemento->chave = 1;
            break;
        case '6':
            elemento->chave = 2;
            break;
        case '7':
            elemento->chave = 3;
            break;
        case 'Q':
            elemento->chave = 4;
            break;
        case 'J':
            elemento->chave = 5;
            break;
        case 'K':
            elemento->chave = 6;
            break;
        case 'A':
            elemento->chave = 7;
            break;
        case '2':
            elemento->chave = 8;
            break;
        case '3':
            elemento->chave = 9;
            break;
        default://caso em que estamos lidando com o naipe; deixar pra depois!
            elemento->chave = 69;
            break;    
    }
}

//cria o simbolo com base na chave de input (ATUALIZAR P/NAIPE);
void set_symbol (item *elemento){
        switch (elemento->chave){
        case 0:
            elemento->simbolo = '4';
            break;
        case 1:
            elemento->simbolo = '5';
            break;
        case 2:
            elemento->simbolo = '6';
            break;
        case 3:
            elemento->simbolo = '7';
            break;
        case 4:
            elemento->simbolo = 'Q';
            break;
        case 5:
            elemento->simbolo = 'J';
            break;
        case 6:
            elemento->simbolo = 'K';
            break;
        case 7:
            elemento->simbolo = 'A';
            break;
        case 8:
            elemento->simbolo = '2';
            break;
        case 9:
            elemento->simbolo = '3';
            break;
        default://caso em que estamos lidando com o naipe; deixar pra depois!
            elemento->simbolo = 'g';
            break;    
    }
}

//cria uma matriz de itens: cada linha é um baralho, e cada coluna, as cartas que contém;
item** ler_input (int size_cartas, int num_bar){
    //reservando uma matriz pra ler os inputs;
    item **matriz = NULL;
    matriz = (item**) malloc (sizeof (item*) * num_bar);
    for (int k = 0; k < num_bar; k++){
        matriz[k] = (item*) malloc (sizeof (item) * (size_cartas + 1));//+1 pra guardar o naipe;
    }

    //lendo o input;
    for (int i = 0; i < num_bar; i++){
        for (int j = 0; j < (size_cartas + 1); j++){
            scanf ("%c", &(matriz[i][j].simbolo));
            set_chave (&(matriz[i][j]));
        }
    }

    return matriz;
}

//objetivo: implementar o count_sort com uma nova ordem (dada pela hierarquia do baralho)
//e usando uma matriz (tudo é no formato de caracteres);
void count_sorting (item **naipes, int num_bar, int exp){
    //criando o vetor count;
    int max = 0;
    for (int i = 0; i < num_bar; i++){
        if (naipes[i][exp].chave > max){
            max = naipes[i][exp].chave;
        }
    }
    int *count = (int*) calloc ((max + 1), sizeof (int));

    //preenche o número de vezes que o simbolo aparece;
    for (int i = 0; i < num_bar; i++){
        count[naipes[i][exp].chave]++;
    }

    //cálculo da soma de prefixos;
    for (int i = 1; i <= max; i++){
        count[i] += count[i - 1];
    }

    //criando e preenchendo um vetor que armazena as posições de troca das linhas da matriz;
    int *new = (int*) malloc (sizeof (int) * num_bar);
    item *output = (item*) malloc (sizeof (item) * num_bar);
    for (int i = (num_bar - 1); i >= 0; i--){
        output[count[naipes[i][exp].chave] - 1].chave = naipes[i][exp].chave;
        count[naipes[i][exp].chave]--;
        set_symbol (&(output[count[naipes[i][exp].chave] - 1]));

        new[count[naipes[i][exp].chave] - 1] = i; 
    }

    item **tmp = (item**) malloc (sizeof (item*) * num_bar);
    for (int i = 0; i < num_bar; i++){
        tmp[i] = naipes[i];
    }

    for (int y = 0; y < num_bar; y++){
        naipes[y] = tmp[new[y]];
        tmp[new[y]] = NULL;
    }

    free (new);
    new = NULL;
    free (tmp);
    tmp = NULL;
    free (output);
    free (count);
    count = NULL;
    output = NULL;
}

//a cada loop do for, desce uma camada do baralho pra ordenar;
void radix_sort (item **naipes, int size_cartas, int num_bar){
    for (int h = (size_cartas + 1); h >0; h--){//bottom to top (LSD);
        count_sorting (naipes, num_bar, h);
    }
}