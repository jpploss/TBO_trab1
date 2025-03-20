# Implementação do Algoritmo de Dijkstra com Heap Binária e Lista Encadeada

Arthur Tosi (2023100573) | João P. Loss (2023102068) | Theo de Sá (2023101082)

## Índice

- [Implementação do Algoritmo de Dijkstra com Heap Binária e Lista Encadeada](#implementação-do-algoritmo-de-dijkstra-com-heap-binária-e-lista-encadeada)
  - [Índice](#índice)
  - [Introdução](#introdução)
  - [Arquivos e Suas Funcionalidades](#arquivos-e-suas-funcionalidades)
    - [`node.c`](#nodec)
    - [`grafo.c`](#grafoc)
    - [`linked-list.c`](#linked-listc)
    - [`heap.c`](#heapc)
    - [`main.c`](#mainc)
    - [`dijkstra.c`](#dijkstrac)
  - [Implementação com Heap](#implementação-com-heap)
  - [Implementação com Lista Encadeada](#implementação-com-lista-encadeada)
  - [Comparação de Desempenho](#comparação-de-desempenho)
    - [Conclusões](#conclusões)
  - [Parâmetros de chamada](#parâmetros-de-chamada)
  - [Entrada](#entrada)
  - [Saída](#saída)
  - [Compilação do Programa](#compilação-do-programa)

## Introdução

O programa tem como objetivo resolver o problema dos caminhos mínimos de fonte única utilizando o algoritmo de Dijkstra com duas estruturas auxiliares
distintas. A seguir, tem-se uma descrição das estruturas desenvolvidas e uma comparação de performance entre as duas estruturas utilizadas pelo Dijkstra.

---

## Arquivos e Suas Funcionalidades

### `node.c`

Este arquivo define uma estrutura básica chamada `Node` contendo três campos: `id` (inteiro), `peso` (float) e `prox` (ponteiro para Node). O significado de cada campo depende da aplicação. O campo `peso` pode tanto indicar o peso de uma aresta (como é o caso dos nós em um lista de adjacências no TAD grafo) quanto indicar o custo até um nó fonte (como acontece com os nós na fila de prioridade). O campo `prox` pode tanto ser usado para o encadeamento de uma lista (como é o caso das listas de adjacências no TAD grafo) quanto para indicar o pai de um nó em uma árvore de caminhos mínimos (como acontece com os nós na fila de prioridade).

**Funções Chave**:

- getters e setters.
- `criaNode`: Cria um novo nó com ID, peso e próximo nó especificados.
- `destroiNode`: Libera a memória alocada para o nó.

---

### `grafo.c`

Este arquivo implementa a **estrutura do grafo** utilizando **listas de adjacências**. Ele é responsável por construir o grafo a partir do arquivo de entrada e fornecer funções de acesso e liberação de memória.

**Funções Chave**:  

- `preencheListaAdj`: Lê o arquivo de entrada e constrói o grafo.  
- `getAdjacentes`: Retorna a lista de nós adjacentes de um vértice.  
- `destroiListaAdj`: Libera a memória alocada para o grafo.  

---

### `linked-list.c`

Este arquivo implementa uma **lista simplesmente encadeada sem sentinela** como fila de prioridades para o algoritmo de Dijkstra. Apesar de ser menos eficiente que a heap, é uma estrutura mais simples de implementar.

Para otimizar operações de inserção e decrescimento de custo optou-se por não ordenar a lista.

---

**Funções Chave**:  

- `insertValue`: Insere um novo nó no início da lista.  
- `removeMinNode`: Percorre a lista para encontrar e remover o nó com menor peso.  
- `getNodeById`: Busca um nó pelo ID na lista.
  
---

### `heap.c`

Este arquivo implementa uma **heap mínima binária** para gerenciar a fila de prioridades utilizada no algoritmo de Dijkstra.

Para otimizar operações de busca optou-se por armazenar um vetor de posições dentro da estrutura, o que deixa constante o tempo de busca (apesar do aumento do consumo de memória). No vetor de posições, o índice i fornece o índice da posição do nó de id i na heap.

---
**Funções Chave**:

- `insereHeap`: Insere um novo nó na heap e corrige sua posição.  
- `extraiMenorElemento`: Remove e retorna o nó com menor peso (raiz da heap).  
- `decresceDistancia`: Decresce o peso e atualiza o pai de um nó, ajustando sua posição na heap.

---

### `main.c`

Programa cliente que **manipula os TADs criados** e **salva os resultados** em um arquivo de saída, além de calcular o tempo de execução do algoritmo.

**Fluxo do Programa**:  

1. Valida os argumentos de entrada (arquivo de entrada e saída).  
2. Constrói o grafo a partir do arquivo de entrada.  
3. Executa o algoritmo de Dijkstra para encontrar os caminhos mínimos.  
4. Ordena e salva os resultados no arquivo de saída.  
5. Libera a memória alocada e exibe o tempo de execução.  

**Funções Chave**:  

- `comparaNode`: Função de comparação entre dois nós pelo peso. A função é utilizada como argumento na chamada ao quicksort da biblioteca padrão.  

**Integração**:  
  
- Utiliza os módulos `Grafo`, `Dijkstra` e `Node` para construir o grafo, calcular os caminhos mínimos e gerenciar os nós.  

---

### `dijkstra.c`

**Fluxo de execução**  

- A estrutura é **inicializada** com todos os nós do grafo, sendo o nó de origem atribuído com custo **zero** e os demais com custo infinito.
- A cada iteração, o **nó com menor custo** é extraído da estrutura e seus vizinhos são avaliados para atualização das distâncias.  
- Se um vizinho pode ser alcançado com menor custo, ele é relaxado (atualiza-se o **nó pai** e o **peso**).

É importante destacar que o Dijkstra realiza quatro operações básicas sobre as estruturas: inserção, extração de mínimo, busca (necessária antes do relaxamento) e descrescimento de chave.
A implementação dessas operações é crítica para o desempenho do algoritmo.

Durante a execução do Dijkstra para um grafo com V vértices e E arestas, tem-se: V operações de inserção, V operações de extração de mínimo, E operações de
busca e, no máximo, E operações de descrescimento de chave.

Conforme dito, o problema de caminhos mínimos foi resolvido utilizando o **algoritmo de Dijkstra** com duas estruturas distintas. São elas:  

1. **Heap mínima binária**
2. **Lista simplesmente encadeada sem sentinela**

A seguir, tem-se as principais diferenças e o impacto de cada abordagem no desempenho do algoritmo.

---

## Implementação com Heap  

**Custos de operações** sobre a heap:

`inserção`: O(log(V))

`extração de mínimo`: O(log(V))

`busca`: O(1)

`descrescimento de chave`: O(log(V))

**Custo total** do Dijkstra com heap:

V\*O(log(V)) + V\*O(log(V)) + E\*O(1) + E\*O(log(V)) = O((V + E)\*log(V)) = **O(V\*log(V))** para grafos esparsos ou **O(V²\*log(V))** para grafos densos.

**Principais Vantagens:**

✅ Melhor eficiência para grafos com muitos vértices.

**Desvantagens:**

❌ Implementação mais complexa.

---

## Implementação com Lista Encadeada  

**Custos de operações** sobre a lista:

`inserção`: O(1)

`extração de mínimo`: O(V)

`busca`: O(V)

`descrescimento de chave`: O(1)

**Custo total** do Dijkstra com lista:

V\*O(1) + V\*O(V) + E\*O(V) + E\*O(1) = O(V² + V\*E) = **O(V²)** para grafos esparsos ou **O(V³)** para grafos densos.

**Principais Vantagens:**

✅ Implementação mais simples.  

**Desvantagens:**

❌ Os tempos de extração do menor nó e de busca crescem significativamente à medida que o número de vértices aumenta.

---

## Comparação de Desempenho  

Para avaliar a eficiência de ambas as implementações, comparou-se seu desempenho em relação a três grafos de entrada:

1. G1: 9 vértices e 28 arestas (esparso)
2. G2: 1.000 vértices e 950.992 arestas (denso)
3. G3: 6.000 vértices e 34.273.941 arestas (denso)

Para cada grafo, foi analisado o tempo total decorrido e a quantidade de bytes alocados pelo programa.

| Implementação              | Complexidade        | G1                      | G2                       | G3       |
|----------------------------|---------------------|-------------------------|--------------------------|----------|
| **Heap**                   | O((E + V)\*log(V))  | 0,0005s / 11.772 bytes  | 0,15s / 22.942.008 bytes | 5,25s / -|
| **Lista Encadeada**        | O(V² + V\*E)        | 0,0004s / 11.800 bytes  | 0,43s / 22.946.000 bytes | 87,2s / -|

---

### Conclusões  

- A **heap** apresentou um **desempenho superior**, especialmente para grafos maiores.
- A **lista encadeada** demonstrou ser uma alternativa válida para grafos pequenos, uma vez que, nesses casos, a diferença de tempo entre as implementações é menos significativa.
- Para aplicações onde a eficiência é um fator crítico, **a implementação com heap é notavelmente a melhor opção**.
- Em termos de utilização de memória a **implementação com lista apresentou um desempenho levemente inferior à implementação com heap**. Isso se deve ao seguinte fato: na heap, tem-se um vetor de ponteiros para os vértices e um vetor de inteiros para as posições dos vértices na heap (conforme explicado anteriormente); na lista, para cada vértice armazenado têm-se um ponteiro para esse e um ponteiro de encadeamento. Sabendo que no computador utilizado para os testes um ponteiro ocupa 8 bytes e um inteiro, 4, é esperado que a lista consuma mais memória, apesar de não ser algo significativamente maior, uma vez que a maior parte dos bytes alocados são para o armazenamento do grafo.

A análise evidencia como a escolha da estrutura de dados impacta diretamente no desempenho de um mesmo algoritmo.  

## Parâmetros de chamada

Os nomes dos arquivos de entrada e saída, respectivamente, devem ser fornecidos na chamada do programa.

**Exemplo**:

```none
./prog grafo_entrada.txt resultado_dijkstra.txt
```

## Entrada

A primeira linha do arquivo de entrada deve ter o nome do nó fonte.

As proximas |V| linhas indicam os nós da rede. Cada linha começa com o nome do nó e os pesos das arestas para os demais nós.

**Obs.**: peso zero ou 'bomba' indica ausência de conexão. Cada linha terá V - 1 distâncias, uma vez que a distância de um nó para si é sempre zero.

**Exemplo**:

```none
node_0
node_0, 10, 0, 5, 0
node_1, 0, 1, 2, 0
node_2, 0, 0, 0, 4
node_3, 0, 3, 3, 0
node_4, 7, 0, 6, 0
```

## Saída

A saída do do programa é salva em um arquivo de texto, contendo os caminhos de menor custo dos nós até a fonte, em ordem crescente de custo.

```none
SHORTEST PATH TO node_0: node_0 <- node_0 (Distance: 0.00)
SHORTEST PATH TO node_3: node_3 <- node_0 (Distance: 5.00)
SHORTEST PATH TO node_1: node_1 <- node_3 <- node_0 (Distance: 8.00)
SHORTEST PATH TO node_2: node_2 <- node_3 <- node_0 (Distance: 8.00)
SHORTEST PATH TO node_4: node_4 <- node_2 <- node_3 <- node_0 (Distance: 12.00)
```

## Compilação do Programa

Para otimizar a **compilação** do programa, foi criado um arquivo Makefile.

`make cheap` compila o código utilizando a heap binária como estrutura auxiliar do Dijkstra.

`make clist` compila o código utilizando a lista encadeada como estrutura auxiliar do Dijkstra.

Ambos os comandos geram um arquivo executável chamado `trab1`.
