#ifndef LISTADJ_H
#define LISTADJ_H

#include "node.h"

/// @brief TAD responsável pela criação, manutenção e destruição de um grafo representado por uma lista de adjacências.
typedef struct _listAdj ListAdj;

/// @brief Cria uma lista de adjacências vazia.
/// @return Ponteiro para a estrutura da lista de adjacências alocada dinamicamente.
ListAdj* criaListaAdj();

/// @brief Preenche uma lista de adjacências vazia a partir de um arquivo de entrada, que deve estar no padrão estabelecido.
/// @param arqEntrada arquivo de entrada padronizado
/// @param lAdj lista a ser preenchida
void preencheListaAdj(FILE* arqEntrada, ListAdj* lAdj);

/// @brief Retorna o número de vértices do grafo representado por 'lAdj'.
/// @param lAdj grafo de entrada
/// @return Inteiro correspondendo ao número de vértices de 'lAdj'.
int getNumVertices(ListAdj* lAdj);

/// @brief Retorna um vetor contendo os nós adjacentes ao nó cujo id foi passado como argumento.
/// @param lAdj grafo que contém o nó
/// @param id id do nó
/// @return Vetor alocado dinamicamente contendo os nós adjacentes (cada nó do vetor são cópias alocadas dinamicamente).
Node** getAdjacentes(ListAdj* lAdj, int id);

/// @brief Retorna a quantidade de adjacentes ao nó cujo id foi passado como argumento.
/// @param lAdj grafo que contém o nó
/// @param id id do nó
/// @return Inteiro correspondendo ao número de adjacentes do nó.
int getNumAdjacentes(ListAdj* lAdj, int id);

/// @brief Libera toda a memória alocada para a lista 'lAdj'.
/// @param lAdj lista a ser liberada
void destroiListaAdj(ListAdj* lAdj);


#endif