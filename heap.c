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
    Vector* elementos;
    Vector* posicoes; // vetor contendo as posições dos vértices na heap (ex.: vet[0] terá o índice do vértice de id 0 na heap)
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

static void corrigeSubida(Heap* heap, int pos) {
    Vector* elementos = heap->elementos;
    Vector* posicoes = heap->posicoes;

    while(pos > 0) {
        int paiPos = pai(pos);
        HeapNode* pai = (HeapNode*) acessaElemento(elementos, paiPos);
        HeapNode* atual = (HeapNode*) acessaElemento(elementos, pos);

        if(pai->distancia <= atual->distancia) break; ; //ja esta certo

        trocaElementos(elementos, pos, paiPos);
        trocaElementos(posicoes, pai->idVertice, atual->idVertice);

        pos = paiPos;
    }
}

void insereHeap(Heap* heap, int idVertice, float distancia) {
    HeapNode* novoNode = (HeapNode*) malloc(sizeof(HeapNode));
    novoNode->idVertice   = idVertice;
    novoNode->distancia = distancia;

    int posInserido = tamanhoVetor(heap->elementos);
    insereElemento(heap->elementos, (void*) novoNode);
    insereElemento(heap->posicoes, (void*) posInserido);

    corrigeSubida(heap, posInserido);
}
