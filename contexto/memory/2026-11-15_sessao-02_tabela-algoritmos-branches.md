# Sessão 02 — 2026-11-15 — Tabela de algoritmos e branches
<!-- session: 3f80acf3-621f-4d04-865c-50c1a520fc74 -->

- **Autor:** Murilo Leandro
- **Prompts no AI_LOG:** #010–#016

## O que foi feito
- T02 + T05 feitas juntas (a T05 dependia da T02): `src/` criada a partir do `projeto-exemplo` com os módulos `metrics`, `search`, `vector`, `sort` e `main.c`, sem `#include "*.c"`.
- T05: tabela `static` de algoritmos (nome + ponteiro para função) em `sort.c`, com `sort_name()` e `sort_run()`. O menu e a tela "comparar todos" viraram laços sobre a tabela.
- Teste de regressão: comparações e trocas idênticas às do protótipo com N = 10 e N = 1000; compila com `-Wall -Wextra` sem warnings.
- Textos exibidos ao usuário traduzidos para português sem acento (#011).
- Git: `master` renomeada para `main`, criadas `dev` e `ESDD/murilo`, tudo enviado ao GitHub, `main` virou a branch padrão e a `master` remota foi apagada (#013–#015).
- Commits na `ESDD/murilo`: `8a3f44c` (T02/T05) e `cb1b238` (fluxo de branches no `CLAUDE.md` + AI_LOG #013–#014).

## Decisões / observações
- Bugs da T03 não foram corrigidos, só marcados com `TODO(T03)` no código, para não misturar escopo.
- Bug novo, fora da lista do `CLAUDE.md`: com N > 2048, `vector_fill_random` entra em laço infinito (só existem 2048 valores únicos). Bloqueia os testes da T09 com 10.000 e 50.000 — resolver na T03.
- `Metrics` ficou struct pública (não opaca), porque o cliente declara `Metrics results[SORT_COUNT]` na pilha.
- `sort_run` recebe o `dest` já alocado (sem malloc escondido), pensando na contagem de memória da T04.
- Ponteiro para função não aparece em nenhum material das aulas: a equipe precisa estudar antes da arguição. Há um comentário explicativo em `sort.h`.
- Fluxo combinado: `ESDD/<integrante>` → revisão de outro integrante → `dev` → `main`. Substituiu a ideia de uma branch por tarefa (`t02-t05-sort-table`).
- O hook `log_prompt.py` grava no AI_LOG blocos injetados pelas extensões (`<browser_instruction>`, `<ide_opened_file>`) junto com o prompt (#010, #011).

## Pendências
- Nomes dos outros integrantes, para criar as branches `ESDD/<nome>` a partir da `dev`.
- Revisão da T02/T05 por outro integrante e merge da `ESDD/murilo` na `dev` (PR ainda não aberto). Só depois marcar T02/T05 como concluídas no plano.
- Corrigir o `log_prompt.py` para remover os blocos injetados pelas extensões.
- AI_LOG #015–#016 ainda sem commit.
- Continuam as pendências da sessão 01: confirmação com o professor sobre a "Integração Interdisciplinar", compartilhar o plano, `README.md` vazio.

## Próximos passos sugeridos
1. Criar as branches dos outros integrantes e abrir o PR `ESDD/murilo` → `dev`.
2. T03: corrigir os `TODO(T03)` (srand, duplicatas, laço infinito com N > 2048, VLAs do merge, `sequential_search`).
3. T04: medir o consumo de memória.
