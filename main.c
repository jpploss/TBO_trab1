#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listAdj.h"
#include "heap.h"
#include "node.h"
#include "dijkstra.h"

int comparaNode(const void* n1, const void* n2) {
    if(*(Node**)n1 == NULL) return -1;
    if(*(Node**)n2 == NULL) return 1;

    float p1 = getNodePeso(*(Node**)n1), p2 = getNodePeso(*(Node**)n2);
    return p1 - p2;
}

int main() {
    
    ListAdj* grafo = criaListaAdj();
    printf("Lendo arquivo e construindo grafo...\n");
    FILE* arqEntrada = fopen("./casos_teste_v3/caso_teste_pequeno_1.txt", "r");
    preencheListaAdj(arqEntrada, grafo);
    fclose(arqEntrada);
    printf("Arquivo lido e grafo construído!\n");

    printf("\nRealizando Dijkstra para encontrar os caminhos mínimos...\n");

    FILE* arqSaida = fopen("./resultado.txt", "w");
    Node** caminhosMinimos = dijkstra(grafo);
    int numVertices = getNumVertices(grafo);
    qsort(caminhosMinimos, numVertices, sizeof(Node*), comparaNode);
    for(int i = 0; i < numVertices; i++) {
        Node* noAtual = caminhosMinimos[i];
        fprintf(arqSaida, "SHORTEST PATH TO %s: ", getNomeVertice(grafo, getNodeId(noAtual)));

        if(getNodePai(noAtual) == NULL)  { 
            fprintf(arqSaida, "%s <- %s (Distance: 0.00)\n", 
                                        getNomeVertice(grafo, getNodeId(noAtual)), 
                                        getNomeVertice(grafo, getNodeId(noAtual)));

            continue;
        }

        for(Node* n = noAtual; n != NULL; n = getNodePai(n)) {
            fprintf(arqSaida, "%s", getNomeVertice(grafo, getNodeId(n)));
            if(getNodePai(n) != NULL) fprintf(arqSaida, " <- ");
            else break;
        }
        fprintf(arqSaida, " (Distance: %.02f)\n", getNodePeso(noAtual));
    }
    fclose(arqSaida);
    printf("Dijkstra feito e caminhos mínimos encontrados!\n");


    // liberação de memória
    for(int i = 0; i < getNumVertices(grafo); i++) destroiNode(caminhosMinimos[i]);
    free(caminhosMinimos);
    destroiListaAdj(grafo);

    return 0;
}