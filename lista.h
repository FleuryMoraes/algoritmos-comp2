#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include "estruturas.h"

lista* lista_criar (int k);
void lista_apagar (lista *list);
void lista_inserir (char *aluno, int diff, lista *list);


#endif