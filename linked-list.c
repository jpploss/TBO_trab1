#include "linked-list.h"

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

Node* removeMinNode(LinkedList* list, int (*compare)(Node*, Node*)) {
  if (list->size == 0) return NULL;

  LLNode *current = list->head, *prev = NULL;
  LLNode *min = current, *prevMin = NULL;

  while (current->next != NULL) {
    if (compare(current->next->data, min->data) < 0) {
      min = current->next;
      prevMin = current;
    }
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
