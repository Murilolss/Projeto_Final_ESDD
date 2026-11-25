# Sessão 13 — 2026-11-24 — Integração do Desfazer (T11)

- **Autor:** xXLucasCruzXx (Codex)
- **Prompts no AI_LOG:** #116–#119, #121

## O que foi feito

- A `ESDD/lucas` local foi atualizada com a `dev`, que já continha a T26 e o TAD de pilha.
- O commit `ebc3a85` integrou o Desfazer ao modo passo a passo. Os testes verificaram o histórico vazio, vários comandos de desfazer e reaplicar e a conclusão do sort a partir de uma tela que tinha voltado no histórico.
- Bubble, Insertion e os dois Merge Sorts foram testados pelo menu. Os logs reproduziram o vetor final, e as execuções terminaram com zero bytes não liberados. O GCC MinGW de 32 bits compilou sem avisos.
- A integração foi publicada no PR #4 com solicitação de revisão da Liliane. O commit `9bf2dff` atende aos cinco apontamentos do Murilo.
- No teste com N = 50 e crescimento do histórico, o relatório e o JSON mostraram 0 bytes extras para Bubble Sort e 200 bytes para Merge Sort iterativo. Os testes também cobriram a separação do pico nos sete algoritmos e a retomada automática ao reaplicar a última alteração.

## Decisões / observações

- Como os eventos chegam após a troca ou escrita, uma cópia para a tela guarda os valores anteriores. O vetor que o algoritmo está ordenando segue separado durante a navegação. O JSON recebe apenas os eventos da ordenação.
- O pico de heap extra pertence ao algoritmo. Antes de chamar o observador, a medição guarda o pico do intervalo atual. Ao voltar, incorpora a diferença de memória do observador à base do próximo intervalo. Todas as alocações continuam no contador global.
- `top` aponta para a próxima posição livre e `cursor` guarda a posição atual da reprodução. Um evento inválido é ignorado. Quando a pilha não pode registrar as alterações, a ordenação continua com a tela do passo a passo.

## Pendências

- Nova revisão da integração da T11 no PR #4.

## Próximos passos sugeridos

1. Após a revisão e o merge, atualizar a T11 no quadro e no espelho de tarefas.
