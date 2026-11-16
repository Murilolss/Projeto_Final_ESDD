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

## #010 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > <browser_instruction># Claude in Chrome browser automation
  >
  > You have access to browser automation tools (mcp__claude-in-chrome__*) for interacting with web pages in Chrome. Follow these guidelines for effective browser automation.
  >
  > ## Loading deferred tools
  >
  > If the mcp__claude-in-chrome__* tools are deferred (must be loaded via ToolSearch before use), load every tool you expect to need in ONE ToolSearch call — the select query accepts a comma-separated list — never one call per tool. Start with the core set:
  >
  > ToolSearch with query "select:mcp__claude-in-chrome__tabs_context_mcp,mcp__claude-in-chrome__navigate,mcp__claude-in-chrome__computer,mcp__claude-in-chrome__read_page,mcp__claude-in-chrome__tabs_create_mcp,mcp__claude-in-chrome__tabs_close_mcp"
  >
  > Add task-specific tools to the same call when the task obviously needs them: read_console_messages / read_network_requests for debugging, form_input for forms, gif_creator for recordings, javascript_tool for page scripting.
  >
  > ## GIF recording
  >
  > When performing multi-step browser interactions that the user may want to review or share, use mcp__claude-in-chrome__gif_creator to record them.
  >
  > You must ALWAYS:
  > * Capture extra frames before and after taking actions to ensure smooth playback
  > * Name the file meaningfully to help the user identify it later (e.g., "login_process.gif")
  >
  > ## Console log debugging
  >
  > You can use mcp__claude-in-chrome__read_console_messages to read console output. Console output may be verbose. If you are looking for specific log entries, use the 'pattern' parameter with a regex-compatible pattern. This filters results efficiently and avoids overwhelming output. For example, use pattern: "[MyApp]" to filter for application-specific logs rather than reading all console output.
  >
  > ## Alerts and dialogs
  >
  > IMPORTANT: Do not trigger JavaScript alerts, confirms, prompts, or browser modal dialogs through your actions. These browser dialogs block all further browser events and will prevent the extension from receiving any subsequent commands. Instead, when possible, use console.log for debugging and then use the mcp__claude-in-chrome__read_console_messages tool to read those log messages. If a page has dialog-triggering elements:
  > 1. Avoid clicking buttons or links that may trigger alerts (e.g., "Delete" buttons with confirmation dialogs)
  > 2. If you must interact with such elements, warn the user first that this may interrupt the session
  > 3. Use mcp__claude-in-chrome__javascript_tool to check for and dismiss any existing dialogs before proceeding
  >
  > If you accidentally trigger a dialog and lose responsiveness, inform the user they need to manually dismiss it in the browser.
  >
  > ## Avoid rabbit holes and loops
  >
  > When using browser automation tools, stay focused on the specific task. If you encounter any of the following, stop and ask the user for guidance:
  > - Unexpected complexity or tangential browser exploration
  > - Browser tool calls failing or returning errors after 2-3 attempts
  > - No response from the browser extension
  > - Page elements not responding to clicks or input
  > - Pages not loading or timing out
  > - Unable to complete the browser task despite multiple approaches
  >
  > Explain what you attempted, what went wrong, and ask how the user would like to proceed. Do not keep retrying the same failing browser action or explore unrelated pages without checking in first.
  >
  > ## Tab context and session startup
  >
  > IMPORTANT: At the start of each browser automation session, call mcp__claude-in-chrome__tabs_context_mcp first to get information about the user's current browser tabs. Use this context to understand what the user might want to work with before creating new tabs.
  >
  > Never reuse tab IDs from a previous/other session. Follow these guidelines:
  > 1. Only reuse an existing tab if the user explicitly asks to work with it
  > 2. Otherwise, create a new tab with mcp__claude-in-chrome__tabs_create_mcp
  > 3. If a tool returns an error indicating the tab doesn't exist or is invalid, call tabs_context_mcp to get fresh tab IDs
  > 4. When a tab is closed by the user or a navigation error occurs, call tabs_context_mcp to see what tabs are available</browser_instruction>
  > Vamos fazer a T05, me explica o plano
- **Objetivo:** fazer a T05 do plano: trocar os 7 blocos `case` duplicados do menu de ordenação, e o bloco repetido 7 vezes na tela de métricas, por uma tabela de algoritmos (vetor de structs com nome e ponteiro para função).
- **Resposta da IA (resumo):** a T05 depende da T02, porque `sort.c` e `main.c` ainda não existiam. A IA perguntou o escopo e a equipe escolheu fazer T02 + T05 juntas. A IA criou a pasta `src/` em inglês a partir do `projeto-exemplo`: `metrics.h/.c`, `search.h/.c`, `vector.h/.c`, `sort.h/.c` e `main.c`, sem nenhum `#include "*.c"`. Em `sort.c`, a tabela `static const SortAlgorithm algorithms[SORT_COUNT]` guarda o nome e a função de cada algoritmo. `sort_run()` copia o vetor, inicia as métricas, mede o tempo e chama o algoritmo (retorna 1/0), e `sort_name()` devolve o nome para o menu. No `main.c`, o menu é gerado por um `for` sobre a tabela e a comparação geral virou um único laço. A opção "Exit" do submenu agora volta ao `main` e libera o vetor, em vez de chamar `exit(0)`. A IA também criou o `.gitignore` (`*.exe`, `*.o`). Testes: compila com `gcc -Wall -Wextra` sem warnings, os 7 algoritmos ordenam corretamente, opções inválidas são rejeitadas e comparações e trocas ficam idênticas às do protótipo com N = 10 e N = 1000.
- **Adaptações / correções:** os bugs da T03 não foram corrigidos, só marcados com `TODO(T03)` no código (srand, VLAs do merge, leitura fora do vetor em `sequential_search`, duplicatas). A IA também achou um bug que não estava na lista: com N > 2048, `vector_fill_random` entra em laço infinito (só existem 2048 valores únicos). Ponteiro para função não aparece no material das aulas, por isso `sort.h` tem um comentário explicando o `typedef` e o assunto fica para a equipe estudar antes da arguição. O hook registrou por engano, nesta entrada, um bloco `<browser_instruction>` que a extensão do navegador acrescenta ao prompt. O bloco não foi apagado e a correção do `log_prompt.py` ficou pendente. Na #011 a equipe pediu que os textos exibidos ao usuário (`printf`) fiquem em português, e não em inglês como a IA tinha feito.

## #011 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > <ide_opened_file>The user opened the file c:\Users\Admin\Documents\IFSP\Professores\2_Semestre\ESDD_Estrutura_de_Dados\Eduardo_Leal\Projeto_Final_ESDD\src\main.c in the IDE. This may or may not be related to the current task.</ide_opened_file>
  > os printf pode ser em portugues mesmo
- **Objetivo:** deixar em português os textos que o programa mostra ao usuário, mantendo o código (identificadores e comentários) em inglês.
- **Resposta da IA (resumo):** traduziu para português sem acento todos os `printf` de `src/main.c` e `src/metrics.c` (menus, mensagens de erro, relatório e tabela de métricas) e os nomes dos algoritmos na tabela de `src/sort.c` ("Merge Sort Iterativo", "Quick Sort Pivo Inicio" etc.). Registrou a regra no `CLAUDE.md` (textos ao usuário em português sem acento; código em inglês). Recompilou com `-Wall -Wextra` sem warnings e testou os menus.
- **Adaptações / correções:** a equipe corrigiu a resposta da #010, em que a IA tinha colocado também os textos da interface em inglês. A IA tirou os acentos por conta própria, seguindo o protótipo, porque o console do Windows costuma exibi-los errado. Este prompt também foi registrado com um bloco `<ide_opened_file>` que a extensão do VS Code acrescenta, o mesmo problema do hook citado na #010.

## #012 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > faz o commit de tudo isso
- **Objetivo:** versionar no git o trabalho das T02 e T05 e os ajustes da #011.
- **Resposta da IA (resumo):** criou a branch `t02-t05-sort-table` a partir da `master` e fez nela um commit com a pasta `src/` (metrics, search, vector, sort com a tabela de algoritmos e main), o `.gitignore`, a regra de idioma da interface no `CLAUDE.md` e as entradas #010–#012 deste log. Nada foi enviado ao GitHub (sem push).
- **Adaptações / correções:** a IA commitou numa branch separada em vez de direto na `master` (como na #009), para que outro integrante revise as T02/T05 antes do merge, como pede a regra do plano. Na #013 a equipe trocou a branch por tarefa pelo fluxo `ESDD/<integrante>` → `dev` → `main`, e `t02-t05-sort-table` foi renomeada para `ESDD/murilo`.

## #013 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > na vdd cria branch main(prod), dev e a ESDD/integrante
- **Objetivo:** organizar as branches do repositório em `main` (produção), `dev` (integração) e uma `ESDD/<integrante>` por pessoa.
- **Resposta da IA (resumo):** só no repositório local: renomeou `master` para `main` (e desfez o vínculo com `origin/master`), criou `dev` a partir da `main` e renomeou `t02-t05-sort-table` para `ESDD/murilo`, que fica com o commit das T02/T05. `main` e `dev` continuam no commit inicial até a revisão. Nada foi enviado ao GitHub, que ainda tem só a `master`.
- **Adaptações / correções:** corrige a #012: a equipe preferiu um fluxo fixo `ESDD/<integrante>` → `dev` → `main` em vez de uma branch por tarefa. As branches dos outros integrantes não foram criadas porque os nomes ainda não foram informados.

## #014 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > pode fazer o push e trocar a padrão para main
- **Objetivo:** publicar no GitHub as branches `main`, `dev` e `ESDD/murilo` e tornar a `main` a branch padrão do repositório.
- **Resposta da IA (resumo):** conferiu que a conta tem permissão de admin, enviou as três branches com `git push -u` e trocou a branch padrão do repositório de `master` para `main` (`gh repo edit --default-branch main`). Depois commitou na `ESDD/murilo` o que estava pendente (entradas #013–#014 deste log e a seção "Branches (git)" do `CLAUDE.md`) e enviou de novo. A `master` antiga continua no GitHub, no mesmo commit da `main`.
- **Adaptações / correções:** a IA não apagou a `master` do GitHub porque isso não foi pedido. A equipe decide se remove.

## #015 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > pode apagar a master do GitHub
- **Objetivo:** remover a branch `master` do GitHub, que sobrou depois da troca para `main`.
- **Resposta da IA (resumo):** antes de apagar, conferiu que a `master` remota estava no mesmo commit da `main` (`4984778`, nada a perder) e que nenhum pull request apontava para ela. Apagou com `git push origin --delete master` e limpou a referência local com `git remote prune origin`. O GitHub agora tem só `main` (padrão), `dev` e `ESDD/murilo`.
- **Adaptações / correções:** nenhuma.

## #016 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > /salvar-memoria
- **Objetivo:** salvar a memória desta sessão com a skill `/salvar-memoria`.
- **Resposta da IA (resumo):** criou a nota `contexto/memory/2026-11-15_sessao-02_tabela-algoritmos-branches.md` (prompts #010–#016). Ela registra as T02/T05 feitas, o fluxo de branches, o bug do laço infinito com N > 2048, que ponteiro para função não está no material das aulas e as pendências (branches dos outros integrantes, PR para a `dev`, correção do hook).
- **Adaptações / correções:** nenhuma.

## #017 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > <browser_instruction># Claude in Chrome browser automation
  >
  > You have access to browser automation tools (mcp__claude-in-chrome__*) for interacting with web pages in Chrome. Follow these guidelines for effective browser automation.
  >
  > ## Loading deferred tools
  >
  > If the mcp__claude-in-chrome__* tools are deferred (must be loaded via ToolSearch before use), load every tool you expect to need in ONE ToolSearch call — the select query accepts a comma-separated list — never one call per tool. Start with the core set:
  >
  > ToolSearch with query "select:mcp__claude-in-chrome__tabs_context_mcp,mcp__claude-in-chrome__navigate,mcp__claude-in-chrome__computer,mcp__claude-in-chrome__read_page,mcp__claude-in-chrome__tabs_create_mcp,mcp__claude-in-chrome__tabs_close_mcp"
  >
  > Add task-specific tools to the same call when the task obviously needs them: read_console_messages / read_network_requests for debugging, form_input for forms, gif_creator for recordings, javascript_tool for page scripting.
  >
  > ## GIF recording
  >
  > When performing multi-step browser interactions that the user may want to review or share, use mcp__claude-in-chrome__gif_creator to record them.
  >
  > You must ALWAYS:
  > * Capture extra frames before and after taking actions to ensure smooth playback
  > * Name the file meaningfully to help the user identify it later (e.g., "login_process.gif")
  >
  > ## Console log debugging
  >
  > You can use mcp__claude-in-chrome__read_console_messages to read console output. Console output may be verbose. If you are looking for specific log entries, use the 'pattern' parameter with a regex-compatible pattern. This filters results efficiently and avoids overwhelming output. For example, use pattern: "[MyApp]" to filter for application-specific logs rather than reading all console output.
  >
  > ## Alerts and dialogs
  >
  > IMPORTANT: Do not trigger JavaScript alerts, confirms, prompts, or browser modal dialogs through your actions. These browser dialogs block all further browser events and will prevent the extension from receiving any subsequent commands. Instead, when possible, use console.log for debugging and then use the mcp__claude-in-chrome__read_console_messages tool to read those log messages. If a page has dialog-triggering elements:
  > 1. Avoid clicking buttons or links that may trigger alerts (e.g., "Delete" buttons with confirmation dialogs)
  > 2. If you must interact with such elements, warn the user first that this may interrupt the session
  > 3. Use mcp__claude-in-chrome__javascript_tool to check for and dismiss any existing dialogs before proceeding
  >
  > If you accidentally trigger a dialog and lose responsiveness, inform the user they need to manually dismiss it in the browser.
  >
  > ## Avoid rabbit holes and loops
  >
  > When using browser automation tools, stay focused on the specific task. If you encounter any of the following, stop and ask the user for guidance:
  > - Unexpected complexity or tangential browser exploration
  > - Browser tool calls failing or returning errors after 2-3 attempts
  > - No response from the browser extension
  > - Page elements not responding to clicks or input
  > - Pages not loading or timing out
  > - Unable to complete the browser task despite multiple approaches
  >
  > Explain what you attempted, what went wrong, and ask how the user would like to proceed. Do not keep retrying the same failing browser action or explore unrelated pages without checking in first.
  >
  > ## Tab context and session startup
  >
  > IMPORTANT: At the start of each browser automation session, call mcp__claude-in-chrome__tabs_context_mcp first to get information about the user's current browser tabs. Use this context to understand what the user might want to work with before creating new tabs.
  >
  > Never reuse tab IDs from a previous/other session. Follow these guidelines:
  > 1. Only reuse an existing tab if the user explicitly asks to work with it
  > 2. Otherwise, create a new tab with mcp__claude-in-chrome__tabs_create_mcp
  > 3. If a tool returns an error indicating the tab doesn't exist or is invalid, call tabs_context_mcp to get fresh tab IDs
  > 4. When a tab is closed by the user or a navigation error occurs, call tabs_context_mcp to see what tabs are available</browser_instruction>
  > Quais as tasks que foram feitas ?
- **Objetivo:** saber quais tarefas do plano já foram feitas.
- **Resposta da IA (resumo):** comparou o código e o git com o progresso salvo no artefato "Plano Projeto ESDD". No código, T02 e T05 estão prontas na branch `ESDD/murilo`, aguardando revisão. No plano, só a T02 está marcada como concluída e a T05 ainda não. As outras 22 tarefas não foram começadas. Nenhum arquivo mudou além deste log.
- **Adaptações / correções:** nenhuma.

## #018 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > <browser_instruction># Claude in Chrome browser automation
  >
  > You have access to browser automation tools (mcp__claude-in-chrome__*) for interacting with web pages in Chrome. Follow these guidelines for effective browser automation.
  >
  > ## Loading deferred tools
  >
  > If the mcp__claude-in-chrome__* tools are deferred (must be loaded via ToolSearch before use), load every tool you expect to need in ONE ToolSearch call — the select query accepts a comma-separated list — never one call per tool. Start with the core set:
  >
  > ToolSearch with query "select:mcp__claude-in-chrome__tabs_context_mcp,mcp__claude-in-chrome__navigate,mcp__claude-in-chrome__computer,mcp__claude-in-chrome__read_page,mcp__claude-in-chrome__tabs_create_mcp,mcp__claude-in-chrome__tabs_close_mcp"
  >
  > Add task-specific tools to the same call when the task obviously needs them: read_console_messages / read_network_requests for debugging, form_input for forms, gif_creator for recordings, javascript_tool for page scripting.
  >
  > ## GIF recording
  >
  > When performing multi-step browser interactions that the user may want to review or share, use mcp__claude-in-chrome__gif_creator to record them.
  >
  > You must ALWAYS:
  > * Capture extra frames before and after taking actions to ensure smooth playback
  > * Name the file meaningfully to help the user identify it later (e.g., "login_process.gif")
  >
  > ## Console log debugging
  >
  > You can use mcp__claude-in-chrome__read_console_messages to read console output. Console output may be verbose. If you are looking for specific log entries, use the 'pattern' parameter with a regex-compatible pattern. This filters results efficiently and avoids overwhelming output. For example, use pattern: "[MyApp]" to filter for application-specific logs rather than reading all console output.
  >
  > ## Alerts and dialogs
  >
  > IMPORTANT: Do not trigger JavaScript alerts, confirms, prompts, or browser modal dialogs through your actions. These browser dialogs block all further browser events and will prevent the extension from receiving any subsequent commands. Instead, when possible, use console.log for debugging and then use the mcp__claude-in-chrome__read_console_messages tool to read those log messages. If a page has dialog-triggering elements:
  > 1. Avoid clicking buttons or links that may trigger alerts (e.g., "Delete" buttons with confirmation dialogs)
  > 2. If you must interact with such elements, warn the user first that this may interrupt the session
  > 3. Use mcp__claude-in-chrome__javascript_tool to check for and dismiss any existing dialogs before proceeding
  >
  > If you accidentally trigger a dialog and lose responsiveness, inform the user they need to manually dismiss it in the browser.
  >
  > ## Avoid rabbit holes and loops
  >
  > When using browser automation tools, stay focused on the specific task. If you encounter any of the following, stop and ask the user for guidance:
  > - Unexpected complexity or tangential browser exploration
  > - Browser tool calls failing or returning errors after 2-3 attempts
  > - No response from the browser extension
  > - Page elements not responding to clicks or input
  > - Pages not loading or timing out
  > - Unable to complete the browser task despite multiple approaches
  >
  > Explain what you attempted, what went wrong, and ask how the user would like to proceed. Do not keep retrying the same failing browser action or explore unrelated pages without checking in first.
  >
  > ## Tab context and session startup
  >
  > IMPORTANT: At the start of each browser automation session, call mcp__claude-in-chrome__tabs_context_mcp first to get information about the user's current browser tabs. Use this context to understand what the user might want to work with before creating new tabs.
  >
  > Never reuse tab IDs from a previous/other session. Follow these guidelines:
  > 1. Only reuse an existing tab if the user explicitly asks to work with it
  > 2. Otherwise, create a new tab with mcp__claude-in-chrome__tabs_create_mcp
  > 3. If a tool returns an error indicating the tab doesn't exist or is invalid, call tabs_context_mcp to get fresh tab IDs
  > 4. When a tab is closed by the user or a navigation error occurs, call tabs_context_mcp to see what tabs are available</browser_instruction>
  > Olá claude, vamos fazer o T03 e T04, qual será o plano?
- **Objetivo:** planejar e implementar a T03 (corrigir os bugs herdados do protótipo) e a T04 (medir o consumo de memória).
- **Resposta da IA (resumo):** montou o plano em modo de planejamento e perguntou três decisões à equipe. Depois da aprovação, implementou:
  - **T03:** `srand(time(NULL))` uma vez no `main`; `vector_fill_random` reescrito como permutação 1..N com Fisher-Yates (acabou o laço infinito com N > 2048 e a sobrescrita por 1..512), com `random_index` combinando dois `rand()` porque `RAND_MAX` = 32767 no MinGW; VLAs do `merge` trocados por alocação no heap com checagem de `NULL`; `merge` e os 7 algoritmos passaram a retornar `int` (1/0), e `SortFunction` mudou para `int (*)(...)`; condição da `sequential_search` invertida (`i < size` primeiro).
  - **T04:** novo módulo `memory.h/.c` (`mem_alloc`, `mem_realloc`, `mem_free` com tamanho explícito, `mem_current`, `mem_peak`, `mem_reset_peak`); `Metrics` ganhou `memory_bytes` (pico de memória extra), exibido no relatório e numa nova coluna da tabela; `vector_resize` com `realloc` num ponteiro temporário; `vector_destroy` recebe o tamanho; nova opção 4 do menu "Alterar tamanho do vetor"; "Mostrar vetor" mostra a memória; na saída aparece "Memoria nao liberada" (deve ser 0).
  - Arquivos: `src/main.c`, `src/vector.c/.h`, `src/sort.c/.h`, `src/metrics.c/.h`, `src/search.c`, novos `src/memory.c/.h`.
  - Verificação: compila com `-Wall -Wextra` sem warnings. Um teste temporário (fora do repositório) com N = 1, 2, 3, 10, 1.000, 10.000 e 50.000 confirmou: permutação válida, os 7 algoritmos ordenam, memória extra = N × 4 bytes nos dois Merge Sorts e 0 nos demais, contador volta a 0 (sem vazamento), `vector_resize` para cima e para baixo. Execução real do menu: vetores diferentes a cada execução e "Memoria nao liberada: 0 bytes".
- **Adaptações / correções:**
  - Decisões da equipe nas perguntas: permutação 1..N (em vez de valores com repetição), tamanho explícito no `mem_free` (em vez de cabeçalho escondido antes do bloco) e opção de menu para o `realloc`.
  - Caso-limite achado na implementação, fora do plano: no Merge Sort iterativo o `merge` pode ser chamado com a metade direita vazia (ex.: N = 10, passo 4, `left` = 8), e `malloc(0)` pode devolver `NULL`, o que pareceria falta de memória. O `merge` agora retorna 1 sem fazer nada quando uma das metades está vazia. Efeito colateral: nesses casos o contador de trocas do Merge Sort iterativo fica um pouco menor que no protótipo, porque a cópia inútil da metade esquerda deixou de ser contada.
  - Com N = 50.000, Bubble Sort leva ~20 s, Selection ~6 s e Insertion ~4 s na máquina de teste. Na T09 vale avisar o usuário antes de rodar "Comparar todos" com N grande.

## #019 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > /salvar-memoria
- **Objetivo:** salvar a nota de memória desta sessão (T03 e T04).
- **Resposta da IA (resumo):** criou `contexto/memory/2026-11-15_sessao-03_bugs-e-memoria.md` com o que foi feito na T03/T04, as decisões da equipe, as armadilhas encontradas (`RAND_MAX` do MinGW, `malloc(0)` no Merge Sort iterativo), as pendências (commits, PR) e os próximos passos.
- **Adaptações / correções:** nenhuma.

## #020 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > faça dois commits separados, um para T03 e outro para T04, pode subir direto para main sem PR
- **Objetivo:** registrar a T03 e a T04 em commits separados e publicar na `main` sem PR.
- **Resposta da IA (resumo):** fez dois commits na `ESDD/murilo`. O da T03 usa a cópia da versão só com a T03, guardada no scratchpad durante a implementação. O da T04 traz a versão final, o módulo `memory`, este log (#015–#020) e as notas das sessões 02 e 03. Depois avançou a `main` até a `ESDD/murilo` por fast-forward, sem commit de merge, e enviou a `main` e a `ESDD/murilo` ao GitHub.
- **Adaptações / correções:** pedido do usuário contra a regra do `CLAUDE.md` ("nunca commitar direto em `main`" e passar por revisão na `dev`). Os commits foram feitos na branch pessoal e a `main` só foi avançada até ela. Como a T03/T04 depende do código da T02/T05, a `main` também recebeu os commits `8a3f44c` (T02/T05) e `cb1b238`, que ainda não tinham revisão. A `dev` ficou para trás da `main`.

## #021 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > sim, atualiza a dev também
- **Objetivo:** deixar a `dev` igual à `main`, com T02–T05.
- **Resposta da IA (resumo):** avançou a `dev` no GitHub até a `main` (`cbac53f`) por fast-forward, com `git push origin main:dev`, e atualizou a `dev` local. Agora `main`, `dev` e `ESDD/murilo` estão no mesmo commit. Nenhum arquivo de código mudou.
- **Adaptações / correções:** a primeira tentativa (`git checkout dev`) falhou porque o hook já tinha gravado esta entrada no `AI_LOG.md`, que estava com alterações locais. Os comandos seguintes da mesma linha rodaram, mas não mudaram nada. A segunda tentativa atualizou a `dev` sem trocar de branch.

## #022 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > <browser_instruction># Claude in Chrome browser automation
  >
  > You have access to browser automation tools (mcp__claude-in-chrome__*) for interacting with web pages in Chrome. Follow these guidelines for effective browser automation.
  >
  > ## Loading deferred tools
  >
  > If the mcp__claude-in-chrome__* tools are deferred (must be loaded via ToolSearch before use), load every tool you expect to need in ONE ToolSearch call — the select query accepts a comma-separated list — never one call per tool. Start with the core set:
  >
  > ToolSearch with query "select:mcp__claude-in-chrome__tabs_context_mcp,mcp__claude-in-chrome__navigate,mcp__claude-in-chrome__computer,mcp__claude-in-chrome__read_page,mcp__claude-in-chrome__tabs_create_mcp,mcp__claude-in-chrome__tabs_close_mcp"
  >
  > Add task-specific tools to the same call when the task obviously needs them: read_console_messages / read_network_requests for debugging, form_input for forms, gif_creator for recordings, javascript_tool for page scripting.
  >
  > ## GIF recording
  >
  > When performing multi-step browser interactions that the user may want to review or share, use mcp__claude-in-chrome__gif_creator to record them.
  >
  > You must ALWAYS:
  > * Capture extra frames before and after taking actions to ensure smooth playback
  > * Name the file meaningfully to help the user identify it later (e.g., "login_process.gif")
  >
  > ## Console log debugging
  >
  > You can use mcp__claude-in-chrome__read_console_messages to read console output. Console output may be verbose. If you are looking for specific log entries, use the 'pattern' parameter with a regex-compatible pattern. This filters results efficiently and avoids overwhelming output. For example, use pattern: "[MyApp]" to filter for application-specific logs rather than reading all console output.
  >
  > ## Alerts and dialogs
  >
  > IMPORTANT: Do not trigger JavaScript alerts, confirms, prompts, or browser modal dialogs through your actions. These browser dialogs block all further browser events and will prevent the extension from receiving any subsequent commands. Instead, when possible, use console.log for debugging and then use the mcp__claude-in-chrome__read_console_messages tool to read those log messages. If a page has dialog-triggering elements:
  > 1. Avoid clicking buttons or links that may trigger alerts (e.g., "Delete" buttons with confirmation dialogs)
  > 2. If you must interact with such elements, warn the user first that this may interrupt the session
  > 3. Use mcp__claude-in-chrome__javascript_tool to check for and dismiss any existing dialogs before proceeding
  >
  > If you accidentally trigger a dialog and lose responsiveness, inform the user they need to manually dismiss it in the browser.
  >
  > ## Avoid rabbit holes and loops
  >
  > When using browser automation tools, stay focused on the specific task. If you encounter any of the following, stop and ask the user for guidance:
  > - Unexpected complexity or tangential browser exploration
  > - Browser tool calls failing or returning errors after 2-3 attempts
  > - No response from the browser extension
  > - Page elements not responding to clicks or input
  > - Pages not loading or timing out
  > - Unable to complete the browser task despite multiple approaches
  >
  > Explain what you attempted, what went wrong, and ask how the user would like to proceed. Do not keep retrying the same failing browser action or explore unrelated pages without checking in first.
  >
  > ## Tab context and session startup
  >
  > IMPORTANT: At the start of each browser automation session, call mcp__claude-in-chrome__tabs_context_mcp first to get information about the user's current browser tabs. Use this context to understand what the user might want to work with before creating new tabs.
  >
  > Never reuse tab IDs from a previous/other session. Follow these guidelines:
  > 1. Only reuse an existing tab if the user explicitly asks to work with it
  > 2. Otherwise, create a new tab with mcp__claude-in-chrome__tabs_create_mcp
  > 3. If a tool returns an error indicating the tab doesn't exist or is invalid, call tabs_context_mcp to get fresh tab IDs
  > 4. When a tab is closed by the user or a navigation error occurs, call tabs_context_mcp to see what tabs are available</browser_instruction>
  > Adicionei um pdf no projeto de exemplo, aquele pdf é a primeira versão do enunciado final e foi nele que eu me basiei para para fazer o projeto de exemplo, adicionei ele para você ter o contexto, crie um arquivo .md para ele e pegue o contexto dele
- **Objetivo:** transcrever o PDF da 1ª versão do enunciado (`contexto/projeto-exemplo/Testes de algoritmos de ordenação.pdf`), base do protótipo, para Markdown e usar como contexto.
- **Resposta da IA (resumo):** criou `contexto/slides/Testes de algoritmos de ordenação.md` com o conteúdo do PDF (recursos, dados exibidos, módulos, `struct Metricas`, fluxo de execução), uma tabela comparando a v1 com o enunciado final e outra com a situação no código atual em `src/`. Encontrou dois itens da v1 que ainda faltam: geração de dados **ordenados/invertidos** e **modo passo a passo**. Atualizou a linha de `contexto/projeto-exemplo/` na tabela de pastas do `CLAUDE.md`.
- **Adaptações / correções:** o `.md` ficou em `contexto/slides/` (e não em `projeto-exemplo/`) para seguir a convenção de um `.md` por PDF nessa pasta. Os dois itens faltantes não são exigidos pelo enunciado final; ficaram registrados como sugestão. A entrada do prompt voltou a gravar o bloco `<browser_instruction>` (pendência já conhecida do `log_prompt.py`).

## #023 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > faz o commit disso
- **Objetivo:** commitar o resumo da 1ª versão do enunciado e os arquivos ligados a ele.
- **Resposta da IA (resumo):** fez um commit na `ESDD/murilo` com o PDF `contexto/projeto-exemplo/Testes de algoritmos de ordenação.pdf`, o novo `contexto/slides/Testes de algoritmos de ordenação.md`, a linha atualizada do `CLAUDE.md` e as entradas #021–#023 do `AI_LOG.md`. Sem push.
- **Adaptações / correções:** nenhuma. O PDF entrou no commit porque o `.md` e o `CLAUDE.md` apontam para ele (os outros PDFs de `contexto/` também são versionados).

## #024 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > faz o push
- **Objetivo:** enviar o commit do enunciado v1 para o GitHub.
- **Resposta da IA (resumo):** rodou `git push origin ESDD/murilo`. A branch remota foi de `cbac53f` para `0c53a42`. Nenhum arquivo de código mudou.
- **Adaptações / correções:** nenhuma. Esta entrada fica pendente de commit, pois o hook a gravou depois do commit enviado.

## #025 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > o que falta do primeiro enunciado para esse novo projeto?
- **Objetivo:** saber quais itens do enunciado v1 (`Testes de algoritmos de ordenação`) ainda faltam no projeto.
- **Resposta da IA (resumo):** conferiu `src/` (menu, `metrics.c`, `vector.h`, `sort.h`). Concluiu que faltam dois itens: geração de dados **ordenados** e **invertidos** e o **modo passo a passo** (tela atualizada a cada troca). O resto da v1 já está pronto. Sugeriu um tipo de dados no gerador e um callback de passo nos algoritmos, que também serviria ao Undo e à exportação JSON/CSV. Nenhum arquivo de código mudou.
- **Adaptações / correções:** nenhuma (só análise).

## #026 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > adicione nas tasks do artefato
- **Objetivo:** incluir no plano do projeto (artefato "Plano Projeto ESDD") os dois itens do enunciado v1 que faltam.
- **Resposta da IA (resumo):** republicou o artefato no mesmo link com duas tarefas novas: **T25** "Gerar dados ordenados e invertidos" (fase 1) e **T26** "Modo passo a passo" (primeira da fase 3, por ser a base da exportação T10 e do Undo T11). Ambas têm a etiqueta "Enunciado v1". O código da página passou a aceitar um número fixo por tarefa, e a barra do cronograma mostra faixas como "T01–T05, T25". Nenhum arquivo do repositório mudou além deste log.
- **Adaptações / correções:** as tarefas novas não receberam os números T06/T10, como a ordem na lista daria, para não renumerar T06–T24, que já são citadas em commits e nas notas de sessão. O progresso marcado não se perde, porque ele é salvo pelo id interno da tarefa, e não pelo número.

## #027 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > faz o commit e o push
- **Objetivo:** commitar e enviar ao GitHub as entradas pendentes do AI_LOG.
- **Resposta da IA (resumo):** fez um commit na `ESDD/murilo` só com o `AI_LOG.md` (entradas #024–#027) e o enviou com `git push origin ESDD/murilo`. O plano (artefato) não fica no repositório, por isso não entrou no commit.
- **Adaptações / correções:** nenhuma.

## #028 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > <browser_instruction># Claude in Chrome browser automation
  >
  > You have access to browser automation tools (mcp__claude-in-chrome__*) for interacting with web pages in Chrome. Follow these guidelines for effective browser automation.
  >
  > ## Loading deferred tools
  >
  > If the mcp__claude-in-chrome__* tools are deferred (must be loaded via ToolSearch before use), load every tool you expect to need in ONE ToolSearch call — the select query accepts a comma-separated list — never one call per tool. Start with the core set:
  >
  > ToolSearch with query "select:mcp__claude-in-chrome__tabs_context_mcp,mcp__claude-in-chrome__navigate,mcp__claude-in-chrome__computer,mcp__claude-in-chrome__read_page,mcp__claude-in-chrome__tabs_create_mcp,mcp__claude-in-chrome__tabs_close_mcp"
  >
  > Add task-specific tools to the same call when the task obviously needs them: read_console_messages / read_network_requests for debugging, form_input for forms, gif_creator for recordings, javascript_tool for page scripting.
  >
  > ## GIF recording
  >
  > When performing multi-step browser interactions that the user may want to review or share, use mcp__claude-in-chrome__gif_creator to record them.
  >
  > You must ALWAYS:
  > * Capture extra frames before and after taking actions to ensure smooth playback
  > * Name the file meaningfully to help the user identify it later (e.g., "login_process.gif")
  >
  > ## Console log debugging
  >
  > You can use mcp__claude-in-chrome__read_console_messages to read console output. Console output may be verbose. If you are looking for specific log entries, use the 'pattern' parameter with a regex-compatible pattern. This filters results efficiently and avoids overwhelming output. For example, use pattern: "[MyApp]" to filter for application-specific logs rather than reading all console output.
  >
  > ## Alerts and dialogs
  >
  > IMPORTANT: Do not trigger JavaScript alerts, confirms, prompts, or browser modal dialogs through your actions. These browser dialogs block all further browser events and will prevent the extension from receiving any subsequent commands. Instead, when possible, use console.log for debugging and then use the mcp__claude-in-chrome__read_console_messages tool to read those log messages. If a page has dialog-triggering elements:
  > 1. Avoid clicking buttons or links that may trigger alerts (e.g., "Delete" buttons with confirmation dialogs)
  > 2. If you must interact with such elements, warn the user first that this may interrupt the session
  > 3. Use mcp__claude-in-chrome__javascript_tool to check for and dismiss any existing dialogs before proceeding
  >
  > If you accidentally trigger a dialog and lose responsiveness, inform the user they need to manually dismiss it in the browser.
  >
  > ## Avoid rabbit holes and loops
  >
  > When using browser automation tools, stay focused on the specific task. If you encounter any of the following, stop and ask the user for guidance:
  > - Unexpected complexity or tangential browser exploration
  > - Browser tool calls failing or returning errors after 2-3 attempts
  > - No response from the browser extension
  > - Page elements not responding to clicks or input
  > - Pages not loading or timing out
  > - Unable to complete the browser task despite multiple approaches
  >
  > Explain what you attempted, what went wrong, and ask how the user would like to proceed. Do not keep retrying the same failing browser action or explore unrelated pages without checking in first.
  >
  > ## Tab context and session startup
  >
  > IMPORTANT: At the start of each browser automation session, call mcp__claude-in-chrome__tabs_context_mcp first to get information about the user's current browser tabs. Use this context to understand what the user might want to work with before creating new tabs.
  >
  > Never reuse tab IDs from a previous/other session. Follow these guidelines:
  > 1. Only reuse an existing tab if the user explicitly asks to work with it
  > 2. Otherwise, create a new tab with mcp__claude-in-chrome__tabs_create_mcp
  > 3. If a tool returns an error indicating the tab doesn't exist or is invalid, call tabs_context_mcp to get fresh tab IDs
  > 4. When a tab is closed by the user or a navigation error occurs, call tabs_context_mcp to see what tabs are available</browser_instruction>
  > Vamos fazer o T25, qual é o plano para essa task?
- **Objetivo:** planejar e implementar a T25, que gera dados ordenados (1..N) e invertidos (N..1) além do aleatório e deixa o usuário escolher o tipo no menu.
- **Resposta da IA (resumo):** primeiro montou um plano (modo de planejamento), que o usuário aprovou, e depois o implementou. `src/vector.h/.c`: constantes `FILL_RANDOM/FILL_SORTED/FILL_REVERSED`, funções `vector_fill_sorted`, `vector_fill_reversed`, `vector_fill(v, size, kind)` (retorna 1/0) e `vector_fill_name`. O `vector_fill_random` passou a reaproveitar o `vector_fill_sorted`. `src/metrics.h/.c`: `metrics_print` e `metrics_print_table` recebem o nome do tipo e mostram "Dados: X". `src/main.c`: pergunta o tipo depois do tamanho, ganhou a opção 5 "Alterar tipo dos dados" (Encerrar virou 6), o cabeçalho do menu mostra o tipo, e "Alterar tamanho" mantém o tipo atual. `src/sort.c`: os dois Quick Sorts chamam a recursão só na parte menor e tratam a maior com um `while`. `contexto/slides/Testes de algoritmos de ordenação.md`: o item virou "Feito". Os testes temporários (no scratchpad) cobriram N = 1 a 50.000 e os 3 tipos: tudo ordena, Insertion Sort tem N−1 comparações e 0 trocas com dados ordenados, não sobra memória, e as contagens do Quick Sort são idênticas às da versão anterior (117 casos).
- **Adaptações / correções:** a IA viu que, com dados ordenados ou invertidos, o Quick Sort recursa N níveis. A versão antiga com N = 50.000 fechava com `C00000FD` (estouro de pilha). Entre as opções apresentadas (recursão no lado menor, aumentar a pilha no gcc, limitar N ou só documentar), o usuário escolheu a recursão no lado menor. Para o menu, escolheu perguntar o tipo no início e ter também uma opção no menu. Fica de fora (T09): o aviso de demora dos O(n²) com N grande. Com N = 50.000 ordenado, o Quick Sort leva cerca de 12 s.

## #029 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > <ide_opened_file>The user opened the file c:\Users\Admin\Documents\IFSP\Professores\2_Semestre\ESDD_Estrutura_de_Dados\Eduardo_Leal\Projeto_Final_ESDD\src\main.c in the IDE. This may or may not be related to the current task.</ide_opened_file>
  > /salvar-memoria
- **Objetivo:** registrar a nota da sessão 04 (T25) em `contexto/memory/`.
- **Resposta da IA (resumo):** criou `contexto/memory/2026-11-15_sessao-04_dados-ordenados-invertidos.md` com o que foi feito na T25, a decisão sobre o estouro de pilha do Quick Sort, os tempos medidos, as pendências (commit, recompilar o `main.exe`, revisão) e os próximos passos.
- **Adaptações / correções:** nenhuma.

## #030 — Domingo, 15/11/2026

- **Autor:** Murilo Leandro
- **Prompt:**
  > faz o commit e o push
- **Objetivo:** commitar a T25 e a nota da sessão 04 e enviar tudo ao GitHub.
- **Resposta da IA (resumo):** fez um commit na `ESDD/murilo` com o código da T25 (`src/vector.*`, `src/sort.c`, `src/metrics.*`, `src/main.c`), o `.md` do enunciado v1, a nota `contexto/memory/2026-11-15_sessao-04_dados-ordenados-invertidos.md` e as entradas #028–#030 do AI_LOG, e o enviou com `git push origin ESDD/murilo`.
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
