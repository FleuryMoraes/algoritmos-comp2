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

void lista_apagar (lista *list){//sentido = início -> fim;
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
    nota *tmp;
    nota *tmp2 = NULL;
    tmp = list->nodulo1;
    bool flag = true;
    
    if ((list->tamanho) == 0){//se vazia, inseir diretamente;
        printf ("primeiro da lista\n");
        list->nodulo1 = (nota*) malloc (sizeof (nota));
        tmp = list->nodulo1;

        tmp->diferenca = diff;
        tmp->next = NULL;

        tmp->nodulo2 = (pessoa*) malloc (sizeof (pessoa));
        tmp->nodulo2->nome = (char*) malloc (sizeof(char) * 51);

        strcpy (tmp->nodulo2->nome, aluno);
        tmp->nodulo2->next2 = NULL;

        tmp = NULL;
        tmp2 = NULL;
        // printf ("nome lido: %s\n", list->nodulo1->nodulo2->nome);
    }else{
        printf ("diferenca = %d\ndiferenca armazenada = %d\n", diff, tmp->diferenca);
        while (diff < tmp->diferenca){//introduzir ordenadamente na lista;
            flag = true;
            if (tmp->next != NULL){
                tmp2 = tmp;
                tmp = tmp->next;
            }else{  
                break;
            }
        }
        if (diff == tmp->diferenca){//se igual, criar novo nódulo2 (nome) e inserir lexicograficamente;
            printf ("nota igual\n");
            pessoa *new = (pessoa*) malloc (sizeof (pessoa));
            pessoa *tmp3;
            new->nome = (char*) malloc (sizeof (char)*51);
            strcpy (new->nome, aluno);
            new->next2 = tmp->nodulo2;

            while ((new->next2 != NULL) && (strcmp (aluno, new->next2->nome) > 0)){
                tmp3 = new->next2;
                new->next2 = new->next2->next2;
            }
            tmp3->next2 = new;

            tmp2 = NULL;
            tmp3 = NULL;
            tmp = NULL;
        }else{//se diferente, criar novo nódulo1 (nota) na ponta e inserir a pessoa;
            printf ("nota nova\n");
            nota *new = (nota*) malloc (sizeof (nota));
            new->diferenca = diff;
            new->next = tmp;

            new->nodulo2 = (pessoa*) malloc (sizeof (pessoa));
            new->nodulo2->next2 = NULL;
            new->nodulo2->nome = (char*) malloc (sizeof(char) * 51);
            strcpy (new->nodulo2->nome, aluno);

            if (tmp2 != NULL){
                tmp2->next = new;
            }

            if (flag == true){
                list->nodulo1 = new;
            }

            tmp = NULL;
            tmp2 = NULL;
        }
    }

    list->tamanho++;
}
