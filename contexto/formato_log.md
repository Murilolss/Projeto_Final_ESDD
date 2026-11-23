# Formato do log de passos (T10 → T14)

Proposta da Liliane (T10, exportação) para o Lucas (T14, interface que desenha e anima as barras). **Status: implementado na T10 (`src/export.h` / `src/export.c`), aguardando o OK do Lucas.** Se algum nome de campo precisar mudar, avise a Liliane: a mudança no C é pequena.

## Resumo

- **JSON**, um arquivo por execução de um algoritmo de ordenação.
- O arquivo grava o vetor **inicial** e a lista de **passos** (comparação, troca e escrita). O vetor inteiro **não** é gravado a cada passo: a interface parte do `initial` e reaplica os passos em ordem.
- No fim vêm o vetor **final** (para conferir a reaplicação) e as **métricas**.
- Exportação só para vetores com **N ≤ 1000** (ver "Limite de tamanho").

## Exemplo

```json
{
  "algorithm": "Bubble Sort",
  "data_kind": "Aleatorio",
  "size": 5,
  "initial": [3, 1, 5, 2, 4],
  "steps": [
    {"type": "compare", "i": 0, "j": 1},
    {"type": "swap", "i": 0, "j": 1},
    {"type": "compare", "i": 1, "j": 2},
    {"type": "write", "i": 2, "j": -1, "value": 4}
  ],
  "final": [1, 2, 3, 4, 5],
  "metrics": {"comparisons": 10, "swaps": 4, "time_ms": 0.0, "memory_bytes": 0}
}
```

(Os passos acima são só ilustrativos; um arquivo real tem todos os passos da ordenação.)

## Campos

| Campo | Tipo | Significado |
|---|---|---|
| `algorithm` | texto | nome do algoritmo, igual ao menu (ex.: `"Merge Sort Recursivo"`) |
| `data_kind` | texto | `"Aleatorio"`, `"Ordenado"` ou `"Invertido"` |
| `size` | inteiro | número de elementos (N) |
| `initial` | lista de inteiros | vetor antes da ordenação (`size` valores, de 1 a N) |
| `steps` | lista de objetos | um objeto por passo, na ordem em que aconteceram |
| `final` | lista de inteiros | vetor depois da ordenação |
| `metrics.comparisons` | inteiro | total de comparações (igual ao relatório do programa) |
| `metrics.swaps` | inteiro | total de trocas (igual ao relatório do programa) |
| `metrics.time_ms` | número | tempo em ms. **Inclui a escrita do arquivo**, então não serve para comparar algoritmos |
| `metrics.memory_bytes` | inteiro | memória extra de heap usada pelo algoritmo |

### Passos (`steps`)

| `type` | Campos | O que a interface faz |
|---|---|---|
| `"compare"` | `i`, `j` | pinta as barras `i` e `j` com a cor de comparação; o vetor **não** muda |
| `"swap"` | `i`, `j` | troca as alturas das barras `i` e `j` |
| `"write"` | `i`, `j`, `value` | a barra `i` passa a ter a altura `value`. `j` é a posição de onde o valor veio, ou `-1` se veio de fora do vetor (a chave do Insertion Sort ou as metades temporárias do Merge Sort) |

Observações:

- Posições começam em 0.
- Um passo descreve o vetor **depois** que ele aconteceu (é o mesmo aviso do modo passo a passo, T26).
- Só o Insertion Sort e os dois Merge Sorts geram `write`. Bubble, Quick e Selection geram só `compare` e `swap`.
- No Merge Sort, um `compare` usa as posições que os dois valores tinham **antes** da intercalação (os valores estão nas metades temporárias). Durante a intercalação, o mesmo valor pode aparecer em duas barras: isso é o comportamento real do algoritmo.
- O Quick Sort com pivô no início pode gerar `swap` com `i == j` (troca de uma posição com ela mesma). A interface pode só ignorar.
- O número de `write` do Insertion Sort é um pouco maior que `metrics.swaps`, porque a colocação final da chave gera um passo mas não é contada como troca.

## Como reaplicar (pseudocódigo em JavaScript)

```js
const log = JSON.parse(texto);
const array = log.initial.slice();   // cópia do vetor inicial

for (const step of log.steps) {
  if (step.type === "swap") {
    const aux = array[step.i];
    array[step.i] = array[step.j];
    array[step.j] = aux;
  } else if (step.type === "write") {
    array[step.i] = step.value;
  }
  // "compare" não muda o vetor: só destaca as barras i e j
  desenhar(array, step);
}
// no fim, array deve ser igual a log.final
```

## Arquivo

- Pasta `logs/`, na raiz do projeto (rodar o programa a partir da raiz).
- Nome: `<algoritmo>_n<N>_<AAAAMMDD>_<HHMMSS>.json`, com o algoritmo em minúsculas e `_` no lugar de espaço. Exemplo: `logs/bubble_sort_n10_20261121_153000.json`.
- Cada execução cria um arquivo novo; nenhum log é sobrescrito. Se duas exportações caírem no mesmo segundo, a segunda ganha `_2` no fim do nome, a terceira `_3`, e assim por diante.
- Os `.json` gerados não vão para o GitHub (`.gitignore`). O arquivo de exemplo [`logs/exemplo_bubble_sort_n10.json`](../logs/exemplo_bubble_sort_n10.json) (Bubble Sort, N = 10, dados aleatórios) fica versionado para a T14 poder ser desenvolvida sem rodar o programa.

## Limite de tamanho (N ≤ 1000)

O número de passos cresce com o quadrado de N. O Bubble Sort gera o maior log: mesmo com dados aleatórios, ele faz por volta de N² comparações (cada passada compara o vetor inteiro, e são quase N passadas) mais umas N²/4 trocas. Com dados invertidos (o pior caso), são N² comparações e N²/2 trocas.

| N | passos, aleatório | arquivo, aleatório | passos, invertido | arquivo, invertido |
|---|---|---|---|---|
| 100 | 11 mil | 490 KB | 15 mil | 640 KB |
| 1.000 | 1,2 milhão | 55 MB | 1,5 milhão | 67 MB |
| 10.000 | 120 milhões | 5,8 GB | 150 milhões | 7 GB |
| 50.000 | 3,1 bilhões | ~150 GB | 3,7 bilhões | ~180 GB |

Os valores de N = 100 e 1.000 foram medidos em arquivos gravados pelo programa (média de 3 vetores aleatórios). Para N = 10.000, como o programa não exporta, o número de passos foi contado e o tamanho foi calculado com o mesmo formato de linha. Os valores de N = 50.000 são estimativas a partir dos de 10.000.

Acima de 1000 o arquivo fica grande demais para gravar e para o navegador abrir, e uma animação com milhões de passos não dá para assistir. Por isso o programa não oferece a exportação nesses casos e explica o motivo ao usuário.

## Pontos para o Lucas confirmar

1. Os nomes dos campos (`initial`, `steps`, `type`, `i`, `j`, `value`, `final`, `metrics`) servem para a T14?
2. A interface vai abrir o arquivo como? Escolhendo-o num `<input type="file">` ou de outro jeito? Isso muda só a forma de ler o arquivo, não o formato.
3. Falta alguma informação para a animação ou para a tela comparativa (T17)?
