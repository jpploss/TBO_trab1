#ifndef LISTADJ_H
#define LISTADJ_H

/// @brief TAD responsável pela criação, manutenção e destruição de um grafo representado por uma lista de adjacências.
typedef struct _listAdj ListAdj;

/// @brief Cria uma lista de adjacências vazia.
/// @return Lista de adjacência vazia.
ListAdj* criaListaAdj();

/// @brief Preenche uma lista de adjacências vazia a partir de um arquivo de entrada, que deve estar no padrão estabelecido.
/// @param arqEntrada arquivo de entrada padronizado
/// @param lAdj lista a ser preenchida
void preencheListaAdj(FILE* arqEntrada, ListAdj* lAdj);

/// @brief Libera toda a memória alocada para a lista 'lAdj'.
/// @param lAdj lista a ser liberada
void destroiListaAdj(ListAdj* lAdj);

/// @brief Retorna o número de vértices do grafo representado por 'lAdj'.
/// @param lAdj grafo de entrada
/// @return Inteiro correspondendo ao número de vértices de 'lAdj'.
int getNumVertices(ListAdj* lAdj);

#endif