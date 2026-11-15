# Métodos de classificação: MergeSort e QuickSort

> Fonte: `contexto/pdfs/Métodos de classificação (MergeSort e QuickSort).pdf` (11 slides)
> Código: `contexto/codigo-exemplos/02. Métodos de classificação/códigos/` (`mergesort_recursivo.c`, `mergesort_iterativo.c`, `quicksort_pivo_inicio.c`, `quicksort_pivo_ultimo.c`)

## Princípio da Divisão e Conquista

- **Dividir** o problema em subproblemas.
- **Conquistar** os subproblemas recursivamente (se pequenos o bastante, resolver diretamente).
- **Combinar** as soluções na solução do problema original.

## MergeSort (ordenação por intercalação)

Divide o vetor pela metade recursivamente até sobrar 1 elemento; depois **intercala** (merge) as partes já ordenadas.

Exemplo do slide: `7 5 2 4 1 6 3 0` → divide até elementos unitários → combina: `5 7 | 2 4 | 1 6 | 0 3` → `2 4 5 7 | 0 1 3 6` → `0 1 2 3 4 5 6 7`.

```c
void mergesort(int vetor[], int esquerda, int direita) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        mergesort(vetor, esquerda, meio);
        mergesort(vetor, meio + 1, direita);
        intercalar(vetor, esquerda, meio, direita);
    }
}

void intercalar(int vetor[], int esquerda, int meio, int direita) {
    int i, j, k;
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;
    int V_Esquerda[n1];   // VLA na pilha — cuidado com vetores grandes
    int V_Direita[n2];
    for (i = 0; i < n1; i++) V_Esquerda[i] = vetor[esquerda + i];
    for (j = 0; j < n2; j++) V_Direita[j] = vetor[meio + 1 + j];
    i = 0; j = 0; k = esquerda;
    while (i < n1 && j < n2) {
        if (V_Esquerda[i] <= V_Direita[j]) { vetor[k] = V_Esquerda[i]; i++; }
        else                               { vetor[k] = V_Direita[j];  j++; }
        k++;
    }
    while (i < n1) { vetor[k] = V_Esquerda[i]; i++; k++; }
    while (j < n2) { vetor[k] = V_Direita[j];  j++; k++; }
}
```

Versão **iterativa** (`mergesort_iterativo.c`): `tamanho_atual = 1, 2, 4, 8...` e para cada `esquerda` calcula `meio = menor(esquerda + tamanho_atual - 1, tamanho - 1)` e `direita = menor(esquerda + 2*tamanho_atual - 1, tamanho - 1)`, chamando `intercalar`.

Complexidade: **O(n log n)** em todos os casos; memória extra O(n).

## QuickSort (ordenação rápida)

- **Escolha do pivô:** primeiro, último ou do meio.
- **Particionamento:** menores que o pivô à esquerda, maiores à direita.
- **Recursão:** repete nas sublistas esquerda e direita.

Exemplo do slide: `25 57 48 37 12 92 86 33` com pivô 25 → `12 25 57 48 37 92 86 33` → subproblemas `(12)` e `(57 48 37 92 86 33)` … → `12 25 33 37 48 57 86 92`.

```c
void QuickSort(int numeros[], int inicio, int fim){
    if (inicio < fim) {
        int pivo = particionar(numeros, inicio, fim);
        QuickSort(numeros, inicio, pivo - 1);
        QuickSort(numeros, pivo + 1, fim);
    }
}

// Pivô = ÚLTIMO elemento (Lomuto)
int particionar(int vetor[], int inicio, int fim) {
    int pivo = vetor[fim];
    int i = (inicio - 1);
    for (int j = inicio; j <= fim - 1; j++) {
        if (vetor[j] < pivo) {
            i++;
            int temp = vetor[i]; vetor[i] = vetor[j]; vetor[j] = temp;
        }
    }
    int temp = vetor[i + 1]; vetor[i + 1] = vetor[fim]; vetor[fim] = temp;
    return (i + 1);
}
```

Variante **pivô = primeiro** (`quicksort_pivo_inicio.c`): percorre de trás para frente (`j = fim .. inicio+1`), move os maiores que o pivô para o fim (`i` começa em `fim + 1` e decrementa), e por fim troca o pivô para `i - 1`.

Complexidade: médio **O(n log n)**; pior **O(n²)** (ex.: vetor já ordenado com pivô no extremo).

## Exercício

Executar passo a passo a função `particionar` com diferentes pivôs (início, meio, último) e diferentes configurações de dados.

## Relevância para o projeto

- O enunciado pede **MergeSort em listas encadeadas** (dividir a lista com ponteiros lento/rápido e intercalar religando nós — sem vetores temporários).
- Para vetores grandes, os VLAs `V_Esquerda[n1]` podem estourar a pilha; com alocação dinâmica, trocar por `malloc`/`free`.
