#include <stdio.h>
#include <stdlib.h>
#include "estrutura.h"
#include <string.h>

//cria a chave pra ordenação com base no símbolo de input; 
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
        default:
            printf("simbolo proibido\n");
            break;    
    }
}

void set_chave_naipe (item *elemento){
    switch (elemento->simbolo){
        case 'o':
            elemento->chave = 0;
            break;
        case 'e':
            elemento->chave = 1;
            break;
        case 'c':
            elemento->chave = 2;
            break;
        case 'p':
            elemento->chave = 3;
            break;
        default:
            printf ("imbolo proibido\n");
            break;                
    }
}

//cria o simbolo com base na chave de input;
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
        default:
            printf ("chave proibida\n");
            break;    
    }
}

void set_symbol_naipe (item *elemento){
    switch (elemento->chave){
        case 0:
            elemento->chave = 'o';
            break;
        case 1:
            elemento->chave = 'e';
            break;
        case 2:
            elemento->chave = 'c';
            break;
        case 3:
            elemento->chave = 'p';
            break;
        default:
            printf ("simbolo proibido\n");
            break;                
    }
}

//as duas funções abaixo traduzem entre naipe e item;
item* naipe_item (char *input){
    item *result = (item*) malloc (sizeof (item));
    const char *espadas = "♠";
	const char *ouros = "♦";
	const char *copas = "♥";
	const char *paus = "♣";
    if (strcmp (ouros, input) == 0){
        result->simbolo = 'o';
        result->chave = 0;
    }
    if (strcmp (espadas, input) == 0){
        result->simbolo = 'e';
        result->chave = 1;
    }
    if (strcmp (copas, input) == 0){
        result->simbolo = 'c';
        result->chave = 2;
    }
    if (strcmp (paus, input) == 0){
        result->simbolo = 'p';
        result->chave = 3;
    }
    return (result);
}

char* item_naipe (item *input){
    const char *espadas = "♠";
	const char *ouros = "♦";
	const char *copas = "♥";
	const char *paus = "♣";
    if (input->chave == 0){
        return ((char*) ouros);
    }
    if (input->chave == 1){
        return ((char*) espadas);
    }
    if (input->chave == 2){
        return ((char*) copas);
    }
    if (input->chave == 3){
        return ((char*) paus);
    }
    return NULL;
}

//cria uma matriz de itens: cada linha é um baralho, e cada coluna, as cartas que contém;
item** ler_input (int size_cartas, int num_bar){
    //reservando uma matriz pra ler os inputs;
    item **matriz;
    matriz = (item**) malloc (sizeof (item*) * num_bar);
    for (int k = 0; k < num_bar; k++){
        matriz[k] = (item*) malloc (sizeof (item) * (size_cartas + 1));//+1 pra guardar o naipe;
    }

    //lendo o input;
    char* tmp = (char*) malloc (sizeof (char) * 4);//vai ler o naipe;
    char* temp = (char*) malloc (sizeof (char) * size_cartas);//vai ler os dígitos;
    for (int i = 0; i < num_bar; i++){
        scanf (" %s", tmp);
        item *symbol = naipe_item (tmp);
        matriz[i][0].simbolo = symbol->simbolo;
        matriz[i][0].chave = symbol->chave;
        free (symbol);
        symbol = NULL;
        scanf (" %s", temp);
        for (int j = 1; j < (size_cartas + 1); j++){
            matriz[i][j].simbolo = temp[j-1];
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
    for (int i = (num_bar - 1); i >= 0; i--){
        new[count[naipes[i][exp].chave] - 1] = i; 
        count[naipes[i][exp].chave]--;
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
    free (count);
    count = NULL;
}

//a cada loop do for, desce uma camada do baralho pra ordenar;
void radix_sort (item **naipes, int size_cartas, int num_bar){
    for (int h = size_cartas; h >= 0; h--){//bottom to top (LSD);
        count_sorting (naipes, num_bar, h);

        if (h == 0){
            printf ("Após ordenar por naipe:\n");
        }else{
            printf ("Após ordenar o %d° dígito dos valores:\n", h);
        }

        for (int p = 0; p < num_bar; p++){//printando os elementos após enésimo count-sorting;
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
}