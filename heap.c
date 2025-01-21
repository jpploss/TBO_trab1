#include "heap.h"
#include <stdlib.h>

typedef struct {
    int vertice; // ID do vértice ("node_0", "node_1",..)
    float distancia;
} HeapNode;

struct _heap {
    Vector* elementos;
    Vector* posicoes; // Vetor contendo as posições dos vértices na heap (heap->elementos)
    // Exemplo: se heap->elementos = [node_0,  node_3, node_1, node_4, node_2], então heap->posicoes = [0, 2, 4, 1, 3]
};

Heap* criaHeap() {
    Heap* heap = (Heap*) malloc (sizeof(Heap));
    heap->elementos = criaVetor();
    heap->posicoes = criaVetor();
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

void insereHeap(Heap* heap, int idVertice, float distancia) {
    HeapNode* novoNode = (HeapNode*) malloc(sizeof(HeapNode));
    novoNode->vertice   = idVertice;
    novoNode->distancia = distancia;

    int posInserido = tamanhoVetor(heap->elementos);
    insereElemento(heap->elementos, (void*) novoNode);
    insereElemento(heap->posicoes, (void*) posInserido);

    // Agora "corrigeSubida" para restabelecer a propriedade de min-heap
    corrigeSubida(heap, posInserido);
}
