# Sessão 13 — 2026-11-24 — Integração do Desfazer (T11)

- **Autor:** xXLucasCruzXx (Codex)
- **Prompts no AI_LOG:** #116–#117

## O que foi feito

- A `ESDD/lucas` local foi atualizada com a `dev`, que já continha a T26 e o TAD de pilha.
- O commit `ebc3a85` integrou o Desfazer ao modo passo a passo. Os testes verificaram o histórico vazio, vários comandos de desfazer e reaplicar e a conclusão do sort a partir de uma tela que tinha voltado no histórico.
- Bubble, Insertion e os dois Merge Sorts foram testados pelo menu. Os logs reproduziram o vetor final, e as execuções terminaram com zero bytes não liberados. O GCC MinGW de 32 bits compilou sem avisos.

## Decisões / observações

- Como os eventos chegam após a troca ou escrita, uma cópia para a tela guarda os valores anteriores. O vetor que o algoritmo está ordenando segue separado durante a navegação. O JSON recebe apenas os eventos da ordenação.
- O pico de memória extra da execução passo a passo inclui eventuais realocações do histórico. Em caso de falha de alocação, a execução continua com a tela do passo a passo.

## Pendências

- Publicação e revisão da integração da T11.

## Próximos passos sugeridos

1. Após a revisão e o merge, atualizar a T11 no quadro e no espelho de tarefas.
