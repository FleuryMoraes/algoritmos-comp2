#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include "estruturas.h"

lista *lista_criar (int size);
void inserir (aluno *pessoa, lista *list);
bool lista_cheia (lista *list);
void queimar_lista (lista *list);
void insercao_efetiva (aluno *pessoa, lista *list, int crivo);

#endif