#include "heap.h"

#include <stdlib.h>

/*
Ideia: em vez de remover da heap, podemos ir jogando para as posições finais do vetor 'elementos' e ir diminuindo o
tamanho útil desse vetor, daí no final teríamos um vetor com todos os vértices e suas distâncias mínimas para a origem.
*/

struct _heap {
  Node** elementos;
  int* posicoes;  // vetor contendo as posições dos vértices na heap (ex.: vet[0] terá o índice do vértice de id 0 na heap)
  int tamAtual;
};

Heap* criaHeap(int numVertices) {
  Heap* heap = (Heap*)malloc(sizeof(Heap));
  heap->elementos = malloc(sizeof(Node*) * numVertices);
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
  Node** elementos = heap->elementos;
  int* posicoes = heap->posicoes;

  while (pos > 0) {
    int paiPos = pai(pos);
    Node* pai = elementos[paiPos];
    Node* atual = elementos[pos];

    if (getNodePeso(pai) <= getNodePeso(atual)) break;  // já esta certo

    Node* tempNode = elementos[pos];
    elementos[pos] = elementos[paiPos];
    elementos[paiPos] = tempNode;

    int temp = posicoes[getNodeId(pai)];
    posicoes[paiPos] = posicoes[getNodeId(atual)];
    posicoes[getNodeId(atual)] = temp;

    pos = paiPos;
  }

  return pos;
}

static void corrigeDescida(Heap* heap, int posicao) {
  Node** elementos = heap->elementos;
  int* posicoes = heap->posicoes;
  int tamAtual = heap->tamAtual;

  while (1) {
    int esq = esquerdo(posicao);
    int dir = direito(posicao);
    int menor = posicao;

    // Verifica se o filho esquerdo é menor
    if (esq < tamAtual && getNodePeso(elementos[esq]) < getNodePeso(elementos[menor]))
      menor = esq;

    // Verifica se o filho direito é menor
    if (dir < tamAtual && getNodePeso(elementos[dir]) < getNodePeso(elementos[menor]))
      menor = dir;

    // O menor é o próprio elemento, sai do loop
    if (menor == posicao) break;

    // Troca o elemento atual com o menor
    Node* temp = elementos[posicao];
    elementos[posicao] = elementos[menor];
    elementos[menor] = temp;

    // Atualiza vetor de posicoes
    posicoes[getNodeId(elementos[posicao])] = posicao;
    posicoes[getNodeId(elementos[menor])] = menor;

    posicao = menor;
  }
}

void insereHeap(Heap* heap, int idVertice, float distancia) {
  Node* novoNode = criaNode(idVertice, distancia);

  int posInserido = heap->tamAtual;
  heap->elementos[posInserido] = novoNode;

  int posCorrigida = corrigeSubida(heap, posInserido);
  heap->posicoes[idVertice] = posCorrigida;

  heap->tamAtual++;
}

int extraiMenorElemento(Heap* heap) {
  if (!heap || heap->tamAtual == 0) return -1;

  Node* raiz = heap->elementos[0];
  int distRaizRemovida = getNodePeso(raiz);

  // Diminui tamanho da heap
  heap->tamAtual--;

  // Substitui a raiz pelo ultimo elemento
  Node* ultimo = heap->elementos[heap->tamAtual];
  heap->elementos[0] = ultimo;

  // Atualiza a posição do último elemento no vetor de posicoes
  heap->posicoes[getNodeId(ultimo)] = 0;

  // Corrige a descida
  corrigeDescida(heap, 0);

  free(raiz);
  return distRaizRemovida;
}

void destroiHeap(Heap* heap) {
  if (heap == NULL) return;
  if (heap->posicoes != NULL) free(heap->posicoes);
  for (int i = 0; i < heap->tamAtual; i++) destroiNode(heap->elementos[i]);
  free(heap->elementos);
  free(heap);
}