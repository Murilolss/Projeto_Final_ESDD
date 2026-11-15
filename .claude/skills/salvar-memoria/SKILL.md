---
name: salvar-memoria
description: Salva (ou atualiza) a nota de memória da sessão atual em contexto/memory/, com o que foi feito, decisões, pendências e próximos passos. Use quando o usuário rodar /salvar-memoria.
argument-hint: "[título curto opcional da sessão]"
disable-model-invocation: true
---

# /salvar-memoria — salvar a memória desta sessão

Registre o que aconteceu **nesta conversa** em uma nota dentro de `contexto/memory/`. Cada sessão tem **uma** nota: se este comando rodar várias vezes na mesma sessão, a nota existente é atualizada, nunca duplicada.

ID desta sessão: `${CLAUDE_SESSION_ID}`
Título sugerido pelo usuário (pode estar vazio): `$ARGUMENTS`

## 1. Achar a nota desta sessão

1. Procure em `contexto/memory/*.md` o marcador `<!-- session: <ID desta sessão> -->` (use Grep).
2. Se o ID acima aparecer literalmente como `${CLAUDE_SESSION_ID}` (substituição não suportada), ou se nada for encontrado, verifique se **nesta conversa** você já criou ou editou uma nota em `contexto/memory/`. Se sim, é ela.
3. Encontrou → **atualize** essa nota (passo 3). Não encontrou → **crie** uma nova (passo 2).

## 2. Criar uma nota nova

- Nome: `AAAA-MM-DD_sessao-NN_<slug>.md`
  - Data de hoje.
  - `NN` = maior número de `sessao-NN` já existente na pasta + 1, com dois dígitos.
  - `<slug>`: do título em `$ARGUMENTS` ou, se vazio, 2–4 palavras do assunto principal da sessão, em minúsculas, com hífens e sem acentos.
- Primeira linha: `# Sessão NN — AAAA-MM-DD — <Título>`.
- Logo abaixo do título: `<!-- session: <ID desta sessão> -->` (omita se o ID não foi substituído).

## 3. Conteúdo (criar ou atualizar)

Use exatamente estas seções, em português, frases curtas e factuais:

```markdown
# Sessão NN — AAAA-MM-DD — <Título>
<!-- session: <ID> -->

- **Autor:** <git config user.name>
- **Prompts no AI_LOG:** #NNN–#MMM

## O que foi feito
- <entregas concretas, com os arquivos criados/alterados>

## Decisões / observações
- <decisões tomadas e o porquê; bugs ou armadilhas descobertos>

## Pendências
- <o que ficou em aberto, inclusive dúvidas a confirmar com o professor>

## Próximos passos sugeridos
1. <próxima ação concreta>
```

Regras:

- **Ao atualizar**, mescle: mantenha o que ainda é verdade, acrescente o que é novo, mova para "O que foi feito" as pendências resolvidas e apague o que ficou errado. Não duplique itens.
- Faixa de prompts: veja no `AI_LOG.md` as entradas desta sessão (a primeira e a última criadas nesta conversa).
- Cite tarefas do plano pelo número (T01…T24) quando for o caso. O plano está em https://claude.ai/artifact/G6eqVDUisHMbyCAS5mDpfr.
- Não copie o que já está no código, no git ou no `CLAUDE.md`. Registre o que **não** dá para deduzir deles: decisões, motivos, dúvidas e combinados da equipe.
- Nada de dados sensíveis (senhas, tokens, e-mails → `[removido]`).

## 4. Responder

Diga em 2–3 linhas se a nota foi **criada** ou **atualizada**, o caminho (como link markdown) e os principais pontos registrados.
