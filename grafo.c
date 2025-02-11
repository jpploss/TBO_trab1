#include "grafo.h"

typedef struct _adjacente Adjacente;

typedef struct _vertice Vertice;
struct _vertice {
    char nome[31];
    int numAdjacentes;
    Node* adjacentes; // lista simplesmente encadeada sem sentinela (onde o encadeamento acontece através do pai de cada nó)
};

struct _grafo {
    Vertice** vertices;
    int idVerticeOrigem;
    int numVertices;
};

Grafo* criaListaAdj() {
    Grafo* lAdj = malloc(sizeof(Grafo));
    lAdj->numVertices = 0;
    lAdj->idVerticeOrigem = -1;
    lAdj->vertices = NULL;

    return lAdj;
}

static int contaVertices(FILE* arqEntrada) {
    fscanf(arqEntrada, "%*[^\n]\n"); // tira a primeira, que diz o nome do vértice de origem
    fscanf(arqEntrada, "%*[^,],"); // tira o nome do vértice 0
    
    char aux = 0;
    int numVertices = 1;
    while(1) {
        fscanf(arqEntrada, "%*[^,\n]");
        numVertices++; // para cada peso lido (correspondente a um vértice), 'numVertices' é incrementado 

        fscanf(arqEntrada, "%c", &aux);
        if(aux == '\n') break; // sai do loop caso tenha alcançado o fim da linha      
    }  

    rewind(arqEntrada); // reseta o ponteiro do arquivo para o início

    return numVertices;
}

void preencheListaAdj(FILE* arqEntrada, Grafo* lAdj) {
    lAdj->numVertices = contaVertices(arqEntrada);
    lAdj->vertices = malloc(sizeof(Vertice*) * lAdj->numVertices);

    char nomeVerticeOrigem[31];
    fscanf(arqEntrada, "%[^\n]\n", nomeVerticeOrigem);

    for(int v = 0; v < lAdj->numVertices; v++) {
        Vertice* verticeAtual = malloc(sizeof(Vertice));
        lAdj->vertices[v] = verticeAtual;
        
        fscanf(arqEntrada, "%[^,], ", verticeAtual->nome); // lê nome do vértice atual
        verticeAtual->numAdjacentes = 0;
        verticeAtual->adjacentes = NULL; // a lista de vértices adjacentes começa vazia

        if(strcmp(nomeVerticeOrigem, verticeAtual->nome) == 0) lAdj->idVerticeOrigem = v; // verifica se vértice atual é o vértice de origem

        for(int adj = 0; adj < lAdj->numVertices; adj++) { // lê os vizinhos do vertice atual
            if(adj == v) continue;

            float peso = 0.0;

            fscanf(arqEntrada, "%f", &peso);
            fscanf(arqEntrada, "%*[^,\n]"); // elimina a string "bomba", se existir, ou algum catactere indesejado (como whitespaces)
            fscanf(arqEntrada, "%*c"); // elimina ',' ou '\n'

            if(peso == 0.0) continue;
            // como definido, caso o custo de acesso (peso) seja zero, assume-se que não há conexão entre os vértices

            Node* verticeAdjacente = criaNode(adj, peso, verticeAtual->adjacentes);

            // insere 'verticeAdjacente' no início da lista de adjacência de 'verticeAtual'
            verticeAtual->adjacentes = verticeAdjacente;
            verticeAtual->numAdjacentes++;
        }
    }
}

float getPesoAresta(Grafo* lAdj, int idPai, int idFilho) {
    
    Node* adjPai = lAdj->vertices[idPai]->adjacentes;
    for(Node* adj = adjPai; adj != NULL; adj = getNodeProx(adj))
        if(getNodeId(adj) == idFilho) return getNodePeso(adj);
    
    return 0;
}

int getNumVertices(Grafo* lAdj) {
    return lAdj->numVertices;
}

Node* getAdjacentes(Grafo* lAdj, Node* vertice) {
    return lAdj->vertices[getNodeId(vertice)]->adjacentes;
}

int getNumAdjacentes(Grafo* lAdj, Node* vertice) {
    return lAdj->vertices[getNodeId(vertice)]->numAdjacentes;
}

int getIdOrigem(Grafo* lAdj) {
    return lAdj->idVerticeOrigem;
}

char* getNomeVertice(Grafo* lAdj, int id) {
    return lAdj->vertices[id]->nome;
}

void destroiListaAdj(Grafo* lAdj) {
    if(lAdj == NULL) return;

    for(int v = 0; v < lAdj->numVertices; v++) {
        Node* atual = lAdj->vertices[v]->adjacentes;
        while(atual != NULL) {
            Node* temp = getNodeProx(atual);
            destroiNode(atual);
            atual = temp;
        }
        free(lAdj->vertices[v]);
    }
    free(lAdj->vertices);
    free(lAdj);
}