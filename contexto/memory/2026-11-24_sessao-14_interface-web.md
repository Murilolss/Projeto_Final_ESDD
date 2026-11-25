# Sessão 14 — 2026-11-24 — Interface Web e vetor inicial (T13 e T14)

- **Autor:** xXLucasCruzXx (Codex)
- **Prompts no AI_LOG:** #120, #122, #159–#161

## O que foi feito

- A T13 ficou definida como HTML, CSS e JavaScript puro. A decisão foi registrada no espelho das tarefas.
- O commit `50e8b78` citado na entrada #120 foi criado na branch local `ESDD/lucas-t14`. No GitHub, a página da T14 entrou como `faffa97` na `ESDD/lucas` e foi integrada à `dev` no PR #5.
- O Murilo corrigiu a largura das barras no modo denso em `613a30e`. O seletor nativo também foi verificado na revisão com logs reais do programa em C.
- A prévia no navegador exibiu as dez barras do Bubble Sort com as alturas esperadas. O leitor também foi exercitado com JSON inválido e vetores de 1 e 1.000 elementos.
- A T13 e a T14 foram integradas pelo PR #5 e constam como concluídas no espelho de tarefas.

## Decisões / observações

- O JSON de exemplo continua em `logs/`. Quando a página é servida por HTTP, o link carrega esse arquivo diretamente. Ao abrir o HTML localmente, o mesmo arquivo pode ser selecionado com **Abrir JSON**.
- A T14 usa uma escala comum para todas as barras do vetor. A página mantém a última visualização válida se o usuário selecionar um arquivo inválido e mostra o erro de leitura junto ao gráfico.

## Pendências

- Confirmar se o quadro do projeto registra os mesmos status do espelho.

## Próximos passos sugeridos

1. Usar a interface integrada à `dev` para os testes finais do projeto.
