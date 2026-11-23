# Tarefas do projeto (espelho do quadro)

Cópia em texto do quadro **"Plano Projeto ESDD"**: https://claude.ai/artifact/G6eqVDUisHMbyCAS5mDpfr

- O quadro é a versão visual (cronograma, checkboxes e responsáveis). Este arquivo existe para quem não consegue ler o quadro: o **Codex**, que não acessa artefatos do claude.ai, e quem estiver sem conta no claude.ai.
- **Os dois precisam bater.** Quem muda um muda o outro no mesmo dia:
  - O Claude atualiza o quadro (`ArtifactData`, coleção `tasks`) e este arquivo juntos.
  - Quem usa o Codex edita este arquivo, commita na sua `ESDD/<nome>` e marca a tarefa no quadro pelo navegador. Sem conta no claude.ai, avise o Murilo para ele marcar.
- Status: `concluída`, `em andamento` ou `pendente`. A tarefa só vira `concluída` depois da revisão de outro integrante.
- Atualizado em: 23/11/2026 (T12 concluída com o merge do PR #1).

## Por integrante

| Integrante | Ferramenta | Branch | Tarefas abertas |
|---|---|---|---|
| Murilo | Claude Code | `ESDD/murilo` | nenhuma (fases 1 e 2 concluídas) |
| Lucas | Codex | `ESDD/lucas` | T11, T13, T14 |
| Liliane | a definir | `ESDD/liliane` | T26, T10, T15, T16, T17 |
| Sem responsável | — | — | T18–T24 |

## Lista completa

| T## | Fase | Tarefa | Responsável | Status | Depende de |
|---|---|---|---|---|---|
| T01 | 1. Vetor e métricas | Dividir os módulos entre os integrantes | — | concluída | |
| T02 | 1. Vetor e métricas | Refatorar o projeto-exemplo para TADs | Murilo | concluída | |
| T03 | 1. Vetor e métricas | Corrigir os bugs conhecidos do projeto-exemplo | Murilo | concluída | |
| T04 | 1. Vetor e métricas | Medir o consumo de memória | Murilo | concluída | |
| T05 | 1. Vetor e métricas | Substituir os 7 blocos case por uma tabela de algoritmos | Murilo | concluída | |
| T25 | 1. Vetor e métricas | Gerar dados ordenados e invertidos | Murilo | concluída | |
| T06 | 2. Listas | Lista simplesmente encadeada com Insertion Sort e Merge Sort | Murilo | concluída | |
| T07 | 2. Listas | Lista duplamente encadeada com Insertion Sort e Merge Sort | Murilo | concluída | |
| T08 | 2. Listas | Lista circular com Insertion Sort e Merge Sort | Murilo | concluída | |
| T09 | 2. Listas | Comparar vetor contíguo × listas | Murilo | concluída | |
| T26 | 3. Pilha, fila e exportação | Modo passo a passo (tela atualiza a cada troca) | Liliane | pendente | |
| T10 | 3. Pilha, fila e exportação | Exportar cada comparação e troca em JSON ou CSV | Liliane | pendente | T26 |
| T11 | 3. Pilha, fila e exportação | Pilha para Desfazer (Undo) no modo passo a passo | Lucas | pendente | T26 (só a integração; o TAD da pilha sai antes) |
| T12 | 3. Pilha, fila e exportação | Fila de testes em lote (batch) | Lucas | concluída | |
| T13 | 4. Interface visual | Decidir a interface: Web ou Java | Lucas | pendente | decisão da equipe |
| T14 | 4. Interface visual | Ler o log exportado e desenhar as barras | Lucas | pendente | T10 (formato do log), T13 |
| T15 | 4. Interface visual | Animar comparações e trocas com cores distintas | Liliane | pendente | T14 |
| T16 | 4. Interface visual | Controles de reprodução | Liliane | pendente | T14 |
| T17 | 4. Interface visual | Tela comparativa das métricas | Liliane | pendente | T13 |
| T18 | 5. Extra: hash | Tabela hash com encadeamento exterior (extra) | — | pendente | |
| T19 | 5. Extra: hash | Buscar relatórios anteriores pelo menu (extra) | — | pendente | T18 |
| T20 | 6. Revisão | Revisar o padrão da disciplina em todo o código | — | pendente | |
| T21 | 6. Revisão | Revisar o AI_LOG.md | — | pendente | |
| T22 | 7. Testes e arguição | Testar casos-limite | — | pendente | |
| T23 | 7. Testes e arguição | Ensaiar a arguição individual | — | pendente | |
| T24 | 7. Testes e arguição | Fazer a entrega (02/12) | — | pendente | |

## Detalhes das tarefas do Lucas

Ordem sugerida: **T12 → T11 → T13 → T14**. A T12 não depende de ninguém, e o TAD da pilha da T11 também pode sair antes do passo a passo da Liliane.

- **T12 — Fila de testes em lote (batch).** Arquivos `queue.h` / `queue.c`. Fila circular com `start`, `count` e `% capacity` (padrão das aulas, ver [Pilhas_e_Filas_Estaticas.md](slides/Pilhas_e_Filas_Estaticas.md)). Cada item é um algoritmo (índice da tabela `sort_name`/`sort_run` de [src/sort.h](../src/sort.h)) + tamanho de entrada. Opção nova no menu: enfileirar vários testes e rodar todos em sequência, imprimindo as métricas.
- **T11 — Pilha para Desfazer (Undo).** Arquivos `stack.h` / `stack.c`. Convenção `top` = próxima posição livre (mesmo slide da T12). Empilhar cada troca (índices i e j); desfazer = desempilhar e trocar de volta. A ligação com o menu depende do modo passo a passo (T26).
- **T13 — Decidir a interface: Web ou Java.** Web: uma página HTML/CSS/JS que lê o arquivo de log. Java: Swing ou JavaFX, com as métricas em classes. A decisão é da equipe; registre-a no AI_LOG e na nota de sessão.
- **T14 — Ler o log exportado e desenhar as barras.** Uma barra por elemento, com altura proporcional ao valor. Depende do formato do log definido na T10 (Liliane): combine o formato com ela antes de começar.
