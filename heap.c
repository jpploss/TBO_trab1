#include "heap.h"
#include <stdlib.h>

/*
Ideia: em vez de remover da heap, podemos ir jogando para as posições finais do vetor 'elementos' e ir diminuindo o 
tamanho útil desse vetor, daí no final teríamos um vetor com todos os vértices e suas distâncias mínimas para a origem.
*/

typedef struct {
    int idVertice; // ID do vértice (na prática, corresponde à posição do vértice no vetor da lista de adjacência)
    float distancia;
} HeapNode;

struct _heap {
    HeapNode** elementos;
    int* posicoes; // vetor contendo as posições dos vértices na heap (ex.: vet[0] terá o índice do vértice de id 0 na heap)
    int tamAtual;
};

Heap* criaHeap(int numVertices) {
    Heap* heap = (Heap*) malloc (sizeof(Heap));
    heap->elementos = malloc(sizeof(HeapNode*)*numVertices);
    heap->posicoes = malloc(sizeof(int)*numVertices);
    heap->tamAtual = 0;

    return heap;
}

// índice do pai
static int pai(int i) {
    return (i - 1) / 2;
}

// índice do filho da esquerda
static int esquerdo(int i) {
    return 2*i + 1;
}

// índice do filho da direita
static int direito(int i) {
    return 2*i + 2;
}

static int corrigeSubida(Heap* heap, int pos) {
    HeapNode** elementos = heap->elementos;
    int* posicoes = heap->posicoes;

    while(pos > 0) {
        int paiPos = pai(pos);
        HeapNode* pai = elementos[paiPos];
        HeapNode* atual = elementos[pos];

        if(pai->distancia <= atual->distancia) break; // já esta certo

        HeapNode* temp = elementos[pos];
        elementos[pos] = elementos[paiPos];
        elementos[paiPos] = temp;

        int temp = posicoes[pai->idVertice];
        posicoes[paiPos] = posicoes[atual->idVertice];
        posicoes[atual->idVertice] = temp;

        pos = paiPos;
    }

    return pos;
}

void insereHeap(Heap* heap, int idVertice, float distancia) {
    HeapNode* novoNode = (HeapNode*) malloc(sizeof(HeapNode));
    novoNode->idVertice   = idVertice;
    novoNode->distancia = distancia;

    int posInserido = heap->tamAtual;
    heap->elementos[posInserido] = novoNode;
    int posCorrigida = corrigeSubida(heap, posInserido);
    heap->posicoes[idVertice] = posCorrigida;
}

void destroiHeap(Heap* heap) {
    if(heap == NULL) return;

    if(heap->posicoes != NULL) free(heap->posicoes);
    for(int i = 0; i < heap->tamAtual; i++) 
        free(heap->elementos[i]);
    free(heap->elementos);
    free(heap);
}