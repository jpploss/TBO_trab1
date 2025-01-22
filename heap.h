#ifndef HEAP_H
#define HEAP_H

#include "vector.h"

typedef struct _heap Heap;

Heap* criaHeap();

void insereHeap (Heap*, int idVertice, float distancia); //-1 se não tiver ligamento com o vértice principal

#endif