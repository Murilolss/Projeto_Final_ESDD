# Sessão 09 — 2026-11-19 — Fila de testes em lote (T12)

- **Autor:** Lucas Cruz (Codex)
- **Prompts no AI_LOG:** #054–#056

## O que foi feito

- Leitura do guia e das tarefas do Lucas, seguida da implementação da T12 na branch local `ESDD/lucas`.
- Validação com GCC MinGW de 32 bits usando `-std=c99 -Wall -Wextra -Werror`. Os testes passaram pela fila cheia e vazia, pelo reaproveitamento das posições e pelo menu com os sete algoritmos.
- Foram injetadas falhas nas duas alocações da fila, nos dois vetores de um teste e nos dois buffers do Merge Sort. O lote continuou após falhas individuais e as execuções encerraram com zero bytes não liberados.
- O código foi commitado em `f5bc813` com a identidade fornecida pelo Lucas. Os registros foram commitados separadamente.

## Decisões / observações

- A fila comporta dez testes. Cada item guarda o índice do algoritmo e o tamanho. O tipo de dados é o mesmo selecionado no menu principal, e os valores são gerados em vetores próprios para evitar alterar o vetor principal.
- A opção 9 abre o lote e a 8 continua encerrando o programa. Dentro do lote, voltar descarta os testes pendentes.
- O tamanho é validado antes da inserção. O limite de `INT_MAX / 2` protege a aritmética de índices do Merge Sort iterativo.

## Pendências

- Publicar a branch do Lucas e submeter a T12 à revisão de outro integrante.

## Próximos passos sugeridos

1. Após a revisão, atualizar o quadro e o espelho de tarefas para refletir o status da T12.
