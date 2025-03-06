#include <stdio.h>
#include <stdlib.h>

#include "linkedList.h"
#include "node.h"
#include "grafo.h"

static void relax(Node* pai, int idFilho, float pesoAresta, LinkedList* lista) {
  float pesoPai = getNodePeso(pai);
  Node* filho = getNodeById(lista, idFilho);
  float novoPesoFilho = pesoPai + pesoAresta;

  if (getNodePeso(filho) == INFINITO || getNodePeso(filho) > novoPesoFilho) {
    setNodePeso(filho, novoPesoFilho);
    setNodeProx(filho, pai);
  }
}

static int visitado(Node** caminhosMinimos, int id) {
  return caminhosMinimos[id] != NULL;
}

Node** dijkstra(Grafo* grafo) {
  int numVertices = getNumVertices(grafo);
  LinkedList* lista = createLinkedList();
  int idOrigem = getIdOrigem(grafo);

  for (int i = 0; i < numVertices; i++) {
    if (i == idOrigem)
      insertValue(lista, criaNode(i, 0, NULL));
    else
      insertValue(lista, criaNode(i, INFINITO, NULL));
  }

  Node** caminhosMinimos = calloc(numVertices, sizeof(Node*));
  while (getSize(lista) > 0) {
    Node* min = removeMinNode(lista);
    int idMin = getNodeId(min);

    caminhosMinimos[idMin] = min;
    Node* adjacentesMin = getAdjacentes(grafo, min);
    for (Node* n = adjacentesMin; n != NULL; n = getNodeProx(n)) {
      int idN = getNodeId(n);
      if (!visitado(caminhosMinimos, idN))
        relax(min, idN, getNodePeso(n), lista);
    }
  }

  destroyLinkedList(lista);
  return caminhosMinimos;
}
