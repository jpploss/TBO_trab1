#include "heap.h"

#include <stdlib.h>

/*
Ideia: em vez de remover da heap, podemos ir jogando para as posições finais do vetor 'elementos' e ir diminuindo o
tamanho útil desse vetor, daí no final teríamos um vetor com todos os vértices e suas distâncias mínimas para a origem.
*/

typedef struct {
  int idVertice;  // ID do vértice (na prática, corresponde à posição do vértice no vetor da lista de adjacência)
  float distancia;
} HeapNode;

struct _heap {
  HeapNode** elementos;
  int* posicoes;  // vetor contendo as posições dos vértices na heap (ex.: vet[0] terá o índice do vértice de id 0 na heap)
  int tamAtual;
};

Heap* criaHeap(int numVertices) {
  Heap* heap = (Heap*)malloc(sizeof(Heap));
  heap->elementos = malloc(sizeof(HeapNode*) * numVertices);
  heap->posicoes = malloc(sizeof(int) * numVertices);
  heap->tamAtual = 0;
  return heap;
}

// índice do pai
static int pai(int i) {
  return (i - 1) / 2;
}

// índice do filho da esquerda
static int esquerdo(int i) {
  return 2 * i + 1;
}

// índice do filho da direita
static int direito(int i) {
  return 2 * i + 2;
}

static int corrigeSubida(Heap* heap, int pos) {
  HeapNode** elementos = heap->elementos;
  int* posicoes = heap->posicoes;

  while (pos > 0) {
    int paiPos = pai(pos);
    HeapNode* pai = elementos[paiPos];
    HeapNode* atual = elementos[pos];

    if (pai->distancia <= atual->distancia) break;  // já esta certo

    HeapNode* tempNode = elementos[pos];
    elementos[pos] = elementos[paiPos];
    elementos[paiPos] = tempNode;

    int temp = posicoes[pai->idVertice];
    posicoes[paiPos] = posicoes[atual->idVertice];
    posicoes[atual->idVertice] = temp;

    pos = paiPos;
  }

  return pos;
}

static void corrigeDescida(Heap* heap, int posicao) {
  HeapNode** elementos = heap->elementos;
  int* posicoes = heap->posicoes;
  int tamAtual = heap->tamAtual;

  while (1) {
    int esq = esquerdo(posicao);
    int dir = direito(posicao);
    int menor = posicao;

    // Verifica se o filho esquerdo é menor
    if (esq < tamAtual && elementos[esq]->distancia < elementos[menor]->distancia)
      menor = esq;

    // Verifica se o filho direito é menor
    if (dir < tamAtual && elementos[dir]->distancia < elementos[menor]->distancia)
      menor = dir;

    // O menor é o próprio elemento, sai do loop
    if (menor == posicao) break;

    // Troca o elemento atual com o menor
    HeapNode* temp = elementos[posicao];
    elementos[posicao] = elementos[menor];
    elementos[menor] = temp;

    // Atualiza vetor de posicoes
    posicoes[elementos[posicao]->idVertice] = posicao;
    posicoes[elementos[menor]->idVertice] = menor;

    posicao = menor;
  }
}

void insereHeap(Heap* heap, int idVertice, float distancia) {
  HeapNode* novoNode = (HeapNode*)malloc(sizeof(HeapNode));
  novoNode->idVertice = idVertice;
  novoNode->distancia = distancia;

  int posInserido = heap->tamAtual;
  heap->elementos[posInserido] = novoNode;

  int posCorrigida = corrigeSubida(heap, posInserido);
  heap->posicoes[idVertice] = posCorrigida;

  heap->tamAtual++;
}

int extraiMenorElemento(Heap* heap) {
  if (!heap || heap->tamAtual == 0) return -1;

  HeapNode* raiz = heap->elementos[0];
  int distRaizRemovida = raiz->distancia;

  // Substitui a raiz pelo ultimo elemento
  HeapNode* ultimo = heap->elementos[heap->tamAtual - 1];
  heap->elementos[0] = ultimo;

  // Atualiza a posição do último elemento no vetor de posicoes
  heap->posicoes[ultimo->idVertice] = 0;

  // Diminui tamanho da heap
  heap->tamAtual--;

  // Corrige a descida
  corrigeDescida(heap, 0);

  free(raiz);
  return distRaizRemovida;
}

void destroiHeap(Heap* heap) {
  if (heap == NULL) return;
  if (heap->posicoes != NULL) free(heap->posicoes);
  for (int i = 0; i < heap->tamAtual; i++)
    free(heap->elementos[i]);
  free(heap->elementos);
  free(heap);
}