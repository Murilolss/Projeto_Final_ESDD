# Introdução às Estruturas de Dados e Notação Big-O

> Fonte: `contexto/pdfs/Introdução às Estruturas de Dados e Notação BigO.pdf` (15 slides)
> Código: `contexto/codigo-exemplos/01. Introdução as Estruturas de dados e Notação Big-O/códigos/exemploBuscaBinaria.c`

## Conceitos

- **Estrutura de dados:** forma organizada de armazenar, gerenciar e processar dados para usá-los de maneira eficiente. Escolher a estrutura certa reduz drasticamente o tempo de execução.
- **Notação Big-O:** mede a eficiência de um algoritmo em relação ao tamanho da entrada `n` — como tempo ou memória crescem com os dados.
  - Foca sempre no **pior caso** (worst-case).
  - **Ignora constantes** e termos de menor ordem.

## Principais complexidades (do mais rápido ao mais lento)

| Big-O | Nome | Exemplo |
|---|---|---|
| O(1) | Constante | Acessar elemento de vetor pelo índice |
| O(log n) | Logarítmica | Busca binária |
| O(n) | Linear | Percorrer uma lista |
| O(n log n) | Linearítmica | Merge Sort, Heap Sort |
| O(n²) | Quadrática | Bubble Sort, Selection Sort |
| O(2ⁿ) | Exponencial | Problemas com todas as combinações possíveis |
| O(n!) | Fatorial | Caixeiro Viajante (força bruta) |

## Custo por estrutura

- **Vetor (array):** acesso por índice O(1); busca por valor O(n); inserção/remoção no início O(n) (desloca elementos).
- **Lista encadeada:** acesso/busca O(n) (nó a nó); inserção/remoção no início O(1) (só ponteiros).
- **Tabela Hash:** busca, inserção e remoção O(1) em média.

| Estrutura | Busca | Inserção | Remoção |
|---|---|---|---|
| Vetor | O(n)* | O(n) | O(n) |
| Lista Ligada | O(n) | O(1)** | O(1)** |
| Pilha | O(n) | O(1) | O(1) |
| Fila | O(n) | O(1) | O(1) |
| Tabela Hash | O(1)*** | O(1)*** | O(1)*** |

\* Acesso por índice é O(1); busca por valor é O(n).
\** Considerando que a posição do elemento já é conhecida.
\*** Média; no pior caso O(n) por colisões.

## Para que serve a análise Big-O

- Comparar algoritmos independentemente do hardware.
- Escolher a estrutura mais adequada ao problema.
- Manter sistemas eficientes com grandes volumes de dados.
- Prever o impacto do crescimento dos dados no desempenho.

## Exemplos de código (slides 10–12)

```c
// O(1) — Retorna o primeiro elemento. Sempre faz apenas 1 operação.
int primeiro_elemento(int arr[], int tamanho) {
    if (tamanho > 0) {
        return arr[0];
    }
    return -1; // Retorno padrão para array vazio
}
```

```c
// O(n) — Busca um elemento. Se o array dobrar de tamanho, o pior caso dobra de tempo.
int buscar_elemento(int arr[], int tamanho, int alvo){
    for (int i = 0; i < tamanho; i++) {
        if (arr[i] == alvo) {
            return 1; // Elemento encontrado
        }
        return 0; // (no slide está dentro do for — bug: deveria ficar após o laço)
    }
}
```

```c
// O(n²) — Verifica se existem números repetidos usando laços aninhados.
int encontrar_duplicatas(int arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        // O laço interno começa uma posição à frente para evitar comparar o número consigo mesmo
        for (int j = i + 1; j < tamanho; j++) {
            if (arr[i] == arr[j]) {
                return 1; // Duplicata encontrada
            }
        }
    }
    return 0;
}
```

## Busca binária — por que O(log n) (slides 13–14)

Código idêntico a `exemploBuscaBinaria.c` (`busca_binaria(int arr[], int tamanho, int alvo)`).

- Passo 1: olha o vetor inteiro (10 elementos), calcula o meio.
- Passo 2: espaço cortado pela metade → 5 elementos.
- Passo 3: → 2 elementos. Passo 4: → 1 elemento.
- Em 1.000.000 elementos: busca linear faz até 1 milhão de comparações; binária, no máximo ~20.
- **Obs.:** usar `int meio = inicio + (fim - inicio) / 2;` em vez de `(inicio + fim) / 2` para evitar **overflow de inteiro**.

## Material web

- Big-O Cheat Sheet (tabelas de complexidade).
- Visualgo (animações de estruturas de dados).
