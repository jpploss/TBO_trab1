// Arthur Tosi (2023100573) | João P. Loss (2023102068) | Theo de Sá (2023101082)
#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include "node.h"

/// @brief TAD responsável pela criação, manutenção e destruição de uma min heap.
///
/// Obs.: nos nós da heap, será utilizado -1 significando infinito.
typedef struct _heap Heap;

/// @brief Aloca a estrutura necessária para a utilização de uma heap inicialmente vazia.
/// @param numVertices quantidade de elementos da heap
/// @return Ponteiro para a estrutura da heap alocada dinamicamente.
Heap* criaHeap(int numVertices);

/// @brief Insere um novo elemento na heap.
/// @param heap heap onde será inserido o novo elemento
/// @param idVertice id do novo elemento
/// @param distancia distância do novo elemento
/// @param pai ponteiro para o pai do vértice de id igual a 'idVertice'
void insereHeap(Heap* heap, int idVertice, float distancia, Node* pai);

/// @brief Atualiza o peso e o pai do nó cujo id foi passado como argumento ('idFilho') mantendo a ordem heap.
/// @param heap heap válida contendo o nó
/// @param idFilho id do nó válido a ser atualizado
/// @param pai novo nó pai
/// @param novaDistancia nova distância do nó de entrada
void decresceDistancia(Heap* heap, int idFilho, Node* pai, float novaDistancia);

/// @brief Extrai o menor elemento da heap.
/// @param heap heap onde será extraído o menor elemento
/// @return Retorna o ponteiro para o nó removido.
///
/// Obs.: como o nó foi removido, é necessário destruí-lo após o uso.
Node* extraiMenorElemento(Heap* heap);

/// @brief Retorna o peso atual do nó na heap. 
/// @param heap heap válida contendo o nó
/// @param id id do nó
/// @return Float correspondendo ao peso atual do nó na heap.
float getPesoHeap(Heap* heap, int id);

/// @brief Retorna o tamanho atual da heap.
/// @param heap heap válida
/// @return Inteiro correspondendo ao tamanho atual da heap passada como argumento.
int getTamAtualHeap(Heap* heap);

/// @brief Libera toda a memória alocada para 'heap'.
/// @param heap heap a ser destroida
void destroiHeap(Heap* heap);

#endif