#ifndef LISTADJ_H
#define LISTADJ_H

#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief TAD responsável pela criação, manutenção e destruição de um grafo representado por uma lista de adjacências.
typedef struct _listAdj ListAdj;

/// @brief Cria uma lista de adjacências vazia.
/// @return Ponteiro para a estrutura da lista de adjacências alocada dinamicamente.
ListAdj* criaListaAdj();

/// @brief Preenche uma lista de adjacências vazia a partir de um arquivo de entrada, que deve estar no padrão estabelecido.
/// @param arqEntrada arquivo de entrada padronizado
/// @param lAdj lista a ser preenchida
void preencheListaAdj(FILE* arqEntrada, ListAdj* lAdj);

/// @brief Retorna o peso de uma aresta.
/// @param lAdj grafo de entrada
/// @param idPai id do nó de origem
/// @param idFilho id do nó de destino
/// @return Float correspondendo ao peso da aresta de pai para filho. Se a aresta não for encontrada será retornado 0.
float getPesoAresta(ListAdj* lAdj, int idPai, int idFilho);

/// @brief Retorna o número de vértices do grafo representado por 'lAdj'.
/// @param lAdj grafo de entrada
/// @return Inteiro correspondendo ao número de vértices de 'lAdj'.
int getNumVertices(ListAdj* lAdj);

/// @brief Retorna um vetor contendo os ids dos nós adjacentes ao nó de entrada.
/// @param lAdj grafo que contém o nó
/// @param vertice nó válido
/// @return Vetor de inteiros alocado dinamicamente contendo os ids dos nós adjacentes (a liberação da memória 
/// é responsabilidade do cliente).
int* getAdjacentes(ListAdj* lAdj, Node* vertice);

/// @brief Retorna a quantidade de adjacentes ao nó de entrada.
/// @param lAdj grafo que contém o nó
/// @param vertice nó válido
/// @return Inteiro correspondendo ao número de adjacentes do nó.
int getNumAdjacentes(ListAdj* lAdj, Node* vertice);

/// @brief Retorna o id do vértice de origem.
/// @param lAdj grafo de entrada
/// @return Inteiro correspondendo ao id do vértice de origem do grafo.
int getIdOrigem(ListAdj* lAdj);

/// @brief Libera toda a memória alocada para a lista 'lAdj'.
/// @param lAdj lista a ser liberada
void destroiListaAdj(ListAdj* lAdj);


#endif