#include "dijkstra.h"

#include <stdio.h>
#include <stdlib.h>

static void relax(Node* pai, Node** aux, int idFilho, float pesoAresta) {
  float pesoPai = getNodePeso(pai);
  float pesoFilho = getNodePeso(aux[idFilho]);
  float novoPesoFilho = pesoPai + pesoAresta;

  if (pesoFilho == INFINITO || pesoFilho > novoPesoFilho) {
    setNodePeso(aux[idFilho], novoPesoFilho);
    setNodeProx(aux[idFilho], pai);
  }
}

static int visitado(Node** caminhosMinimos, int id) {
  return caminhosMinimos[id] != NULL;
}

Node** dijkstra(Grafo* grafo) {
  int numVertices = getNumVertices(grafo);
  int idOrigem = getIdOrigem(grafo);

  // Vetor auxiliar de nodes
  Node** aux = calloc(numVertices, sizeof(Node*));

  for (int i = 0; i < numVertices; i++) {
    if (i == idOrigem)
      aux[i] = criaNode(i, 0, NULL);
    else
      aux[i] = criaNode(i, INFINITO, NULL);
  }

  Node** caminhosMinimos = calloc(numVertices, sizeof(Node*));

  while (1) {
    Node* min = NULL;
    int indexMin = -1;

    // Busca o menor o no de menor peso
    for (int i = 0; i < numVertices; i++) {
      if (!visitado(caminhosMinimos, i) && (min == NULL || getNodePeso(aux[i]) < getNodePeso(min))) {
        min = aux[i];
        indexMin = i;
      }
    }

    // Se nao existir mais um menor no ainda nao visitado, encerra o loop
    if (indexMin == -1)
      break;

    caminhosMinimos[indexMin] = min;

    // Remove no do vetor auxiliar
    aux[indexMin] = NULL;

    Node* adjacentes = getAdjacentes(grafo, min);
    for (Node* n = adjacentes; n != NULL; n = getNodeProx(n)) {
      int idN = getNodeId(n);
      if (!visitado(caminhosMinimos, idN))
        relax(min, aux, idN, getNodePeso(n));
    }
  }

  free(aux);
  return caminhosMinimos;
}