#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listAdj.h"
#include "heap.h"
#include "node.h"
#include "dijkstra.h"

int main() {
    
    ListAdj* grafo = criaListaAdj();
    FILE* arqEntrada = fopen("./casos_teste_v3/caso_teste_muito_pequeno_2.txt", "r");
    preencheListaAdj(arqEntrada, grafo);
    fclose(arqEntrada);

    Node** caminhosMinimos = dijkstra(grafo);
    for(int i = 0; i < getNumVertices(grafo); i++) {
        Node* noAtual = caminhosMinimos[i];
        printf("SHORTEST PATH TO %d: ", getNodeId(noAtual));

        for(Node* n = noAtual; n != NULL; n = getNodePai(n)) {
            printf("%d", getNodeId(n));
            if(getNodePai(n) != NULL) printf(" <- ");
            else break;
        }

        printf(" (Distance: %.02f)\n", getNodePeso(noAtual));
    }

    for(int i = 0; i < getNumVertices(grafo); i++) destroiNode(caminhosMinimos[i]);
    free(caminhosMinimos);
    destroiListaAdj(grafo);

    return 0;
}