# Tipo Abstrato de Dado (TAD)

> Fonte: `contexto/pdfs/TAD.pdf` (15 slides)
> Código: `contexto/codigo-exemplos/05. Tipos Abstratos de Dados/carrinho_compras/` (`carrinho.h`, `carrinho.c`, `main.c`) e `cesar.c`

## Motivação

Construir sistemas seguros, escaláveis e de fácil manutenção; mapear problemas do mundo real para o digital.

## Tipos da linguagem

> "...conjunto de valores a que uma constante pertence, ou que podem ser assumidos por uma variável ou expressão, ou gerados por uma função." (Wirth, 1976)

- Primitivos: `int`, `float`, `double`…
- Compostos homogêneos: matrizes/vetores.
- Compostos heterogêneos: `struct`.

Ex.: número racional pode ser vetor de 2 inteiros ou struct com numerador/denominador — implementações diferentes, **mesmas operações** (criar, somar, multiplicar, imprimir, comparar).

## Problema e solução

Mudar a implementação pode quebrar quem usa o tipo. Solução: **encapsular** (esconder) a implementação.

## Definições de TAD

- Modelo matemático + operações definidas sobre ele (Ziviani, 2003).
- Novo tipo de dado + conjunto de operações para manipulá-lo (Rangel e Celes, 2002).
- **Tupla (v, o):** v = valores, o = operações. Ex.: v = ℝ, o = {+, -, *, /, ==, !=, <, >, <=, >=}.

## Utilidade

- **Encapsulamento:** pensar nas operações, não em como são implementadas.
- **Segurança:** o usuário não acessa os dados diretamente.
- **Flexibilidade/Reuso:** trocar a implementação sem alterar as aplicações.

Analogia do carro: volante/pedais = interface pública; motor = implementação; trocar motor por elétrico não muda a forma de dirigir.

## Exemplos

| Mundo real | Dados | Tipo | Operações |
|---|---|---|---|
| Pessoa | idade | int | nasce, aniversário |
| Cadastro de funcionários | setor, cargo, salário | lista | entra/sai da lista, altera cargo/salário |
| Fila de espera | nome, posição | fila | entra (fim), sai (primeiro) |
| Pilha de cartas | naipe, valor, posição | pilha | põe/retira do topo |

## Estrutura de um TAD em C (3 arquivos)

1. **`.h` (cabeçalho):** o *contrato* — protótipos, tipos (ponteiros opacos), dados globalmente acessíveis.
2. **`.c` (implementação):** declaração real da `struct` + implementação das funções.
3. **`main.c` (cliente):** usa o TAD apenas via `.h`.

### Exemplo — Carrinho de compras (ponteiro opaco)

```c
// carrinho.h
#ifndef CARRINHO_H
#define CARRINHO_H
typedef struct item Item;
typedef struct carrinho Carrinho;
Carrinho* carrinho_criar();
void carrinho_adicionar(Carrinho* c, int id, float preco);
float carrinho_calcular_total(Carrinho* c);
void carrinho_esvaziar(Carrinho* c);
#endif
```

```c
// carrinho.c
#define MAX_ITENS 100
struct item { int id_produto; float preco; };
struct carrinho { Item itens[MAX_ITENS]; int qtd_atual; };

Carrinho* carrinho_criar() {
    Carrinho* c = (Carrinho*) malloc(sizeof(Carrinho));
    if (c != NULL) c->qtd_atual = 0;
    return c;
}
// ... adicionar, calcular_total, esvaziar (free)
```

## Relevância para o projeto

**Padrão esperado pela disciplina:** cada estrutura (vetor dinâmico, lista simples, dupla, circular, pilha, fila, hash, métricas) como TAD separado em `.h` + `.c`, com `struct` escondida no `.c` e `typedef` opaco no `.h`, consumido por `main.c`. O `projeto-exemplo` **não** segue isso (faz `#include "arquivo.c"`), o que deve ser corrigido.
