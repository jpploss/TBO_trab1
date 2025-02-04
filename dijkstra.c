#include "dijkstra.h"
#include <stdlib.h>
#include <stdio.h>

static void relax(Node* pai, int idFilho, ListAdj* grafo, Heap* heap) {
    float pesoPai = getNodePeso(pai);
    float pesoFilhoHeap = getPesoHeap(heap, idFilho);
    float novoPesoFilho = pesoPai + getPesoAresta(grafo, getNodeId(pai), idFilho);

    if(pesoFilhoHeap == INFINITO || pesoFilhoHeap > novoPesoFilho) {
        atualizaDistanciaEPai(heap, idFilho, pai, novoPesoFilho);
    }
}

static int visitado(Node** caminhosMinimos, int id) {
    return caminhosMinimos[id] != NULL;
}

Node** dijkstra(ListAdj* grafo) {
    
    // inicializa a heap
    int numVertices = getNumVertices(grafo);
    Heap* heap = criaHeap(numVertices);
    int idOrigem = getIdOrigem(grafo);
    for(int i = 0; i < numVertices; i++) {
        if(i == idOrigem) insereHeap(heap, i, 0, NULL);
        else insereHeap(heap, i, INFINITO, NULL);
    }

    Node** caminhosMinimos = calloc(numVertices, sizeof(Node*)); // as posições contendo NULL é porque o nó ainda não foi visitado
    while(getTamAtualHeap(heap) > 0) {
        Node* min = extraiMenorElemento(heap);
        int idMin = getNodeId(min);
        
        caminhosMinimos[idMin] = min;
        int numAdjacentes = getNumAdjacentes(grafo, min);
        Node* adjacentesMin = getAdjacentes(grafo, min);
        for(Node* n = adjacentesMin; n != NULL; n = getNodeProx(n)) {
            int idN = getNodeId(n);
            if(!visitado(caminhosMinimos, idN))
                relax(min, idN, grafo, heap);
        }
    }

    destroiHeap(heap);
    return caminhosMinimos;
}