#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include "node.h"

#define INFINITO -1

/// @brief TAD responsável pela criação, manutenção e destruição de uma min heap.
///
/// Obs.: nos nós da heap, será utilizado -1 significando infinito.
typedef struct _heap Heap;

/// @brief Aloca a estrutura necessária para a utilização de uma heap inicialmente vazia.
/// @param numVertices quantidade de elementos da heap
/// @return Ponteiro para a estrutura da heap alocada dinamicamente.
Heap* criaHeap(int numVertices);

/// @brief Verfica se um nó tem peso infinito.
/// @param n nó válido a ser verificado se o peso é infinito
/// @return 0 se o peso não é infinito e 1 caso contrário.
int pesoInfinito(Node* n);

/// @brief Insere um novo elemento na heap.
/// @param heap heap onde será inserido o novo elemento
/// @param idVertice id do novo elemento
/// @param distancia distância do novo elemento
/// @param pai ponteiro para o pai do vértice de id igual a 'idVertice'
void insereHeap(Heap* heap, int idVertice, float distancia, Node* pai);

/// @brief Atualiza o peso do nó de entrada mantendo a ordem heap.
/// @param heap heap válida contendo o nó
/// @param n nó válido a ser atualizado
/// @param novaDistancia nova distância do nó de entrada
void atualizaDistancia(Heap* heap, Node* n, float novaDistancia);

/// @brief Extrai o menor elemento da heap.
/// @param heap heap onde será extraído o menor elemento
/// @return Retorna o ponteiro para o nó removido.
///
/// Obs.: como o nó foi removido, é necessário destruí-lo após o uso.
Node* extraiMenorElemento(Heap* heap);

/// @brief Retorna o tamanho atual da heap.
/// @param heap heap válida
/// @return Inteiro correspondendo ao tamanho atual da heap passada como argumento.
int getTamAtualHeap(Heap* heap);

/// @brief Libera toda a memória alocada para 'heap'.
/// @param heap heap a ser destroida
void destroiHeap(Heap* heap);

#endif