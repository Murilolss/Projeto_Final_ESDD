# Sessão 07 — 2026-11-17 — Lista circular (T08)
<!-- session: 7d74abb0-4cc4-41a0-b44a-4812de9eeb5d -->

- **Autor:** Murilo Leandro
- **Prompts no AI_LOG:** #043–#044

## O que foi feito
- T08 primeiro planejada (plano aprovado pelo usuário) e depois implementada. Arquivos novos: `src/circular_list.h/.c`, um TAD opaco que guarda só o `tail` e o `size`, no mesmo formato da `singly_list` (tabela `CLIST_SORT_COUNT`/`clist_sort_name`/`clist_sort_run`).
- `src/main.c`: o menu "Ordenar listas encadeadas" foi para 6 algoritmos (1–2 lista simples, 3–4 dupla, 5–6 circular, 7 Voltar, 8 Encerrar). "Comparar todos" passou a ter 13 linhas.
- Teste caixa-branca no scratchpad, fora do repositório (`#include "circular_list.c"`, ligado com `singly_list.c` para comparar as contagens): N de 0 a 50.000, dados aleatórios, ordenados, invertidos e repetidos. Tudo ordena, `tail->next` é o menor valor, o ciclo fecha em exatamente N passos, as contagens são idênticas às da lista simples, a memória extra é 0 e nada vaza. O menu real também foi testado com entrada automática.
- Commit `f2babc9` na `ESDD/murilo`, só com o código.

## Decisões / observações
- Lista circular **simples** (nó com `value` + `next`, 8 bytes), escolhida pelo usuário. Só o `tail` na struct: o primeiro nó é `tail->next`, e o `insert_back` é O(1) sem um segundo ponteiro. Com um nó só, ele aponta para si mesmo.
- O usuário escolheu **abrir o ciclo nos dois algoritmos** (a recomendação era o Insertion andar direto no círculo). `open_cycle` faz `tail->next = NULL`, o código da T06 ordena e `close_cycle` anda até o último nó (O(n)) e religa. Na arguição: sem o `NULL`, o `split_middle` e o merge nunca achariam o fim.
- `clear`, `to_array` e `print` contam `size` nós (`for`/`do-while`), porque um `while (current != NULL)` daria volta para sempre.
- Números com N = 50.000, dados aleatórios (para a T09): Insertion circular ~24 s e lista simples ~29 s na mesma execução, com as mesmas 625 milhões de comparações. Na sessão 06, a lista simples tinha levado ~13 s: a variação é da máquina, então medir de novo na T09. Merge circular: 21 ms.
- Com N = 50.000, o Insertion só foi testado com dados ordenados (teste) e aleatórios (menu). Invertidos e repetidos só foram testados com N = 1.000.

## Pendências
- Commit do `AI_LOG.md` (#043–#044) e desta nota na `ESDD/murilo`.
- Levar a T08 para a `dev` (merge direto, sem PR, enquanto não houver outros integrantes).
- Revisão por outro integrante; só depois marcar a T08 no plano.
- Continuam: o hook `log_prompt.py` gravou de novo o bloco `<browser_instruction>` no prompt (#043), o `README.md` está vazio e faltam as branches dos outros integrantes.

## Próximos passos sugeridos
1. Commitar o log e esta nota, depois fazer o merge da `ESDD/murilo` na `dev` e o push.
2. T09 (comparativo vetor × listas): as três listas estão prontas. Avisar antes do Insertion das listas com dados aleatórios e N grande (~13–29 s cada, conforme a máquina).
3. Corrigir o `log_prompt.py` para remover os blocos injetados pelas extensões.
