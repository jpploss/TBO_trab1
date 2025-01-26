#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

int main(int argc, char const* argv[]) {
  Heap* heap = criaHeap(10);

  insereHeap(heap, 1, 5);
  insereHeap(heap, 2, 3);
  insereHeap(heap, 3, 8);
  insereHeap(heap, 4, 2);
  insereHeap(heap, 5, 1);
  insereHeap(heap, 6, 7);

  for (int i = 0; i < 3; i++)
    printf("%d\n", extraiMenorElemento(heap));

  destroiHeap(heap);
  return 0;
}
