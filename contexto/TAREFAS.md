# Tarefas do projeto (espelho do quadro)

Cópia em texto do quadro **"Plano Projeto ESDD"**: https://claude.ai/artifact/G6eqVDUisHMbyCAS5mDpfr

- O quadro é a versão visual (cronograma, checkboxes e responsáveis). Este arquivo existe para quem não consegue ler o quadro: o **Codex**, que não acessa artefatos do claude.ai, e quem estiver sem conta no claude.ai.
- **Os dois precisam bater.** Quem muda um muda o outro no mesmo dia:
  - O Claude atualiza o quadro (`ArtifactData`, coleção `tasks`) e este arquivo juntos.
  - Quem usa o Codex edita este arquivo, commita na sua `ESDD/<nome>` e marca a tarefa no quadro pelo navegador. Sem conta no claude.ai, avise o Murilo para ele marcar.
- Status: `concluída`, `em andamento` ou `pendente`. A tarefa só vira `concluída` depois da revisão de outro integrante.
- Atualizado em: 24/11/2026 (T26 e T10 concluídas com o PR #2, T11 com o PR #4, T13 e T14 com o PR #5, T15 com o PR #7, T16 com o PR #8, T17 com o PR #9).

## Por integrante

| Integrante | Ferramenta | Branch | Tarefas abertas |
|---|---|---|---|
| Murilo | Claude Code | `ESDD/murilo` | nenhuma (fases 1 e 2 concluídas) |
| Lucas | Codex | `ESDD/lucas` | nenhuma (T11, T12, T13 e T14 concluídas) |
| Liliane | Claude Code | `ESDD/liliane` | nenhuma (T26, T10, T15, T16 e T17 concluídas) |
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
| T26 | 3. Pilha, fila e exportação | Modo passo a passo (tela atualiza a cada troca) | Liliane | concluída | |
| T10 | 3. Pilha, fila e exportação | Exportar cada comparação e troca em JSON ou CSV | Liliane | concluída | T26 |
| T11 | 3. Pilha, fila e exportação | Pilha para Desfazer (Undo) no modo passo a passo | Lucas | concluída | T26 (só a integração; o TAD da pilha sai antes) |
| T12 | 3. Pilha, fila e exportação | Fila de testes em lote (batch) | Lucas | concluída | |
| T13 | 4. Interface visual | Decidir a interface: Web ou Java | Lucas | concluída | decisão da equipe |
| T14 | 4. Interface visual | Ler o log exportado e desenhar as barras | Lucas | concluída | T10 (formato do log), T13 |
| T15 | 4. Interface visual | Animar comparações e trocas com cores distintas | Liliane | concluída | T14 |
| T16 | 4. Interface visual | Controles de reprodução | Liliane | concluída | T14 |
| T17 | 4. Interface visual | Tela comparativa das métricas | Liliane | concluída | T13 |
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
- **T13 — Interface Web.** Em 24/11/2026, Lucas escolheu HTML, CSS e JavaScript puro. O navegador lê o JSON exportado pelo programa em C por meio de um seletor de arquivos locais.
- **T14 — Ler o log exportado e desenhar as barras.** Abra [`web/index.html`](../web/index.html) no navegador e selecione o [JSON de exemplo](../logs/exemplo_bubble_sort_n10.json) em **Abrir JSON**. O gráfico desenha uma barra por elemento de `initial`, na ordem do vetor e com altura proporcional ao valor.

## Detalhes das tarefas da Liliane

- **T15 — Animar comparações e trocas com cores distintas.** Em [`web/`](../web/), o botão **Reproduzir** parte do `initial` e reaplica os passos do log em ordem. `compare` pinta as duas barras de amarelo e mostra `value_i` e `value_j`, `swap` pinta de vermelho e troca as alturas, e `write` pinta de azul e muda a altura da barra `i`. No fim, o vetor reaplicado é conferido com o `final`: se bater, todas as barras ficam verdes; se não bater, a página avisa que o log pode estar incompleto. A animação dura no máximo cerca de 30 s; num log com mais de 1.800 passos, cada quadro aplica vários passos e pinta só o último. Passos com tipo ou posição inválidos são rejeitados ao abrir o arquivo.
- **T16 — Controles de reprodução.** Abaixo do status, em [`web/`](../web/): **Reproduzir/Pausar/Continuar** (um só botão), **◀ Passo** e **Passo ▶** (um passo exato, pausando a animação), **Reiniciar** (volta ao vetor inicial) e um controle de **Velocidade** com cinco posições, de 1 s a 16 ms por quadro, que muda a animação mesmo com ela rodando. A reprodução guarda a posição no log (`replay.position`). Voltar um passo reconstrói o vetor a partir do `initial`, reaplicando os passos até a posição anterior: os passos não têm "desfazer", e assim o código fica simples. Depois da revisão do PR #8, o visualizador aceita logs de até 100 números (o C continua exportando até 1000), e a animação mostra um passo por quadro em todas as velocidades, menos na "Muito rápida": nela, um log com mais de 1.800 passos junta vários passos por quadro para terminar em cerca de 30 s.
- **T17 — Tela comparativa das métricas.** No C, a opção **Comparar todos os algoritmos** pergunta se exporta o comparativo (`export_report` em `src/export.c`) para `logs/comparativo_n<N>_<data>_<hora>.json`, com tempo, comparações, trocas e memória extra dos 7 algoritmos do vetor e dos 2 de cada lista. Na Web, a página [`web/comparativo.html`](../web/comparativo.html) (link **Comparativo** no topo) abre esse arquivo, mostra um gráfico de barras para a métrica escolhida, agrupado por estrutura, e uma tabela com todas as métricas. Formato em [formato_comparativo.md](formato_comparativo.md); exemplo em [`logs/exemplo_comparativo_n10000.json`](../logs/exemplo_comparativo_n10000.json).
