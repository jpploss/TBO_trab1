# 📌 Implementação do Algoritmo de Dijkstra com Heap de Fibonacci

## 📖 Introdução

Este projeto implementa o **algoritmo de Dijkstra** para encontrar o **menor caminho em um grafo ponderado**. Para otimização, utilizamos a **Heap**.

O código segue uma modularização que agrega com clareza, organização e reusabilidade. Além disso, o projeto é gerenciado por um **Makefile**, que automatiza a compilação e execução.

Este documento detalha:
- **A funcionalidade de cada arquivo**.
- **A lógica do Makefile**.
- **Como a entrada é processada**.
- **Passos para execução**.
- **Possíveis melhorias**.

---

## Arquivos e Suas Funcionalidades

# `main.c`

Responsável por:
1. **Ler a entrada do arquivo de input** e transformar os dados na estrutura do grafo.
2. **Criar e inicializar o grafo**, preenchendo sua matriz de adjacência.
3. **Chamar o algoritmo de Dijkstra** a partir do nó de origem especificado.
4. **Exibir os resultados**, ou seja, o caminho mínimo e seus custos.
5. **Liberar a memória alocada** para o grafo.

---

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

Para avaliar a eficiência de ambas as implementações, comparamos seu desempenho em diferentes métricas:  

| Implementação              | Complexidade | Muito Pequeno | Pequeno | Médio | Eficiência Geral |
|----------------------------|---------------------|--------------------------------|------------------|----------------|
| **Heap**                   | O(E + V log V)      | R                         | Moderado         |            |
| **Lista Encadeada Ordenada** | O(V²)             | 0,0004s                          | 0,22s            | 48,14s          |

Caso medio1: 40.3 s
Caso medio2: 44.04 s
Caso medio3: 40.17 s
Caso medio4: 68.05 s
Caso muito pequeno1: 0.00033 s
Caso muito pequeno2: 0.00048 s
Caso pequeno1: 0.0041 s
Caso pequeno2: 0.0044 s
Caso pequeno3: 0.43 s
Caso pequeno4: 0.43 s

---

## **Conclusões**  

- A **Heap** apresentou **desempenho superior**, especialmente para grafos grandes, devido à eficiência da extração e atualização de nós.  
- A **Lista Encadeada** demonstrou ser uma alternativa válida, mas **mais lenta**, devido ao tempo elevado de busca pelo menor elemento a cada iteração.  
- Para aplicações onde a eficiência é um fator crítico, **a implementação com Heap é claramente a melhor opção**.  

Essa análise demonstra como a escolha da estrutura de dados impacta diretamente no desempenho do algoritmo, reforçando a importância da **fila de prioridade eficiente** no problema de caminhos mínimos. 🚀  

---

# `grafo.c` - Implementação da Estrutura de Dados do Grafo

Responsável por gerenciar a **estrutura de dados do grafo**.

📌 **Funções principais em `grafo.c`:**
- `Grafo* criarGrafo(int n);`
  - Inicializa um grafo com `n` vértices.
- `void adicionarAresta(Grafo* g, int origem, int destino, float peso);`
  - Adiciona uma aresta ponderada ao grafo.
- `void destruirGrafo(Grafo* g);`
  - Libera a memória alocada para o grafo.

---

### 📌 `heap.c`

Este arquivo implementa a **Heap de Fibonacci**, uma estrutura avançada para manipulação de **filas de prioridade**.

📌 **Funções principais em `heap.c`:**
- `Heap* criarHeap();`
  - Inicializa uma heap vazia.
- `void inserirHeap(Heap* h, int chave, float prioridade);`
  - Insere um elemento na heap com prioridade associada.
- `int extrairMinimo(Heap* h);`
  - Remove e retorna o menor elemento da heap.
- `void diminuirPrioridade(Heap* h, int chave, float novaPrioridade);`
  - Atualiza a prioridade de um nó na heap.

---

### 📌 `node.c` - Manipulação de Nós

Este módulo define a estrutura dos **nós** do grafo.

📌 **Funções principais em `node.c`:**
- `Node* criarNode(int id, float peso);`
  - Cria um novo nó na lista de adjacência.
- `void destruirNode(Node* node);`
  - Libera a memória alocada para um nó.

---

### 📌 `Makefile` - Automação da Compilação e Execução

O **Makefile** simplifica o processo de **compilação** e **execução** do programa. Ele define três comandos:

```make
comp:
	gcc main.c heap.c node.c grafo.c dijkstra.c -o trab1
```
- **Compila o código** e gera o executável `trab1`.

```make
run:
	./trab1
```
- **Executa o programa** gerado.

```make
runv:
	valgrind --leak-check=full ./trab1
```
- **Executa o Valgrind** para verificar vazamentos de memória.

---

## 📝 Como a Entrada é Tratada

O programa recebe um **arquivo de entrada** contendo:
1. **O nome do nó de origem** (primeira linha).
2. **A matriz de adjacência**:
   - Cada linha representa um **vértice** do grafo.
   - Os valores indicam o **peso da aresta** entre os vértices.
   - `"bomba"` representa **ausência de conexão** (peso infinito).

### 🔹 Exemplo de Entrada:
```
node_54
node_0, 6748.80, 2035.20, 8387.20, bomba, 2886.40, 192.00, 7209.60, ...
node_1, 6748.80, 1292.80, 4617.60, 7539.20, 1920.00, 4854.40, 3091.20, ...
node_2, 2035.20, 1292.80, 8795.20, 2569.60, 8700.80, bomba, 9884.80, ...
```

📌 **Fluxo de processamento:**
1. Lê o **nó de origem** (`node_54`).
2. Constrói a **matriz de adjacência**, transformando `"bomba"` em **infinito**.
3. Adiciona **arestas ao grafo** chamando `adicionarAresta()`.
4. **Executa o algoritmo de Dijkstra** a partir do nó de origem.
5. **Imprime o menor caminho e o custo total**.

---

## 🚀 Execução do Programa

Para **compilar e rodar** o programa:

```sh
make comp
make run
```

Para verificar **vazamentos de memória** com Valgrind:

```sh
make runv
```

---

## 🔧 Melhorias Futuras

- Permitir **pesquisa do menor caminho entre qualquer par de nós**.
- Implementar **leitura dinâmica** do arquivo de entrada.
- Otimizar a **Heap de Fibonacci** para melhor desempenho.
- Criar uma **interface gráfica (GUI)** para melhor visualização.

---

## 📜 Conclusão

Este projeto implementa o **algoritmo de Dijkstra com Heap de Fibonacci**, garantindo alta eficiência na busca pelo menor caminho em grafos ponderados. 🚀

Dúvidas ou sugestões? Contribua com melhorias! 🎯