# AGENTS.md — instruções para o Codex

Este arquivo é para o **Codex**. A equipe usa dois assistentes ao mesmo tempo: o Murilo trabalha com o **Claude Code** e o Lucas com o **Codex**, cada um no próprio computador e na própria branch. As regras do projeto são as mesmas para os dois.

## 1. A fonte das regras é o CLAUDE.md

Antes de qualquer coisa, leia o [CLAUDE.md](CLAUDE.md) inteiro e siga-o **como se estivesse escrito aqui**: requisitos, regras obrigatórias do código, branches, ambiente, AI_LOG e mapa das pastas. Onde ele disser "o Claude", leia "o assistente" (Claude ou Codex). Este arquivo só acrescenta o que muda no Codex. Não copie as regras do CLAUDE.md para cá, para não ficarem duas versões.

Resumo do que não pode faltar:
- Responder sempre em **português do Brasil**. Código, comentários e o `README.md` em **inglês**; textos do `printf` em português **sem acento**.
- Seguir o padrão das aulas (TAD em `.h`/`.c`, `malloc` checado, retorno `int` 1/0 com ponteiro de saída, nada de "caixa-preta").
- Commitar só na `ESDD/<integrante>` do usuário. Nunca em `main` ou `dev`, nunca `git push --force`.

## 2. Início de uma sessão nova

1. Leia o [PRIMEIROS_PASSOS.md](PRIMEIROS_PASSOS.md). Se for a primeira vez neste computador, conduza o usuário pela configuração (seções 0, 2 e 3) antes de qualquer outra coisa.
2. Leia a nota de sessão mais recente em [contexto/memory/](contexto/memory/) (a de maior `sessao-NN`).
3. **Assim que terminar de ler o guia, abra o quadro e liste as tarefas do usuário:**
   - Abra o quadro no navegador do usuário: no Windows, `start "" "https://claude.ai/artifact/G6eqVDUisHMbyCAS5mDpfr"` (no macOS, `open`; no Linux, `xdg-open`).
   - Você não consegue ler o quadro: ele é um artefato do claude.ai e os responsáveis ficam num banco de dados dele. Leia o espelho [contexto/TAREFAS.md](contexto/TAREFAS.md).
   - Descubra quem é o usuário pelo `git config user.name` (o primeiro nome é o mesmo do campo "Responsável" e da branch `ESDD/<nome>`). Liste as tarefas dele que não estão concluídas, com número, título, dependências e a ordem sugerida. Depois pergunte por qual ele quer começar.

## 3. O que muda no Codex

| Assunto | Claude Code | Codex |
|---|---|---|
| Instruções do projeto | `CLAUDE.md` | este `AGENTS.md` (que manda ler o `CLAUDE.md`) |
| Hook do AI_LOG | [.claude/settings.json](.claude/settings.json) | [.codex/hooks.json](.codex/hooks.json); os dois rodam o mesmo [.claude/hooks/log_prompt.py](.claude/hooks/log_prompt.py) |
| Skills | `.claude/skills/` (`/atualizar-branch`, `/salvar-memoria`) | [.agents/skills/](.agents/skills/): as mesmas duas, que apontam para as do Claude |
| Quadro de tarefas | lê e marca o artefato direto | abre o link no navegador e usa o [contexto/TAREFAS.md](contexto/TAREFAS.md) |

### AI_LOG.md
- O hook só roda depois que o usuário confia no projeto e no hook (`/hooks` no Codex; veja a seção 3 do PRIMEIROS_PASSOS). Ele cria a entrada com `- **Ferramenta:** Codex` e devolve o aviso `[AI_LOG] ... #NNN`.
- Com o aviso: ao final da resposta, substitua os três `_(a preencher pelo Claude ao final da resposta)_` da entrada #NNN por **Objetivo**, **Resposta da IA (resumo)** e **Adaptações / correções**. O texto diz "pelo Claude", mas vale para você também. Não crie outra entrada.
- Sem o aviso (hook não confiável, Python fora do PATH ou Codex aberto fora da raiz do repositório), crie a entrada à mão no mesmo formato, incluindo a linha `- **Ferramenta:** Codex`, e avise o usuário que o hook não rodou.
- Aviso "não é um prompt do usuário": nada foi registrado e não é preciso criar entrada.

### Quadro de tarefas
- Quando uma tarefa mudar de status ou de responsável, atualize o [contexto/TAREFAS.md](contexto/TAREFAS.md) no mesmo commit dos registros e lembre o usuário de marcar no quadro pelo navegador (ou de pedir ao Murilo, se ele não tiver conta no claude.ai).

### Commits
- Mesmo formato do PRIMEIROS_PASSOS (seção 5.5): mensagem em inglês, no imperativo, com a tarefa (`Add circular queue for batch tests (T12)`), com código e registros em commits separados.
- Não use a linha `Co-Authored-By: Claude ...`, que é só dos commits feitos pelo Claude.
