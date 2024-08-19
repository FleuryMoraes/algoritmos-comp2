
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ponto.h"
#include "circulo.h"

struct circulo_ {
    float r;
    PONTO *centro;
};

CIRCULO *circulo_criar (PONTO *p, float raio);
bool circulo_set_ponto (CIRCULO *c, PONTO *p);
bool circulo_set_raio (CIRCULO *c, float raio);
PONTO *circulo_get_ponto (CIRCULO *c);
float circulo_get_raio (CIRCULO *c);
void circulo_apagar (CIRCULO **circulo);

CIRCULO *circulo_criar (PONTO *p, float raio){
    //criaremos uma struct CIRCULO na forma de ponteiro;
    CIRCULO *circ;
    circ = malloc (sizeof(CIRCULO));
    if (circ == NULL){
        printf ("Erro na alocação dinâmica\n");
        exit(1);
    }
    circ->centro = p;
    circ->r = raio;
    return circ;
}

bool circulo_set_ponto (CIRCULO *c, PONTO *p){
    //ajustaremos um novo centro à circunferência;
    c->centro = p; //é ok fazer isso pois as duas structs sao do mesmo tipo;
    return true;
}

bool circulo_set_raio (CIRCULO *c, float raio){
    c->r = raio;
    return true;
}

PONTO* circulo_get_ponto (CIRCULO *c){
    return c->centro;
}

float circulo_get_raio (CIRCULO *c){
    float raio;
    raio = c->r;
    return raio;
}

void circulo_apagar (CIRCULO **circulo){
    //pensei bastante, e primeiro vou ter que apagar o ponto no circulo
    ponto_apagar (&((*circulo)->centro));
    free (*circulo);
    *circulo = NULL;
}