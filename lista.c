#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "estruturas.h"

lista* lista_criar (int k){//dupla linked list;
    lista *list = (lista*) malloc (sizeof (lista));
    
    if (list == NULL){
        printf ("erro pra alocar\n");
        exit(1);
    }

    list->tamanho = 0;
    list->max = k;
    list->nodulo1 = NULL;

    return list;
}

void lista_apagar (lista *list){
    while (list->nodulo1 != NULL){//livra os ponteiros com as diferenças;
        while (list->nodulo1->nodulo2 != NULL){//livra os ponteiros com os nomes;
            free (list->nodulo1->nodulo2->nome);
            list->nodulo1->nodulo2->nome = NULL;
            
            pessoa *tmp;
            tmp = list->nodulo1->nodulo2->next2;

            list->nodulo1->nodulo2->next2 = NULL;
            free (list->nodulo1->nodulo2);
            list->nodulo1->nodulo2 = tmp;
            tmp = NULL;
        }
        nota *tmp;
        tmp = list->nodulo1->next;

        list->nodulo1->next = NULL;
        free (list->nodulo1);

        list->nodulo1 = tmp;
        tmp = NULL;
    }
    free (list);
    list = NULL;
}

void lista_inserir (char *aluno, int diff, lista *list){
    //percorrer a lista ordenadamente;
    list->tamanho++;
    nota *tmp;
    tmp = list->nodulo1;
    
    if ((list->tamanho) == 0){//se vazia, inseir diretamente;
        tmp->diferenca = diff;
        tmp->next = NULL;
        strcpy (tmp->nodulo2->nome, aluno);
        tmp->nodulo2->next2 = NULL;
    }else{
        while (diff < tmp->diferenca){
            tmp = tmp->next;
        }
        if (diff == tmp->diferenca){//se igual, criar novo nódulo2 (nome) e inserir lexicograficamente;
            pessoa *new = (pessoa*) malloc (sizeof (pessoa));
            pessoa *tmp2;
            strcpy (new->nome, aluno);
            new->next2 = tmp->nodulo2;

            while (strcmp (aluno, new->next2->nome) > 0){
                tmp2 = new->next2;
                new->next2 = new->next2->next2;
            }
            tmp2->next2 = new;

            tmp2 = NULL;
            tmp = NULL;
        }else{//se diferente, criar novo nódulo1 (nota) e inserir a pessoa;
            nota *new = (nota*) malloc (sizeof (nota));
            new->diferenca = diff;
            new->next = NULL;

            new->nodulo2 = (pessoa*) malloc (sizeof (pessoa));
            new->nodulo2->next2 = NULL;
            strcpy (new->nodulo2->nome, aluno);

            tmp->next = new;
        }
    }
}
