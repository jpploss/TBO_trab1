#include "heap.h"

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

int pesoInfinito(Node* n) {
  return getNodePeso(n) == INFINITO;
}

static int corrigeSubida(Heap* heap, int pos) {
  Node** elementos = heap->elementos;
  int* posicoes = heap->posicoes;

  while (pos > 0) {
    int paiPos = pai(pos);
    Node* pai = elementos[paiPos];
    Node* atual = elementos[pos];

    if (!pesoInfinito(pai) && getNodePeso(pai) <= getNodePeso(atual)) break;  // já esta certo

    elementos[pos] = pai;
    elementos[paiPos] = atual;

    posicoes[getNodeId(pai)] = pos;
    posicoes[getNodeId(atual)] = paiPos;

    pos = paiPos;
  }

  return pos;
}

static int corrigeDescida(Heap* heap, int posicao) {
  Node** elementos = heap->elementos;
  int* posicoes = heap->posicoes;
  int tamAtual = heap->tamAtual;

  while (1) {
    int esq = esquerdo(posicao);
    int dir = direito(posicao);
    int menor = posicao;

    // Verifica se o filho esquerdo é menor
    if (esq < tamAtual && !pesoInfinito(elementos[esq]) && getNodePeso(elementos[esq]) < getNodePeso(elementos[menor]))
      menor = esq;

    // Verifica se o filho direito é menor
    if (dir < tamAtual && !pesoInfinito(elementos[dir]) && getNodePeso(elementos[dir]) < getNodePeso(elementos[menor]))
      menor = dir;

    // O menor é o próprio elemento, sai do loop
    if (menor == posicao) break;

    // Troca o elemento atual com o menor
    Node* nodePosicao = elementos[posicao];
    Node* nodeMenor = elementos[menor];
    elementos[posicao] = nodeMenor;
    elementos[menor] = nodePosicao;

    // Atualiza vetor de posicoes
    posicoes[getNodeId(nodePosicao)] = menor;
    posicoes[getNodeId(nodeMenor)] = posicao;

    posicao = menor;
  }
  return posicao;
}

void atualizaDistanciaEPai(Heap* heap, int idFilho, Node* pai, float novaDistancia) {
  int posFilho = heap->posicoes[idFilho];
  setNodePeso(heap->elementos[posFilho], novaDistancia);
  setNodeProx(heap->elementos[posFilho], pai);

  corrigeDescida(heap, posFilho);
  corrigeSubida(heap, posFilho);
}

void insereHeap(Heap* heap, int idVertice, float distancia, Node* pai) {
  Node* novoNode = criaNode(idVertice, distancia, pai);

  int posInserido = heap->tamAtual;
  heap->elementos[posInserido] = novoNode;
  heap->posicoes[idVertice] = posInserido;
  heap->tamAtual++;

  if(!pesoInfinito(novoNode)) corrigeSubida(heap, posInserido);
}

int getTamAtualHeap(Heap* heap) {
  return heap->tamAtual;
}

float getPesoHeap(Heap* heap, int id) {
  int pos = heap->posicoes[id];
  return getNodePeso(heap->elementos[pos]);
}

Node* extraiMenorElemento(Heap* heap) {
  if (!heap || heap->tamAtual == 0) return NULL;
  Node* raiz = heap->elementos[0];

  // Diminui tamanho da heap
  heap->tamAtual--;

  // Substitui a raiz pelo ultimo elemento
  Node* ultimo = heap->elementos[heap->tamAtual];
  heap->elementos[0] = ultimo;

  // Atualiza a posição do último elemento no vetor de posicoes
  heap->posicoes[getNodeId(ultimo)] = 0;

  // Corrige a descida
  corrigeDescida(heap, 0);

  return raiz;
}

void destroiHeap(Heap* heap) {
  if (heap == NULL) return;
  if (heap->posicoes != NULL) free(heap->posicoes);
  for (int i = 0; i < heap->tamAtual; i++) destroiNode(heap->elementos[i]);
  free(heap->elementos);
  free(heap);
}