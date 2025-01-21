#ifndef VECTOR_H
#define VECTOR_H

#define CAPACIDADE_INICIAL 10

typedef struct _vector Vector;

Vector* criaVetor(); //cria com a capacidade inicial fornecida

void insereElemento(Vector* v, void* elemento); //caso o vetor esteja cheio, dobra a capacidade

void* removeElemento(Vector* v, int pos);

void* acessaElemento(Vector* v, int pos);

int tamanhoVetor(Vector* v);

void trocaElementos(Vector* v, int pos1, int pos2); // a heap precisa de frequentes trocas

void destroiVetor(Vector* v);
 
#endif