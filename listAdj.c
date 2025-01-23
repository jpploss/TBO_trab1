#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listAdj.h"

typedef struct _adjacente Adjacente;
struct _adjacente {
    int id; // id do vértice adjacente (corresponde à posição no vetor 'vertices' de 'ListAdj')
    float peso; // custo da conexão
    Adjacente* prox;
};

typedef struct _vertice Vertice;
struct _vertice {
    char nome[31];
    int numAdjacentes;
    Adjacente* adjacentes; // lista simplesmente encadeada sem sentinela contendo os adjcentes
};

struct _listAdj {
    Vertice** vertices;
    int idVerticeOrigem;
    int numVertices;
};

ListAdj* criaListaAdj() {
    ListAdj* lAdj = malloc(sizeof(ListAdj));
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

void preencheListaAdj(FILE* arqEntrada, ListAdj* lAdj) {
    lAdj->numVertices = contaVertices(arqEntrada);
    lAdj->vertices = malloc(sizeof(Vertice*) * lAdj->numVertices);

    char nomeVerticeOrigem[31];
    fscanf(arqEntrada, "%[^\n]\n", nomeVerticeOrigem);

    for(int v = 0; v < lAdj->numVertices; v++) {
        Vertice* verticeAtual = malloc(sizeof(Vertice));
        lAdj->vertices[v] = verticeAtual;
        
        fscanf(arqEntrada, "%[^,], ", verticeAtual->nome); // lê nome do vértice atual
        verticeAtual->numAdjacentes = 0;
        verticeAtual->adjacentes = NULL; // a lista de vértices adjacentes começa vazia

        if(strcmp(nomeVerticeOrigem, verticeAtual->nome) == 0) lAdj->idVerticeOrigem = v; // verifica se vértice atual é o vértice de origem

        for(int adj = 0; adj < lAdj->numVertices; adj++) { // lê os vizinhos do vertice atual
            if(adj == v) continue;

            float peso = 0.0;

            fscanf(arqEntrada, "%f", &peso);
            fscanf(arqEntrada, "%*[^,\n]"); // elimina a string "bomba", se existir, ou algum catactere indesejado (como whitespaces)
            fscanf(arqEntrada, "%*c"); // elimina ',' ou '\n'

            if(peso == 0.0) continue;
            // como definido, caso o custo de acesso (peso) seja zero, assume-se que não há conexão entre os vértices

            Adjacente* verticeAdjacente = malloc(sizeof(Adjacente));
            verticeAdjacente->peso = peso;
            verticeAdjacente->id = adj;

            // insere 'verticeAdjacente' no início da lista de adjacência de 'verticeAtual'
            verticeAdjacente->prox = verticeAtual->adjacentes;
            verticeAtual->adjacentes = verticeAdjacente;
            verticeAtual->numAdjacentes++;
        }
    }


    for(int i = 0; i < lAdj->numVertices; i++) {
        printf("Adjcentes vértice %s:\n", lAdj->vertices[i]->nome);
        for(Adjacente* j = lAdj->vertices[i]->adjacentes; j != NULL; j = j->prox) 
            printf("  id: %d, custo: %.02f\n", j->id, j->peso);
        printf("\n");
    }
}

int getNumVertices(ListAdj* lAdj) {
    return lAdj->numVertices;
}

void destroiListaAdj(ListAdj* lAdj) {
    if(lAdj == NULL) return;

    for(int v = 0; v < lAdj->numVertices; v++) {
        Adjacente* atual = lAdj->vertices[v]->adjacentes;
        while(atual != NULL) {
            Adjacente* temp = atual->prox;
            free(atual);
            atual = temp;
        }
        free(lAdj->vertices[v]);
    }
    free(lAdj->vertices);
    free(lAdj);
}