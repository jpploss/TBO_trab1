#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include "node.h"

typedef struct _LinkedList LinkedList;

/// @brief Cria uma lista encadeada vazia
/// @return Ponteiro para a lista encadeada criada
LinkedList* createLinkedList();

/// @brief Insere um node na lista encadeada
/// @param list lista encadeada
/// @param value node a ser inserido
void insertValue(LinkedList* list, Node* value);

/// @brief Remover o node com menor peso da lista encadeada
/// @param list lista
/// @param compare funcao que compara os nodes (com base no peso)
/// @return Node com menor peso
Node* removeMinNode(LinkedList* list, int (*compare)(Node*, Node*));

/// @brief Obtem o tamanho da lista
/// @param list lista encadeada
/// @return Tamanho da lista
unsigned int getSize(LinkedList* list);

/// @brief Desaloca memoria da lista encadeada
/// @param list lista encadeada
void destroyLinkedList(LinkedList* list);

/// @brief Obtem o node na lista pelo id
/// @param list lista encadeada
/// @param id id do node a ser procurado
/// @return Node com o id especificado
Node* getNodeById(LinkedList* list, int id);

#endif
