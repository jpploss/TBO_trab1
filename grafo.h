#ifndef GRAFO_H
#define GRAFO_H

#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief TAD responsável pela criação, manutenção e destruição de um grafo representado por uma lista de adjacências.
typedef struct _grafo Grafo;

/// @brief Cria uma lista de adjacências vazia.
/// @return Ponteiro para a estrutura da lista de adjacências alocada dinamicamente.
Grafo* criaListaAdj();

/// @brief Preenche uma lista de adjacências vazia a partir de um arquivo de entrada, que deve estar no padrão estabelecido.
/// @param arqEntrada arquivo de entrada padronizado
/// @param lAdj lista a ser preenchida
void preencheListaAdj(FILE* arqEntrada, Grafo* lAdj);

/// @brief Retorna o peso de uma aresta.
/// @param lAdj grafo de entrada
/// @param idPai id do nó de origem
/// @param idFilho id do nó de destino
/// @return Float correspondendo ao peso da aresta de pai para filho. Se a aresta não for encontrada será retornado 0.
float getPesoAresta(Grafo* lAdj, int idPai, int idFilho);

/// @brief Retorna o número de vértices do grafo representado por 'lAdj'.
/// @param lAdj grafo de entrada
/// @return Inteiro correspondendo ao número de vértices de 'lAdj'.
int getNumVertices(Grafo* lAdj);

/// @brief Retorna os nós adjacentes ao nó de entrada.
/// @param lAdj grafo que contém o nó
/// @param vertice nó válido
/// @return Ponteiro para o início da lista de adjacentes encadeada através do pai de cada nó.
///
/// Obs.: a lista não é uma cópia, portanto, as alterações modificam permanentemente o grafo de entrada (podendo comprometer
/// o funcionamento do programa).
Node* getAdjacentes(Grafo* lAdj, Node* vertice);

/// @brief Retorna a quantidade de adjacentes ao nó de entrada.
/// @param lAdj grafo que contém o nó
/// @param vertice nó válido
/// @return Inteiro correspondendo ao número de adjacentes do nó.
int getNumAdjacentes(Grafo* lAdj, Node* vertice);

/// @brief Retorna o id do vértice de origem.
/// @param lAdj grafo de entrada
/// @return Inteiro correspondendo ao id do vértice de origem do grafo.
int getIdOrigem(Grafo* lAdj);

/// @brief Retorna o nome do vértice cujo id é fornecido como argumento.
/// @param lAdj grafo que contém o nó
/// @param id id do nó
/// @return Ponteiro para o vetor contendo o nome do vértice.
///
/// Obs.: o ponteiro corresponde ao endereço original, não é uma cópia.
char* getNomeVertice(Grafo* lAdj, int id);

/// @brief Libera toda a memória alocada para a lista 'lAdj'.
/// @param lAdj lista a ser liberada
void destroiListaAdj(Grafo* lAdj);


#endif