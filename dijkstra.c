#include "dijkstra.h"

#include <stdio.h>
#include <stdlib.h>

#include "linked-list.h"

static void relax(Node* pai, Node* filho, float pesoAresta) {
  float pesoPai = getNodePeso(pai);
  float pesoFilho = getNodePeso(filho);
  float novoPesoFilho = pesoPai + pesoAresta;

  if (pesoFilho == INFINITO || pesoFilho > novoPesoFilho) {
    setNodePeso(filho, novoPesoFilho);
    setNodeProx(filho, pai);
  }
}

static int visitado(Node** caminhosMinimos, int id) {
  return caminhosMinimos[id] != NULL;
}

static int comparaNodes(void* a, void* b) {
  Node* nodeA = (Node*)a;
  Node* nodeB = (Node*)b;
  if (getNodePeso(nodeA) < getNodePeso(nodeB))
    return -1;
  if (getNodePeso(nodeA) > getNodePeso(nodeB))
    return 1;
  return 0;
}

Node** dijkstra(Grafo* grafo) {
  int numVertices = getNumVertices(grafo);
  int idOrigem = getIdOrigem(grafo);

  // Lista encadeada para substituir a heap
  LinkedList* list = createLinkedList();

  for (int i = 0; i < numVertices; i++) {
    if (i == idOrigem)
      insertValue(list, criaNode(i, 0, NULL));
    else
      insertValue(list, criaNode(i, INFINITO, NULL));
  }

  Node** caminhosMinimos = calloc(numVertices, sizeof(Node*));

  while (getSize(list) > 0) {
    // Obtem o node de menor peso na lista encadeada
    Node* min = (Node*)removeMinValue(list, comparaNodes);
    int idMin = getNodeId(min);
    caminhosMinimos[idMin] = min;

    Node* adjacentes = getAdjacentes(grafo, min);
    for (Node* n = adjacentes; n != NULL; n = getNodeProx(n)) {
      int idN = getNodeId(n);
      if (!visitado(caminhosMinimos, idN))
        relax(min, n, getNodePeso(n));
    }
  }

  destroyLinkedList(list);
  return caminhosMinimos;
}