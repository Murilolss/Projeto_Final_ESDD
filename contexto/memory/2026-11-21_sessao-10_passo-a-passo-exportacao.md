# Sessão 10 — 2026-11-21 — Passo a passo (T26) e exportação JSON (T10)

- **Autor:** lilianeperim-ifsp
- **Prompts no AI_LOG:** #058–#079

## O que foi feito
- `ESDD/liliane` atualizada com a `dev`. Houve conflito no `AI_LOG.md`, resolvido renumerando por data: as #052–#053 da `dev` (18/11) viraram #058–#059 e as entradas de 21/11 começam na #060.
- **T26 (modo passo a passo)**, commit `7e49ee3`, no PR #2 (`ESDD/liliane` → `dev`, revisor: Lucas):
  - `sort.h` / `sort.c`: `StepFunction`, `StepObserver { function, context }` e os passos `STEP_COMPARE`, `STEP_SWAP` e `STEP_WRITE`. Os 7 algoritmos recebem `const StepObserver *` e chamam `notify()` depois de cada passo. Novo `sort_run_steps`; o `sort_run` manteve a assinatura.
  - `step_view.h` / `step_view.c`: barras proporcionais ao maior valor e qualquer N (acima de 20 itens, só as linhas a até 4 posições do passo). ENTER avança; `f` vai até o fim.
  - `main.c`: a pergunta aparece no `menu_sort` ("Digite Sim ou Nao").
- **Especificação do log** `contexto/formato_log.md` (commit `1f544b3`, enviada ao PR #2 com um comentário para o Lucas).
- **T10 (exportação JSON)**, commit `896583f`. Era para ficar só local até o merge do PR #2, mas foi enviado ao GitHub fora do Claude e entrou no PR #2. A Liliane decidiu mantê-lo lá:
  - `export.h` / `export.c`: TAD `Exporter` com `export_open`, `export_step` (a `StepFunction`), `export_path` e `export_close`.
  - `main.c`: `run_sort` (substituiu o `run_step_by_step`), `ask_export` e `step_both`.
  - `.gitignore` com `logs/*`, mais `logs/.gitkeep` e `logs/exemplo_bubble_sort_n10.json`.
- AI_LOG #069–#077 commitado (`0b802f3`), também já no GitHub e no PR #2.
- **Revisão do PR #1 do Lucas** (T12 fila + pilha da T11) enviada com "Request changes": menu com "Encerrar" no meio, `read_batch_int` e `size_t` fora do estilo das aulas, tamanho máximo do teste de cerca de 1 bilhão. Depois, um comentário no PR #1 marcou o Lucas, porque o PR foi aberto pelo Murilo e ele poderia não receber o aviso, com o resumo das tarefas dele.
- PR #2 renomeado para "T26 + T10: step-by-step mode and JSON step log". A descrição ganhou a seção "T10" com um aviso de que a T10 ainda vai ser revisada pela própria Liliane e não deve ser mesclada antes disso. Os comentários dos PRs #1 e #2 que diziam "a T10 vem num PR separado" foram corrigidos (editar comentário não gera aviso novo no GitHub).

## Decisões / observações
- Os algoritmos avisam cada passo por um ponteiro para função recebido por parâmetro (pedido no card da T26). O mesmo mecanismo serve ao passo a passo, à exportação e ao Undo. Quando há duas funções de passo, uma terceira (`step_both`) repassa o passo às duas.
- O passo a passo e a exportação ficaram dentro do `menu_sort`, e não no menu principal, para não conflitar com a opção 9 do Lucas.
- `STEP_WRITE` existe porque o Insertion Sort (deslocamentos) e o Merge Sort (cópia das metades) não fazem trocas. O passo é avisado **depois** de acontecer.
- Log em JSON: vetor `initial` + `steps` + `final` + `metrics`. O vetor não é gravado a cada passo (seriam gigabytes); a interface reaplica os passos.
- Limite de exportação: N ≤ 1000 (`EXPORT_MAX_SIZE`), com mensagem explicando o motivo. O pior caso medido foi Bubble Sort, N = 1000, dados invertidos: 67 MB e uns 10 s.
- Os logs gerados não vão para o Git (são recriáveis e grandes). Só o exemplo N = 10 fica versionado para a T14.
- Curiosidades para a arguição:
  - no Insertion Sort, "Trocas/escritas" fica maior que `swaps`, porque a colocação final da chave gera passo mas não é contada como troca;
  - no Merge Sort, durante a intercalação, o mesmo valor aparece em duas posições;
  - o Quick Sort com pivô no início faz "troca" de uma posição com ela mesma.
- O tempo medido inclui as pausas (passo a passo) e a escrita do arquivo (exportação). O programa avisa nos dois casos.
- Erro cometido: o commit `7e49ee3` juntou código e AI_LOG (o guia pede commits separados). Ele não foi reescrito porque já estava no GitHub.
- Para rodar o programa: estar na raiz do projeto, porque a exportação grava em `logs/`. Fechar o `main.exe` antes de recompilar, senão dá "Permission denied".

## Pendências
- PR #2 (T26 + T10) aguardando a revisão do Lucas (parte da T26). A T26 só vira "concluída" no quadro e no `TAREFAS.md` depois do merge; a Liliane disse que ia marcá-la no quadro, então conferir se ficou "em andamento".
- Lucas precisa confirmar o formato do log: os três pontos do fim de `contexto/formato_log.md`.
- Combinar com o Lucas o Undo das escritas: a pilha guarda o valor antigo, ou o Undo fica só para Bubble, Quick e Selection.
- PR #1 do Lucas aguardando os ajustes, para a Liliane revisar de novo.
- **A Liliane quer revisar a T10 antes do merge do PR #2** (`export.h`, `export.c`, `run_sort` / `ask_export` / `step_both` no `main.c`, `formato_log.md`).
- Merge dos PRs #1 e #2: conflito esperado no `src/main.c` (includes e protótipos) e no `AI_LOG.md` (numeração a partir da #054).
- O `contexto/TAREFAS.md` não foi atualizado (ainda diz T26 e T10 "pendente").

## Próximos passos sugeridos
1. Rodar `/atualizar-branch` e ver no PR #2 se o Lucas revisou a T26 e respondeu sobre o formato do log.
2. Liliane revisa a T10, com o Claude explicando `export.c` e `run_sort` parte por parte. Ajustar o que ela pedir e, se o Lucas pedir, também o formato (`export.c` + `formato_log.md`).
3. Depois das duas revisões, tirar o aviso "não fazer merge" da descrição do PR #2 e fazer o merge na `dev` (resolvendo o conflito com o PR #1, se ele entrar antes).
4. Revisar de novo o PR #1 quando o Lucas avisar.
5. Atualizar o `TAREFAS.md` junto com o quadro quando T26 e T10 forem mescladas.
