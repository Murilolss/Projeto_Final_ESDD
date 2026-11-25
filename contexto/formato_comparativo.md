# Formato do comparativo de métricas (T17)

Arquivo escrito pelo programa em C na opção **3 - Comparar todos os algoritmos** do menu principal, quando o usuário responde `Sim` em "Exportar o comparativo para a interface Web?". A página [`web/comparativo.html`](../web/comparativo.html) lê esse arquivo e mostra um gráfico de barras por métrica e uma tabela com todas as métricas.

- Função: `export_report` em [`src/export.c`](../src/export.c) (protótipo em `src/export.h`).
- Arquivo: `logs/comparativo_n<N>_<AAAAMMDD>_<HHMMSS>.json`. Se já existir um arquivo com esse nome, o programa acrescenta `_2`, `_3`, ... (igual aos logs de passos).
- **Sem limite de tamanho:** o arquivo tem uma linha por algoritmo, qualquer que seja N. Diferente do log de passos ([formato_log.md](formato_log.md)), que só é exportado com N ≤ 1000.
- Exemplo versionado: [`logs/exemplo_comparativo_n10000.json`](../logs/exemplo_comparativo_n10000.json) (N = 10.000, dados aleatórios).

## Exemplo

```json
{
  "report": "comparativo",
  "data_kind": "Aleatorio",
  "size": 10000,
  "results": [
    {"algorithm": "Bubble Sort", "structure": "Vetor", "comparisons": 98860113, "swaps": 25050577, "time_ms": 333.000, "memory_bytes": 0},
    {"algorithm": "Merge Lista Simples", "structure": "Lista Simples", "comparisons": 120420, "swaps": 120420, "time_ms": 0.000, "memory_bytes": 0}
  ]
}
```

(Um arquivo real tem os 13 algoritmos: os 7 do vetor e os 2 de cada lista.)

## Campos

| Campo | Tipo | Significado |
|---|---|---|
| `report` | texto | sempre `"comparativo"`; a página usa isso para reconhecer o arquivo |
| `data_kind` | texto | `"Aleatorio"`, `"Ordenado"` ou `"Invertido"` |
| `size` | inteiro | número de elementos (N) |
| `results` | lista de objetos | um objeto por algoritmo, na ordem da tabela impressa no console |
| `results[].algorithm` | texto | nome do algoritmo, igual ao menu (ex.: `"Insertion Lista Dupla"`) |
| `results[].structure` | texto | `"Vetor"`, `"Lista Simples"`, `"Lista Dupla"` ou `"Lista Circular"` |
| `results[].comparisons` | inteiro | comparações entre elementos |
| `results[].swaps` | inteiro | trocas. Nas listas, nós religados em outra posição (nenhum valor é copiado) |
| `results[].time_ms` | número | tempo de execução em ms. Ao contrário do log de passos, **não** inclui gravação de arquivo |
| `results[].memory_bytes` | inteiro | pico de memória extra alocada pelo algoritmo, além do vetor ou da lista |

Observações:

- Todos os algoritmos ordenam os **mesmos** valores (o vetor do menu), então as métricas podem ser comparadas entre si.
- Um algoritmo que falha (falta de memória) não entra na lista.
- O tempo é medido com `clock()`. No Windows ele avança de cerca de 10 em 10 ms, então tempos pequenos aparecem como 0 (com N = 1000, quase todos ficam em 0). Para comparar tempos, use N = 10.000 ou mais. A página mostra esse aviso junto do gráfico de tempo.

## O que a página faz

- Um botão para cada métrica (tempo, comparações, trocas, memória extra) escolhe o que o gráfico mostra.
- As barras ficam agrupadas por estrutura (Vetor, Lista Simples, Lista Dupla e Lista Circular), todas na mesma escala, com o valor ao lado. Todas têm a mesma cor: a estrutura vem escrita no título do grupo, porque quatro cores não ficam distinguíveis para quem tem daltonismo (conferido com o validador de paletas).
- Passar o mouse sobre uma linha (ou focá-la com Tab) mostra as quatro métricas daquele algoritmo.
- A tabela abaixo do gráfico tem todas as métricas, com o menor valor de cada coluna em negrito.
- Se o arquivo for um log de passos, a página avisa para abri-lo na página **Animação**, e vice-versa.
