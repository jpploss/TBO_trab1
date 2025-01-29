#include "node.h"

struct _node {
    int id;
    Node* pai;
    float peso;
};

Node* criaNode(int id, float peso, Node* nodePai) {
    Node* n = malloc(sizeof(Node));
    n->id = id;
    n->peso = peso;
    n->pai = nodePai;
    return n;
}

void setNodePeso(Node* n, float novoPeso) {
    n->peso = novoPeso;
}

void setNodePai(Node* filho, Node* pai) {
    filho->pai = pai;
}

int getNodeId(Node* n) {
    return n->id;
}

Node* getNodePai(Node* n) {
    return n->pai;
}

float getNodePeso(Node* n) {
    return n->peso;
}

Node* copiaNode(Node* n) {
    Node* nodeCopia = malloc(sizeof(Node));
    nodeCopia->id = n->id;
    nodeCopia->peso = n->peso;
    nodeCopia->pai = n->pai;
    return nodeCopia;
}

void destroiNode(Node* n) {
    if(n != NULL) free(n);
}