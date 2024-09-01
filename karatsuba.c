#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "operacoes.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

unsigned long min(unsigned long a, unsigned long b) {
    return a < b ? a:b;
}

char* strdupi(char* str, unsigned long tam){
    char* duplicated_string = (char *)malloc(tam + 1);

    memcpy(duplicated_string, str, tam);

    duplicated_string[tam] = '\0';

    return duplicated_string;
}

char* multiplicacao(const char* str1, const char* str2){
    int tam1, tam2;
    tam1 = strlen (str1);
    tam2 = strlen (str2);

    char *str_result = (char*)malloc((tam1 + tam2 + 1) * sizeof(char));

    if(str1[0] == '0' || str2[0] == '0') {
        str_result[0] = '0';
        str_result[1] = '\0';
        return str_result;
    }

    for(int i = 0; i < tam1 + tam2; ++i) str_result[i] = '0';
    str_result[tam1 + tam2] = '\0';

    int carry = 0;

    int res_pos_1 = 0;
    int res_pos_2 = 0;

    for (int i = tam1 - 1; i >= 0; --i) {
        carry = 0;
        
        int curr_1_val = str1[i] - '0';

        int res_pos_2 = 0; 

        for (int j = tam2 - 1; j >= 0; --j){
            int curr_2_val = str2[j] - '0';

            int res = curr_1_val * curr_2_val + (str_result[res_pos_1 + res_pos_2] - '0') + carry;

            carry = res/10;

            str_result[res_pos_1 + res_pos_2] = (res % 10) + '0';

            ++res_pos_2;
        }

        if (carry > 0) {
            str_result[res_pos_1 + res_pos_2] += carry;
        }

        ++res_pos_1;
    }

    int bigest_digit = tam1 + tam2;
    for(int i = tam1 + tam2 - 1; i >= 0; --i) {
        if(str_result[i] != '0') {
            bigest_digit = i;
            break;
        }
    }

    char* t_res = (char *)malloc((bigest_digit + 2) * sizeof(char));

    int it = bigest_digit;
    for (int i = 0; i <= bigest_digit; ++i) {
        t_res[i] = str_result[it];
        --it;
    }   

    t_res[bigest_digit + 1] = '\0';

    free(str_result);

    if(t_res[0] == '0')
        t_res[1] = '\0';

    return t_res;
}

char* karatsuba(char* str1, char* str2){

    if (strlen(str1) <= 1 || strlen(str2) <= 1) {
        return multiplicacao(str1, str2);
    }

    unsigned long maior_meio = min(strlen(str1), strlen(str2));
    unsigned long meio = maior_meio/2;

    unsigned long str1_cut_val = strlen(str1) - meio;
    unsigned long str2_cut_val = strlen(str2) - meio;

    char *metade_superior1 = strdupi(&str1[0], str1_cut_val);
    char *metade_inferior1 = strdupi(&str1[0] + str1_cut_val, meio);
    char *metade_superior2 = strdupi(&str2[0], str2_cut_val);
    char *metade_inferior2 = strdupi(&str2[0] + str2_cut_val, meio);

    char *tmp1 = add(metade_inferior1, metade_superior1);
    char *tmp2 = add(metade_inferior2, metade_superior2);

    char *z0 = karatsuba(metade_inferior1, metade_inferior2);
    char *z1 = karatsuba(tmp1, tmp2);
    char *z2 = karatsuba(metade_superior1, metade_superior2);

    free(metade_superior1);
    free(metade_inferior1);
    free(metade_inferior2);
    free(metade_superior2);

    return add(add(potencia_de_10(z2, (meio * 2)), potencia_de_10(sub(z1,add(z2, z0)), meio)), z0);
}

int main() {
    // Inicialização

    char *str1 = malloc(10000);
    char *str2 = malloc(10000);

    scanf(" %s %s", str1, str2);
    printf("%s\n", multiplicacao(str1, str2));
    printf("%s\n", karatsuba(str1, str2));

    free(str1);
    free(str2);

}