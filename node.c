#include "node.h"
#include <stdlib.h>
#include <stdio.h>

struct _node {
    int id;
    float peso;
};

Node* criaNode(int id, float peso) {
    Node* n = malloc(sizeof(Node));
    n->id = id;
    n->peso = peso;
    return n;
}

int getNodeId(Node* n) {
    return n->id;
}

float getNodePeso(Node* n) {
    return n->peso;
}

Node* copiaNode(Node* n) {
    Node* nodeCopia = malloc(sizeof(Node));
    nodeCopia->id = n->id;
    nodeCopia->peso = n->peso;
    return nodeCopia;
}

void destroiNode(Node* n) {
    if(n != NULL) free(n);
}