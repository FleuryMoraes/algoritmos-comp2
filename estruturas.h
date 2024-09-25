#ifndef ESTRUTURA_H
#define ESTRUTURA_H

typedef struct PESSOA{
    char *nome;
    struct PESSOA *next2;
}pessoa;

typedef struct NOTA{
    int diferenca;
    pessoa *nodulo2;
    struct NOTA *next;
}nota;

typedef struct LISTA{
    int tamanho;
    nota *nodulo1;
    int max;
}lista;

#endif