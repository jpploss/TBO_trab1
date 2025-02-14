#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <stdio.h>

/// @brief TAD responsável pela criação, manutenção e destruição de um nó contendo um id, um peso e um ponteiro para outro nó.
typedef struct _node Node;

/// @brief Cria um novo nó a partir de um id, peso e ponteiro para outro nó fornecidos.
/// @param id id do nó a ser criado
/// @param peso peso do nó a ser criado
/// @param nodeProx ponteiro para o próximo nó (ou NULL caso não exista próximo)
/// @return Ponteiro para a estrura do nó alocada dinamicamente.
Node* criaNode(int id, float peso, Node* nodeProx);

/// @brief Atualiza o valor do peso do nó de entrada.
/// @param n nó válido a ser atualizado
/// @param novoPeso valor do novo peso
void setNodePeso(Node* n, float novoPeso);

/// @brief Atualiza o valor de prox do nó filho.
/// @param n nó válido a ser atualizado
/// @param nodeProx nó válido representando o próximo nó de 'n'
void setNodeProx(Node* n, Node* nodeProx);

/// @brief Retorna o id de um nó válido.
/// @param n nó válido a partir do qual será retornado um id
/// @return Id do nó
int getNodeId(Node* n);

/// @brief Retorna um ponteiro para o pai do nó de entrada.
///
/// Obs.: o ponteiro retornado é para o próximo nó original, não uma cópia, portanto liberar a estutura ou alterá-la pode comprometer
/// o funcionamento adequado do programa.
/// @param n nó válido a partir do qual será retornado o próximo
/// @return Ponteiro para o próximo nó a partir do nó de entrada (ou NULL caso não exista).
Node* getNodeProx(Node* n);

/// @brief Retorna o peso de um nó válido.
/// @param n nó a partir do qual será retornado um peso
/// @return Peso do nó
float getNodePeso(Node* n);

/// @brief Cria um nó com mesmo id e peso do nó passado como argumento.
/// @param n nó a ser copiado
/// @return Ponteiro para a estrura do nó cópia alocada dinamicamente.
Node* copiaNode(Node* n);

/// @brief Libera toda a memória alocada para o nó 'n'.
/// @param n nó a ser liberado
void destroiNode(Node* n);

#endif