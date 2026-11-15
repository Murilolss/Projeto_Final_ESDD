# Enunciado v1 — Projeto Testes de algoritmos de ordenação

> Fonte: `contexto/projeto-exemplo/Testes de algoritmos de ordenação.pdf` (2 páginas).
> É a **primeira versão** do enunciado do projeto final. O `projeto-exemplo` foi feito a partir dela.
> A versão final, que vale para a entrega, está em [Enunciado.md](Enunciado.md).

## Descrição

Programa que simula uma **plataforma interativa para testar e comparar algoritmos de ordenação**. Ele mede o tempo de execução, conta trocas e comparações e mostra informações do processo com **diferentes tamanhos e tipos de listas de números**.

### Visão geral

O software funciona como um **laboratório visual** para analisar o desempenho de códigos de ordenação em tempo real.

### Principais recursos

- Seleção de algoritmos: **Bolha, Inserção, Seleção, Merge e Quick**.
- Geração de dados **aleatórios, invertidos ou ordenados**.
- Painel de estatísticas com **tempo exato**, **número de comparações** e **movimentações**.
- **Modo passo a passo** para avançar a execução do código.

### Dados técnicos exibidos

- Nome do algoritmo em execução.
- Quantidade de itens no conjunto de dados.
- Tempo gasto em milissegundos.
- Contador total de operações lógicas (comparações) e de trocas.

## Estrutura do sistema em C

O programa é dividido em módulos ligados por um **menu principal no terminal**.

### 1. Módulos principais

| Módulo | Função |
|---|---|
| **Gerador de Vetores** | Aloca um conjunto de inteiros com dados aleatórios, ordenados ou invertidos. |
| **Módulo de Algoritmos** | Arquivo `.c` com as funções de ordenação, que recebem o vetor e seu tamanho. |
| **Módulo de Métricas** | Mede o tempo com `time.h` e incrementa contadores (globais ou em struct) de trocas e comparações. |

### 2. Estrutura de dados sugerida

```c
typedef struct {
    char nome[30];
    long long comparacoes;
    long long trocas;
    double tempo_ms;
} Metricas;
```

### 3. Fluxo de execução

1. O usuário define o tamanho do vetor com `scanf`.
2. O sistema aloca o vetor e gera os números base.
3. O usuário escolhe o algoritmo (ex.: `bubble_sort`).
4. A tela atualiza a cada troca de posição de memória.
5. O programa exibe o relatório final de desempenho.

## Comparação com o enunciado final

O enunciado final mantém a ideia da v1 (menu em C, métricas, vários algoritmos) e acrescenta estruturas e integrações.

| Tema | v1 (este PDF) | Final ([Enunciado.md](Enunciado.md)) |
|---|---|---|
| Vetor | Alocado e preenchido | Alocação dinâmica com `malloc`/`realloc`/`free` |
| Métricas | Tempo, comparações e trocas | Também **consumo de memória** |
| Tipos de dados | **Aleatórios, ordenados ou invertidos** | Não menciona |
| Passo a passo | Tela atualiza a cada troca | Pilha para **Desfazer/Undo** no passo a passo |
| Listas | — | Simples, dupla e circular, com Insertion e Merge Sort por ponteiros |
| Fila | — | Execução de testes em lote (batch) |
| Hash | — | (EXTRA) relatórios indexados pelo nome do algoritmo |
| Visualização | No próprio terminal | Exportar JSON/CSV e animar as barras em HTML/CSS/JS |
| Documentação | — | Código e `README.md` em inglês, Git/GitHub, `AI_LOG.md` |

## Situação no código atual (`src/`)

| Item da v1 | Situação |
|---|---|
| Bolha, Inserção, Seleção, Merge e Quick | Feito (7 variantes, `src/sort.c`) |
| `struct Metricas` | Feito como `Metrics` em `src/metrics.h`, em inglês e com `memory_bytes` |
| Tamanho via `scanf`, menu no terminal, relatório final | Feito (`src/main.c`) |
| Dados **aleatórios** | Feito (`vector_fill_random`, permutação 1..N) |
| Dados **ordenados** e **invertidos** | **Falta** (`src/vector.h` só tem preenchimento aleatório) |
| **Modo passo a passo** (tela atualiza a cada troca) | **Falta** (no enunciado final vira o passo a passo com Undo pela pilha) |

Os dois itens que faltam não são exigidos pelo enunciado final, mas valem a pena:

- **Ordenado e invertido** são o melhor e o pior caso de vários algoritmos (Insertion Sort em vetor ordenado é O(n); Quick Sort com pivô no início em vetor ordenado é O(n²)). Isso enriquece a comparação e a arguição.
- O **passo a passo** é a base do Undo da pilha e do log de trocas/comparações que a interface Web vai animar.
