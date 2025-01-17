#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listAdj.h"

typedef struct _vertice vertice;
struct _vertice {
    char* nome;
    float peso;
    vertice* prox;
};

struct _listAdj {
    vertice** vertices;
    vertice* origem;
    int numVertices;
};


/// @brief Cria uma lista de adjacências vazia.
/// @return Lista de adjacência vazia.
listAdj* criaListaAdj() {
    listAdj* lAdj = malloc(sizeof(listAdj));
    lAdj->numVertices = 0;
    lAdj->origem = NULL;
    lAdj->vertices = NULL;

    return lAdj;
}

static int contaVertices(FILE* arqEntrada) {

}

void preencheListaAdj(FILE* arqEntrada, listAdj* lAdj) {
    lAdj->numVertices = contaVertices(arqEntrada);
    
    char* nomeVerticeOrigem = NULL;
    fscanf(arqEntrada, "%[^\n]", nomeVerticeOrigem);
    fscanf(arqEntrada, "%*c"); // limpa o '\n'

    char* nomeVerticeAtual = NULL;
    while( fscanf(arqEntrada, "%[^,], ", nomeVerticeAtual) ) { 
    // enquanto for possível ler vértices de 'arqEntrada' o código é executado
        
    }

}