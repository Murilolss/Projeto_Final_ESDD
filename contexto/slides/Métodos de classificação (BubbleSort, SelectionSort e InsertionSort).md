# Métodos de classificação: BubbleSort, SelectionSort e InsertionSort

> Fonte: `contexto/pdfs/Métodos de classificação (BubbleSort, SelectionSort e InsertionSort).pdf` (13 slides)
> Código: `contexto/codigo-exemplos/02. Métodos de classificação/códigos/` (`bubblesort.c`, `selectionsort.c`, `insertionsort.c`) + vídeo `softsort.mp4`

## Classificação / ordenação

- Dados chegam em ordem aleatória; muitas vezes precisamos deles ordenados.
- Buscar em dados ordenados é mais eficiente (ex.: busca binária).
- Algoritmos clássicos fazem **comparações sucessivas** e **trocas de posição** — exatamente as métricas que o projeto contabiliza.

Métodos: **Seleção** (Selection), **Troca** (Bubble), **Inserção** (Insertion).

## SelectionSort (seleção)

1. Selecionar o menor valor do conjunto.
2. Trocá-lo com o elemento da primeira posição.
3. Repetir para os demais até restar apenas um.

```c
void SelectionSort(int numeros[]){
    int i, j, posMenor, aux;
    for(i=0;i<TAM-1;i++){
        posMenor = i;
        for(j=i+1;j<TAM;j++){
            if(numeros[j]<numeros[posMenor])
                posMenor = j;
        }
        if(i!= posMenor){
            aux=numeros[i];
            numeros[i]=numeros[posMenor];
            numeros[posMenor]=aux;
        }
    }
}
```

## BubbleSort (método da bolha)

Compara vizinhos e troca se estiverem fora de ordem. A cada passagem, o maior elemento ainda não ordenado "flutua" para o fim.

1. **Comparação par a par:** posição `i` com `i+1`.
2. **Troca:** se esquerda > direita.
3. **Avanço:** próximo par até o fim.
4. **Repetição:** nova varredura; encerra quando uma varredura completa não faz nenhuma troca.

```c
void BubbleSort(int numeros[]){
    int i, continua, aux;
    do{
        continua = 0;
        for(i=0;i<TAM-1;i++){
            if(numeros[i]>numeros[i+1]){
                aux=numeros[i];
                numeros[i]=numeros[i+1];
                numeros[i+1]=aux;
                continua=1;
            }
        }
    }while(continua);
}
```

## InsertionSort (inserção)

Mantém um "subconjunto" ordenado no início e, a cada passo, insere mais um elemento nele.

1. **Divisão inicial:** `i=0` é um subconjunto ordenado de tamanho 1.
2. **Seleção da chave:** próximo elemento não ordenado.
3. **Comparação e deslocamento:** da direita para a esquerda, elementos maiores que a chave são deslocados uma posição à direita.
4. **Inserção:** a chave vai para o espaço vago.
5. **Repetição** até o fim.

```c
void insertionSort(int numeros[]) {
    for (int i = 1; i < TAM; i++) {
        int chave = numeros[i];
        int j = i - 1;
        // Desloca elementos maiores que a chave para abrir espaço
        while (j >= 0 && numeros[j] > chave) {
            numeros[j + 1] = numeros[j];
            j = j - 1;
        }
        numeros[j + 1] = chave; // Insere a chave na posição correta
    }
}
```

## Complexidade (referência: slide Big-O)

| Algoritmo | Melhor | Médio | Pior |
|---|---|---|---|
| Bubble | O(n) (com flag `continua`) | O(n²) | O(n²) |
| Selection | O(n²) | O(n²) | O(n²) |
| Insertion | O(n) | O(n²) | O(n²) |

## Relevância para o projeto

- O enunciado pede **InsertionSort sobre listas encadeadas** manipulando ponteiros (na lista duplamente encadeada dá para andar para trás como no vetor; na simples, insere-se o nó na posição correta de uma lista resultado).
- Estilo de nomes do professor: funções `BubbleSort`, `SelectionSort`, `insertionSort`; vetor chamado `numeros`; variáveis `aux`, `chave`, `posMenor`, `continua`.
