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
    FILE* arqEntrada = fopen("./casos_teste_v3/caso_teste_medio_1.txt", "r");
    preencheListaAdj(arqEntrada, grafo);
    fclose(arqEntrada);
    printf("Arquivo lido e grafo construído!\n");

    printf("\nRealizando Dijkstra para encontrar os caminhos mínimos...\n");
    Node** caminhosMinimos = dijkstra(grafo);
    printf("Dijkstra feito e caminhos mínimos encontrados!\n");

    FILE* arqSaida = fopen("./resultado.txt", "w");
    int numVertices = getNumVertices(grafo);
    qsort(caminhosMinimos, numVertices, sizeof(Node*), comparaNode);
    for(int i = 0; i < numVertices; i++) {
        Node* noAtual = caminhosMinimos[i];
        char* nomeNoAtual = getNomeVertice(grafo, getNodeId(noAtual));
        fprintf(arqSaida, "SHORTEST PATH TO %s: ", nomeNoAtual);

        if(pesoInfinito(noAtual)) { // sem conexão
            fprintf(arqSaida, "-\n");
            continue;
        }

        if(getNodePai(noAtual) == NULL)  { // nó raíz (origem)
            fprintf(arqSaida, "%s <- %s (Distance: 0.00)\n", nomeNoAtual, nomeNoAtual);
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


    // liberação de memória
    for(int i = 0; i < getNumVertices(grafo); i++) destroiNode(caminhosMinimos[i]);
    free(caminhosMinimos);
    destroiListaAdj(grafo);

    return 0;
}