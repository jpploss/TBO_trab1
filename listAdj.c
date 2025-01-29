#include "listAdj.h"

typedef struct _adjacente Adjacente;

struct _adjacente {
    Node* node;
    Adjacente* prox;
};

typedef struct _vertice Vertice;
struct _vertice {
    char nome[31];
    int numAdjacentes;
    Adjacente* adjacentes; // lista simplesmente encadeada sem sentinela contendo os adjcentes
};

struct _listAdj {
    Vertice** vertices;
    int idVerticeOrigem;
    int numVertices;
};

ListAdj* criaListaAdj() {
    ListAdj* lAdj = malloc(sizeof(ListAdj));
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

void preencheListaAdj(FILE* arqEntrada, ListAdj* lAdj) {
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

            Adjacente* verticeAdjacente = malloc(sizeof(Adjacente));
            verticeAdjacente->node = criaNode(adj, peso, NULL); // não é relevante saber o pai nesse momento, por isso: NULL

            // insere 'verticeAdjacente' no início da lista de adjacência de 'verticeAtual'
            verticeAdjacente->prox = verticeAtual->adjacentes;
            verticeAtual->adjacentes = verticeAdjacente;
            verticeAtual->numAdjacentes++;
        }
    }


    // for(int i = 0; i < lAdj->numVertices; i++) {
    //     printf("Adjcentes vértice %s:\n", lAdj->vertices[i]->nome);
    //     for(Adjacente* j = lAdj->vertices[i]->adjacentes; j != NULL; j = j->prox) 
    //         printf("  id: %d, custo: %.02f\n", getNodeId(j->node), getNodePeso(j->node));
    //     printf("\n");
    // }
}

float getPesoAresta(ListAdj* lAdj, Node* pai, Node* filho) {
    int idPai = getNodeId(pai), idFilho = getNodeId(filho);

    Adjacente* adjPai = lAdj->vertices[idPai]->adjacentes;
    for(Adjacente* adj = adjPai; adj != NULL; adj = adj->prox) {
        Node* temp = adj->node;
        if(getNodeId(temp) == idFilho) return getNodePeso(temp);
    }
    return 0;
}

int getNumVertices(ListAdj* lAdj) {
    return lAdj->numVertices;
}

Node** getAdjacentes(ListAdj* lAdj, Node* vertice) {
    Vertice* v = lAdj->vertices[getNodeId(vertice)];
    Node** adjcentes = malloc(sizeof(Node*) * v->numAdjacentes);

    int count = 0;
    for(Adjacente* j = v->adjacentes; j != NULL; j = j->prox) 
        adjcentes[count++] = copiaNode(j->node);

    return adjcentes;
}

int getNumAdjacentes(ListAdj* lAdj, Node* vertice) {
    return lAdj->vertices[getNodeId(vertice)]->numAdjacentes;
}

int getIdOrigem(ListAdj* lAdj) {
    return lAdj->idVerticeOrigem;
}

void destroiListaAdj(ListAdj* lAdj) {
    if(lAdj == NULL) return;

    for(int v = 0; v < lAdj->numVertices; v++) {
        Adjacente* atual = lAdj->vertices[v]->adjacentes;
        while(atual != NULL) {
            Adjacente* temp = atual->prox;
            destroiNode(atual->node);
            free(atual);
            atual = temp;
        }
        free(lAdj->vertices[v]);
    }
    free(lAdj->vertices);
    free(lAdj);
}