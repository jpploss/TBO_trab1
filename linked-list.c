#include "linked-list.h"

#include "stdlib.h"

typedef struct LLNode {
  void* data;  // Sera um ponteiro para o tipo 'Node'
  struct LLNode* next;
} LLNode;

static LLNode* createLLNode(void* value) {
  LLNode* node = malloc(sizeof(LLNode));
  node->data = value;
  node->next = NULL;
  return node;
}

struct _LinkedList {
  LLNode* head;
  unsigned int size;
};

LinkedList* createLinkedList() {
  LinkedList* list = malloc(sizeof(LinkedList));
  list->head = NULL;
  list->size = 0;
  return list;
}

void insertValue(LinkedList* list, void* value) {
  LLNode* newNode = createLLNode(value);
  newNode->next = list->head;
  list->head = newNode;
  list->size++;
}

unsigned int getSize(LinkedList* list) {
  return list->size;
}

void* removeMinValue(LinkedList* list, int (*compare)(void*, void*)) {
  if (list->size == 0) return NULL;

  LLNode* current = list->head;
  LLNode* prev = NULL;
  LLNode* min = current;
  LLNode* prevMin = NULL;

  while (current != NULL) {
    if (compare(current->data, min->data) < 0) {
      min = current;
      prevMin = prev;
    }
    prev = current;
    current = current->next;
  }

  void* data = min->data;

  if (prevMin == NULL) {
    list->head = min->next;
  } else {
    prevMin->next = min->next;
  }

  free(min);
  list->size--;

  return data;
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