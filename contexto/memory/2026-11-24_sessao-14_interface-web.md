# Sessão 14 — 2026-11-24 — Interface Web e vetor inicial (T13 e T14)

- **Autor:** xXLucasCruzXx (Codex)
- **Prompts no AI_LOG:** #120, #122

## O que foi feito

- A T13 ficou definida como HTML, CSS e JavaScript puro. A decisão foi registrada no espelho das tarefas.
- O commit `50e8b78` adicionou a página da T14. O usuário abre o arquivo JSON localmente e o gráfico desenha os valores de `initial` na ordem original.
- Após o merge da T11, a decisão e a implementação foram trazidas para a `ESDD/lucas` a pedido do Lucas. O commit do visualizador nessa branch é `faffa97`.
- A prévia no navegador exibiu as dez barras do Bubble Sort com as alturas esperadas. O leitor também foi exercitado com JSON inválido e vetores de 1 e 1.000 elementos.

## Decisões / observações

- O JSON de exemplo continua em `logs/`. Quando a página é servida por HTTP, o link carrega esse arquivo diretamente. Ao abrir o HTML localmente, o mesmo arquivo pode ser selecionado com **Abrir JSON**.
- A T14 usa uma escala comum para todas as barras do vetor. A página mantém a última visualização válida se o usuário selecionar um arquivo inválido e mostra o erro de leitura junto ao gráfico.

## Pendências

- Publicação e revisão das alterações da T13 e da T14 após avaliação do Lucas.

## Próximos passos sugeridos

1. Depois da revisão, atualizar o status das duas tarefas no quadro e no espelho.
