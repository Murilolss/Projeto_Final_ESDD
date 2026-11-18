# Sessão 08 — 2026-11-17 — Comparativo vetor × listas (T09)
<!-- session: feca3ad7-0e0f-4724-b5e6-f31af34d103a -->

- **Autor:** Murilo Leandro
- **Prompts no AI_LOG:** #046–#049

## O que foi feito
- T09 primeiro planejada (o usuário aprovou o plano) e depois implementada. Arquivos novos: `src/benchmark.h/.c`, um módulo de funções sem estado, como o `search`. Em `src/main.c`, a opção 7 "Comparativo vetor x listas" é nova e Encerrar passou a ser a 8.
- O comparativo gera 9 tabelas (3 tipos de dados × N = 1.000, 10.000 e 50.000), cada uma com os 13 algoritmos (7 do vetor + 2 de cada lista) rodando sobre o mesmo vetor `source`.
- Teste pelo menu real com entrada automática: levou cerca de 3 min, sem nenhuma falha e com 0 bytes não liberados. A resposta 0 no aviso volta ao menu sem rodar nada.
- Commit `f7da2ea` na `ESDD/murilo`, só com o código.

## Decisões / observações
- O usuário escolheu rodar **os três tipos de dados** e **todos os 7 algoritmos do vetor**. A recomendação era só o tipo atual e só Insertion + Merge.
- A impressão da tabela ficou dentro do `benchmark.c` (`print_header`/`print_row`), para não mexer no `metrics.c` nem no "Comparar todos". A coluna nova "Estrutura (B)" mostra a memória do vetor ou da lista (struct + nós), separada do "Extra (B)", que é o pico durante o sort.
- As linhas saem com `fflush(stdout)` assim que cada algoritmo termina, para o usuário ver o progresso. Antes de rodar há um aviso de demora e uma confirmação (1/0), como foi pedido nas sessões 03 a 07.
- Números com N = 50.000 nesta máquina:
  - Dados aleatórios: Insertion do vetor 4,0 s, da lista simples 10,5 s, da dupla 16,4 s e da circular 10,7 s. As comparações quase não mudam (~624–626 milhões), então a diferença vem da memória contígua (cache). O Merge fica entre 15 e 45 ms em todas as estruturas. O Bubble levou 20,9 s e o Selection 5,7 s.
  - Dados invertidos: as listas simples e circular fazem só 2(N−1) comparações (0 ms), porque buscam a partir do início. A dupla, que busca para trás, e o vetor fazem N²/2 (~11 s).
  - Dados ordenados: os dois Quick Sort levam ~10,5 s (pivô na ponta, O(n²)). Todos os Insertion fazem N−1 comparações.
  - Memória: o vetor ocupa 200.000 B, as listas simples e circular 400.008 B e a dupla 600.012 B. O Merge do vetor usa mais 200.000 B de memória extra; o das listas, 0.
- Os tempos das listas foram bem menores que os das sessões 06–07 (13 a 29 s), então variam bastante entre execuções. Tempos abaixo de ~16 ms aparecem como 0, 8 ou 16 (granularidade do `clock()` no Windows).
- O hook `log_prompt.py` também gravou o aviso automático `<task-notification>` (fim do teste em segundo plano) como se fosse um prompt (#048).

## Pendências
- Commit do `AI_LOG.md` (#046–#049) e desta nota na `ESDD/murilo`.
- Levar a T09 para a `dev` (merge direto, sem PR, enquanto não houver outros integrantes).
- Revisão por outro integrante; só depois marcar a T09 no plano.
- Corrigir o `log_prompt.py` para ignorar os blocos `<browser_instruction>` e `<task-notification>`.
- Continuam: o `README.md` está vazio e faltam as branches dos outros integrantes.

## Próximos passos sugeridos
1. Commitar o log e esta nota, depois fazer o merge da `ESDD/murilo` na `dev` e o push.
2. Começar a fase 3: T26 (passo a passo com ponteiro para função), que prepara a T10 (exportação JSON/CSV) e a T11 (pilha do Undo).
3. Corrigir o `log_prompt.py`.
