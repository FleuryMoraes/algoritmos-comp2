#include "ponto.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

struct ponto_{
    float x;
    float y;
};

PONTO *ponto_criar (float x, float y);
void ponto_apagar (PONTO **p);
bool ponto_set (PONTO *p, float x, float y);
float ponto_get_x (PONTO *p);
float ponto_get_y (PONTO *p);
void ponto_print (PONTO *p);
float distancia (PONTO *pa, PONTO *pb);

PONTO *ponto_criar (float x, float y){
    //a função exige que devolvamos um ponteiro tipo PONTO. Logo, usaremos malloc;
    PONTO *pontinho;
    pontinho = (PONTO*)malloc(sizeof(PONTO));
    if (pontinho == NULL){
        printf ("Erro na alocação dinâmica");
        exit (1);
    }
    pontinho->x = x;
    pontinho->y = y;
    return pontinho;
}

//faz mais sentido escrever a função distância no TAD ponto pois ela relaciona dois pontos;
float distancia (PONTO *pa, PONTO *pb){
    float distancia;
    distancia = sqrt (pow (ponto_get_x(pa)-ponto_get_x(pb), 2) + pow (ponto_get_y(pa)-ponto_get_y(pb), 2));
    return distancia;
}

void ponto_apagar (PONTO **p){
    //recebemos um ponteiro para um ponteiro para struct. Devemos usar um * para desrreferenciar e
    //o primeiro ponteiro, assim usando o segundo, fazendo com que ele agora seja NULL;
    free (*p);
    *p = NULL;
}

bool ponto_set (PONTO *p, float x, float y){
    //queremos settar um ponto já criado a novos dados;
    p->x = x;
    p->y = y;
    return true;
}

float ponto_get_x (PONTO *p){
    //essas funções "get" devolvem os valores do ponto;
    float aux;
    aux = p->x;
    return aux;
}

float ponto_get_y (PONTO *p){
    float aux;
    aux = p->y;
    return aux;
}

void ponto_print (PONTO *p){
    printf ("%.1f,%.1f", p->x, p->y);
}