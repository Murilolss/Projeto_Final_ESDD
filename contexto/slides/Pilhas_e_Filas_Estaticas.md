# Pilhas e Filas (estáticas)

> Fonte: `contexto/pdfs/Pilhas_e_Filas_Estaticas.pdf`
> Código: não há arquivo em `codigo-exemplos` — o código abaixo é o dos slides. Próximo passo anunciado: "implementar pilha e fila em C usando TAD".

## Objetivos

Funcionamento de pilhas (LIFO) e filas (FIFO); implementação com vetor de tamanho fixo; inserção/remoção/consulta com controle de limites; overflow/underflow; custos.

## Estrutura estática

- Dados + regras; interface (inserir/remover/consultar) separada da implementação.
- **Estática = capacidade fixa** durante a execução (vetor de N posições, mesmo vazias). Não significa que os valores não mudam.

## Pilha (LIFO — Last In, First Out)

- Último a entrar é o primeiro a sair. Acesso e remoção no **topo**.
- `push` (empilhar), `pop` (desempilhar), `peek/top` (consultar sem remover).

### Representação em vetor

Convenção didática: **`topo` = índice da próxima posição livre**.

- Vazia: `topo == 0`
- Com 4 itens: `topo == 4`, último em `pilha[topo - 1]`
- Cheia: `topo == capacidade`
- (Outra convenção possível: `topo = -1` quando vazia.)

### Código

```c
#define CAP 5
int pilha[CAP];
int topo = 0; // próxima posição livre

int push(int x) {
    if (topo == CAP) return 0;      // overflow
    pilha[topo++] = x;
    return 1;
}

int pop(int *saida) {
    if (topo == 0) return 0;        // underflow
    *saida = pilha[--topo];
    return 1;
}

int peek(void) {
    if (topo == 0) return ERRO;
    return pilha[topo - 1];
}
```

> Em código real, prefira indicar erro por retorno/parâmetro separado, pois `ERRO` pode ser um valor válido.

Rastreamento: `push(1) push(2) push(3) pop() push(4) pop()` → `[1,2]`, `topo = 2`.

### Usos

**Desfazer/refazer (undo/redo)**, pilha de chamadas/recursão, parênteses balanceados, conversão de bases, avaliação de expressões, histórico de navegação.

## Fila (FIFO — First In, First Out)

- Primeiro a entrar é o primeiro a sair.
- `enqueue` (no fim), `dequeue` (no início), `front/peek` (consultar o primeiro).

### Problema da fila linear

`inicio` e `fim` só avançam; após remoções sobram posições livres no começo e a inserção pode falhar mesmo com espaço. **Solução: fila circular** (aritmética modular).

### Fila circular

- Próximo índice: `(indice + 1) % capacidade`.
- Usa `inicio` + `qtd`: vazia `qtd == 0`; cheia `qtd == CAP`.

```c
#define CAP 5
int fila[CAP];
int inicio = 0, qtd = 0;

int enqueue(int x) {
    if (qtd == CAP) return 0;
    int fim = (inicio + qtd) % CAP;
    fila[fim] = x;
    qtd++;
    return 1;
}

int dequeue(int *saida) {
    if (qtd == 0) return 0;
    *saida = fila[inicio];
    inicio = (inicio + 1) % CAP;
    qtd--;
    return 1;
}
```

Exemplo (CAP 3): `enqueue(A) enqueue(B) enqueue(C) dequeue() enqueue(D)` → `B C D`, `inicio=1, qtd=3` — a posição de A é reutilizada por D.

## Pilha × fila

| | Pilha | Fila |
|---|---|---|
| Regra | LIFO | FIFO |
| Inserção | topo | final |
| Remoção | topo | início |
| Variáveis | `topo` | `inicio + fim` ou `inicio + qtd` |
| Exemplo | desfazer última ação | atendimento por ordem de chegada |
| Cuidado | cheia/vazia | cheia/vazia; circularidade |

## Custos

- Pilha estática: `push`, `pop`, `peek` — O(1).
- Fila circular: `enqueue`, `dequeue`, `front` — O(1).
- Fila com deslocamento: `dequeue` pode ser O(n).
- A complexidade depende da **implementação**, não só do nome da estrutura.

## Erros comuns

- Confundir `topo` (próxima livre) com índice do último item.
- `pop`/`dequeue` sem verificar vazia; inserir sem verificar cheia.
- Esquecer `% capacidade` na fila circular.
- Atualizar `qtd`/`inicio` de forma inconsistente.
- Assumir que a posição física 0 é o início lógico da fila.
- **Boa prática:** documentar a convenção dos índices e testar casos-limite.

## Exercícios

- Pilha (CAP 4): `push(8) push(3) push(5) pop() push(9) push(2)` — registrar vetor, topo e retorno; qual falha?
- Fila circular (CAP 4): `enqueue(10) enqueue(20) enqueue(30) dequeue() enqueue(40) enqueue(50)` — registrar `inicio`, `qtd`, vetor físico; ordem lógica final?
- Respostas teóricas: sai primeiro o último inserido; FIFO = primeiro a entrar, primeiro a sair; pilha cheia ⇔ `topo == capacidade`; fila circular reaproveita espaços; push/pop O(1).

## Relevância para o projeto

- **Pilha → Undo** no modo passo a passo: empilhar cada operação (troca/comparação com índices e valores anteriores) e desempilhar para desfazer.
- **Fila → Batch Processing:** enfileirar testes (algoritmo, estrutura, tamanho, tipo de entrada) e executá-los em ordem.
- Como o projeto exige alocação dinâmica, a capacidade pode ser alocada com `malloc` e expandida com `realloc`, ou as estruturas podem ser encadeadas.
