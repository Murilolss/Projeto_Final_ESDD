---
name: atualizar-branch
description: Atualiza a branch de trabalho do integrante (ESDD/<integrante>) com a dev, rodando git pull origin dev, e envia o resultado ao GitHub. Use quando o usuário pedir para atualizar a branch ou puxar as novidades da dev.
disable-model-invocation: true
---

# Atualizar a branch com a dev

Traz para a branch `ESDD/<integrante>` o que o grupo já integrou na `dev`, inclusive entradas do `AI_LOG.md` e notas de `contexto/memory/`.

## Passos

1. **Conferir a branch:** execute `git branch --show-current`. Se o resultado não começar com `ESDD/`, pare e avise o usuário. Nunca rode esta skill em `dev` ou `main`.
2. **Atualizar:** execute `git pull --no-edit origin dev`.
3. **Se houver conflito ou erro:** pare e mostre ao usuário os arquivos afetados e a mensagem do Git. Não resolva o conflito, não descarte alterações nem aborte o merge sem o usuário pedir. Nesse caso, não faça o push.
4. **Enviar:** se o pull trouxe commits novos, execute `git push origin <branch atual>`. Se a branch já estava atualizada e não há commits locais pendentes (`git status -sb` sem `ahead`), pule o push.
5. **Responder em português do Brasil:** informe o commit atual (`git log -1 --format="%h %s"`) e o que chegou (commits e arquivos), ou diga que a branch já estava atualizada. Informe também se o push foi feito.

## Regras

- Esta skill não faz commit manual nem abre PR. O `git pull` pode criar sozinho um commit de merge na branch local.
- O push vai só para a própria `ESDD/<integrante>`, nunca para `dev` ou `main`, e nunca com `--force`.
