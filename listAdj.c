#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listAdj.h"

typedef struct _adjacente adjacente;
struct _adjacente {
    int id; // id do vértice adjacente (corresponde à posição no vetor 'vertices' de 'listAdj')
    float peso; // custo da conexão
    adjacente* prox;
};

typedef struct _vertice vertice;
struct _vertice {
    char nome[31];
    int numAdjacentes;
    adjacente* adjacentes; // lista simplesmente encadeada sem sentinela contendo os adjcentes
};

struct _listAdj {
    vertice** vertices;
    int idVerticeOrigem;
    int numVertices;
};

listAdj* criaListaAdj() {
    listAdj* lAdj = malloc(sizeof(listAdj));
    lAdj->numVertices = 0;
    lAdj->idVerticeOrigem = -1;
    lAdj->vertices = NULL;

    return lAdj;
}

static int contaVertices(FILE* arqEntrada) {
    fscanf(arqEntrada, "%*[^\n]\n"); // tira a primeira, que diz o nome do vértice de origem
    fscanf(arqEntrada, "%*[^,],"); // tira o nome do vértice 0
    
    char aux = 0;
    int numVertices = 1;
    while(1) {
        fscanf(arqEntrada, "%*[^,\n]");
        numVertices++; // para cada peso lido (correspondente a um vértice), 'numVertices' é incrementado 

        fscanf(arqEntrada, "%c", &aux);
        if(aux == '\n') break; // sai do loop caso tenha alcançado o fim da linha      
    }  

    rewind(arqEntrada); // reseta o ponteiro do arquivo para o início

    return numVertices;
}

void preencheListaAdj(FILE* arqEntrada, listAdj* lAdj) {
    lAdj->numVertices = contaVertices(arqEntrada);
    lAdj->vertices = malloc(sizeof(vertice*) * lAdj->numVertices);

    char nomeVerticeOrigem[31];
    fscanf(arqEntrada, "%[^\n]\n", nomeVerticeOrigem);

    for(int v = 0; v < lAdj->numVertices; v++) {
        vertice* verticeAtual = malloc(sizeof(vertice));
        lAdj->vertices[v] = verticeAtual;
        
        fscanf(arqEntrada, "%[^,], ", verticeAtual->nome); // lê nome do vértice atual
        verticeAtual->numAdjacentes = 0;
        verticeAtual->adjacentes = NULL; // a lista de vértices adjacentes começa vazia

        if(strcmp(nomeVerticeOrigem, verticeAtual->nome) == 0) lAdj->idVerticeOrigem = v;

        for(int adj = 0; adj < lAdj->numVertices; adj++) { // lê os vizinhos do vertice atual
            if(adj == v) continue;

            float peso = 0.0;
            if(fscanf(arqEntrada, "%f", &peso) != 1) 
            // caso não seja possível ler um float, presume-se que há a string "bomba", indicando ausência de conexão entre vértices
                fscanf(arqEntrada, "%*[^,\n]"); // elimina a string "bomba"
            
            fscanf(arqEntrada, "%*c"); // elimina ',' ou '\n'

            if(peso == 0.0) continue;
            // como definido, caso o custo de acesso (peso) seja zero, assume-se que não há conexão entre os vértices

            adjacente* verticeAdjacente = malloc(sizeof(adjacente));
            verticeAdjacente->peso = peso;
            verticeAdjacente->id = adj;

            // insere 'verticeAdjacente' no início da lista de adjacência de 'verticeAtual'
            verticeAdjacente->prox = verticeAtual->adjacentes;
            verticeAtual->adjacentes = verticeAdjacente;
            verticeAtual->numAdjacentes++;
        }
    }


    // for(int i = 0; i < lAdj->numVertices; i++) {
    //     printf("Adjcentes vértice %s:\n", lAdj->vertices[i]->nome);
    //     for(adjacente* j = lAdj->vertices[i]->adjacentes; j != NULL; j = j->prox) 
    //         printf("  id: %d, custo: %.02f\n", j->id, j->peso);
    //     printf("\n");
    // }
}

void destroiListAdj(listAdj* lAdj) {
    if(lAdj == NULL) return;

    for(int v = 0; v < lAdj->numVertices; v++) {
        adjacente* atual = lAdj->vertices[v]->adjacentes;
        while(atual != NULL) {
            adjacente* temp = atual->prox;
            free(atual);
            atual = temp;
        }
        free(lAdj->vertices[v]);
    }
    free(lAdj->vertices);
    free(lAdj);
}