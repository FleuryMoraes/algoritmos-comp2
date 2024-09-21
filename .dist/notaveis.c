#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "estruturas.h"
#include "lista.h"

//declarando nossas funções;
void ler_input (int k, FILE *fp);
aluno* ler_linha (char buffer[50]);
void buscar_nerds (int k, FILE *fp, lista *list);
void printar_nerds (lista* list);

int main (void){
    int k;//numero de pessoas com maxima diferença de notas;
    FILE *fp;//ponteiro para acessar o nosso file CSV;
    ler_input (k, fp);
    lista *list = lista_criar (k);
    buscar_nerds (k, fp, list);//buscamos as pessoas requeridas e armazenamos na nossa lista;
    printar_nerds (list);//printamos o resultado;
    queimar_lista (list);
    free (fp);
    fp = NULL;

    return 0;
}

void ler_input (int k, FILE *fp){
    char buffer[50];//armazenará o nome do file;
    scanf ("%s %d", buffer, k);//ATENÇÃO
    fp = fopen (buffer, "r");
    if (fp == NULL){
        printf ("erro na abertura do arquivo!\n");
        exit(1);
    }
}

aluno* ler_linha (char *buffer){//responsável por pegar a linha do file e devolver uma struct utilizável para o programa;
    aluno *estudante = (*aluno) malloc (sizeof (aluno));
    char *token;
    int i;
    for (i = 0; i < 4; i++){
        token = strtok(buffer, ",");
        switch (i){
            case 0: estudante->nome = token;
                break;
            case 1: estudante->nota -= 10*(atoi (token));
                break;
            case 3: estudante->nota += 10*(atoi (token));    
                break;
        }    
    }
    return estudante;
}

void buscar_nerds (int k, FILE *fp, lista *list){//criará a lista desejada;
    char buffer[70];//ATENÇÃO;
    char *ptr;//descartável;
    ptr = fgets (buffer, 70, fp);//descartando a primeira linha (lixo);
    ptr = fgets (buffer, 70, fp);
    list->inicio = ler_linha (buffer);//armazenando a 1° pessoa na fila;

    while (!feof(fp) && fgets (buffer, 70, fp)){
        inserir (list, ler_linha (buffer));
    }
} 

void printar_nerds (lista* list){//printa em ordem crescente
    no* tmp;//criando um ponteiro para "nó" a fim de percorrer a lista e printar os resultados;
    tmp = list->inicio;
    while (tmp != NULL){
        printf ("%s\n", tmp->estudante->nome);
        tmp = tmp->next;
    }
}