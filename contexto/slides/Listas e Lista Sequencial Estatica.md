# Listas — Lista Sequencial Estática

> Fonte: `contexto/pdfs/Listas e Lista Sequencial Estatica.pdf`
> Código: `contexto/codigo-exemplos/06. Listas e Lista sequencial estatica/codigos/` (`ListaSequencial.h`, `ListaSequencial.c`, `main.c`)

## Definição geral

- Lista: conjunto de zero (vazia) ou mais itens `x1, x2, ..., xn` do mesmo tipo; `n` = tamanho.
- Propriedade estrutural: posições relativas — `x1` primeiro, `xn` último; `xi` precede `xi+1`.
- Estrutura interna dos elementos é abstraída; pode ser representada como TAD.

## Principais operações

Criar · destruir · inserir no fim · inserir no meio (ordenada) · remover do fim · remover do meio · consultar por chave · consultar por posição · contar itens · verificar vazia · verificar cheia · imprimir.

As operações dependem do tipo de alocação: **estática** ou **dinâmica**.

## Lista sequencial estática

- Memória alocada em compilação; número máximo de nós definido (`#define MAX`).
- Pode ser percorrida em qualquer direção; inserção no final O(1).
- Elementos em endereços consecutivos.

**Vantagens:** acesso por índice rápido e constante; alterar dado pelo índice é fácil.
**Desvantagens:** precisa conhecer o tamanho antes; inserção/remoção no início/meio exige **deslocamentos** (custo O(n)), principalmente em lista ordenada.

**Quando usar:** poucos dados; inserção/remoção sempre no final; tamanho conhecido; operação mais frequente é a busca.

## TAD — valores

```c
#define MAX 5
typedef struct aluno { int matricula; char nome[40]; float n1, n2, n3; } Aluno;
typedef struct lista {
    int prox;            // próxima posição livre = quantidade de elementos
    Aluno alunos[MAX];
} Lista;
```

## TAD — operações (assinaturas e convenções de retorno)

| Operação | Assinatura | Retorno |
|---|---|---|
| Criar | `Lista* criaLista();` | ponteiro ou `NULL` |
| Inserir no fim | `int insereFinal(Lista*, Aluno);` | 1 sucesso / 0 falha |
| Inserir no início | `int insereInicio(Lista*, Aluno);` | 1 / 0 (desloca todos p/ frente) |
| Inserir ordenada | `int insereOrdenada(Lista*, Aluno);` | 1 / 0 (busca posição, desloca) |
| Remover do início | `int removeInicio(Lista*);` | 1 / 0 (desloca p/ trás) |
| Remover por chave | `int removeMatricula(Lista*, int mat);` | 1 / 0 |
| Remover do fim | `int removeFinal(Lista*);` | 1 / 0 (só `prox--`) |
| Consultar por chave | `int consultaMatricula(Lista*, int, Aluno*);` | 1 achou / 0 não |
| Consultar por posição | `int consultaPosicao(Lista*, int, Aluno*);` | 1 / 0 |
| Tamanho | `int tamLista(Lista*);` | `prox` ou -1 |
| Cheia | `int listaCheia(Lista*);` | 1 / 0 / -1 (não criada) |
| Vazia | `int listaVazia(Lista*);` | 1 / 0 / -1 |
| Imprimir | `void imprimeLista(Lista*);` | — |
| Apagar | `void apagaLista(Lista*);` | — (`free`) |

Padrão recorrente: **testar existência da lista (`list == NULL`) e limites (cheia/vazia) antes de operar**; devolver dados via **ponteiro de saída** (`Aluno *estudante`) e status via `int`.

> Obs.: em `ListaSequencial.c`, `consultaPosicao` valida `pos <= 0 || pos > prox` mas acessa `alunos[pos]` (mistura base 0/1). E o `#endif` do `.h` está logo após o `#define`, então o include guard não protege nada.
