# Sessão 03 — 2026-11-15 — Bugs do protótipo e medição de memória
<!-- session: ef2091ce-6124-4714-aa22-0881604c17c5 -->

- **Autor:** Murilo Leandro
- **Prompts no AI_LOG:** #018–#019

## O que foi feito
- T03: corrigidos todos os `TODO(T03)`. `srand` no `main`, vetor como permutação 1..N (Fisher-Yates), VLAs do `merge` trocados por heap, `sequential_search` com `i < size` primeiro. Os 7 algoritmos e o `SortFunction` agora retornam `int` (1/0).
- T04: novo módulo `src/memory.h/.c` (contador global com pico), campo `memory_bytes` em `Metrics` (coluna "Memoria (B)"), `vector_resize` com `realloc`, opção 4 "Alterar tamanho do vetor" no menu e aviso "Memoria nao liberada" na saída.
- Teste temporário (fora do repositório) com N de 1 a 50.000: tudo ordena, o vetor é uma permutação válida, Merge Sort = N × 4 bytes extras e os outros = 0, sem vazamento. Rodei o menu de verdade também.

## Decisões / observações
- Decisões da equipe: permutação 1..N (as barras da interface ficam todas com alturas diferentes), `mem_free(p, bytes)` com tamanho explícito (sem cabeçalho escondido, mais fácil de explicar) e opção de menu para cobrir o `realloc` do enunciado.
- Armadilha: no MinGW `RAND_MAX` = 32767. Um `rand()` só não alcança posições acima disso, então `random_index` combina dois `rand()`.
- Armadilha: o Merge Sort iterativo chama `merge` com a metade direita vazia (ex.: N = 10, passo 4, `left` = 8), e `malloc(0)` pode devolver `NULL`. O `merge` agora retorna 1 nesse caso. Por isso as trocas do Merge Sort iterativo ficam um pouco abaixo das do protótipo.
- Memória extra = pico do heap durante a ordenação menos o que já estava alocado antes. A pilha da recursão (Quick Sort, Merge recursivo) não entra na conta.
- Todo `malloc`/`realloc`/`free` novo (listas da T06–T08, pilha, fila) deve passar por `mem_alloc`/`mem_realloc`/`mem_free`, senão a comparação vetor × listas da T09 fica errada.
- Tempo com N = 50.000: Bubble ~20 s, Selection ~6 s, Insertion ~4 s.

## Pendências
- Sem commit ainda: falta decidir entre dois commits (T03 e T04 separados) ou um só. A versão só com a T03 está no scratchpad da sessão (`src_t03`), que pode ser apagado.
- Revisão por outro integrante e PR `ESDD/murilo` → `dev` (agora com T02–T05). Só depois marcar T03/T04 como concluídas no plano.
- Continuam as pendências da sessão 02: branches dos outros integrantes, limpeza do `log_prompt.py` (o hook ainda grava o bloco `<browser_instruction>` no AI_LOG), `README.md` vazio.

## Próximos passos sugeridos
1. Fazer o(s) commit(s) da T03/T04 e abrir o PR para a `dev`.
2. Estudar para a arguição: `realloc` com ponteiro temporário, por que o Merge Sort gasta O(n) de memória extra e o Fisher-Yates.
3. Começar a T06 (lista simplesmente encadeada) usando `mem_alloc`/`mem_free`.
4. Na T09, avisar antes de rodar os algoritmos O(n²) com N grande.
