# Enunciado — Projeto Final ESDD

> Fonte: `contexto/pdfs/Enunciado.pdf` (2 páginas)

## Projeto: Plataforma de Análise de Estruturas e Algoritmos

Desenvolvimento de um **Sistema Completo de Benchmarking e Visualização de Estruturas de Dados**.
Equipes de **3 a 4 integrantes**. É a **Avaliação Final** da disciplina.

## Implementações obrigatórias

| Item | Requisito |
|---|---|
| **Alocação Dinâmica e Ponteiros** | Substituir vetores estáticos por alocação dinâmica (`malloc`, `realloc`, `free`). O sistema deve **monitorar o tempo** (via métricas) e o **consumo de memória**. |
| **Listas Lineares** (Encadeadas, Duplamente Encadeadas e Circulares) | Implementar algoritmos de ordenação (ex.: **Insertion Sort** e **Merge Sort**) **adaptados para manipular ponteiros** em listas encadeadas, **comparando o desempenho com vetores contíguos**. |
| **Pilhas e Filas** | Módulo de histórico de operações: **Pilha** para **Desfazer/Undo** no modo passo a passo, e **Fila** de execução de testes em lote (**Batch Processing**). |
| **(EXTRA) Tabelas Hash** | Tabela Hash com tratamento de colisões por **encadeamento exterior** para indexar e recuperar **relatórios de testes anteriores pelo nome do algoritmo**. |

## Integração interdisciplinar

- **Interfaces Web + Linguagem de Script:** o programa em C **exporta os logs de cada troca/comparação em JSON ou CSV**. A equipe desenvolve uma interface em **HTML, CSS e JavaScript** que lê esse arquivo e **anima as barras de ordenação**.
- **Orientação a Objetos (alternativa à Web):** interface visual em **Java** (Swing ou JavaFX), encapsulando as estruturas de métricas em classes.
- **Engenharia de Software:** controle de versão (**Git/GitHub**) em equipe, **levantamento de requisitos funcionais** e **documentação da arquitetura**.
- **Inglês:** **toda a documentação do código (comentários, nomes de variáveis/funções) e o `README.md` devem estar em inglês.**

## 3. Diretrizes para uso de IA

Uso de IA generativa é **permitido e incentivado** como apoio, com regras de integridade acadêmica:

- **Registro de Prompts:** entregar um arquivo **`AI_LOG.md`** com os principais prompts e explicando **como as respostas foram adaptadas ou corrigidas**.
- **Proibição de "Caixa-Preta":** código gerado por IA **deve ser refatorado para seguir os padrões da disciplina**.
- **Arguição Individual:** cada integrante responderá oralmente a perguntas técnicas sobre trechos do código. A nota individual é ponderada pela capacidade de explicar o funcionamento interno das estruturas.

## Checklist derivado

- [ ] Vetores alocados dinamicamente (`malloc`/`realloc`/`free`) + métricas de tempo e memória
- [ ] Lista simplesmente encadeada, duplamente encadeada e circular
- [ ] Insertion Sort e Merge Sort sobre listas (manipulando ponteiros, não copiando para vetor)
- [ ] Comparativo lista × vetor
- [ ] Pilha de Undo (modo passo a passo)
- [ ] Fila de testes em lote (batch)
- [ ] (Extra) Hash com encadeamento exterior, chave = nome do algoritmo
- [ ] Exportação de log de trocas/comparações em JSON ou CSV
- [ ] Interface HTML/CSS/JS animando as barras (ou Java Swing/JavaFX)
- [ ] Código, comentários e README em inglês
- [ ] Requisitos funcionais + documentação de arquitetura
- [ ] `AI_LOG.md`
