# Implementação do Algoritmo de Dijkstra com Heap Binária

## Introdução

O código segue uma modularização que agrega com clareza, organização e reusabilidade. Além disso, o projeto é gerenciado por um **Makefile**, que automatiza a compilação e execução.

Este documento detalha:
- **A funcionalidade de cada arquivo**.
- **A lógica do Makefile**.
- **Como a entrada é processada**.
- **Passos para execução**.
- **Possíveis melhorias**.

---

## Arquivos e Suas Funcionalidades

----------------

# `main.c` - **Execução do Programa**

Responsável por **manipular os TADs criados** e **salvar os resultados** em um arquivo de saída. Ele também mede o tempo de execução do algoritmo.

---

## **Principais Pontos**  
- **Fluxo do Programa**:  
  1. Valida os argumentos de entrada (arquivo de entrada e saída).  
  2. Constrói o grafo a partir do arquivo de entrada.  
  3. Executa o algoritmo de Dijkstra para encontrar os caminhos mínimos.  
  4. Ordena e salva os resultados no arquivo de saída.  
  5. Libera a memória alocada e exibe o tempo de execução.  

- **Funções Chave**:  
  - `comparaNode`: Função de comparação para ordenar os nós pelo peso.  

- **Integração**:  
  - Utiliza os módulos `grafo`, `dijkstra` e `node` para construir o grafo, calcular os caminhos mínimos e gerenciar os nós.  

---

## **Decisões Importantes**  
- **Ordenação dos Resultados**: Os caminhos mínimos são ordenados pelo peso antes de serem salvos no arquivo de saída.  
- **Medição de Tempo**: O tempo de execução é medido e exibido ao final, permitindo a análise de desempenho.  

----------------

# `dijkstra.c` - **Análise do Algoritmo de Dijkstra**

O problema de caminhos mínimos foi resolvido utilizando o **algoritmo de Dijkstra** em duas abordagens distintas:  
1. **Implementação com Heap** – que otimiza as operações de extração e atualização de prioridades.  
2. **Implementação com Lista Encadeada** – que utiliza uma estrutura mais simples, mas com maior custo computacional.  

A seguir, detalhamos as principais diferenças e o impacto de cada abordagem no desempenho do algoritmo.  

---

## **1. Implementação com Heap (Fila de Prioridade Eficiente)**  

A primeira versão do **Dijkstra** foi implementada utilizando uma **Heap** como fila de prioridade. Essa estrutura permite a extração eficiente do menor elemento e a atualização de pesos com um custo otimizado, resultando em um tempo de execução próximo de **O(V log V)**.  

### **Funcionamento:**  
- A heap é **inicializada** com todos os nós do grafo, sendo o nó de origem atribuído com custo **zero** e os demais com custo infinito.  
- A cada iteração, o **nó com menor custo** é extraído da heap e seus vizinhos são avaliados para atualização das distâncias.  
- Se um vizinho pode ser alcançado com menor custo, ele é atualizado na heap e tem seu **nó pai ajustado**, garantindo a reconstrução correta do caminho mínimo.  

### **Principais Vantagens:**  
✅ Melhor eficiência para grafos grandes, pois a extração do menor custo ocorre em **O(log V)**.  
✅ Atualizações rápidas na fila de prioridade, reduzindo o tempo total de execução.  
✅ Boa escalabilidade para redes com **muitos vértices e arestas**.  

### **Desvantagens:**  
❌ A implementação da **Heap** é mais complexa e exige mais memória do que outras abordagens.  

---

## **2. Implementação com Lista Encadeada (Fila de Prioridade Simples)**  

A segunda implementação do algoritmo de Dijkstra substitui a heap por uma **lista encadeada ordenada**, onde os nós são armazenados em ordem crescente de custo. Embora mais simples de implementar, essa abordagem **tem um custo maior na busca pelo menor elemento**, resultando em um tempo de execução **O(V²)** em casos desfavoráveis, visto que a lista deve ser percorrida a cada iteração.

### **Funcionamento:**  
- A estrutura é inicializada como uma **lista ordenada** contendo todos os nós do grafo. O nó de origem começa com custo **zero** e os demais com infinito.  
- A cada iteração, percorremos a lista para encontrar o **nó com menor custo**, que é então removido e processado.  
- Os vizinhos do nó removido são atualizados conforme necessário, garantindo a propagação das menores distâncias ao longo da rede.  

### **Principais Vantagens:**  
✅ Implementação mais simples, sem a necessidade de gerenciar estruturas complexas como heaps.  
✅ Menor consumo de memória, pois não exige estruturas adicionais além da lista encadeada.  

### **Desvantagens:**  
❌ O tempo de busca do menor nó cresce significativamente à medida que o grafo aumenta.  
❌ A ordenação manual dos elementos na lista encadeada torna o algoritmo **menos eficiente para grandes volumes de dados**.  
---

## **Comparação de Desempenho**  

Para avaliar a eficiência de ambas as implementações, comparamos seu desempenho em relação à média dos tipos de arquivos de entrada:

| Implementação              |     Complexidade    |         Muito Pequeno          |      Pequeno     |     Médio      |
|----------------------------|---------------------|--------------------------------|------------------|----------------|
| **Heap**                   | O((E + V) log V)      | 0.00046s                       | 0.083s           | 4,27s          |
| **Lista Encadeada Ordenada** | O(V²)             | 0,0004s                        | 0,22s            | 48,14s         |

---

## **Conclusões**  

- A **Heap** apresentou **desempenho superior**, especialmente para grafos grandes, devido à eficiência da extração e atualização de nós.
- Para grafos pequenos, a diferença de tempo entre as implementações é menos significativa, mas ainda favorece a **Heap**. 
- A **Lista Encadeada** demonstrou ser uma alternativa válida, mas **mais lenta**, devido ao tempo elevado de busca pelo menor elemento a cada iteração.  
- Para aplicações onde a eficiência é um fator crítico, **a implementação com Heap é claramente a melhor opção**.  

Essa análise demonstra como a escolha da estrutura de dados impacta diretamente no desempenho do algoritmo, reforçando a importância da **fila de prioridade eficiente** no problema de caminhos mais curtos.  

----------------

# `grafo.c` - Implementação da Estrutura de Dados do Grafo

Este arquivo implementa a **estrutura do grafo** utilizando uma **lista de adjacências**. Ele é responsável por ler o arquivo de entrada, construir o grafo e fornecer funções de acesso para o algoritmo de Dijkstra.

---

## **Principais Pontos**  
- **Estruturas**:  
  - `Grafo`: Armazena vértices, número de vértices e o ID do vértice de origem.  
  - `Vertice`: Contém o nome do vértice, número de adjacentes e uma lista encadeada de nós adjacentes.  

- **Funções Chave**:  
  - `preencheListaAdj`: Lê o arquivo de entrada e constrói o grafo.  
  - `getAdjacentes`: Retorna a lista de nós adjacentes de um vértice.  
  - `destroiListaAdj`: Libera a memória alocada para o grafo.  

- **Integração**:  
  - Fornece dados essenciais para o Dijkstra, como vértices adjacentes e pesos das arestas.  

---

## **Decisões Importantes**  
- Listas de adjacência **sem sentinela** para eficiência.  
- Arestas com peso zero são **ignoradas**, simplificando a representação.  

----------------

# `heap.c` - **Gerenciamento da Fila de Prioridades**

Este arquivo implementa uma **heap binária** para gerenciar a fila de prioridades utilizada no algoritmo de Dijkstra. A heap é otimizada para operações de inserção, remoção e atualização de prioridades, garantindo eficiência no algoritmo.

---

## **Principais Pontos**  
- **Estruturas**:  
  - `Heap`: Armazena um array de nós (`elementos`), um vetor de posições (`posicoes`) e o tamanho atual da heap (`tamAtual`).  

- **Funções Chave**:  
  - `insereHeap`: Insere um novo nó na heap e corrige sua posição.  
  - `extraiMenorElemento`: Remove e retorna o nó com menor peso (raiz da heap).  
  - `atualizaDistanciaEPai`: Atualiza o peso e o pai de um nó, ajustando sua posição na heap.  

- **Integração**:  
  - Fornece uma estrutura eficiente para o Dijkstra gerenciar os nós a serem processados, garantindo operações rápidas de extração e atualização.  

---

## **Decisões Importantes**  
- **Vetor de posições**: Mantém o controle das posições dos nós na heap, permitindo atualizações eficientes.    

----------------

# `linked-list.c` - **Fila de Prioridades com Lista Encadeada**

Este arquivo implementa uma **lista encadeada simples** como fila de prioridades para o algoritmo de Dijkstra. É uma alternativa menos eficiente à heap, porém mais simples de implementar.

---

## **Principais Pontos**  
- **Estruturas**:  
  - `LinkedList`: Armazena a cabeça da lista (`head`) e seu tamanho (`size`).  
  - `LLNode`: Nós da lista, contendo um ponteiro para `Node` (dados do vértice) e o próximo nó (`next`).  

- **Funções Chave**:  
  - `insertValue`: Insere um novo nó no início da lista (`O(1)`).  
  - `removeMinNode`: Percorre a lista para encontrar e remover o nó com menor peso (`O(n)`).  
  - `getNodeById`: Busca um nó pelo ID na lista (`O(n)`).  

- **Integração**:  
  - Fornece a funcionalidade básica de fila de prioridades para o Dijkstra, porém com custo computacional maior na remoção do menor elemento.  

---

## **Decisões Importantes**  
- **Inserção no início**: Garante `O(1)` para inserção, mas exige busca linear (`O(n)`) para extrair o mínimo.  
- **Sem ordenação**: A lista não mantém os elementos ordenados, o que simplifica a inserção mas penaliza a extração.  

Este módulo é uma **alternativa mais simples** à heap, porém recomendado apenas para grafos pequenos devido ao alto custo de operações.

----------------

# `node.c` - **Gerenciamento de Nós**

Este arquivo define a estrutura básica de um **nó** (`Node`), utilizado para representar vértices e suas conexões no grafo. Ele fornece funções para criação, manipulação e destruição de nós.

---

## **Principais Pontos**  
- **Estrutura**:  
  - `Node`: Armazena o ID do vértice (`id`), o peso da aresta (`peso`) e um ponteiro para o próximo nó (`prox`).  

- **Funções Chave**:  
  - `criaNode`: Cria um novo nó com ID, peso e próximo nó especificados.  
  - `destroiNode`: Libera a memória alocada para o nó.  

- **Integração**:  
  - Utilizado em listas de adjacências, heaps e outras estruturas para representar vértices.

---

## **Decisões Importantes**  
- **Simplicidade**: A estrutura é minimalista, focada em armazenar apenas informações essenciais.  
- **Reutilização**: O nó é usado em múltiplos contextos (listas, heaps, etc.), garantindo consistência no projeto.  

----------------

# Execução do Programa

Para **compilar e rodar** o programa:

```sh
make comp
make run
```

Para verificar **vazamentos de memória** com Valgrind:

```sh
make runv
```
