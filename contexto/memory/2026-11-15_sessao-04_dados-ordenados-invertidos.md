# Sessão 04 — 2026-11-15 — Dados ordenados e invertidos (T25)
<!-- session: 98683b70-a142-4454-a89f-4f8f31b359b1 -->

- **Autor:** Murilo Leandro
- **Prompts no AI_LOG:** #028–#033

## O que foi feito
- T25 implementada, primeiro como plano aprovado pelo usuário e depois em código. O vetor pode ser aleatório, ordenado (1..N) ou invertido (N..1): `vector_fill(v, size, kind)` com `FILL_RANDOM/FILL_SORTED/FILL_REVERSED` e `vector_fill_name` em `src/vector.h/.c`.
- `src/main.c`: o tipo é perguntado depois do tamanho, a opção 5 "Alterar tipo dos dados" é nova (Encerrar virou 6) e o cabeçalho do menu mostra o tipo. "Alterar tamanho" mantém o tipo atual.
- `src/metrics.h/.c`: `metrics_print` e `metrics_print_table` recebem o nome do tipo e mostram "Dados: X".
- `src/sort.c`: os dois Quick Sorts recursam só na parte menor e tratam a maior com um `while`.
- `contexto/slides/Testes de algoritmos de ordenação.md`: o item "ordenados e invertidos" passou a "Feito".
- Teste temporário (no scratchpad, fora do repositório): N de 1 a 50.000 nos 3 tipos, tudo ordena e não sobra memória. As contagens do Quick Sort são idênticas às da versão anterior nos 117 casos. Também rodei o menu de verdade com entrada automática.
- A T25 foi commitada e enviada: commit `3ea8ce3` na `ESDD/murilo`.
- Skill nova `/atualizar-branch` em `.claude/skills/atualizar-branch/SKILL.md`: roda `git pull --no-edit origin dev` na `ESDD/<integrante>` e depois o push dessa branch. Está citada no `CLAUDE.md` (commit `9812b4d`, enviado).

## Decisões / observações
- Armadilha: com dados ordenados ou invertidos, o pivô do Quick Sort cai sempre numa ponta e a recursão desce N níveis. A versão antiga com N = 50.000 fechava sem mensagem, com o código `C00000FD` (estouro de pilha no MinGW). O usuário escolheu a recursão no lado menor, que limita a profundidade a log2(n), em vez de aumentar a pilha no gcc, limitar N ou só documentar. As partições não mudaram, por isso as contagens continuam iguais. Bom tema para a arguição.
- Decisão de menu (do usuário): perguntar o tipo no início e também oferecer a opção no menu, em vez de perguntar a cada ordenação.
- O módulo `metrics` recebe o nome do tipo como `const char *` para não depender do `vector.h`.
- Tempos com N = 50.000: Quick Sort com dados ordenados leva ~12 s e com invertidos ~9 s (pior caso O(n²)). Com dados aleatórios, ~15 ms.
- O compilador instalado é MinGW.org GCC 6.3.0, de 32 bits.
- `/atualizar-branch`: o usuário preferiu copiar a skill do projeto de INOO (`Projeto_Final_INOO/.claude/skills/`) em vez de escrever uma do zero. Lá também há `documento` e `sincronizar-quadro`, que podem ser reaproveitadas. Na adaptação, o prefixo `logitech/` virou `ESDD/`. O push automático foi escolha do usuário (a original não fazia push), mas fica limitado à própria branch e nunca usa `--force`. Se houver conflito, a skill para sem fazer o push.

## Pendências
- `/atualizar-branch` ainda não foi testada de verdade (a `dev` não tinha novidades). Talvez seja preciso reiniciar a sessão para ela aparecer.
- `src/output/main.exe` não foi recompilado: estava aberto (travado). Recompilar com `gcc -Wall -Wextra src/*.c -o src/output/main.exe` depois de fechar o programa.
- Marcar a T25 no plano só depois da revisão de outro integrante.
- Continuam as pendências das sessões anteriores: PR `ESDD/murilo` → `dev`, branches dos outros integrantes, o hook `log_prompt.py` ainda grava `<browser_instruction>` e `<ide_opened_file>` no AI_LOG, e o `README.md` está vazio.

## Próximos passos sugeridos
1. Abrir o PR `ESDD/murilo` → `dev` (T02–T05 e T25) e pedir a revisão de outro integrante.
2. Os outros integrantes criam suas `ESDD/<integrante>` e usam `/atualizar-branch` depois de cada merge na `dev`.
3. Na T09, avisar antes dos O(n²) com N grande, incluindo o Quick Sort com dados ordenados ou invertidos.
4. Começar a T06 (lista simplesmente encadeada) usando `mem_alloc`/`mem_free`, já com os três tipos de dados.
