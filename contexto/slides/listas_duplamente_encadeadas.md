# Listas Duplamente Encadeadas

> Fonte: `contexto/pdfs/listas_duplamente_encadeadas.pdf`
> Código: não há arquivo em `codigo-exemplos` — o código abaixo é o dos slides.

## Objetivos

Explicar `ant` e `prox`; inicializar lista vazia e criar nós com `malloc`; inserir no início e fim mantendo elos consistentes; percorrer nos dois sentidos; buscar e remover sem perder referências; liberar tudo com `free`.

## Revisão (lista simples)

Navegação em um único sentido; para voltar, é preciso percorrer desde o início. Econômica em memória.

## Conceito

- Cada nó guarda **dado**, endereço do **anterior** (`ant`) e do **próximo** (`prox`).
- Primeiro nó: `ant = NULL`; último: `prox = NULL`.
- Percorre do início ao fim e do fim ao início.
- **Regra de consistência:** se `A->prox == B`, então `B->ant == A`.

## Estruturas

```c
typedef struct No {
    int dado;
    struct No *ant;   // endereço do nó anterior
    struct No *prox;  // endereço do próximo nó
} No;

typedef struct {
    No *inicio;       // primeiro nó
    No *fim;          // último nó
} Lista;
```

Manter `inicio` e `fim` permite inserir nas duas extremidades em O(1).

## Inicialização e criação de nó

```c
void inicializar(Lista *lista) { lista->inicio = NULL; lista->fim = NULL; }

No *criarNo(int valor) {
    No *novo = malloc(sizeof(No));
    if (novo == NULL) return NULL;
    novo->dado = valor;
    novo->ant = NULL;
    novo->prox = NULL;
    return novo;
}
```

## Inserção

```c
void inserirInicio(Lista *l, int valor) {
    No *n = criarNo(valor);
    if (n == NULL) return;
    n->prox = l->inicio;
    if (l->inicio != NULL) l->inicio->ant = n;
    else l->fim = n;                 // lista estava vazia
    l->inicio = n;
}

void inserirFim(Lista *l, int valor) {
    No *n = criarNo(valor);
    if (n == NULL) return;
    n->ant = l->fim;
    if (l->fim != NULL) l->fim->prox = n;
    else l->inicio = n;              // lista estava vazia
    l->fim = n;
}
```

## Percurso nos dois sentidos

```c
void mostrarInicio(Lista *l) {
    for (No *p = l->inicio; p != NULL; p = p->prox) printf("%d ", p->dado);
    printf("\n");
}
void mostrarFim(Lista *l) {
    for (No *p = l->fim; p != NULL; p = p->ant) printf("%d ", p->dado);
    printf("\n");
}
```

`10 <-> 20 <-> 30` → direto `10 20 30`, inverso `30 20 10`.

## Busca

```c
No *buscar(Lista *l, int valor) {
    No *p = l->inicio;
    while (p != NULL) {
        if (p->dado == valor) return p;
        p = p->prox;
    }
    return NULL;
}
```

## Remoção (reconectar os vizinhos)

```c
void remover(Lista *l, int valor) {
    No *p = buscar(l, valor);
    if (p == NULL) return;
    if (p->ant != NULL) p->ant->prox = p->prox;
    else l->inicio = p->prox;
    if (p->prox != NULL) p->prox->ant = p->ant;
    else l->fim = p->ant;
    free(p);
}
```

Liberar o nó **somente depois** de ajustar os elos.

## Erros comuns e casos-limite

- Lista vazia: `inicio` e `fim` = `NULL`.
- Primeira inserção: `inicio` e `fim` apontam para o mesmo nó.
- Remover nó único: ambos voltam a `NULL`.
- Remover o primeiro: atualizar `inicio` e garantir `inicio->ant == NULL`.
- Remover o último: atualizar `fim` e garantir `fim->prox == NULL`.
- Nunca acessar `p->ant`/`p->prox` sem validar `p`; não usar após `free`; não liberar duas vezes.

## Liberar a lista

```c
void liberarLista(Lista *l) {
    No *p = l->inicio;
    while (p != NULL) {
        No *temp = p;     // guarda nó atual
        p = p->prox;      // avança antes de liberar
        free(temp);
    }
    l->inicio = NULL;
    l->fim = NULL;
}
```

## Complexidade

| Operação | Custo |
|---|---|
| Inserir no início | O(1) |
| Inserir no fim (com `fim`) | O(1) |
| Percurso direto/inverso | O(n) |
| Busca por valor | O(n) |
| Remoção de nó já localizado | O(1) |
| Busca + remoção por valor | O(n) |
| Espaço | O(n), 2 ponteiros por nó |

## Estudo de caso: histórico do navegador

```c
typedef struct Pagina {
    char url[100];
    struct Pagina *ant;
    struct Pagina *prox;
} Pagina;
Pagina *atual; // página exibida
```

Voltar: `atual = atual->ant`; avançar: `atual = atual->prox`; ao navegar para página nova, **descartar o ramo à frente** antes de inserir.

## Vantagens / desvantagens / usos

- **+** navegação bidirecional, remoção eficiente de nó conhecido.
- **−** mais memória, mais atualizações de ponteiros.
- Usos: histórico de navegação, playlists, galerias, editores.

## Exercícios

1. Diferença entre lista simples e dupla. 2. Papel de `ant` e `prox`. 3. Desenhar 4, 8, 12 com `ant`/`prox`. 4. Ponteiros `NULL` numa lista de dois nós. 5. Percorrer nos dois sentidos. 6. Saída inversa de `5 <-> 10 <-> 15`. 7. Quando usar `malloc`/`free`. 8. Complexidade das operações. 9. Contar nós. 10. Busca retornando endereço. 11. Remover primeira ocorrência tratando todos os casos.

## Relevância para o projeto

InsertionSort em lista dupla pode deslocar a chave para trás usando `ant`, de forma análoga ao vetor.
