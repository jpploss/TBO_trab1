#ifndef HEAP_H
#define HEAP_H

// #include "vector.h"

/// @brief TAD responsável pela criação, manutenção e destruição de uma min heap.
typedef struct _heap Heap;

/// @brief Aloca a estrutura necessária para a utilização de uma heap inicialmente vazia.
/// @param numVertices quantidade de elementos da heap
/// @return Ponteiro para a estrutura da heap alocada dinamicamente.
Heap* criaHeap(int numVertices);

/// @brief Insere um novo elemento na heap.
/// @param heap heap onde será inserido o novo elemento
/// @param idVertice id do novo elemento
/// @param distancia distância do novo elemento
void insereHeap(Heap* heap, int idVertice, float distancia);  //-1 se não tiver ligamento com o vértice principal

/// @brief Extrai o menor elemento da heap.
/// @param heap heap onde será extraído o menor elemento
/// @return Retorna o id do vértice com a menor distância
int extraiMenorElemento(Heap* heap);

/// @brief Libera toda a memória alocada para 'heap'.
/// @param heap heap a ser destroida
void destroiHeap(Heap* heap);

#endif