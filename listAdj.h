#ifndef LISTADJ_H
#define LISTADJ_H

typedef struct _listAdj listAdj;

/// @brief Cria uma lista de adjacências vazia.
/// @return Lista de adjacência vazia.
listAdj* criaListaAdj();

/// @brief Preenche uma lista de adjacência vazia a partir de um arquivo de entrada, que deve estar no padrão estabelecido.
/// @param arqEntrada arquivo de entrada padronizado
/// @param lAdj lista a ser preenchida
void preencheListaAdj(FILE* arqEntrada, listAdj* lAdj);

void destroiListAdj(listAdj* lAdj);


#endif