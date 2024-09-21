#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "estruturas.h"

bool lista_cheia (lista *list){
    if (list != NULL){
        if (list->tamanho >= list->max){
            return true;
        }
    }
    return false;
}

lista *lista_criar (int size){
    lista *list = (lista*) malloc (sizeof (lista));
    if (list == NULL){
        printf ("erro em alocar a lista\n");
        exit(1);
    }
    list->tamanho = 0;
    list->max = size;
    list->inicio = NULL;
}

void insercao_efetiva (aluno *pessoa, lista *list, int crivo){
    int i = 0; 
    no* tmp = (no*) malloc (sizeof (no));
    tmp->estudante = pessoa;
    no* tmp2;
    tmp->next = list->inicio;

    if (crivo == 0){
        while ((tmp->next->estudante->nota == tmp->estudante->nota) && (strcmp (tmp->next->estudante->nome, tmp->estudante->nome) > 0)){
            tmp2 = tmp->next;
            tmp->next = tmp->next->next;
            if (tmp->next == NULL) break;
            i++;
        }
    }else{
        while ((tmp->next->estudante->nota < tmp->estudante->nota) || (strcmp (tmp->next->estudante->nome, tmp->estudante->nome) > 0)){
            tmp2 = tmp->next;
            tmp->next = tmp->next->next;
            if (tmp->next == NULL) break;
            i++;
        }
    }

    if (i == 0){
        list->inicio = tmp;//settando o ponteiro inicial pro novo primeiro elemento
    }else{
        tmp2->next = tmp;
    }

    tmp2 = NULL;
    tmp = NULL;
}

void inserir (aluno *pessoa, lista *list){//utilizar só depois da 1° inserção!! --> do contrário dá SEGFAULT (JA DEVE TER TAMANHO 1 AGORA);
    if (pessoa == NULL || list == NULL){
        printf ("lista ou item não existe!\n");
        return;
    }
    int crivo = pessoa->nota - list->inicio->estudante->nota;//nos ajudará a tomar decisões importantes de ordenação;

    if (lista_cheia (list) == false){//se a lista não estiver cheia, inserimos automaticamente, sem questionar;
        list->tamanho++;
        insercao_efetiva (pessoa, list, crivo);

    }else{//se a lista já estiver cheia, devemos tomar um certo cuidado na inserção para checar se ela se estende além do esperado (pessoas com mesmas notas);
        if (crivo < 0){//se a lista já está cheia e a nota do que se quer add for menor que a nota do último da nossa fila, não inserir; 
            return;
        }

        if (crivo == 0){//estenderemos a lita além de seu tamanho máximo, com inserção lexicográfica;
            list->tamanho++;
            insercao_efetiva (pessoa, list, crivo);

        }else{//devemos arrancar nós da lista até que seu tamanho fique MAX-1, isto é, 'lista_cheia() == false', e aí efetuar a inserção;
            while (lista_cheia(list) == true){
                list->tamanho--;

                no* tmp;
                tmp = list->inicio;

                free (tmp->estudante);
                tmp->estudante = NULL;

                list->inicio = list->inicio->next;
                free (tmp);
                tmp = NULL;
            }
            insercao_efetiva (pessoa, list, crivo);
        }
    } 
}

void queimar_lista (lista *list){
    while (list->inicio != NULL){//enquanto o temporário não chegar no fim da lista;
        no* tmp;
        tmp = list->inicio;
        free (list->inicio->estudante);//livrando o conteúdo do nó;
        list->inicio->estudante = NULL;
        list->inicio = list->inicio->next;//passando o ponteiro do começo da lista para o próximo;
        free (tmp);//livrando o nó ao dar free () no ponteiro temporário que aponta pra ele;
        tmp = NULL;
    }
    free (list);//liberando o ponteiro pra lista;
    list = NULL;
}