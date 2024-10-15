#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "estrutura.h"

item** ler_input (int size_cartas, int num_bar);
void radix_sort (item **naipes, int size_cartas, int num_bar);
char* item_naipe (item *input);
item* naipe_item (char *input);
