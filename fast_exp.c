#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long exp_tradicional (long long base, long long expoente);
long long exp_rapida (long long base, long long expoente);

int main (void){
    //inicializando as variáveis que serão utilizadas
    long long expoente, base; //tipo 'int' suporta até 4 bytes, armazenando com sucesso 'n' e 'k' (base e expoente, respectivamente)
    clock_t t1, t2;
    scanf ("%lld %lld", &base, &expoente);

    //comparando os algoritmos de exponenciação
    t1  = clock ();
    printf ("exponenciação usual: %d\n", exp_tradicional (base, expoente));
    t2 = clock ();
    printf ("tempo consumido: %lfs\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    t1 = clock ();
    printf ("%lld\n", exp_rapida (base % 10000, expoente % 10000));
    t2 = clock ();
    printf ("tempo consumido: %lfs\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    return 0;   
}

long long exp_tradicional (long long base, long long expoente){
    long long aux = base;
    while (expoente > 1){
        base = ((base * aux) % 10000);
        expoente--;
    }
    return base;
}

long long exp_rapida (long long base, long long expoente){
    //qualquer número elevado a 0 é igual a 1; tratamos desse caso de imediato
    if (expoente == 0) return 1;

    //marca o fim da recursão e o início das multiplicações
    if (expoente == 1) return base;

    //começa a recursão; como base < 10⁴, a operação 'mod' só precisa ser aplicada a partir daqui
    if (expoente % 2 == 1){
        return ((exp_rapida (base, expoente/2) * exp_rapida (base, expoente/2) * base) % 10000);
    }else{
        return ((exp_rapida (base, expoente/2) * exp_rapida (base, expoente/2)) % 10000);
    }
}
