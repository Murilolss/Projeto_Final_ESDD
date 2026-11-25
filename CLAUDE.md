# CLAUDE.md — Projeto Final ESDD (Estrutura de Dados, IFSP Araraquara, Prof. Eduardo Leal)

## O que é o projeto

**Plataforma de Análise de Estruturas e Algoritmos**: sistema de *benchmarking* e visualização de estruturas de dados em **C**, com interface Web (HTML/CSS/JS) que anima as barras de ordenação a partir de logs JSON/CSV exportados pelo C. Avaliação final da disciplina, equipe de 3–4 pessoas.

Requisitos completos: `contexto/slides/Enunciado.md` (original em `contexto/pdfs/Enunciado.pdf`). As pastas `contexto/pdfs/` e `contexto/slides/` **não estão no git** (estão no `.gitignore`): cada integrante guarda a própria cópia. Se elas não existirem no computador, use o resumo dos requisitos abaixo e peça os arquivos a outro integrante, sem recriá-los nem colocá-los no git.

Primeira vez no projeto (integrante novo ou sessão nova do Claude): leia [PRIMEIROS_PASSOS.md](PRIMEIROS_PASSOS.md), com a configuração, a criação da branch `ESDD/<integrante>`, o fluxo de trabalho e os registros obrigatórios.

**Claude + Codex:** o Murilo usa o Claude Code e o Lucas usa o Codex, em paralelo e em computadores diferentes. O Codex lê o [AGENTS.md](AGENTS.md), que manda seguir **este** arquivo. Toda regra nova vai para cá, nunca só para o `AGENTS.md`. Os dois assistentes usam o mesmo hook do AI_LOG.

**Quadro de tarefas:** o artefato "Plano Projeto ESDD" (https://claude.ai/artifact/G6eqVDUisHMbyCAS5mDpfr; responsáveis e status na coleção `tasks`, lida com `ArtifactData`) tem um espelho em texto, o [contexto/TAREFAS.md](contexto/TAREFAS.md), que é o que o Codex consegue ler. Ao mudar o status ou o responsável de uma tarefa num dos dois, atualize o outro também.

Resumo dos requisitos:
1. Vetores com alocação dinâmica (`malloc`/`realloc`/`free`) + métricas de **tempo** e **consumo de memória**.
2. Listas **simplesmente**, **duplamente** encadeadas e **circulares**, com **Insertion Sort** e **Merge Sort** manipulando ponteiros; comparar com vetores contíguos.
3. **Pilha** para Desfazer/Undo no modo passo a passo; **Fila** para execução de testes em lote (batch).
4. (EXTRA) **Tabela Hash** com encadeamento exterior, chave = nome do algoritmo, para recuperar relatórios anteriores.
5. Exportar cada troca/comparação em **JSON ou CSV**; front-end HTML/CSS/JS anima as barras (alternativa: Java Swing/JavaFX).
6. Git/GitHub, requisitos funcionais e documentação de arquitetura.
7. Entregar **`AI_LOG.md`** com prompts usados e como as respostas foram adaptadas.

## Registro obrigatório de prompts — AI_LOG.md

Todo prompt enviado neste projeto é registrado em [AI_LOG.md](AI_LOG.md).

**Parte automática (hook):** o hook `UserPromptSubmit` em [.claude/settings.json](.claude/settings.json) (no Codex, [.codex/hooks.json](.codex/hooks.json)) roda [.claude/hooks/log_prompt.py](.claude/hooks/log_prompt.py) a cada prompt. Ele cria a entrada numerada (`## #NNN — <Dia da semana>, DD/MM/AAAA`), com autor (`git config user.name`), ferramenta (`Claude Code`/`Codex`) e o prompt literal, troca e-mails por `[removido]` e avisa ao assistente o número da entrada (mensagem `[AI_LOG] ... #NNN`). Blocos injetados por extensões são removidos, e avisos automáticos (`<task-notification>`, `<agent-message>`) não viram entrada: o aviso diz que não é um prompt do usuário, e então não se cria entrada manual. Requer Python 3 no PATH (`python`, `python3` ou `py`).

**Parte do Claude:**

1. Quando receber o aviso `[AI_LOG] ... #NNN`, **não criar outra entrada**: ao final da resposta, substituir os três `_(a preencher pelo Claude ao final da resposta)_` da entrada #NNN por **Objetivo**, **Resposta da IA (resumo)** (o que foi feito e quais arquivos mudaram) e **Adaptações / correções**.
2. Se o aviso **não** aparecer (hook desativado, sem Python), criar a entrada manualmente no mesmo formato, no fim do arquivo (antes do `---` que precede o bloco `<!-- MODELO ... -->`).
3. Nunca apagar nem reescrever entradas antigas, exceto para atualizar "Adaptações / correções" quando o usuário corrigir ou rejeitar algo de uma resposta anterior.
4. Não registrar dados sensíveis (senhas, tokens, e-mails); substituir por `[removido]`.

Isso atende à exigência do enunciado ("Registro de Prompts") e serve de material para a arguição individual.

## Regras obrigatórias para o código

- **Idioma do código: inglês.** Nomes de funções, variáveis, tipos, comentários e o `README.md` em inglês (exigência do enunciado). Os textos exibidos ao usuário (`printf`, nomes dos algoritmos no menu) ficam em **português sem acento** (decisão da equipe; o console do Windows estraga acentos). Conversa com o usuário continua em português.
- **Seguir os padrões da disciplina** (proibição de "caixa-preta"): o código deve se parecer com o dos exemplos das aulas e ser explicável na arguição oral.
  - TAD em 3 arquivos: `.h` (contrato, `typedef struct X X;` opaco + protótipos), `.c` (struct real + implementação), `main.c` (cliente). Nunca `#include "arquivo.c"`.
  - Include guards corretos (`#ifndef X_H / #define X_H / ... / #endif`).
  - Sempre checar retorno de `malloc` (`if (p == NULL)`), liberar com `free` e zerar o ponteiro (`p = NULL`).
  - Funções que podem falhar retornam `int` (1 = sucesso, 0 = falha) e devolvem dados por ponteiro de saída (ex.: `int pop(Stack *s, int *out)`).
  - Validar existência da estrutura (`== NULL`) e limites (vazia/cheia) antes de operar.
  - Pilha: convenção `top` = próxima posição livre. Fila: circular com `start` + `count` e `% capacity`.
  - Lista dupla com `head` e `tail`; tratar casos-limite (vazia, nó único, primeiro, último).
  - Código simples e didático, sem truques — cada integrante precisa explicar o funcionamento interno.
- Toda sugestão gerada com IA fica registrada no `AI_LOG.md` (ver seção acima).

## Branches (git)

- `main` = produção (versão de entrega); `dev` = integração; `ESDD/<integrante>` = trabalho de cada pessoa (ex.: `ESDD/murilo`).
- Fluxo: commitar na própria `ESDD/<integrante>` → merge em `dev` depois da revisão de outro integrante → merge de `dev` em `main` quando estável. Nunca commitar direto em `main` ou `dev`.

## Ambiente

- Windows 11, compilador MinGW (gcc). O `projeto-exemplo` usa `#define __USE_MINGW_ANSI_STDIO 1` para `%lld`, `system("cls")` e `sleep()` de `unistd.h`.

## Estrutura de pastas

| Pasta | Conteúdo |
|---|---|
| `.claude/` | hooks e skills do projeto (`/salvar-memoria` grava a nota da sessão em `contexto/memory/`; `/atualizar-branch` faz `git pull origin dev` na `ESDD/<integrante>` e o push) |
| `.codex/`, `.agents/skills/`, `AGENTS.md` | configuração do Codex: hook (o mesmo script do `.claude/hooks/`), as mesmas skills (apontam para as do `.claude/skills/`) e as instruções |
| `contexto/TAREFAS.md` | espelho em texto do quadro de tarefas (T01–T26) |
| `contexto/codigo-exemplos/` | códigos das aulas (padrão de estilo a seguir) — recursão, ordenação, busca, hash (endereçamento aberto), ponteiros, TAD (carrinho), lista sequencial estática, lista simplesmente encadeada |
| `contexto/pdfs/` | slides das aulas + `Enunciado.pdf` (**fora do git**: só na cópia de cada integrante) |
| `contexto/slides/` | um `.md` por PDF; consultar estes em vez dos PDFs (**fora do git**: só na cópia de cada integrante) |
| `contexto/projeto-exemplo/` | protótipo feito à mão (menu de ordenação + métricas em vetor) — ponto de partida, não o padrão final. Inclui `Testes de algoritmos de ordenação.pdf`, a **1ª versão do enunciado** em que o protótipo se baseou (resumo e comparação com o final em `contexto/slides/Testes de algoritmos de ordenação.md`) |
| `contexto/memory/` | uma nota por sessão, criada ou atualizada com `/salvar-memoria` (ler a mais recente ao iniciar) |

Os PDFs de pilhas/filas e lista dupla **não** têm código em `codigo-exemplos`; o código de referência está nos `.md` correspondentes em `contexto/slides/`. Não há material de lista circular. Sem a pasta `contexto/slides/`, use como referência o código do projeto, que já segue esse padrão: `src/stack.c`, `src/queue.c`, `src/doubly_list.c` e `src/circular_list.c`.

## projeto-exemplo — o que já existe e o que falta corrigir

Existe: geração de vetor dinâmico, 7 ordenações (Bubble, Insertion, Merge iterativo/recursivo, Quick pivô início/fim, Selection) com struct `Metricas { nome, comparacoes, trocas, tempo_ms }`, menu e tabela comparativa.

Problemas conhecidos:
- `#include "*.c"` em vez de `.h` (quebra o padrão TAD).
- Nomes e comentários em português (enunciado exige inglês).
- `srand()` nunca é chamado → mesmos números a cada execução.
- `alocarVetor` gera números únicos e depois sobrescreve com `rand` 1..512 (duplicatas); `PesqSeq` lê memória não inicializada e testa `numeros[i]` antes de `i < tam`.
- `Intercalar` usa VLAs (`int V_Esquerda[n1]`) → estouro de pilha com vetores grandes; usar `malloc`.
- `malloc` da cópia sem checar `NULL`; 7 blocos `case` duplicados (poderia ser tabela de ponteiros para função).
- Não mede memória; não tem listas, pilha, fila, hash nem exportação JSON/CSV.
