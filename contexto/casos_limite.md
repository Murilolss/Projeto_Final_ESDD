# Casos-limite testados (T22)

Teste feito em 25/11/2026 no Windows 11 com o MinGW de 32 bits (o mesmo da máquina de referência). O teste tem duas partes:

1. **Teste automático** dos TADs: [tests/edge_cases.c](../tests/edge_cases.c), com 590 verificações. Como compilar e rodar está no [PRIMEIROS_PASSOS.md](../PRIMEIROS_PASSOS.md), seção 5.4.
2. **Testes manuais** do menu e da interface Web, descritos nas tabelas abaixo. O menu foi testado com a entrada mandada por pipe (`printf "..." | ./src/output/main.exe`).

Resultado: um bug encontrado e corrigido (o tamanho do vetor estourava o `size_t`, ver abaixo). Todos os outros casos já eram tratados. Em todas as execuções o programa terminou com `Memoria nao liberada: 0 bytes`.

## Bug encontrado: tamanho do vetor muito grande

**Sintoma:** ao digitar `1100000000` (ou `99999999999`) como tamanho do vetor, o programa fechava sozinho (falha de segmentação).

**Causa:** o tamanho em bytes é `size * sizeof(int)`, calculado em `size_t`. No MinGW de 32 bits o `size_t` tem 4 bytes e vai até cerca de 4,29 bilhões. Com `size = 1100000000`, a conta dá 4,4 bilhões, passa do limite e "dá a volta" para cerca de 105 MB. O `malloc` consegue esse bloco menor, e o preenchimento escreve além do fim dele. Com `1073741825`, a conta vira só 4 bytes. Já `99999999999` nem cabe em `int`: o `scanf("%d")` com esse número tem comportamento indefinido (o MinGW devolve 1215752191).

**Correção:**
- [vector.h](../src/vector.h) define `VECTOR_MAX_SIZE = INT_MAX / sizeof(int)` (536.870.911). `vector_create` e `vector_resize` recusam tamanhos acima disso, então a conta em bytes nunca passa de `INT_MAX` e não dá a volta.
- No [main.c](../src/main.c), o tamanho do vetor (no início e em **Alterar tamanho**) é lido por `read_size`. Ela usa a mesma leitura rígida da fila em lote (`read_int`: no máximo 9 caracteres, sem texto sobrando na linha) e aceita só de 1 a `VECTOR_MAX_SIZE`.
- Efeito colateral: `12abc` agora é recusado, enquanto antes era lido como 12, igual ao que a fila em lote já fazia.

Com o código antigo, o teste automático acusa 3 falhas (`vector_create` e `vector_resize` com 1073741825 e 4 bytes não liberados).

## Teste automático (tests/edge_cases.c)

| Módulo | Casos |
|---|---|
| Vetor | tamanho 0, negativo, `VECTOR_MAX_SIZE + 1`, 1073741825 e `INT_MAX` recusados; vetor de 1 item; tipo de dados inválido não muda o vetor; resize para 0 ou acima do limite falha e mantém o vetor; resize para maior mantém o 1º valor; resize para menor; dados aleatórios são 1..N sem repetição; `destroy` duas vezes e com `NULL` |
| Busca sequencial | vetor `NULL`, vetor vazio, valor na 1ª posição, valor repetido, valor ausente, tamanho menor que o vetor |
| 7 ordenações do vetor | N = 1, 2, 3, 4, 5, 8, 16, 17, 100 e 1000, cada um com dados aleatórios, ordenados e invertidos; todos os valores iguais; só dois valores repetidos; `INT_MAX`, `INT_MIN`, 0 e negativos. Cada caso roda sem observador e com um observador que reaplica os passos (como a página Web faz com o log) e confere com o vetor ordenado. Também: `NULL`, índice fora da tabela, tamanho 0; contagens do melhor e do pior caso (Bubble, Insertion e Selection com N = 10); memória extra do Merge > 0 e do Bubble = 0 |
| Lista simples | lista vazia, 1 nó, argumentos inválidos, tamanho diferente em `to_array`; a lista continua válida depois do Merge; Insertion em dados invertidos faz 2(n-1) comparações e move n-1 nós; Merge sem memória extra; `clear` de lista vazia; `destroy` duas vezes |
| Lista dupla | lista vazia, 1 nó (`head == tail`); depois do Merge, o `tail` aponta para o último nó (`insert_back`) e os `prev` estão certos (o Insertion volta pelos `prev`); `to_array` com espaço menor que a lista é recusado |
| Lista circular | lista vazia, 1 nó (aponta para si mesmo); depois do Merge e do Insertion o círculo está fechado e o `tail` certo (`insert_back` liga o novo nó entre o último e o primeiro) |
| Pilha (desfazer) | capacidade 0 ou negativa; pilha vazia (desfazer, refazer e pop falham); a pilha cresce de 1 para 2; LIFO (a escrita é desfeita antes da troca); refazer até o fim; push depois de desfazer descarta o refazer; posição fora do vetor e argumentos `NULL` não mudam nada |
| Fila (lote) | capacidade 0 ou negativa; fila vazia; o exercício dos slides (capacidade 4: enqueue 10, 20, 30, dequeue, enqueue 40 e 50, com a volta à posição 0); enqueue na fila cheia falha; a ordem de saída é FIFO; `NULL` |
| Exportação | N acima de `EXPORT_MAX_SIZE` e N = 0 recusados; `NULL`; passo de tipo ou posição inválidos é ignorado; log de 3 itens gravado; comparativo sem resultados recusado e com 1 resultado gravado (o teste apaga os arquivos que cria) |
| Outros | `mem_alloc(0)`, `mem_free(NULL)`, nome de algoritmo com mais de 29 caracteres, `benchmark_size` inválido, `step_view_create` com argumentos inválidos, `step_view_show` com passo inválido |
| Vazamento | no fim, `mem_current() == 0` |

## Testes manuais do menu

| Caso | Entrada | Resultado |
|---|---|---|
| Tamanho 0, negativo, letras ou vazio | `0`, `-5`, `abc`, ENTER e fim da entrada | "Tamanho invalido", o programa termina sem alocar nada |
| Tamanho com texto sobrando | `12abc` | recusado (antes da correção era lido como 12) |
| Tamanho que estoura o `size_t` | `1100000000`, `1073741825`, `99999999999` | **travava (bug corrigido)**; agora é recusado com o limite na mensagem |
| Tamanho máximo | `536870911` (2 GB) | "Erro ao alocar memoria", sem travar |
| Tipo de dados inválido | `4`, `x` | "Tipo de dados invalido" |
| Opção inválida no menu | `x`, `123456` | "Opcao invalida!", volta ao menu |
| Fim da entrada em cada pergunta | menu, submenus, Sim/Nao, passo a passo, lote, Alterar tamanho | o programa encerra e libera tudo (os submenus foram corrigidos na T20) |
| Resposta Sim/Nao inválida | `x` | "Resposta invalida.", pergunta de novo |
| Alterar tamanho para 0, letras ou valor grande | `0`, `abc`, `1100000000` | "Tamanho invalido", o vetor não muda |
| Alterar tamanho para 1 | `1` | vetor `{1}` |
| N = 1 | Comparar todos os algoritmos | as 13 linhas com 0 comparações e 0 trocas |
| N = 1 e N = 2 | passo a passo + exportação | JSON válido (N = 1 sem passos; N = 2 do Merge com 3 passos) |
| Exportar no limite | N = 1000 invertido, Bubble Sort | 1.498.500 passos, 99 MB, JSON válido, cerca de 28 s |
| Exportar acima do limite | N = 1001 | explica o limite e ordena sem exportar |
| Passo a passo: desfazer e refazer | Insertion invertido, `u` várias vezes e ENTER | desfaz até não haver mais alterações e reaplica; a saída é idêntica à de antes da T20 |
| Fila cheia | 11 testes com capacidade 10 | "A fila esta cheia", o 11º não entra; os 10 rodam |
| Fila vazia | `0` sem testes | "A fila esta vazia." |
| Algoritmo inválido no lote | `8`, `-2`, `abc`, `1x` | "Opcao invalida." nos quatro |
| Tamanho inválido no lote | `0`, `50001`, `1234567890`, `5 5` | "Tamanho invalido" nos quatro |
| Tamanho máximo no lote | `50000` | roda (Insertion Sort, cerca de 627 milhões de comparações) |

## Testes da interface Web

As funções de leitura (`parseLog` em [web/app.js](../web/app.js) e `parseReport` em [web/comparativo.js](../web/comparativo.js)) foram chamadas com Node.js e um `document` falso. Todos os arquivos inválidos foram recusados com a mensagem certa, e a última visualização válida continua na tela.

| Página | Aceita | Recusa |
|---|---|---|
| Animação | log válido; N = 1 sem passos; arquivo com BOM; N = 100 (limite); `write` com `j = -1` | arquivo vazio; texto que não é JSON; JSON cortado; `null`, número e lista; `size` 0, 2.5 ou diferente de `initial`; `final` curto; valor 0, negativo ou texto; N = 101; passo de tipo desconhecido, posição fora do vetor, `j = -2`, `value` 0 ou `null`; um comparativo (manda abrir na página Comparativo) |
| Comparativo | o exemplo; todas as métricas 0 (avisa que todos os valores são 0) | arquivo vazio; `results` vazio; métrica negativa ou texto; resultado sem `structure`; um log de passos (manda abrir na página Animação) |

Com um log de N = 1 (0 passos), **Reproduzir** vai direto para o fim e as barras ficam verdes, porque o vetor bate com o `final`.

## O que não foi testado

- O comparativo vetor × listas (opção 7) com N = 50000 completo: leva minutos e foi medido na T09.
- O passo a passo em vetores grandes além de N = 30: a tela só mostra as posições perto do passo, e o `f` vai até o fim.
- A falta de memória no meio de uma ordenação (Merge Sort) só foi forçada pelo tamanho máximo do vetor, não por um `malloc` que falha no meio.
