#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "estruturas.h"
#include "lista.h"

typedef struct informacao{//usada para ler as linhas do arquivo;
    char nome[51];
    int diff;
}info;

info* ler_linha (char *buffer){//responsável por pegar a linha do file e devolver uma struct utilizável para o programa;
    info *estudante = (info*) malloc (sizeof (info));
    estudante->diff = 0;
    char *token;
    int i;
    token = strtok(buffer, ",");
    
    for (i = 0; i < 4; i++){
        switch (i){
            case 0: strcpy(estudante->nome, token); 
                break;
            case 1: (estudante->diff) -= (int) 10*(atof (token));
                break;
            case 3: (estudante->diff) += (int) 10*(atof (token));    
                break;
        }
        token = strtok(NULL, ",");    
    }
    return estudante;
}

lista* receber_input (void){
    FILE *fp;
    lista *list;
    char buffer[80];//pra ler input;
    int k;
    scanf ("%s %d", buffer, &k);

    list = lista_criar (k);
    if (list == NULL){
        printf ("erro na alocação da fila\n");
        exit (1);
    }

    fp = fopen (buffer, "r");
    if (fp == NULL){
        printf ("erro no arquivo\n");
        exit(1);
    }

    fgets (buffer, sizeof (buffer), fp);//pula 1° linha

    while (fgets (buffer, sizeof (buffer),fp)){//armazenando tudo na lista;
        info* tmp = (info*) malloc (sizeof (info));
        tmp = ler_linha (buffer);
        lista_inserir (tmp->nome, tmp->diff, list);

        free (tmp);
        tmp = NULL;
    }

    fclose (fp);
    return list;
}

void printar_resultado (lista *list){
    int count = list->max;
    nota* tmp;
    tmp = list->nodulo1;

    while ((tmp != NULL) && (count > 0)){
        while ((tmp->nodulo2 != NULL) && (count > 0)){
            printf ("%s\n", tmp->nodulo2->nome);
            tmp->nodulo2 = tmp->nodulo2->next2;
            count--;
        }
        tmp = tmp->next;
    }
}

int main (void){
    lista *list = receber_input ();
    printar_resultado (list);

    lista_apagar (list);
    return 0;
}