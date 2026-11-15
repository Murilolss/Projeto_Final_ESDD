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
- **Adaptações / correções:** a IA commitou numa branch separada em vez de direto na `master` (como na #009), para que outro integrante revise as T02/T05 antes do merge, como pede a regra do plano.

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
