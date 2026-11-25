# Plataforma de Análise de Estruturas e Algoritmos

**Documentação de Engenharia de Software (ENGS)**

Projeto Final integrado — Estrutura de Dados (ESDD), Interfaces Web, Engenharia de Software e Inglês

Instituto Federal de São Paulo — Câmpus Araraquara — 2º semestre de 2026

**Integrantes:**

- Murilo Leandro
- Lucas Cruz
- Liliane Perim Vigetta
- Matheus Miasaki

Repositório: <https://github.com/Murilolss/Projeto_Final_ESDD>

Versão do documento: 1.0 — 25/11/2026

<div style="page-break-after: always;"></div>

## Sumário

1. Introdução
2. Escopo do sistema
3. Requisitos funcionais
4. Requisitos não funcionais
5. Arquitetura do sistema
6. Módulos do programa em C
7. Interface Web
8. Formatos de troca de dados
9. Decisões de projeto
10. Controle de versão e fluxo de trabalho
11. Gestão das tarefas
12. Uso de IA generativa
13. Como compilar e executar
14. Limitações conhecidas e trabalhos futuros

<div style="page-break-after: always;"></div>

## 1. Introdução

A **Plataforma de Análise de Estruturas e Algoritmos** é um sistema de *benchmarking* e visualização de estruturas de dados. O núcleo é um programa em **linguagem C** que ordena vetores alocados dinamicamente e listas encadeadas, mede o desempenho de cada algoritmo (tempo, comparações, trocas e memória) e exporta cada passo da ordenação para um arquivo **JSON**. Uma interface **Web** (HTML, CSS e JavaScript) lê esse arquivo e anima as barras da ordenação, além de exibir gráficos comparativos das métricas.

Este documento reúne a parte de Engenharia de Software pedida no enunciado: o levantamento dos requisitos funcionais e não funcionais, a documentação da arquitetura e a descrição do controle de versão em equipe com Git e GitHub.

### 1.1 Objetivos

- Comparar, com números medidos, algoritmos de ordenação sobre um vetor contíguo e sobre três tipos de lista encadeada.
- Tornar visível o funcionamento interno dos algoritmos, tanto no console (modo passo a passo) quanto no navegador (animação).
- Aplicar na prática as estruturas estudadas na disciplina: alocação dinâmica, listas, pilha e fila.

### 1.2 Público-alvo

Estudantes e professores de Estrutura de Dados que queiram observar o comportamento dos algoritmos de ordenação e comparar o custo de cada estrutura.

### 1.3 Glossário

| Termo | Significado |
|---|---|
| TAD | Tipo Abstrato de Dados: estrutura cujo conteúdo só é acessado pelas funções do seu módulo |
| N | Número de elementos do vetor ou da lista |
| Passo | Uma comparação, troca ou escrita feita pelo algoritmo durante a ordenação |
| Log de passos | Arquivo JSON com o vetor inicial, todos os passos e o vetor final de uma ordenação |
| Comparativo | Arquivo JSON com as métricas de todos os algoritmos sobre o mesmo vetor |
| Lote (*batch*) | Conjunto de testes enfileirados e executados em sequência |
| Pico de memória extra | Maior quantidade de memória de *heap* que o algoritmo alocou além do vetor ou da lista |

<div style="page-break-after: always;"></div>

## 2. Escopo do sistema

**Dentro do escopo:**

- Geração de vetores de tamanho escolhido pelo usuário, com dados aleatórios (sem repetição), ordenados ou invertidos.
- Sete algoritmos de ordenação sobre o vetor: Bubble Sort, Insertion Sort, Merge Sort iterativo, Merge Sort recursivo, Quick Sort com pivô no início, Quick Sort com pivô no fim e Selection Sort.
- Insertion Sort e Merge Sort sobre lista simplesmente encadeada, duplamente encadeada e circular, manipulando apenas ponteiros.
- Métricas de tempo, comparações, trocas e memória.
- Modo passo a passo no console, com Desfazer (pilha).
- Fila de testes em lote.
- Exportação do log de passos e do comparativo de métricas em JSON.
- Interface Web para animar o log e exibir o comparativo.

**Fora do escopo:**

- Persistência em banco de dados e acesso por rede: o programa e a página trabalham com arquivos locais.
- Interface gráfica nativa (a alternativa em Java Swing/JavaFX não foi adotada).
- Exportação em CSV (o enunciado permite JSON **ou** CSV; a equipe escolheu JSON).

**Planejado (extra do enunciado, ainda não implementado):** Tabela Hash com encadeamento exterior, indexada pelo nome do algoritmo, para recuperar relatórios de testes anteriores (tarefas T18 e T19).

<div style="page-break-after: always;"></div>

## 3. Requisitos funcionais

Prioridade: **E** = essencial (exigido no enunciado), **D** = desejável (melhoria proposta pela equipe), **X** = extra do enunciado.

### 3.1 Vetor e métricas

| ID | Requisito | Prioridade | Situação |
|---|---|---|---|
| RF01 | O sistema deve pedir o tamanho N e criar o vetor com alocação dinâmica (`malloc`). | E | Implementado |
| RF02 | O sistema deve preencher o vetor com dados aleatórios sem repetição, ordenados ou invertidos, à escolha do usuário. | D | Implementado |
| RF03 | O sistema deve permitir alterar o tamanho do vetor em tempo de execução, usando `realloc`. | E | Implementado |
| RF04 | O sistema deve permitir trocar o tipo dos dados sem recriar o vetor. | D | Implementado |
| RF05 | O sistema deve ordenar o vetor com qualquer um dos 7 algoritmos, sempre sobre uma cópia, para que o vetor original continue disponível. | E | Implementado |
| RF06 | Para cada execução, o sistema deve exibir tempo (ms), número de comparações, número de trocas e pico de memória extra (bytes). | E | Implementado |
| RF07 | O sistema deve executar todos os algoritmos sobre o mesmo vetor e exibir uma tabela comparativa. | E | Implementado |
| RF08 | O sistema deve exibir o vetor atual quando o usuário pedir. | D | Implementado |

### 3.2 Listas encadeadas

| ID | Requisito | Prioridade | Situação |
|---|---|---|---|
| RF09 | O sistema deve copiar os valores do vetor para uma lista simplesmente encadeada, duplamente encadeada ou circular. | E | Implementado |
| RF10 | O sistema deve ordenar cada lista com Insertion Sort e Merge Sort alterando apenas os ponteiros dos nós, sem copiar valores nem alocar nós novos. | E | Implementado |
| RF11 | O sistema deve executar um comparativo vetor × listas para N = 1.000, 10.000 e 50.000, com os três tipos de dados, exibindo tempo, comparações, trocas, memória da estrutura e memória extra. | E | Implementado |

### 3.3 Pilha, fila e modo passo a passo

| ID | Requisito | Prioridade | Situação |
|---|---|---|---|
| RF12 | O sistema deve oferecer um modo passo a passo em que a tela é redesenhada a cada passo da ordenação e espera o usuário. | E | Implementado |
| RF13 | No modo passo a passo, o usuário deve poder escolher se o programa para também nas comparações ou só nas trocas e escritas. | D | Implementado |
| RF14 | No modo passo a passo, o sistema deve registrar cada troca e escrita numa **pilha** e permitir Desfazer (`u`), Refazer (ENTER) e terminar a ordenação sem pausas (`f`). | E | Implementado |
| RF15 | O sistema deve permitir enfileirar até 10 testes (algoritmo + tamanho, com N até 50.000) numa **fila** e executá-los em sequência, na ordem de entrada. | E | Implementado |
| RF16 | O usuário deve poder descartar o lote antes de executá-lo. | D | Implementado |

### 3.4 Exportação e interface Web

| ID | Requisito | Prioridade | Situação |
|---|---|---|---|
| RF17 | O sistema deve exportar cada comparação, troca e escrita de uma ordenação para um arquivo JSON, junto com o vetor inicial, o vetor final e as métricas. | E | Implementado |
| RF18 | O sistema deve recusar a exportação do log de passos quando N > 1.000 e explicar o motivo ao usuário. | D | Implementado |
| RF19 | O sistema deve exportar a tabela comparativa (RF07) para um arquivo JSON. | D | Implementado |
| RF20 | A interface Web deve abrir um log de passos local e desenhar uma barra por elemento, com altura proporcional ao valor. | E | Implementado |
| RF21 | A interface Web deve animar o log com cores distintas para comparação (amarelo), troca (vermelho) e escrita (azul), e conferir o resultado com o vetor final (verde). | E | Implementado |
| RF22 | A interface Web deve oferecer Reproduzir/Pausar, avançar e voltar um passo, Reiniciar e cinco velocidades. | D | Implementado |
| RF23 | A interface Web deve abrir o comparativo e exibir um gráfico de barras por métrica, agrupado por estrutura, e uma tabela com todas as métricas. | D | Implementado |
| RF24 | A interface Web deve rejeitar arquivos inválidos com uma mensagem, mantendo a última visualização válida. | D | Implementado |

### 3.5 Extra

| ID | Requisito | Prioridade | Situação |
|---|---|---|---|
| RF25 | O sistema deve guardar os relatórios de testes numa Tabela Hash com encadeamento exterior, usando o nome do algoritmo como chave. | X | Planejado (T18) |
| RF26 | O usuário deve poder buscar, pelo menu, os relatórios anteriores de um algoritmo. | X | Planejado (T19) |

<div style="page-break-after: always;"></div>

## 4. Requisitos não funcionais

| ID | Categoria | Requisito |
|---|---|---|
| RNF01 | Linguagem | O núcleo deve ser escrito em C (padrão C99), compilado com gcc (MinGW) sem *warnings* com `-Wall -Wextra`. |
| RNF02 | Padrão da disciplina | Cada estrutura deve ser um TAD em três arquivos (`.h` com a struct opaca e os protótipos, `.c` com a implementação, `main.c` como cliente), com *include guards*. |
| RNF03 | Robustez | Todo `malloc`/`realloc` deve ter o retorno conferido; toda memória alocada deve ser liberada com `free`, e o ponteiro zerado. Funções que podem falhar retornam 1 (sucesso) ou 0 (falha). |
| RNF04 | Idioma | Nomes, comentários do código e o `README.md` em inglês. Textos exibidos no console em português sem acento, porque o console do Windows não exibe acentos corretamente. |
| RNF05 | Plataforma | O programa deve rodar no Windows 11 a partir da raiz do projeto. A interface Web deve funcionar em navegadores atuais, abrindo os arquivos locais sem servidor. |
| RNF06 | Desempenho | O comparativo vetor × listas deve rodar com N = 50.000 sem estouro de pilha, mesmo no pior caso do Quick Sort. |
| RNF07 | Usabilidade | Entradas inválidas no menu não podem encerrar o programa; o sistema mostra uma mensagem e pede de novo. |
| RNF08 | Tamanho dos arquivos | O log de passos é limitado a N ≤ 1.000 (cerca de 100 MB no pior caso). O visualizador Web aceita logs de até N = 100. |
| RNF09 | Acessibilidade | Os gráficos não podem depender só da cor para diferenciar estruturas; a estrutura aparece escrita no título de cada grupo. |
| RNF10 | Manutenibilidade | O código deve ser simples e didático: cada integrante precisa explicar o funcionamento interno na arguição oral. |
| RNF11 | Rastreabilidade | Todo prompt enviado a ferramentas de IA deve ser registrado no `AI_LOG.md`. |

<div style="page-break-after: always;"></div>

## 5. Arquitetura do sistema

### 5.1 Visão geral

O sistema tem duas aplicações independentes que se comunicam **por arquivos**. O programa em C produz os arquivos JSON na pasta `logs/`; a interface Web os lê pelo seletor de arquivos do navegador. Não há chamada direta entre as duas partes.

```
+--------------------------------------------------+
|              Programa em C (console)             |
|                                                  |
|   main.c  (menu, leitura das opcoes)             |
|     |                                            |
|     +--> vector / sort / singly, doubly e        |
|     |    circular_list   (estruturas e ordenacao)|
|     +--> benchmark       (vetor x listas)        |
|     +--> step_view + stack   (passo a passo,     |
|     |                         desfazer)          |
|     +--> queue           (testes em lote)        |
|     +--> export          (gravacao dos JSON)     |
|     |                                            |
|   metrics / memory  (medicoes, usados por todos) |
+-------------------------+------------------------+
                          |
                          |  grava
                          v
              +-----------------------+
              |      pasta logs/      |
              |  <algoritmo>_n<N>_... |
              |  comparativo_n<N>_... |
              +-----------+-----------+
                          |
                          |  usuario abre o arquivo
                          v
+--------------------------------------------------+
|           Interface Web (navegador)              |
|                                                  |
|   index.html + app.js        -> animacao         |
|   comparativo.html + .js     -> graficos         |
|   styles.css                 -> estilo comum     |
+--------------------------------------------------+
```

### 5.2 Camadas do programa em C

| Camada | Módulos | Responsabilidade |
|---|---|---|
| Apresentação | `main.c`, `step_view` | Menus, leitura das opções, impressão das tabelas e do modo passo a passo |
| Serviços | `benchmark`, `export`, `queue`, `stack` | Comparativo, gravação dos arquivos, lote de testes, histórico de Desfazer |
| Estruturas e algoritmos | `vector`, `sort`, `singly_list`, `doubly_list`, `circular_list`, `search` | Estruturas de dados e algoritmos de ordenação e busca |
| Infraestrutura | `metrics`, `memory` | Registro das métricas e contador de memória usado por todos os módulos |

Cada camada só usa as camadas abaixo dela. Os módulos de estruturas e algoritmos não fazem `printf` de menus nem gravam arquivos.

### 5.3 Padrão Observador nos algoritmos de ordenação

Um mesmo algoritmo de ordenação atende três usos diferentes: o *benchmark* (sem interrupções), o modo passo a passo (desenha a tela e espera o usuário) e a exportação (grava uma linha por passo). Para não ter três cópias de cada algoritmo, cada função de ordenação recebe um **ponteiro para função** (`StepObserver`, definido em `sort.h`) e o chama depois de cada comparação, troca ou escrita:

```
sort (ex.: bubble_sort)
   |
   |  a cada passo: observer->function(kind, i, j, ..., context)
   v
+-----------------+-----------------+-------------------+
| NULL            | step_view_show  | export_step       |
| (benchmark:     | (redesenha e    | (grava uma linha  |
|  ninguem olha)  |  empilha troca) |  no JSON)         |
+-----------------+-----------------+-------------------+
```

Quando o usuário pede o passo a passo **e** a exportação ao mesmo tempo, `main.c` usa uma função intermediária (`step_both`) que repassa o passo aos dois observadores. O algoritmo não sabe quem está observando: só recebe um ponteiro e um `void *context`.

### 5.4 Tabela de algoritmos

Os 7 algoritmos do vetor ficam numa tabela de ponteiros para função (`SortFunction`) em `sort.c`, acessada por índice com `sort_name(i)` e `sort_run(i, ...)`. Cada lista tem uma tabela igual com os seus 2 algoritmos. Assim o menu, o comparativo, o lote e a exportação percorrem a tabela em vez de repetir um bloco `case` por algoritmo, e um algoritmo novo entra em um só lugar.

### 5.5 Medição de memória

O C não informa o tamanho de um bloco alocado. Por isso todas as alocações do projeto passam por `mem_alloc`, `mem_realloc` e `mem_free` (`memory.h`), que chamam as funções da biblioteca padrão e somam ou subtraem os bytes de um contador global. Antes de cada algoritmo o programa zera o pico (`mem_reset_peak`) e, ao final, lê `mem_peak()`: a diferença é a memória extra do algoritmo. O mesmo contador detecta vazamentos: o comparativo vetor × listas imprime a memória que não foi liberada ao final.

### 5.6 Fluxo de uma ordenação com exportação

```
Usuario           main.c            sort.c            export.c        logs/
  | escolhe algoritmo |                 |                  |              |
  |------------------>|                 |                  |              |
  | "Exportar? Sim"   |                 |                  |              |
  |------------------>| export_open --------------------->| cria arquivo |
  |                   |                 |                  |------------->|
  |                   | sort_run_steps->|                  |              |
  |                   |                 | export_step ---->| grava passo  |
  |                   |                 | (a cada passo)   |------------->|
  |                   |<-- metricas ----|                  |              |
  |                   | export_close ---------------------->| final+metric|
  |<-- tabela e nome  |                 |                  |------------->|
  |    do arquivo     |                 |                  |              |
```

<div style="page-break-after: always;"></div>

## 6. Módulos do programa em C

Todos os arquivos ficam em `src/`. Cada módulo tem um `.h` (contrato público) e um `.c` (implementação).

| Módulo | Estrutura / função | Pontos principais |
|---|---|---|
| `memory` | Contador de memória | Envolve `malloc`, `realloc` e `free`; guarda memória atual e pico |
| `metrics` | `Metrics` (struct pública) | Nome, comparações, trocas, tempo (ms) e memória; impressão de relatório e tabela |
| `vector` | Vetor dinâmico de `int` | Criação, `realloc` para mudar o tamanho, preenchimento aleatório (embaralhamento de 1..N), ordenado e invertido |
| `sort` | 7 algoritmos do vetor | Tabela de ponteiros para função; notificação de passos (`StepObserver`); Merge Sort com vetores auxiliares em *heap*; Quick Sort com recursão no lado menor |
| `singly_list` | `SinglyList` (opaca): `head`, `size` | Nós com `value` e `next`; Insertion e Merge Sort religando `next` |
| `doubly_list` | `DoublyList` (opaca): `head`, `tail`, `size` | Nós com `prev` e `next`; regra de consistência `A->next == B` ⇒ `B->prev == A` |
| `circular_list` | `CircularList` (opaca): `tail`, `size` | O último nó aponta para o primeiro (`tail->next`); a ordenação abre o círculo, ordena e fecha de novo |
| `benchmark` | Comparativo vetor × listas | N = 1.000, 10.000 e 50.000; três tipos de dados; todos os algoritmos sobre os mesmos valores |
| `stack` | `Stack` (opaca), vetor dinâmico | `top` = próxima posição livre; cresce com `realloc`; guarda trocas e escritas; Desfazer e Refazer |
| `queue` | `Queue` (opaca), fila circular | `start` + `count` e índice `% capacity`; cada item é um `BatchTest` (algoritmo + tamanho) |
| `step_view` | Modo passo a passo | Barras horizontais no console; vetores com mais de 20 itens mostram só as linhas perto do passo |
| `export` | `Exporter` (opaco) | Grava o log de passos e o comparativo em JSON; nome do arquivo com data e hora, sem sobrescrever |
| `search` | Busca sequencial | Herdada do protótipo inicial |
| `main.c` | Cliente | Menu principal com 9 opções e submenus |

### 6.1 Menu principal

```
1 - Metodos de ordenacao
2 - Mostrar vetor
3 - Comparar todos os algoritmos
4 - Alterar tamanho do vetor
5 - Alterar tipo dos dados
6 - Ordenar listas encadeadas
7 - Comparativo vetor x listas (N = 1000, 10000 e 50000)
9 - Fila de testes em lote
8 - Encerrar programa
```

### 6.2 Custo de memória por estrutura

Valores medidos no compilador de referência (MinGW GCC 6.3.0, 32 bits, ponteiro de 4 bytes):

| Estrutura | Bytes por elemento | Memória extra do Merge Sort |
|---|---|---|
| Vetor | 4 (`int`) | N × 4 bytes (vetores auxiliares) |
| Lista simples | 8 (`int` + 1 ponteiro) | 0 (só religa ponteiros) |
| Lista dupla | 12 (`int` + 2 ponteiros) | 0 |
| Lista circular | 8 (`int` + 1 ponteiro) | 0 |

<div style="page-break-after: always;"></div>

## 7. Interface Web

Arquivos em `web/`, escritos em HTML, CSS e JavaScript puro, sem bibliotecas externas.

| Página | Arquivos | Função |
|---|---|---|
| Visualizador de ordenação | `index.html`, `app.js` | Abre um log de passos e anima as barras |
| Comparativo de métricas | `comparativo.html`, `comparativo.js` | Abre um comparativo e mostra gráfico e tabela |
| (comum) | `styles.css` | Estilo das duas páginas |

**Reprodução do log.** A página não recebe o vetor a cada passo. Ela parte do vetor `initial` e reaplica os passos em ordem: `swap` troca duas alturas, `write` muda a altura de uma barra e `compare` só destaca as barras. Ao final, o vetor reaplicado é comparado com o `final` do arquivo. Para voltar um passo, a página reconstrói o vetor a partir do `initial` até a posição anterior; com N ≤ 100 isso é instantâneo e evita guardar um histórico de "desfazer" no navegador.

**Velocidade.** Cinco posições, de 1 s a 16 ms por quadro. Na mais rápida, um log com mais de 1.800 passos junta vários passos por quadro, para a animação terminar em cerca de 30 s.

**Comparativo.** Botões escolhem a métrica (tempo, comparações, trocas ou memória extra). As barras ficam agrupadas por estrutura e na mesma escala, e a tabela destaca em negrito o menor valor de cada coluna. A página avisa que tempos abaixo de cerca de 10 ms aparecem como zero, por causa da resolução do `clock()` no Windows.

**Validação.** Cada página reconhece o seu tipo de arquivo. Se o usuário abrir um comparativo no visualizador (ou o contrário), a página indica a página correta. Arquivos com JSON inválido, passos com tipo desconhecido ou posições fora do vetor são rejeitados com uma mensagem.

<div style="page-break-after: always;"></div>

## 8. Formatos de troca de dados

### 8.1 Log de passos

Nome: `logs/<algoritmo>_n<N>_<AAAAMMDD>_<HHMMSS>.json`. Se já existir um arquivo com o mesmo nome, o programa acrescenta `_2`, `_3`, e assim por diante.

```json
{
  "algorithm": "Bubble Sort",
  "data_kind": "Aleatorio",
  "size": 5,
  "initial": [3, 1, 5, 2, 4],
  "steps": [
    {"type": "compare", "i": 0, "j": 1, "value_i": 3, "value_j": 1},
    {"type": "swap", "i": 0, "j": 1},
    {"type": "write", "i": 2, "j": -1, "value": 4}
  ],
  "final": [1, 2, 3, 4, 5],
  "metrics": {"comparisons": 10, "swaps": 4,
              "time_ms": 0.0, "memory_bytes": 0}
}
```

| Tipo de passo | Campos | Efeito na animação |
|---|---|---|
| `compare` | `i`, `j`, `value_i`, `value_j` | Destaca as barras; o vetor não muda |
| `swap` | `i`, `j` | Troca as alturas das barras `i` e `j` |
| `write` | `i`, `j`, `value` | A barra `i` recebe `value`; `j = -1` quando o valor veio de fora do vetor |

**Por que o limite de N ≤ 1.000.** O número de passos cresce com N². O Bubble Sort com N = 1.000 gera cerca de 1,2 milhão de passos (85 MB) com dados aleatórios; com N = 10.000 seriam cerca de 120 milhões de passos (9 GB), grandes demais para gravar e para o navegador abrir.

### 8.2 Comparativo de métricas

Nome: `logs/comparativo_n<N>_<AAAAMMDD>_<HHMMSS>.json`. Não tem limite de N, porque guarda só uma linha por algoritmo (13 no total: 7 do vetor e 2 de cada lista).

```json
{
  "report": "comparativo",
  "data_kind": "Aleatorio",
  "size": 10000,
  "results": [
    {"algorithm": "Bubble Sort", "structure": "Vetor",
     "comparisons": 98860113, "swaps": 25050577,
     "time_ms": 333.000, "memory_bytes": 0}
  ]
}
```

Os arquivos gerados não vão para o repositório (`.gitignore`). Dois exemplos ficam versionados em `logs/` para que a interface possa ser testada sem rodar o programa.

<div style="page-break-after: always;"></div>

## 9. Decisões de projeto

| # | Decisão | Alternativas consideradas | Motivo |
|---|---|---|---|
| D1 | Interface em HTML/CSS/JS puro | Java Swing/JavaFX; bibliotecas de gráficos | Abre direto no navegador, sem instalação; o código fica explicável na arguição |
| D2 | Exportar em JSON | CSV | Os passos têm campos diferentes por tipo; o JSON é lido nativamente pelo JavaScript |
| D3 | Gravar só os passos, não o vetor inteiro a cada passo | Um retrato do vetor por passo | Arquivo N vezes menor; a página reaplica os passos |
| D4 | Ponteiro para função (`StepObserver`) nos algoritmos | Uma cópia de cada algoritmo por modo | Um só algoritmo atende *benchmark*, passo a passo e exportação |
| D5 | Tabela de algoritmos | 7 blocos `case` repetidos (protótipo) | Menos código duplicado; um algoritmo novo entra em um só lugar |
| D6 | Contador próprio de memória (`memory.h`) | Ferramentas externas do sistema operacional | O C não informa o tamanho dos blocos; o contador mede o pico de cada algoritmo e detecta vazamentos |
| D7 | Quick Sort com recursão no lado menor | Aumentar a pilha do gcc; limitar N | Com dados ordenados e N = 50.000 a versão antiga estourava a pilha; a nova limita a profundidade a log₂ N sem mudar as contagens |
| D8 | Merge Sort com vetores auxiliares em *heap* | Vetores de tamanho variável (VLA) na pilha, como no protótipo | VLAs estouram a pilha com vetores grandes |
| D9 | Ordenação das listas só com ponteiros | Copiar para vetor, ordenar e copiar de volta | Exigência do enunciado; mostra a diferença real entre as estruturas |
| D10 | Pilha que guarda trocas e escritas, com Desfazer e Refazer | Pilha só de trocas | O Insertion e o Merge Sort alteram o vetor por escrita, não por troca |
| D11 | Textos do console sem acento | Configurar a página de código do console | O console do Windows estraga os acentos; a solução é a mesma em qualquer máquina |

<div style="page-break-after: always;"></div>

## 10. Controle de versão e fluxo de trabalho

### 10.1 Branches

| Branch | Papel |
|---|---|
| `main` | Produção: versão de entrega |
| `dev` | Integração: recebe o trabalho revisado dos integrantes |
| `ESDD/murilo`, `ESDD/lucas`, `ESDD/liliane` | Trabalho individual de cada integrante |

```
ESDD/<integrante>  --commits-->  Pull Request  --revisao-->  dev  --estavel-->  main
```

Regras combinadas pela equipe:

1. Ninguém commita direto em `main` ou `dev`.
2. Cada integrante trabalha na própria branch e abre um *Pull Request* para a `dev`.
3. O PR só é aceito depois da revisão de **outro** integrante. Os comentários da revisão são corrigidos na mesma branch, antes do *merge*.
4. Antes de começar uma tarefa, o integrante atualiza a própria branch com a `dev` (`git pull origin dev`).
5. A `dev` vai para a `main` quando estiver estável, para a entrega.

Mensagens de *commit* em inglês, no imperativo e citando a tarefa, por exemplo: `Add circular linked list with insertion and merge sort (T08)`.

### 10.2 Histórico de Pull Requests

| PR | Tarefa | Autor (branch) | Data do *merge* |
|---|---|---|---|
| #1 | T12 — fila circular para testes em lote | `ESDD/lucas` | 19/11/2026 |
| #2 | T26 + T10 — modo passo a passo e log JSON | `ESDD/liliane` | 21/11/2026 |
| #3 | Registro de prompts e atualização do quadro | `ESDD/murilo` | 23/11/2026 |
| #4 | T11 — Desfazer integrado ao passo a passo | `ESDD/lucas` | 24/11/2026 |
| #5 | T13 + T14 — visualizador Web dos logs | `ESDD/lucas` | 24/11/2026 |
| #6 | Registro de prompts das revisões | `ESDD/murilo` | 24/11/2026 |
| #7 | T15 — animação com cores distintas | `ESDD/liliane` | 24/11/2026 |
| #8 | T16 — controles de reprodução | `ESDD/liliane` | 24/11/2026 |
| #9 | T17 — exportação e página do comparativo | `ESDD/liliane` | 25/11/2026 |

As fases 1 e 2 (vetor, métricas e listas, tarefas T01 a T09 e T25) foram feitas antes da adoção dos *Pull Requests* e integradas diretamente na `dev`.

<div style="page-break-after: always;"></div>

## 11. Gestão das tarefas

As tarefas ficam num quadro com responsável, status e dependências, espelhado no arquivo `contexto/TAREFAS.md` do repositório. Uma tarefa só é marcada como concluída depois da revisão de outro integrante.

| Fase | Tarefas | Responsáveis | Situação em 25/11/2026 |
|---|---|---|---|
| 1. Vetor e métricas | T01–T05, T25: refatoração do protótipo em TADs, correção de *bugs*, medição de memória, tabela de algoritmos, dados ordenados e invertidos | Murilo | Concluída |
| 2. Listas | T06–T09: listas simples, dupla e circular com Insertion e Merge Sort; comparativo vetor × listas | Murilo | Concluída |
| 3. Pilha, fila e exportação | T26, T10, T11, T12: passo a passo, exportação JSON, pilha de Desfazer, fila de lote | Liliane, Lucas | Concluída |
| 4. Interface visual | T13–T17: decisão da interface, leitura do log, animação, controles, comparativo | Lucas, Liliane | Concluída (T17 em revisão) |
| 5. Extra: hash | T18–T19: tabela hash e busca de relatórios | — | Pendente |
| 6. Revisão | T20–T21: padrão da disciplina e `AI_LOG.md` | — | Pendente |
| 7. Testes e arguição | T22–T24: casos-limite, ensaio da arguição, entrega (02/12/2026) | — | Pendente |

### 11.1 Ponto de partida

O projeto começou de um protótipo feito à mão (menu de ordenação com métricas em vetor). A primeira tarefa foi refatorá-lo, corrigindo os problemas encontrados:

- Inclusão de arquivos `.c` em vez de `.h`, o que quebrava o padrão de TAD.
- Nomes e comentários em português (o enunciado exige inglês).
- `srand()` nunca chamado, gerando os mesmos números a cada execução.
- Preenchimento do vetor que gerava valores únicos e depois os sobrescrevia com repetidos.
- Vetores de tamanho variável no Merge Sort, com estouro de pilha em vetores grandes.
- Retorno de `malloc` sem conferência e sete blocos `case` duplicados.
- Ausência de medição de memória, listas, pilha, fila e exportação.

<div style="page-break-after: always;"></div>

## 12. Uso de IA generativa

O enunciado permite e incentiva o uso de IA, com três regras: registrar os prompts, refatorar o código gerado para o padrão da disciplina e explicar o código na arguição individual. A equipe atendeu às regras assim:

- **Registro automático.** Um *hook* (`.claude/hooks/log_prompt.py`) grava cada prompt no `AI_LOG.md` com número, data, autor e ferramenta, e remove dados pessoais como e-mails. Ao final de cada resposta, o assistente preenche o objetivo, o resumo da resposta e as adaptações feitas.
- **Ferramentas.** Cada integrante usou a ferramenta que preferiu (Claude Code, Codex ou Claude Web). As regras do projeto ficam num único arquivo (`CLAUDE.md`), lido por todas, para que o código gerado siga o mesmo padrão.
- **Contra a "caixa-preta".** As regras exigem o estilo dos exemplos das aulas (TAD em três arquivos, retorno 1/0, `if (p == NULL)` depois de cada `malloc`, `free` seguido de `p = NULL`). Todo código passou por revisão de outro integrante no *Pull Request*.
- **Memória das sessões.** Ao fim de cada sessão de trabalho, uma nota em `contexto/memory/` registra o que foi feito, as decisões e as pendências, o que também serve de material de estudo para a arguição.

<div style="page-break-after: always;"></div>

## 13. Como compilar e executar

**Requisitos:** Windows 10 ou 11, gcc (MinGW) no PATH e um navegador atual.

**Compilar** (a partir da raiz do projeto):

```
mkdir src\output
gcc -Wall -Wextra src/*.c -o src/output/main.exe
```

**Executar** (também a partir da raiz, para que a pasta `logs/` seja encontrada):

```
src\output\main.exe
```

O programa pede o tamanho do vetor e o tipo dos dados e abre o menu principal.

**Visualizar um log:**

1. No menu, escolha **1 - Metodos de ordenacao** e um algoritmo, e responda **Sim** em "Exportar log das comparacoes e trocas?" (N ≤ 1.000; para a animação, N ≤ 100).
2. Abra `web/index.html` no navegador.
3. Clique em **Abrir JSON** e selecione o arquivo criado em `logs/`.
4. Use **Reproduzir**, os botões de passo e a velocidade.

**Visualizar o comparativo:** escolha **3 - Comparar todos os algoritmos**, responda **Sim** em exportar e abra o arquivo `logs/comparativo_...json` em `web/comparativo.html` (link **Comparativo** no topo da página).

## 14. Limitações conhecidas e trabalhos futuros

- **Resolução do tempo.** O tempo é medido com `clock()`, que no Windows avança de cerca de 10 em 10 ms. Com N pequeno, quase todos os tempos aparecem como zero; para comparar tempos, recomenda-se N ≥ 10.000.
- **Tempo no modo passo a passo e na exportação.** Nesses modos o tempo inclui as pausas e a gravação do arquivo, por isso não serve para comparar algoritmos. Para isso, usa-se o comparativo.
- **Tamanho do log.** Exportação limitada a N ≤ 1.000 e animação a N ≤ 100 (seção 8.1).
- **Tabela Hash.** O extra do enunciado (RF25 e RF26) está planejado nas tarefas T18 e T19.
- **CSV.** Só a exportação em JSON foi implementada.
- **Testes automatizados.** Os testes foram manuais, com casos-limite (vetor de 1 elemento, dados ordenados e invertidos, arquivos inválidos na Web). A tarefa T22 prevê a revisão sistemática desses casos.
