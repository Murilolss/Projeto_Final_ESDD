# Sessão 09 — 2026-11-17 — Onboarding da Liliane
<!-- session: 211c3627-8a6e-4228-be16-8bca4449c849 -->

- **Autor:** lilianeperim-ifsp
- **Prompts no AI_LOG:** #052–#057 (o primeiro prompt da sessão foi registrado como #021 na `main` e se perdeu, ver abaixo)

## O que foi feito
- Primeira sessão da Liliane no projeto: lidos `contexto/` (notas, slides, códigos-exemplo, projeto-exemplo), `.claude/` (hook do AI_LOG e as skills `/salvar-memoria` e `/atualizar-branch`) e `PRIMEIROS_PASSOS.md`.
- Criada a branch `ESDD/liliane` a partir de `origin/dev` (commit `60f612f`) e publicada no GitHub com upstream `origin/ESDD/liliane`.
- Nenhum código alterado.

## Decisões / observações
- A sessão começou na `main`, que parou na T04 e só tem as notas 01–03. Isso deu uma visão desatualizada do projeto. A visão certa é a da `dev`, que vai até a T09. Ler sempre a partir da `dev` ou da própria `ESDD/<nome>`.
- Armadilha do AI_LOG: o primeiro prompt ("leia contexto e todas as suas subpastas") virou a entrada #021 no `AI_LOG.md` da `main`. Ao trocar para a `dev`, essa alteração não commitada foi descartada, e a numeração da `dev` seguiu da #052. Para não perder entradas, trocar de branch só depois de commitar ou guardar o `AI_LOG.md` (`git stash`).
- `/atualizar-branch` rodado na `dev` parou no passo 1, como previsto: a skill só roda em `ESDD/*`.
- A usuária preferiu deixar o commit dos registros para o fim da sessão.

## Pendências
- Commit do `AI_LOG.md` (#052–#057) e desta nota na `ESDD/liliane`, seguido do push.
- Pedir ao Murilo acesso ao artefato do plano. Ainda não está definido quais tarefas são da Liliane.
- Continuam das sessões anteriores: correção do `log_prompt.py` (blocos injetados e `<task-notification>`), `README.md` vazio, revisão da T06–T09 por outro integrante (a Liliane pode ser essa revisora).

## Próximos passos sugeridos
1. Commitar os registros e fazer o push da `ESDD/liliane`.
2. Combinar com a equipe as tarefas da Liliane. Candidatas: a T26 (passo a passo com ponteiro para função), sugerida pela sessão 08, ou a revisão das T06–T09.
3. Compilar o projeto na própria máquina (`mkdir -p src/output` e `gcc -Wall -Wextra src/*.c -o src/output/main.exe`) para conferir o ambiente.
