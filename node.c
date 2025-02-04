#include "node.h"

struct _node {
    int id;
    Node* prox;
    float peso;
};

Node* criaNode(int id, float peso, Node* nodeProx) {
    Node* n = malloc(sizeof(Node));
    n->id = id;
    n->peso = peso;
    n->prox = nodeProx;
    return n;
}

void setNodePeso(Node* n, float novoPeso) {
    n->peso = novoPeso;
}

void setNodeProx(Node* n, Node* nodeProx) {
    n->prox = nodeProx;
}

int getNodeId(Node* n) {
    return n->id;
}

Node* getNodeProx(Node* n) {
    return n->prox;
}

float getNodePeso(Node* n) {
    return n->peso;
}

Node* copiaNode(Node* n) {
    Node* nodeCopia = malloc(sizeof(Node));
    nodeCopia->id = n->id;
    nodeCopia->peso = n->peso;
    nodeCopia->prox = n->prox;
    return nodeCopia;
}

void destroiNode(Node* n) {
    if(n != NULL) free(n);
}