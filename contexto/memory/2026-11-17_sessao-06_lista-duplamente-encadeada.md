# Sessão 06 — 2026-11-17 — Lista duplamente encadeada (T07)
<!-- session: 644057ef-f677-4c1f-a461-2b59fa2a87e7 -->

- **Autor:** Murilo Leandro
- **Prompts no AI_LOG:** #038–#041

## O que foi feito
- T07 primeiro planejada (plano aprovado pelo usuário) e depois implementada. Arquivos novos: `src/doubly_list.h/.c`, um TAD opaco com `head`, `tail` e `size`, no mesmo formato da `singly_list` (tabela `DLIST_SORT_COUNT`/`dlist_sort_name`/`dlist_sort_run`).
- `src/main.c`: a opção 6 virou "Ordenar listas encadeadas", com os 4 algoritmos (1–2 lista simples, 3–4 lista dupla, 5 Voltar, 6 Encerrar). A lista dupla também é impressa do fim ao início. "Comparar todos" passou a ter 11 linhas.
- Teste caixa-branca no scratchpad, fora do repositório (`#include "doubly_list.c"` para ver a struct): N de 0 a 50.000, dados aleatórios, ordenados, invertidos e com valores repetidos. Tudo ordena, os ponteiros ficam consistentes nos dois sentidos, a memória extra é 0 e nada vaza. O menu real também foi testado com entrada automática.
- Commit `5b06661` na `ESDD/murilo`, só com o código. O `AI_LOG.md` ficou para um commit de log separado.

## Decisões / observações
- Insertion da lista dupla procura **para trás** pelo `prev`, como o vetor e como sugere o slide ("deslocar a chave para trás usando `ant`"). Com dados invertidos: N(N−1)/2 comparações (igual ao vetor), contra 2(N−1) da lista simples, que procura a partir do `head`. Nas duas listas, só N−1 nós movidos. Tema para a arguição.
- Para desligar o nó, o Insertion usa o `remover` do slide sem o `free`. O Merge é o da T06, acertando o `prev` de cada nó ligado (também na sobra) e o `tail` com uma passada no final.
- `dlist_from_array` usa `insert_back` (O(1) graças ao `tail`) e lê o vetor em ordem. A T06 precisou inserir no início, de trás para frente, porque não tem `tail`.
- Memória: 12 bytes por nó (int + 2 ponteiros, gcc de 32 bits), contra 8 na lista simples e 4 no vetor. A struct da lista também ocupa 12 bytes.
- Números com N = 50.000 (para a T09): Insertion da lista dupla com dados aleatórios ~20 s (lista simples ~13 s), mais lento que o invertido (~12,8 s), que faz o dobro de comparações. Causa provável: nós espalhados na memória, muitos acessos fora da cache. Merge da lista dupla: 30 ms (aleatório).

## Pendências
- Commit do `AI_LOG.md` (#038–#041) e desta nota na `ESDD/murilo`.
- Levar a T07 para a `dev` (merge direto, sem PR, enquanto não houver outros integrantes; a T06 já foi no #037).
- Revisão por outro integrante; só depois marcar a T07 no plano.
- Continuam: o hook `log_prompt.py` gravou de novo o bloco `<browser_instruction>` no prompt (#038), o `README.md` está vazio e faltam as branches dos outros integrantes.

## Próximos passos sugeridos
1. Commitar o log e esta nota, depois fazer o merge da `ESDD/murilo` na `dev` e o push.
2. T08 (lista circular), no mesmo formato: abrir o ciclo, ordenar com o código das listas e fechar de novo. Acrescentar as linhas em `menu_list_sort` e `menu_compare_all` (o menu de listas vai para 6 algoritmos).
3. Na T09, avisar antes do Insertion das listas com dados aleatórios e N grande (13–20 s).
4. Corrigir o `log_prompt.py` para remover os blocos injetados pelas extensões.
