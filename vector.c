#include "vector.h"

#include <stdlib.h>

/* Poderá ser usado para manipular a Heap e armazenar as distâncias dos vértices */

struct _vector {
    int capacidade;
    int tamanho;
    void** elementos;
};

Vector* criaVetor() {
    Vector* v = malloc(sizeof(Vector));
    v->capacidade = CAPACIDADE_INICIAL;
    v->tamanho = 0;
    v->elementos = malloc(CAPACIDADE_INICIAL * sizeof(void*));

    return v;
}

void insereElemento(Vector* v, void* elemento) {
    if (v->tamanho == v->capacidade) {
        v->capacidade *= 2; // é padrão dobrar sempre a capacidade
        v->elementos = realloc(v->elementos, v->capacidade * sizeof(void*));
    }

    v->elementos[v->tamanho] = elemento;
    v->tamanho++;
}

void* acessaElemento(Vector* v, int pos) {
    return v->elementos[pos];
}

int tamanhoVetor(Vector* v) {
    return v->tamanho;
}

void trocaElementos(Vector* v, int pos1, int pos2) {
    void* aux = v->elementos[pos1];
    v->elementos[pos1] = v->elementos[pos2];
    v->elementos[pos2] = aux;
}

void destroiVetor(Vector* v) {
    free(v->elementos);
    free(v);
}