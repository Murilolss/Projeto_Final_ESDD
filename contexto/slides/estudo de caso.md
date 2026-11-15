# Estudo de caso — Sistema de gerenciamento de links favoritos

> Fonte: `contexto/pdfs/estudo de caso.pdf`
> Relacionado: `listas_encadeadas.md`, código-base em `contexto/codigo-exemplos/08. Lista simplesmente encadeada/codigos/`

## Contexto

Uma empresa quer um sistema para usuários armazenarem links favoritos. O sistema deve:

1. Cadastrar um novo link.
2. Remover um link cadastrado.
3. Consultar se um link está armazenado.
4. Exibir todos os links.

Cada link possui **identificador**, **nome/descrição** e **URL**.

| ID | Descrição | URL |
|---|---|---|
| 1 | Google | https://www.google.com |
| 2 | GitHub | https://github.com |
| 3 | W3Schools | https://www.w3schools.com |

## Modelagem

Cada nó armazena os dados de um link e um ponteiro para o próximo:

`inicio → [1|Google|google.com|*] → [2|GitHub|github.com|*] → [3|W3Schools|w3schools.com|NULL]`

## Exercício

Adaptar o TAD da aula para:

```c
typedef struct Link {
    int id;
    char descricao[100];
    char url[200];
} Link;

typedef struct No {
    Link dado;
    struct No *prox;
} No;
```

Operações: `criarLista()`, `inserirLink()`, `removerLink()`, `buscarLink()`, `listarLinks()`, `destruirLista()`.

## Regras

- Não permitir dois links com o mesmo identificador.
- Não permitir remoção de identificador inexistente.
- Permitir lista vazia.
- Exibir mensagem quando nenhum link estiver cadastrado.
- Liberar a memória ao encerrar.

## Questões para reflexão

1. Por que uma lista encadeada pode ser interessante aqui?
2. O que acontece se o usuário remover o primeiro link?
3. Como o sistema identifica o último elemento?
4. Consequência de não usar `free()` na remoção?
5. Seria possível usar vetor? Vantagens e desvantagens?

## Relevância para o projeto

Mostra o padrão de **nó com payload `struct`** (em vez de `int`) — útil para listas de relatórios de teste (`Metricas`) e para os buckets da tabela hash.
