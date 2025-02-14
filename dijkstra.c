#include "dijkstra.h"

#include <stdio.h>
#include <stdlib.h>

#include "linked-list.h"

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

static int comparaPesoNodes(Node* a, Node* b) {
  return (getNodePeso(a) > getNodePeso(b)) - (getNodePeso(a) < getNodePeso(b));
}

Node** dijkstra(Grafo* grafo) {
  int numVertices = getNumVertices(grafo);
  LinkedList* lista = createLinkedList();
  int idOrigem = getIdOrigem(grafo);

  for (int i = 0; i < numVertices; i++) {
    Node* novoNode = criaNode(i, i == idOrigem ? 0 : INFINITO, NULL);
    insertValue(lista, novoNode);
  }

  Node** caminhosMinimos = calloc(numVertices, sizeof(Node*));
  while (getSize(lista) > 0) {
    Node* min = removeMinNode(lista, comparaPesoNodes);
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
