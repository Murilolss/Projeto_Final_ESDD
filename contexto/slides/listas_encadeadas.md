# Listas Encadeadas (simplesmente encadeadas)

> Fonte: `contexto/pdfs/listas_encadeadas.pdf`
> Código: `contexto/codigo-exemplos/08. Lista simplesmente encadeada/codigos/` (`lista.h`, `lista.c`, `main.c`, `exemplo.png`)

## Objetivos

Conceito de lista encadeada e nó; comparar com vetores; papel dos ponteiros e memória dinâmica; relacionar TAD/interface/implementação; implementar inserção, busca, remoção e percurso em C.

## Motivação

Sistema web de **links favoritos**: o usuário adiciona, remove e pesquisa links; a quantidade varia. Como armazenar uma coleção que cresce e diminui **sem deslocar elementos**?

## O que é

- Estrutura dinâmica de **nós conectados por ponteiros**.
- Cada nó guarda um **dado** e o **endereço do próximo**.
- Nós não precisam ser contíguos na memória.
- Ponteiro `inicio` (head) aponta para o primeiro nó; o último aponta para `NULL`.

`inicio → [10|*] → [20|*] → [30|NULL]`

## Tipos

| Simples | Dupla | Circular |
|---|---|---|
| um ponteiro (próximo) | dois ponteiros (anterior e próximo) | último aponta para o primeiro |
| `[10]→[20]→[30]` | `[10]⇄[20]⇄[30]` | `[10]→[20]→[30]→(volta)` |

## TAD

| Interface (o que faz) | Implementação (como faz) |
|---|---|
| `criarLista()` | `struct` para nós |
| `inserirInicio()`, `inserirFim()` | ponteiros para ligar |
| `buscar()`, `remover()` | `malloc()` |
| `imprimir()`, `destruirLista()` | `free()` |

## Nó em C

```c
typedef struct No {
    int dado;
    struct No *prox;
} No;

No *inicio = NULL;   // NULL = lista vazia / fim
```

## Implementação de referência (`lista.c`, ponteiro opaco `Lista`)

```c
// lista.h
typedef struct Lista Lista;
Lista *criarLista(void);
int inserirInicio(Lista *lista, int valor);
int inserirFim(Lista *lista, int valor);
int buscar(Lista *lista, int valor);
int remover(Lista *lista, int valor);
void imprimir(Lista *lista);
void destruirLista(Lista *lista);
```

```c
// lista.c (trechos)
struct Lista { No *inicio; };

int inserirInicio(Lista *lista, int valor) {
    if (lista == NULL) return 0;
    No *novo = malloc(sizeof(No));
    if (novo == NULL) return 0;
    novo->dado = valor;
    novo->prox = lista->inicio;
    lista->inicio = novo;
    return 1;
}

int inserirFim(Lista *lista, int valor) {
    /* ... */
    if (lista->inicio == NULL) lista->inicio = novo;
    else {
        No *atual = lista->inicio;
        while (atual->prox != NULL) atual = atual->prox;
        atual->prox = novo;
    }
    return 1;
}

int remover(Lista *lista, int valor) {
    No *atual = lista->inicio, *anterior = NULL;
    while (atual != NULL && atual->dado != valor) { anterior = atual; atual = atual->prox; }
    if (atual == NULL) return 0;
    if (anterior == NULL) lista->inicio = atual->prox;
    else anterior->prox = atual->prox;
    free(atual);
    return 1;
}

void destruirLista(Lista *lista) {
    No *atual = lista->inicio;
    while (atual != NULL) { No *temp = atual; atual = atual->prox; free(temp); }
    free(lista);
}
```

## Operações (resumo dos slides)

1. **Inserir no início:** `novo->prox = inicio; inicio = novo;` — O(1).
2. **Inserir no fim:** percorre até `atual->prox == NULL` e liga — O(n) (O(1) mantendo ponteiro para o último).
3. **Percorrer:** `atual = atual->prox` até `NULL`.
4. **Buscar:** compara `atual->dado` com o valor.
5. **Remover:** localizar, guardar anterior, religar (anterior ou início), `free()`.

## Custos

| Operação | Custo |
|---|---|
| Inserir no início | O(1) |
| Inserir no final | O(n)* |
| Buscar | O(n) |
| Remover por valor | O(n) |
| Percorrer | O(n) |

## Vetor × lista encadeada

| Característica | Vetor | Lista encadeada |
|---|---|---|
| Acesso por índice | O(1) | O(n) |
| Inserção no início | O(n) | O(1) |
| Tamanho | definido / realocável | dinâmico |
| Memória extra | baixa | ponteiro por nó |
| Armazenamento | sequencial | nós ligados por endereço |

## Estudo de caso

Links favoritos: nó com `Link { int id; char descricao[100]; char url[200]; }` — ver `estudo de caso.md`.

## Resumo

Lista encadeada = nós + ponteiros; TAD separa interface e implementação; `malloc()` aloca, `free()` libera; escolha a estrutura conforme o problema.

## Relevância para o projeto

Base para as listas do benchmark. Para a **lista circular** (não há código-exemplo), o último nó aponta para o primeiro e os laços terminam quando `atual->prox == inicio`.
