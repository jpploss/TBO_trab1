#ifndef NODE_H
#define NODE_H

/// @brief TAD responsável pela criação, manutenção e destruição de um nó contendo um id e um peso.
typedef struct _node Node;

/// @brief Cria um novo nó a partir de um id e peso fornecidos.
/// @param id id do nó a ser criado
/// @param peso peso do nó a ser criado
/// @return Ponteiro para a estrura do nó alocada dinamicamente.
Node* criaNode(int id, float peso);

/// @brief Retorna o id de um nó válido.
/// @param n nó a partir do qual será retornado um id
/// @return Id do nó
int getNodeId(Node* n);

/// @brief Retorna o peso de um nó válido.
/// @param n nó a partir do qual será retornado um peso
/// @return Peso do nó
float getNodePeso(Node* n);

/// @brief Cria um nó com mesmo id e peso do nó passa como argumento.
/// @param n nó a ser copiado
/// @return Ponteiro para a estrura do nó cópia alocada dinamicamente.
Node* copiaNode(Node* n);

/// @brief Libera toda a memória alocada para o nó 'n'.
/// @param n nó a ser liberado
void destroiNode(Node* n);

#endif