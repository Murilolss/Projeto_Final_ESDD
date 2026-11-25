# Sessão 05 — 2026-11-16 — Lista simplesmente encadeada (T06)
<!-- session: 349960fb-391f-483e-a986-2724d105cc3d -->

- **Autor:** Murilo Leandro
- **Prompts no AI_LOG:** #034–#035

## O que foi feito
- T06 implementada, primeiro como plano aprovado pelo usuário e depois em código. Arquivos novos: `src/singly_list.h/.c` (TAD opaco com `head` + `size`, nós criados por `mem_alloc`/`mem_free`, tabela `SLIST_SORT_COUNT`/`slist_sort_name`/`slist_sort_run` no mesmo padrão da T05).
- `src/main.c`: a opção 6 é a nova "Ordenar lista encadeada", com submenu (Encerrar virou 7). A tela "Comparar todos" agora mostra 9 linhas: os 7 algoritmos do vetor e os 2 da lista, com os mesmos dados.
- `src/metrics.c`: a coluna do nome passou para 24 caracteres e o rodapé explica as "Trocas" das listas.
- Teste temporário no scratchpad (fora do repositório): N de 1 a 50.000 nos 3 tipos de dados. Tudo ordena (resultado = 1..N), memória extra = 0 e nada vaza. Também rodei o menu de verdade com entrada automática.
- Ainda sem commit.

## Decisões / observações
- "Trocas" na lista = **nós movidos** (religados em outra posição). O usuário pediu a opção mais próxima do material do professor: a 1ª versão do enunciado fala em "movimentações", e mover um nó é o `remover` + `inserir` do `lista.c` da aula, só que sem `free`/`malloc`. No Merge, a sobra ligada de uma vez não conta.
- `slist_from_array` insere no início, do último valor para o primeiro: fica O(n) e sem ponteiro `tail`. O `inserirFim` da aula seria O(n²) para montar a lista.
- Insertion na lista: a busca começa pelo `head`, porque não há ponteiro para o anterior. Com dados ordenados: N-1 comparações e 0 movimentos. Com invertidos: 2(N-1) comparações e N-1 movimentos, enquanto o vetor faz cerca de N²/2. Tema para a arguição.
- O merge da lista é iterativo de propósito: um merge recursivo desce N níveis e estoura a pilha com N = 50.000, a mesma armadilha do Quick Sort na T25.
- Números com N = 50.000 (para a T09): Insertion da lista com dados aleatórios leva ~13,4 s, contra ~4 s no vetor (acesso por ponteiros, sem memória contígua). Merge da lista: 17 ms. A lista ocupa 8 bytes por nó (int + ponteiro, gcc de 32 bits) contra 4 bytes por item no vetor, mas o Merge da lista não usa memória extra (o do vetor usa N × 4).

## Pendências
- Commit da T06 na `ESDD/murilo` (o usuário ainda não pediu).
- Revisão por outro integrante; só depois marcar a T06 no plano.
- Continuam as pendências das sessões anteriores: PR `ESDD/murilo` → `dev`, branches dos outros integrantes, testar a `/atualizar-branch`, o hook `log_prompt.py` ainda grava `<browser_instruction>` no AI_LOG (aconteceu de novo no #034) e o `README.md` está vazio.

## Próximos passos sugeridos
1. Commitar a T06 e incluí-la no PR `ESDD/murilo` → `dev`.
2. T07 (lista dupla) e T08 (lista circular), copiando o formato de `singly_list` (mesma tabela, nomes "Insertion Lista Dupla"/"... Circular") e acrescentando as linhas em `menu_list_sort` e em `menu_compare_all`.
3. Na T09, avisar antes do Insertion da lista com dados aleatórios e N grande (~13 s).
4. Corrigir o `log_prompt.py` para remover os blocos injetados pelas extensões.
