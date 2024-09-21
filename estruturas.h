#ifndef ESTRUTURA_H
#define ESTRUTURA_H

typedef struct student{
    int nota;
    char nome[50];
}aluno;

typedef struct nodulo{
    aluno *estudante;
    struct nodulo *next;
}no;

typedef struct list{
    int tamanho;
    int max;
    no* inicio;
} lista;

#endif