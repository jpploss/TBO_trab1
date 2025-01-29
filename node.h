#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <stdio.h>

/// @brief TAD responsável pela criação, manutenção e destruição de um nó contendo um id e um peso.
typedef struct _node Node;

/// @brief Cria um novo nó a partir de um id e peso fornecidos.
/// @param id id do nó a ser criado
/// @param peso peso do nó a ser criado
/// @param nodePai ponteiro para o nó pai
/// @return Ponteiro para a estrura do nó alocada dinamicamente.
Node* criaNode(int id, float peso, Node* nodePai);

/// @brief Atualiza o valor do peso do nó de entrada.
/// @param n nó válido a ser atualizado
/// @param novoPeso valor do novo peso
void setNodePeso(Node* n, float novoPeso);

/// @brief Atualiza o valor do pai do nó filho.
/// @param filho nó válido a ser atualizado
/// @param pai nó válido representando o novo pai
void setNodePai(Node* filho, Node* pai);

/// @brief Retorna o id de um nó válido.
/// @param n nó válido a partir do qual será retornado um id
/// @return Id do nó
int getNodeId(Node* n);

/// @brief Retorna um ponteiro para o pai do nó de entrada.
///
/// Obs.: o ponteiro retornado é para o pai original, não uma cópia, portanto liberar a estutura ou alterá-la pode comprometer
/// o funcionamento adequado do programa.
/// @param n nó válido a partir do qual será retornado o pai
/// @return Ponteiro para o nó pai.
Node* getNodePai(Node* n);

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