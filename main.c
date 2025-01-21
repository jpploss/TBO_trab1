#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listAdj.h"

int main() {
    listAdj* l = criaListaAdj();
    FILE* arq = fopen("./casos_teste_v3/caso_teste_muito_pequeno_2.txt", "r");
    preencheListaAdj(arq, l);

    fclose(arq);
    destroiListAdj(l);

    return 0;
}