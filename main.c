#include <stdlib.h>
#include <stdio.h>
#include "radix.h"
#include "time.h"

int main (void) {
	int num_bar, size_cartas;
	scanf ("%d %d", &num_bar, &size_cartas);
	item **matriz =  ler_input (size_cartas, num_bar);
	if (matriz == NULL){
		printf ("erro com alocação\n");
		exit(1);
	}

	//printando a ordem no início;
	for (int i = 0; i < num_bar; i++){
		for (int j = 0; j < size_cartas+1; j++){
			printf ("%c", matriz[i][j].simbolo);
			if(j==0){
				printf(" ");
			}
		}
		printf(";");
	}
	printf("\n");

	radix_sort (matriz, size_cartas, num_bar);

	return 0;
}