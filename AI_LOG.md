# AI_LOG — Registro de uso de Inteligência Artificial

Registro exigido pelo enunciado do Projeto Final de ESDD (seção "Diretrizes para Uso de Inteligência Artificial"): os prompts utilizados e **como as respostas da IA foram adaptadas ou corrigidas**.

- **Ferramenta:** Claude Code (Anthropic)
- **Formato:** uma entrada por prompt, em ordem cronológica, numeração sequencial, sem apagar entradas antigas.

---

## #001 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > Olá claude, esse é o projeto de ESDD, projeto de estrutura de dados na linguagem C, alise as pastas e tenha o contexto do projeto
  >
  > .claude: Pasta desdicada para skills/pluguins
  > contexto: Pasta para contexto do projeto
  > contexto/codigos-exemplos: Todos os codigos de exemplos utilizados em aula(provavelmente serão reutilizados no projeto do enunciado)
  > contexto/memory: Pasta para salvar a memoria de cada sessao
  > contexto/pdfs: Aqui estão todos os slides das aulas para você se basear no que o professor pede, tem tambem o enunciado do projeto
  > contexto/projeto-exemplo: Pasta onde tem meio que um projeto final feito a mão, quase sem uso da IA
  > contexto/slides: Aqui para cada pdf da pasta contexto/pdfs você vai criar um .md do pdf para as consultas futuras
  > CLAUDE.md: aqui é a configuração do claude para esse projeto
  > README.md: um readme com a descrição do projeto
- **Objetivo:** dar à IA o contexto da disciplina e do enunciado e converter os slides em Markdown para consultas futuras.
- **Resposta da IA (resumo):** leu os 14 PDFs, os códigos das aulas e o `projeto-exemplo`. Criou um `.md` por PDF em `contexto/slides/`, preencheu o `CLAUDE.md` (requisitos, padrões da disciplina, diagnóstico do `projeto-exemplo`) e registrou a sessão em `contexto/memory/`.
- **Adaptações / correções:** nenhum código de produção gerado. A transcrição do código que aparece como imagem nos slides foi conferida com os arquivos de `contexto/codigo-exemplos/`. Bugs dos exemplos de aula foram apontados em vez de copiados.

## #002 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > crie o AI_LOG.md para registrar todos os meus prompts, para cada prompts coloque o dia e a data, deixe isso anotado no claude,md assim todo mundo que mexer no projeto já vai fazer automaticamente
- **Objetivo:** criar o arquivo de registro exigido pelo enunciado e padronizar o registro para toda a equipe.
- **Resposta da IA (resumo):** criou este `AI_LOG.md` com o modelo de entrada, registrou retroativamente o prompt #001 e adicionou ao `CLAUDE.md` a regra de registrar todo prompt automaticamente.
- **Adaptações / correções:** nenhuma até o momento.

## #003 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > sim, configura o hook
- **Objetivo:** tornar o registro de prompts automático, sem depender do Claude lembrar da regra.
- **Resposta da IA (resumo):** criou `.claude/hooks/log_prompt.py` (cria a entrada numerada com dia da semana, data, autor via `git config user.name` e prompt literal; troca e-mails por `[removido]`) e `.claude/settings.json` com o hook `UserPromptSubmit` que o executa. Atualizou a regra no `CLAUDE.md`: o hook cria a entrada e o Claude preenche objetivo, resumo e adaptações. Esta entrada #003 foi gerada pelo próprio script durante o teste.
- **Adaptações / correções:** a IA usou Python em vez de `jq` (não instalado na máquina) e incluiu tentativas com `python`, `python3` e `py` para funcionar nos computadores dos outros integrantes.

## #004 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > crie um artefato parecido com esse para sabermos oq precisa fazer e a questão de tempo data de entrega pode ser dia 02/12 mas se fosse possivel terminar antes seria bom
- **Objetivo:** ter um plano visual com tudo o que precisa ser feito e um cronograma até a entrega (02/12/2026), tentando terminar antes.
- **Resposta da IA (resumo):** publicou um artefato no claude.ai, o "Plano Projeto ESDD". Ele tem 8 fases e 28 tarefas tiradas do enunciado e do diagnóstico do `projeto-exemplo`, um cronograma dia a dia de 15/11 a 02/12 e a meta interna de code freeze em 29/11, com 30/11–01/12 de folga para testes e para ensaiar a arguição. As marcações de "concluída" e o responsável de cada tarefa ficam salvos e são compartilhados com quem abrir a página. Nenhum arquivo do repositório mudou além deste log.
- **Adaptações / correções:** o prompt dizia "parecido com esse", mas nenhuma referência foi anexada, então a IA montou o formato por conta própria. As datas das fases são uma sugestão e a equipe deve ajustá-las na divisão de tarefas. Na entrada #005 a equipe pediu para tirar as tarefas de Engenharia de Software e de Inglês, deixar a tecnologia da interface em aberto e numerar as tarefas.

## #005 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > pode tirar a parte de engenharia de software, inglês e front vamos deixar em aberto, fiquei com duvida se era para escolher um ou todos e enumera cada tarefa ex: T01
- **Objetivo:** enxugar o plano: tirar Engenharia de Software e Inglês, deixar em aberto se a interface será Web ou Java, numerar as tarefas (T01, T02…) e esclarecer se a "Integração Interdisciplinar" é para escolher um item ou fazer todos.
- **Resposta da IA (resumo):** a nova versão do artefato "Plano Projeto ESDD" ficou com 7 fases e 24 tarefas, numeradas de T01 a T24. Saíram as tarefas de repositório no GitHub, requisitos funcionais, documentação de arquitetura e README em inglês. A definição do formato do log passou para a tarefa de exportação (T10). A fase de interface virou "Interface visual", com a tecnologia em aberto, e a primeira tarefa dela (T13) é escolher entre Web e Java. A IA releu o `Enunciado.pdf` e explicou que só o Java aparece como "alternativa à interface Web". Engenharia de Software e Inglês estão na mesma lista sem nada que diga que são opcionais.
- **Adaptações / correções:** as tarefas foram removidas a pedido da equipe, mesmo o enunciado parecendo exigir esses itens. Foi sugerido confirmar com o professor.

## #006 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > vou confirmar com o professor sobre Integração Interdisciplinar
- **Objetivo:** avisar que a equipe vai confirmar com o professor se os itens da "Integração Interdisciplinar" são todos obrigatórios.
- **Resposta da IA (resumo):** registrou a pendência na nota da sessão em `contexto/memory/` e sugeriu uma pergunta curta para o professor. O plano não mudou.
- **Adaptações / correções:** nenhuma.

## #007 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > crie a skill /salvar-memoria para que cada vez que eu rodar ele, ele salve a memoria da sessao que eu estou
- **Objetivo:** ter um comando que grave a memória da sessão atual em `contexto/memory/` sempre que for executado.
- **Resposta da IA (resumo):** criou a skill `.claude/skills/salvar-memoria/SKILL.md`, que só roda quando o usuário digita `/salvar-memoria`, com um título opcional. A nota leva um marcador com o ID da sessão. Se a nota da sessão já existir, a skill a atualiza em vez de criar outra. A nota tem seções fixas: o que foi feito, decisões, pendências e próximos passos. Também acrescentou o marcador desta sessão à nota `2026-11-15_sessao-01_contexto-inicial.md` e atualizou a tabela de pastas no `CLAUDE.md`.
- **Adaptações / correções:** nenhuma até o momento.

## #008 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > /salvar-memoria
- **Objetivo:** salvar a memória desta sessão com a skill `/salvar-memoria`.
- **Resposta da IA (resumo):** atualizou a nota existente `contexto/memory/2026-11-15_sessao-01_contexto-inicial.md`, que já tinha o marcador desta sessão, para o formato da skill. A nota agora traz o autor, a faixa de prompts #001–#008, o que foi feito, as decisões, as pendências (confirmação com o professor, compartilhar o plano, README vazio) e os próximos passos (T01–T05).
- **Adaptações / correções:** nenhuma.

## #009 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > faz o commit de tudo isso
- **Objetivo:** versionar no git tudo o que foi feito na sessão.
- **Resposta da IA (resumo):** fez o primeiro commit do repositório, na branch `master`, com todos os arquivos: `CLAUDE.md`, `AI_LOG.md`, `README.md` (ainda vazio), o hook e a skill em `.claude/`, e a pasta `contexto/` (PDFs, slides em `.md`, códigos das aulas, `projeto-exemplo` e a nota de memória). O repositório não tem remote, então nada foi enviado ao GitHub.
- **Adaptações / correções:** nenhuma.

---

<!--
MODELO DE ENTRADA (copiar abaixo da última entrada, incrementando o número):

## #NNN — <Dia da semana>, DD/MM/AAAA

- **Autor:** <nome do integrante — `git config user.name`>
- **Prompt:**
  > <texto do prompt, literal>
- **Objetivo:** <o que se queria obter>
- **Resposta da IA (resumo):** <o que a IA fez/gerou, arquivos afetados>
- **Adaptações / correções:** <o que a equipe mudou, corrigiu ou rejeitou e por quê>
-->
