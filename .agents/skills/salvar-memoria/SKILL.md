---
name: salvar-memoria
description: Salva (ou atualiza) a nota de memória da sessão atual em contexto/memory/, com o que foi feito, decisões, pendências e próximos passos. Use quando o usuário pedir para salvar a memória da sessão.
---

# Salvar a memória da sessão (versão Codex)

Esta skill é a mesma do Claude Code. Para não manter duas cópias, as instruções ficam num arquivo só:

1. Leia [.claude/skills/salvar-memoria/SKILL.md](../../../.claude/skills/salvar-memoria/SKILL.md) e siga as instruções de lá.
2. Diferenças no Codex:
   - `${CLAUDE_SESSION_ID}` não é substituído. Use o caminho alternativo da própria skill: se nesta conversa você já criou ou editou uma nota em `contexto/memory/`, atualize essa; senão, crie uma nova sem o marcador `<!-- session: ... -->`.
   - `$ARGUMENTS` também não é substituído. O título é o que o usuário escreveu junto do pedido (pode estar vazio).
   - Na linha **Autor**, acrescente ` (Codex)` depois do nome.
