# Recursividade

> Fonte: `contexto/pdfs/Recursividade.pdf` (16 slides)
> Código: `contexto/codigo-exemplos/01. Recursividade/codigos/` (`fatorial.c`, `1_contador_paginas.c`, `2_entrega_troco.c`, `3_descarga_smartphone.c`)

## Fatorial (motivação)

- `n! = n * (n-1) * (n-2) * ... * 1`; por definição `0! = 1`.
- Ex.: `5! = 5 × 4 × 3 × 2 × 1 = 120`. Usado em análise combinatória (4 livros → 4! = 24 arranjos).
- Desdobramento: `5! = 5 * 4! = 5 * 4 * 3! = ... = 5 * 4 * 3 * 2 * 1`.

## Recursão em C

Uma função é **recursiva** quando chama a si mesma.

### Estrutura básica

- **Caso base:** condição de parada que resolve o problema mais simples diretamente.
- **Caso recursivo:** chamada com argumento modificado, reduzindo o problema rumo ao caso base.

### Iterativo × recursivo

```c
int fatorial_iterativo(int num) {
  int fatorial = 1;
  // Multiplica o número por seus antecessores até 1
  for (int i = 2; i <= num; i++) {
    fatorial = fatorial * i;
  }
  return fatorial;
}

int fatorial_recursivo(int num){
  // implementa a regra n! = n * (n-1)!
  if ( num <= 1 ){
    return num;
  }
  return num * fatorial_recursivo(num-1);
}
```

Slide 6 ilustra a pilha de chamadas: `Fatorial(5) → 5*Fatorial(4) → ... → Fatorial(1)` (condição de parada) e o **processo de retorno** `1 → 2 → 6 → 24 → 120`.

> Observações sobre `fatorial.c`: o `main` imprime `fatorial_iterativo` duas vezes (a linha "recursivo" chama a função errada); e `fatorial_recursivo(0)` retorna 0, não 1.

## Vantagens e cuidados

- **Vantagens:** código mais limpo e natural para problemas matemáticos, árvores e **divisão e conquista** (MergeSort, QuickSort).
- **Cuidados:** cada chamada consome espaço na **pilha de execução (stack)**. Sem caso base → recursão infinita → **stack overflow**.

## Exercícios (com soluções nos códigos-exemplo)

1. **Contador de páginas** — `contarPaginas(pagina_atual, pagina_final)`: imprime a página e chama com `pagina_atual + 1`. Caso base: `pagina_atual > pagina_final`.
2. **Troco no caixa** — `entregarTroco(valor_saque)`: imprime "Entregando 1 nota de R$ 50" e chama com `valor_saque - 50`. Caso base: `valor_saque < 50` (avisa se sobrou resto).
3. **Descarga do smartphone** — `monitorarBateria(porcentagem_bateria)`: imprime status e chama com `-10`. Caso base: `<= 0` → "Celular desligado!".

## Relevância para o projeto

MergeSort recursivo e QuickSort são recursivos; em listas encadeadas, o MergeSort recursivo é a abordagem natural (dividir a lista em duas metades por ponteiros).
