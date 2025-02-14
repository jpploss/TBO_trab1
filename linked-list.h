#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

typedef struct _LinkedList LinkedList;

LinkedList* createLinkedList();

void insertValue(LinkedList* list, void* value);

void* removeMinValue(LinkedList* list, int (*compare)(void*, void*));

unsigned int getSize(LinkedList* list);

void destroyLinkedList(LinkedList* list);

#endif