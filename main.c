#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "grafo.h"
#include "heap.h"
#include "node.h"

int comparaNode(const void* n1, const void* n2) {
    if(*(Node**)n1 == NULL) return -1;
    if(*(Node**)n2 == NULL) return 1;

    float p1 = getNodePeso(*(Node**)n1), p2 = getNodePeso(*(Node**)n2);
    float comp = p1 - p2;
    if(comp < 0) return -1;
    else if(comp > 0) return 1;
    return 0;
}

Node** dijkstra(Grafo* grafo); // assinatura de uma função externa que deverá ser linkada durante a compilação

int main(int argc, char *argv[]) {
    if(argc != 3) {
        printf("Problema nos parâmetros na chamada do programa.\nFormato esperado: ./trab1 <nome_arquivo_entrada> <nome_arquivo_saida>.\n");
        return EXIT_FAILURE;
    }

    clock_t inicio = clock();
    
    FILE* arqEntrada = fopen(argv[1], "r");
    if(!arqEntrada) {
        printf("Não foi possível abrir o arquivo de entrada '%s'.\n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("Lendo arquivo e construindo grafo...\n");
    Grafo* grafo = criaListaAdj();
    preencheListaAdj(arqEntrada, grafo);
    printf("Arquivo lido e grafo construído!\n");
    
    fclose(arqEntrada);

    printf("\nRealizando Dijkstra para encontrar os caminhos mínimos...\n");
    Node** caminhosMinimos = dijkstra(grafo);
    printf("Dijkstra feito e caminhos mínimos encontrados!\n");

    FILE* arqSaida = fopen(argv[2], "w");
    if(!arqSaida) {
        printf("Não foi possível abrir o arquivo de saída '%s'.\n", argv[2]);
        fclose(arqEntrada);
        return EXIT_FAILURE;
    }

    printf("\nSalvando caminhos em arquivo.\n");
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

        if(getNodeProx(noAtual) == NULL)  { // nó raíz (origem)
            fprintf(arqSaida, "%s <- %s (Distance: 0.00)\n", nomeNoAtual, nomeNoAtual);
            continue;
        }

        for(Node* n = noAtual; n != NULL; n = getNodeProx(n)) {
            fprintf(arqSaida, "%s", getNomeVertice(grafo, getNodeId(n)));
            if(getNodeProx(n) != NULL) fprintf(arqSaida, " <- ");
            else break;
        }
        fprintf(arqSaida, " (Distance: %.02f)\n", getNodePeso(noAtual));
    }

    fclose(arqSaida);

    // liberação de memória
    for(int i = 0; i < getNumVertices(grafo); i++) destroiNode(caminhosMinimos[i]);
    free(caminhosMinimos);
    destroiListaAdj(grafo);

    clock_t fim = clock();
    double tempoTotal = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo decorrido %f seconds\n", tempoTotal);

    return EXIT_SUCCESS;
}