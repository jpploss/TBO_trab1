#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

int main(int argc, char const* argv[]) {
  Heap* heap = criaHeap(10);

  insereHeap(heap, 1, 5, NULL);
  insereHeap(heap, 2, 3, NULL);
  insereHeap(heap, 3, 8, NULL);
  insereHeap(heap, 4, 2, NULL);
  insereHeap(heap, 5, 1, NULL);
  insereHeap(heap, 6, 7, NULL);

  for (int i = 0; i < 10; i++) {
    Node* n = extraiMenorElemento(heap);
    if(!n) {
      printf("Heap vazia.\n");
      continue;
    }
    printf("%d %.02f\n", getNodeId(n), getNodePeso(n));
    free(n);
  }

  destroiHeap(heap);
  return 0;
}
