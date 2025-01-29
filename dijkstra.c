#include "dijkstra.h"
#include <stdlib.h>
#include <stdio.h>

static void relax(Node* pai, Node* filho, ListAdj* grafo, Heap* heap) {
    float pesoPai = getNodePeso(pai);
    float pesoFilho = getNodePeso(filho);
    float novoPesoFilho = pesoPai + getPesoAresta(grafo, pai, filho);

    if(pesoInfinito(filho) || pesoFilho > novoPesoFilho) {
        printf("Tinha que relaxa nó %d\n", getNodeId(filho));
        setNodePai(filho, pai);
        atualizaDistancia(heap, filho, novoPesoFilho);
    }
}

Node** dijkstra(ListAdj* grafo) {
    // inicializa a heap
    int numVertices = getNumVertices(grafo);
    Heap* heap = criaHeap(numVertices);
    int idOrigem = getIdOrigem(grafo);
    for(int i = 0; i < numVertices; i++) {
        if(i == idOrigem) insereHeap(heap, i, 0, NULL);
        else insereHeap(heap, i, INFINITO, NULL); // -1 será utilizado como infinito
    }


    Node** caminhosMinimos = malloc(numVertices*sizeof(Node*));
    int nosVisitados = 0;
    while(getTamAtualHeap(heap) > 0) {
        Node* min = extraiMenorElemento(heap);
        caminhosMinimos[nosVisitados] = min;
        nosVisitados++;

        int numAdjacentes = getNumAdjacentes(grafo, min);
        Node** adjacentesMin = getAdjacentes(grafo, min);
        for(int v = 0; v < numAdjacentes; v++) {
            relax(min, adjacentesMin[v], grafo, heap);
        }
    }

    return caminhosMinimos;
}