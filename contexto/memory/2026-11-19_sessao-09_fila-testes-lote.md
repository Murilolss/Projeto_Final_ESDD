# Sessão 09 — 2026-11-19 — Fila de testes em lote e pilha de desfazer

- **Autor:** Lucas Cruz (Codex)
- **Prompts no AI_LOG:** #054–#060

## O que foi feito

- Leitura do guia e das tarefas do Lucas, seguida da implementação da T12 na branch local `ESDD/lucas`.
- Validação com GCC MinGW de 32 bits usando `-std=c99 -Wall -Wextra -Werror`. Os testes passaram pela fila cheia e vazia, pelo reaproveitamento das posições e pelo menu com os sete algoritmos.
- Foram injetadas falhas nas duas alocações da fila, nos dois vetores de um teste e nos dois buffers do Merge Sort. O lote continuou após falhas individuais e as execuções encerraram com zero bytes não liberados.
- O código foi commitado em `f5bc813` com a identidade fornecida pelo Lucas. Os registros foram commitados separadamente.
- O convite de escrita foi aceito e os commits da T12 foram publicados na branch `ESDD/lucas`.
- A T11 recebeu o TAD de pilha e a operação de desfazer em `afd76a5`. Foram testados o crescimento, a ordem LIFO, a restauração do vetor e falhas de alocação, com zero bytes não liberados. O teste do menu da T12 passou novamente.
- Os commits da T11 foram publicados na branch `ESDD/lucas` após autorização do Lucas.
- Em 23/11, os ajustes de revisão do PR #1 ficaram no commit `373907c`. O teste de limite aceitou N = 50.000 e rejeitou N = 50.001.
- A revisão da T26 reproduziu operandos incorretos na tela do Insertion e do Merge. A reaplicação de um log exportado de cada algoritmo manteve o resultado correto. A simulação de merge dos PRs integrou o `main.c` e encontrou conflito no `AI_LOG.md`.

## Decisões / observações

- A fila comporta dez testes. Cada item guarda o índice do algoritmo e o tamanho. O tipo de dados é o mesmo selecionado no menu principal, e os valores são gerados em vetores próprios para evitar alterar o vetor principal.
- A opção 9 abre o lote e a 8 continua encerrando o programa. Dentro do lote, voltar descarta os testes pendentes.
- O lote usa o maior tamanho do comparativo como limite por teste. A leitura usa `scanf` com largura máxima para proteger a conversão e rejeita texto extra na mesma linha. Os campos da fila e da pilha são `int`.
- Para integrar a T11, o chamador registra os índices antes de aplicar a troca. Se o registro falhar, o chamador pode interromper a operação com o histórico intacto. O desfazer valida os índices antes de consumir a entrada.
- A revisão do PR #2 propõe manter a notificação após o evento e usar uma cópia do vetor para recuperar o valor anterior de cada escrita. A T14 pode ler o JSON pelo seletor de arquivos. O tempo exportado inclui a gravação e as pausas, quando ativadas.

## Pendências

- Nova revisão do PR #1 após os ajustes.
- Alinhar com a Liliane os operandos exibidos nas comparações e a estratégia de Undo para escritas. Integrar o desfazer após a T26.
- Ao integrar os dois PRs, preservar os registros dos integrantes e renumerar as entradas em conflito no `AI_LOG.md`.

## Próximos passos sugeridos

1. Após a revisão, atualizar o quadro e o espelho de tarefas para refletir o status da T12.
2. Quando a T26 estiver disponível, ligar o histórico ao modo passo a passo e testar o desfazer pelo menu.
