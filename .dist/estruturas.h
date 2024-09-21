#ifndef ESTRUTURA_H
#define ESTRUTURA_H

typedef student{
    int nota;
    char nome[50];
}aluno;

typedef nodulo{
    aluno *estudante;
    no *next;
}no;

typedef struct list{
    int tamanho;
    int max;
    no* inicio;
} lista;

#endif