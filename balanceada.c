#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Pilha.h"
#include "item.h"

bool balanceada (char* sequencia){
    //checaremos se a sequencia está vazia ou não antes de prosseguir com o código;
    if (sequencia[0] != '(' && sequencia[0] != '[' && sequencia[0] != '{'){
        return false;
    }
    //criamos a pilha e os itens para prosseguir com o algoritmo;
    int count = 0;
    PILHA *pile;
    ITEM *item;
    pile = pilha_criar();
    //enquanto não chegarmos no fim da pilha (que já checamos ser não vazia), o while executa;
    while (sequencia[count] != '\0'){
        item = item_criar (0, &(sequencia[count]));
        //comparamos os números ASCII dos parenteses, chaves, e colchete;
        if (pilha_vazia (pile) == true){ 
            pilha_empilhar (pile, item);
        }else{
            char* num1 = (char*)item_get_dados (pilha_topo (pile));
            char* num2 = (char*)item_get_dados (item);
            printf ("Eu li agora: %c ;No topo da pilha tem: %c\n", *num2,*num1);    
            if (*num2 != 91 && *num2 != 40 && *num2 != 123){
                //checa se o próximo é complementar ou não ao anterior;
                if (num1 == num2 - 2 || num1 == num2 - 1){
                    if (pilha_tamanho (pile) != 0){
                        pilha_desempilhar (pile);
                    }else{
                        break;
                    }      
                }else{
                    pilha_apagar (&pile);
                    item_apagar (&item);
                    printf ("NAruto\n");
                    return false;
                }
            }else{
                pilha_empilhar (pile, item);
            }
        }        
        count++;       
    }
    if (pilha_vazia (pile) == true){
        pilha_apagar (&pile);
        item_apagar (&item);
        return true;
    }else{
        pilha_apagar (&pile);
        item_apagar (&item);
        return false;
    }
}