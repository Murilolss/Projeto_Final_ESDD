# Algoritmos de Busca — Sequencial, Binária e Interpolação

> Fonte: `contexto/pdfs/Algoritmos de Busca.pdf` (16 slides, set/2026)
> Código: `contexto/codigo-exemplos/03. Algoritmos de busca/códigos/` (`busca_sequencial.c`, `busca_binaria.c`, `busca_interpolacao.c`)

## Busca

- Operação muito frequente; a eficiência impacta diretamente o desempenho.
- Um algoritmo de busca recebe um argumento `a` e tenta encontrar o elemento cuja chave seja `a`.

## Busca sequencial

- Percorre todo o vetor comparando cada elemento com a **chave**, até encontrar ou chegar ao fim.
- Funciona para vetor **ordenado ou não**; ineficiente para grandes volumes.
- Melhor caso O(1) (primeira posição); pior caso O(n).

```c
int buscaSequencial(int v[], int chave){
    int i = 0;
    while ((v[i] != chave) && (i < TAM))   // obs.: a ordem ideal é (i < TAM) && (v[i] != chave)
        i = i + 1;
    if (i < TAM) return i;
    else return -1;
}
```

## Busca binária

- **Requisito: vetor ordenado.**
- Divide repetidamente ao meio, comparando o elemento central com a chave:
  - igual → encontrou;
  - chave menor → busca na metade esquerda;
  - chave maior → busca na metade direita (ordem crescente).
- Melhor caso O(1) (chave no meio); pior caso **O(log n)** — cada comparação reduz os candidatos pela metade.

```c
int buscaBinaria(int v[], int chave){
    int ini=0, fim=TAM-1, meio;
    while(ini<=fim){
        meio=(ini+fim)/2;
        if(v[meio]==chave) return meio;
        if(v[meio]<chave) ini=meio+1;
        if(v[meio]>chave) fim=meio-1;
    }
    return -1;
}
```

## Busca por interpolação

- Evolução da binária para vetores **ordenados e uniformemente distribuídos** (como abrir o dicionário perto do início para "Algoritmo").
- Fórmula do "meio":
  `meio = ini + ((fim-ini)*(chave-v[ini])) / (v[fim]-v[ini]);`
- Melhor/médio caso **O(log log n)**; pior caso **O(n)** com dados desproporcionais (ex.: `[1, 2, 4, 8, 1000]`).

```c
int buscaInterpolacao(int v[], int chave) {
    int ini = 0, fim = TAM - 1, meio;
    while (ini <= fim && chave >= v[ini] && chave <= v[fim]) {
        meio = ini + ((fim-ini)*(chave-v[ini])) / (v[fim]-v[ini]);
        if(v[meio]==chave) return meio;
        if(v[meio]<chave) ini=meio+1;
        if(v[meio]>chave) fim=meio-1;
    }
    return -1;
}
```

> Cuidado: se `v[fim] == v[ini]` há divisão por zero.

## Relevância para o projeto

O `projeto-exemplo` usa `PesqSeq` (busca sequencial) para gerar números sem repetição. Em listas encadeadas só a busca sequencial é viável (sem acesso por índice).
