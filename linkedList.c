// Arthur Tosi (2023100573) | João P. Loss (2023102068) | Theo de Sá (2023101082)
#include "linkedList.h"

#include "stdlib.h"

typedef struct LLNode {
  Node* data;
  struct LLNode* next;
} LLNode;

struct _LinkedList {
  LLNode* head;
  unsigned int size;
};

static LLNode* createLLNode(Node* value) {
  LLNode* node = malloc(sizeof(LLNode));
  node->data = value;
  node->next = NULL;
  return node;
}

LinkedList* createLinkedList() {
  LinkedList* list = malloc(sizeof(LinkedList));
  list->head = NULL;
  list->size = 0;
  return list;
}

void insertValue(LinkedList* list, Node* value) {
  LLNode* newNode = createLLNode(value);
  newNode->next = list->head;
  list->head = newNode;
  list->size++;
}

unsigned int getSize(LinkedList* list) {
  return list->size;
}

Node* removeMinNode(LinkedList* list) {
  if (list->size == 0) return NULL;

  LLNode *current = list->head, *min = list->head;
  LLNode *prev = NULL, *prevMin = NULL;

  float menorPeso = INFINITO;

  while (current != NULL) {
    if (menorPeso == INFINITO && getNodePeso(current->data) != INFINITO) {
      menorPeso = getNodePeso(current->data);
      min = current;
      prevMin = prev;
    } else if (getNodePeso(current->data) < menorPeso && getNodePeso(current->data) != INFINITO) {
      menorPeso = getNodePeso(current->data);
      min = current;
      prevMin = prev;
    }
    prev = current;
    current = current->next;
  }

  Node* data = min->data;

  if (prevMin == NULL)
    list->head = min->next;
  else
    prevMin->next = min->next;

  free(min);
  list->size--;
  return data;
}

Node* getNodeById(LinkedList* list, int id) {
  LLNode* current = list->head;
  while (current != NULL) {
    if (getNodeId(current->data) == id) return current->data;
    current = current->next;
  }
  return NULL;
}

void destroyLinkedList(LinkedList* list) {
  LLNode* current = list->head;
  while (current != NULL) {
    LLNode* next = current->next;
    free(current);
    current = next;
  }
  free(list);
}
