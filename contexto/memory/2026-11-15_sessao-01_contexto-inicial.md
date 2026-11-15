# Sessão 01 — 2026-11-15 — Contexto, AI_LOG e plano da equipe
<!-- session: c9397dae-7035-4045-92a1-9724c9dbe7b8 -->

- **Autor:** Murilo Leandro
- **Prompts no AI_LOG:** #001–#008

## O que foi feito
- Lidos os 14 PDFs de `contexto/pdfs/`, os códigos de `contexto/codigo-exemplos/` e o `contexto/projeto-exemplo/`.
- Criado um `.md` por PDF em `contexto/slides/`. O código que aparece como imagem nos slides confere com `codigo-exemplos`; o de pilhas/filas e o de lista dupla foram transcritos dos slides.
- Preenchido o `CLAUDE.md` (requisitos, padrões da disciplina, mapa de pastas, diagnóstico do `projeto-exemplo`).
- Criado o `AI_LOG.md`, com o hook `UserPromptSubmit` (`.claude/settings.json` + `.claude/hooks/log_prompt.py`) que registra cada prompt automaticamente.
- Publicado o plano da equipe como artefato "Plano Projeto ESDD" (https://claude.ai/artifact/G6eqVDUisHMbyCAS5mDpfr): 7 fases, tarefas T01–T24, code freeze em 29/11 e entrega em 02/12/2026. Concluída/responsável ficam salvos na própria página e são compartilhados.
- Criada a skill `/salvar-memoria` (`.claude/skills/salvar-memoria/SKILL.md`).

## Decisões / observações
- O código do projeto deve ser em inglês (enunciado); a conversa fica em português.
- O padrão da disciplina é TAD `.h`/`.c`/`main.c` com ponteiro opaco.
- Não há material de aula sobre lista circular (T08 parte do zero).
- O hook do AI_LOG usa Python (o `jq` não está instalado) e tenta `python`, `python3` e `py` para funcionar nos outros computadores.
- A pedido da equipe, saíram do plano as tarefas de Engenharia de Software (GitHub, requisitos, arquitetura) e de Inglês (README). A definição do formato do log ficou dentro da T10.
- A interface (Web ou Java) está em aberto e é decidida na T13.
- Bugs nos exemplos do professor (para não copiar): o exemplo O(n) do slide Big-O retorna 0 dentro do `for`; `fatorial.c` chama a versão iterativa duas vezes; `ListaSequencial.h` tem `#endif` no lugar errado; `consultaPosicao` mistura base 0/1.

## Pendências
- Confirmar com o professor se todos os itens da "Integração Interdisciplinar" são obrigatórios. Pelo PDF, só o Java aparece como "alternativa à Web"; Engenharia de Software e Inglês não aparecem como opcionais. Se forem obrigatórios, as tarefas voltam para a fase 6 do plano.
- Compartilhar o artefato do plano com a equipe com acesso de Colaborador (hoje só o dono abre).
- `README.md` continua vazio.

## Próximos passos sugeridos
1. Dividir os módulos entre os integrantes e preencher o responsável no plano (T01).
2. Refatorar o `projeto-exemplo` para TADs e corrigir os bugs conhecidos (T02–T03).
3. Implementar a medição de memória e a tabela de algoritmos (T04–T05).
