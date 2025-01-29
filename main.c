#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listAdj.h"
#include "heap.h"
#include "node.h"
#include "dijkstra.h"

int main() {
    
    ListAdj* grafo = criaListaAdj();
    FILE* arqEntrada = fopen("./casos_teste_v3/caso_teste_muito_pequeno_1.txt", "r");
    preencheListaAdj(arqEntrada, grafo);
    fclose(arqEntrada);

    Node** caminhosMinimos = dijkstra(grafo);
    for(int i = 0; i < getNumVertices(grafo); i++) {
        Node* noAtual = caminhosMinimos[i];
        printf("Id: %d, dist. mín.: %0.2f\n", getNodeId(noAtual), getNodePeso(noAtual));
    }

    destroiListaAdj(grafo);

    return 0;
}