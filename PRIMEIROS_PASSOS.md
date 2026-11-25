# Primeiros passos — Projeto Final ESDD

**Repositório:** https://github.com/Murilolss/Projeto_Final_ESDD

Guia para quem começa a trabalhar no repositório: um integrante novo ou uma sessão nova do **Claude Code** ou do **Codex**. Explica o ambiente, as branches, o fluxo de trabalho do dia a dia e os registros obrigatórios (`AI_LOG.md` e notas de sessão).

As regras de código e o resumo dos requisitos ficam no [CLAUDE.md](CLAUDE.md), que o Claude Code carrega sozinho em toda sessão. O Codex carrega o [AGENTS.md](AGENTS.md), que manda seguir o mesmo `CLAUDE.md` e explica o que muda no Codex. Este guia não repete essas regras: ele explica **como trabalhar** no repositório.

> **Para o assistente (Claude ou Codex):** assim que terminar de ler este guia, **abra o quadro de tarefas e liste as tarefas do usuário** (veja o quadro na seção 1).
> - **Claude:** abra o artefato (`Artifact` com `action: "open"`), leia os responsáveis com `ArtifactData` (`action: "list"`, `collection: "tasks"`) e confira com o [contexto/TAREFAS.md](contexto/TAREFAS.md).
> - **Codex:** abra o link no navegador (`start "" "https://claude.ai/artifact/G6eqVDUisHMbyCAS5mDpfr"` no Windows) e leia o [contexto/TAREFAS.md](contexto/TAREFAS.md), porque o Codex não lê artefatos do claude.ai.
>
> O usuário é o `git config user.name`. Liste as tarefas dele que não estão concluídas (número, título, dependências e ordem sugerida) e pergunte por qual ele quer começar. Se for a primeira vez neste computador, faça antes a configuração das seções 0, 2 e 3.

---

## 0. Acesso ao repositório (uma vez por pessoa)

1. O Murilo convida o integrante como colaborador no GitHub.
2. O integrante **aceita o convite**: pelo e-mail do GitHub ou em https://github.com/Murilolss/Projeto_Final_ESDD/invitations (logado na própria conta).
3. O repositório é público, então o clone funciona antes do aceite. O **push** só funciona depois: sem o aceite, o `git push` falha com `403` / `Permission denied`.

---

## 1. Antes de tudo: o que ler

Leia nesta ordem:

1. [CLAUDE.md](CLAUDE.md): requisitos, padrões obrigatórios do código (TAD em `.h`/`.c`, inglês no código, `malloc` checado etc.) e mapa das pastas. Quem usa o Codex lê também o [AGENTS.md](AGENTS.md).
2. **A nota de sessão mais recente** em [contexto/memory/](contexto/memory/), a de maior `sessao-NN`. Ela diz o que foi feito por último, o que ficou pendente e qual é o próximo passo. As anteriores contam o histórico das decisões.
3. `contexto/slides/Enunciado.md`, se precisar do texto completo do enunciado. As pastas `contexto/slides/` e `contexto/pdfs/` **não estão no git**: cada integrante guarda a própria cópia. Se você não tiver, peça a outro integrante e copie para dentro de `contexto/`; o `.gitignore` impede que elas entrem num commit.
4. **O quadro de tarefas da equipe:** artefato "Plano Projeto ESDD" (https://claude.ai/artifact/G6eqVDUisHMbyCAS5mDpfr). Ele lista as tarefas **T01–T26**, com responsável, status e cronograma. As conversas e os commits citam as tarefas por esse número (ex.: "Vamos fazer a T12").
   - Qualquer pessoa com o link vê a página. Para ver e marcar o progresso é preciso estar logado no claude.ai.
   - O [contexto/TAREFAS.md](contexto/TAREFAS.md) é o espelho em texto do quadro, para o Codex e para quem está sem conta no claude.ai. Os dois precisam bater: quem muda um muda o outro.

> **Para o assistente:** quando o usuário disser "vamos fazer a T##", leia a descrição da tarefa (Claude: artefato com `action: "read"`; Codex: [contexto/TAREFAS.md](contexto/TAREFAS.md)) e a nota de sessão mais recente antes de propor o plano.

---

## 2. Pré-requisitos

| Ferramenta | Para quê | Observação |
|---|---|---|
| Git | versionamento | conta no GitHub com acesso ao repositório |
| MinGW (gcc) | compilar o C | a máquina de referência tem MinGW.org GCC 6.3.0, **32 bits** (ponteiro = 4 bytes, por isso os nós da lista têm 8 ou 12 bytes) |
| Python 3 no PATH | hook do `AI_LOG.md` | o hook tenta `python`, `python3` e `py`, nessa ordem; sem Python o registro automático não acontece |
| Claude Code (VS Code ou terminal) **ou** Codex (CLI, extensão do VS Code ou app) | assistente | o Claude lê o `CLAUDE.md` e o `.claude/`; o Codex lê o `AGENTS.md`, o `.codex/hooks.json` e o `.agents/skills/` |

Sistema usado pela equipe: Windows 11. O código usa `system("cls")` e `#define __USE_MINGW_ANSI_STDIO 1` (para o `%lld` funcionar no MinGW).

---

## 3. Configuração inicial (uma vez por computador)

```bash
# 1. Clonar já na dev (a main está atrasada e ainda não tem este guia, o AGENTS.md nem o hook do Codex)
git clone -b dev https://github.com/Murilolss/Projeto_Final_ESDD.git
cd Projeto_Final_ESDD

# 2. Nome do autor: aparece em cada entrada do AI_LOG.md e nos commits.
#    Use o primeiro nome igual ao do quadro (ex.: "Lucas ..."), porque o assistente acha suas tarefas por ele.
git config user.name "Nome Sobrenome"

# 3. Pasta do executável (o .exe é ignorado pelo git, então a pasta não vem no clone)
mkdir -p src/output

# 4. Teste de compilação
gcc -Wall -Wextra src/*.c -o src/output/main.exe

# 5. Python para o hook do AI_LOG
python --version
```

Depois disso, crie a sua branch (seção 4.2) e configure o seu assistente (3.1 ou 3.2).

### 3.1 Claude Code

Abra o Claude Code na pasta do projeto e mande qualquer prompt. Uma entrada nova deve aparecer no fim do `AI_LOG.md` (com `- **Ferramenta:** Claude Code`), e o Claude recebe o aviso `[AI_LOG] ... #NNN`. Se nada aparecer, veja se o Python está no PATH (`python --version`).

### 3.2 Codex

1. Abra o Codex **na raiz do repositório**, a pasta `Projeto_Final_ESDD`. No Windows, o hook usa o caminho relativo `.claude/hooks/log_prompt.py` e não roda se o Codex for aberto numa subpasta.
2. Quando o Codex perguntar se você confia na pasta, responda que **sim**. Ele só carrega o `.codex/hooks.json` de projetos confiáveis.
3. Rode `/hooks`, confira que o hook `UserPromptSubmit` aponta para `.claude/hooks/log_prompt.py` e marque-o como **confiável** (trust). Toda vez que o `hooks.json` mudar, o Codex pede essa revisão de novo.
4. O Codex lê o [AGENTS.md](AGENTS.md) sozinho. As skills `atualizar-branch` e `salvar-memoria` ficam em [.agents/skills/](.agents/skills/): peça "atualiza minha branch" / "salva a memória da sessão" ou chame a skill pelo nome (`$atualizar-branch`).
5. Teste: mande qualquer prompt. Uma entrada nova deve aparecer no fim do `AI_LOG.md` com `- **Ferramenta:** Codex`. Se nada aparecer, confira os passos 1 a 3 e o `python --version`. Se o Windows só tiver o comando `py`, troque `python` por `py` no `commandWindows` do [.codex/hooks.json](.codex/hooks.json) **só no seu computador**: não commite essa mudança, que vale só para você.

---

## 4. Branches

### 4.1 Como funcionam

| Branch | Papel | Quem escreve |
|---|---|---|
| `main` | produção: a versão de entrega | ninguém commita direto; recebe merge da `dev` quando está estável e só quando o grupo decide |
| `dev` | integração: junta o trabalho revisado de todos | ninguém commita direto; recebe merge das `ESDD/<integrante>` depois da revisão |
| `ESDD/<integrante>` | trabalho de cada pessoa (ex.: `ESDD/murilo`) | só o dono da branch |

O caminho do código é sempre este:

```
ESDD/<integrante>  --(revisão de outro integrante)-->  dev  --(quando estável)-->  main
```

Regras:
- Nunca commitar direto em `main` ou `dev`.
- Nunca usar `git push --force` em branch compartilhada.
- Cada pessoa commita só na própria `ESDD/<integrante>`.
- O nome da branch usa o primeiro nome em minúsculas, sem acento: `ESDD/murilo`, `ESDD/joao`.

### 4.2 Criar a branch de um integrante (local + GitHub)

A branch nasce **a partir da `dev` atualizada**, não da `main`, porque a `main` está bem atrás da `dev`.

```bash
git fetch origin
git switch -c ESDD/<nome> origin/dev    # cria a branch local a partir da dev remota
git push -u origin ESDD/<nome>          # publica no GitHub e liga a local à remota
```

Para conferir: `git branch -vv` deve mostrar `ESDD/<nome>` ligada a `[origin/ESDD/<nome>]`.

Se a branch já existe no GitHub (criada em outro computador):

```bash
git fetch origin
git switch ESDD/<nome>                  # o git cria a local ligada à origin/ESDD/<nome>
```

### 4.3 Estado atual (18/11/2026)

| Integrante | Assistente | Branch | Situação |
|---|---|---|---|
| Murilo | Claude Code | `ESDD/murilo` | ativa |
| Lucas | Codex | `ESDD/lucas` | a criar (seção 4.2), depois de aceitar o convite (seção 0) |
| Liliane | a definir | `ESDD/liliane` | a criar |

- A `dev` tem tudo até a T09, além da configuração do Codex. A `main` parou na T04.
- **Exceção temporária:** enquanto o Murilo for o único integrante commitando, a `ESDD/murilo` vai direto para a `dev`, sem PR e sem revisão, com um fast-forward feito sem trocar de branch:
  ```bash
  git fetch . ESDD/murilo:dev    # avança a dev local até a ESDD/murilo (só funciona se for fast-forward)
  git push origin dev
  ```
  Isso só acontece quando o usuário pede. Quando o primeiro commit de outro integrante chegar, volta o fluxo com PR + revisão (seção 5.6).
- Merge na `main` só quando o usuário pedir explicitamente.

### 4.4 Claude e Codex trabalhando em paralelo

Cada pessoa usa o seu assistente no seu computador. Os dois nunca mexem na mesma branch, e o que eles compartilham passa pelo GitHub:

```
PC do Murilo (Claude Code)  --push-->  ESDD/murilo --PR + revisao--> dev <--PR + revisao-- ESDD/lucas  <--push--  PC do Lucas (Codex)
                            <------------------ /atualizar-branch (git pull origin dev) ------------------>
```

| O que é compartilhado | Onde fica | Quem lê |
|---|---|---|
| Regras do projeto | [CLAUDE.md](CLAUDE.md) (única fonte) | o Claude direto; o Codex pelo [AGENTS.md](AGENTS.md) |
| Registro de prompts | [AI_LOG.md](AI_LOG.md), pelo mesmo [log_prompt.py](.claude/hooks/log_prompt.py) | os dois; cada entrada diz a **Ferramenta** |
| Notas de sessão | [contexto/memory/](contexto/memory/) | os dois |
| Skills | `.claude/skills/` (original) e `.agents/skills/` (aponta para a original) | Claude e Codex, respectivamente |
| Tarefas | quadro (artefato) + [contexto/TAREFAS.md](contexto/TAREFAS.md) | Claude: o quadro; Codex: o `.md` |

Regras para não atrapalhar o outro:
1. Comece a sessão com `/atualizar-branch` (no Codex, a skill `atualizar-branch`) e termine com commit + push da sua branch. Assim o outro recebe o seu trabalho quando ele entrar na `dev`.
2. Cada um trabalha nas **suas** tarefas do quadro. Se precisar mexer num arquivo de outra pessoa (ex.: `main.c`, que todos editam para pôr opções no menu), avise antes e mantenha a mudança pequena para o merge ficar fácil.
3. Uma regra nova ou alterada vai para o `CLAUDE.md`, nunca só para o `AGENTS.md`, para os dois assistentes seguirem a mesma coisa.
4. Os conflitos mais comuns ficam no `AI_LOG.md` e na numeração das notas. A solução está nas seções 6.1 e 6.2: manter as duas versões e renumerar as suas.

---

## 5. Fluxo de trabalho do dia a dia

### 5.1 Começar a sessão
1. Confirme que está na sua branch: `git branch --show-current` deve mostrar `ESDD/<nome>`.
2. Traga as novidades da `dev` com a skill **`/atualizar-branch`**. Ela roda `git pull --no-edit origin dev` e, se vierem commits, faz o push da sua branch. Ela para se você não estiver numa `ESDD/...` e nunca resolve conflitos sozinha.
3. Leia a nota de sessão mais recente (seção 1).

### 5.2 Escolher e planejar a tarefa
- Escolha uma tarefa do plano (T##) que seja sua.
- Peça um plano ao Claude antes de codar ("Vamos fazer a T##, qual é o plano?"). A equipe tem trabalhado assim: o plano é aprovado e só depois vem a implementação.
- Quando houver uma decisão de projeto (ex.: o que medir, quais algoritmos entram), o Claude pergunta, recomenda uma opção e registra a escolha do usuário no AI_LOG e na nota de sessão.

### 5.3 Implementar
- Siga as regras do [CLAUDE.md](CLAUDE.md): código e comentários em inglês, textos do `printf` em português **sem acento**, TAD em `.h`/`.c`, checar `malloc`, retorno `int` 1/0 com ponteiro de saída.
- **Toda alocação passa pelo contador de memória:** use `mem_alloc` / `mem_realloc` / `mem_free` (de [src/memory.h](src/memory.h)), nunca `malloc`/`free` direto. Sem isso, as medições de memória e a checagem de vazamento ("Memoria nao liberada: 0 bytes") ficam erradas.
- Algoritmo novo de ordenação entra na tabela de algoritmos do módulo (ponteiro para função), não em mais um `case` no menu.

### 5.4 Compilar e testar
```bash
gcc -Wall -Wextra src/*.c -o src/output/main.exe    # tem que compilar sem warnings
./src/output/main.exe
```
- Se o link falhar com "Permission denied", o `main.exe` está aberto em outro terminal. Feche o programa e compile de novo.
- Para testar sem digitar, mande a entrada pelo pipe. Exemplo: vetor de 100 itens aleatórios, abrir o comparativo (opção 7), confirmar, ENTER e sair (8):
  ```bash
  printf "100\n1\n7\n1\n\n8\n" | ./src/output/main.exe > saida.txt
  ```
  A última linha da saída deve ser `Memoria nao liberada: 0 bytes`.
- Testes caixa-branca (que incluem o `.c` para enxergar a struct) ficam **fora do repositório**: no scratchpad do Claude ou numa pasta temporária. Nunca deixe `#include "x.c"` no `src/`.
- Os algoritmos O(n²) (Bubble, Selection, Insertion, Quick com dados ordenados ou invertidos) levam vários segundos com N = 50.000, e o comparativo completo (opção 7) leva uns 3 minutos. Avise antes de rodar e, no Claude, rode em segundo plano.

### 5.5 Commitar
- Mensagem em **inglês**, no imperativo, citando a tarefa: `Add circular linked list with insertion and merge sort (T08)`.
- **Código e registros em commits separados:**
  1. o código da tarefa (`src/...`);
  2. depois, `Log AI prompts #NNN-#MMM and session note NN` (o `AI_LOG.md` + a nota de `contexto/memory/`).
- Quando o Claude escreve o commit, ele termina a mensagem com a linha `Co-Authored-By` que o próprio Claude Code indica. O Codex não usa essa linha.
- Nunca commitar `.exe` ou `.o` (já estão no `.gitignore`).
- Push só para a própria branch: `git push origin ESDD/<nome>`.

### 5.6 Levar para a `dev` (fluxo normal, com equipe)
1. Faça o push da sua `ESDD/<nome>`.
2. Abra um PR `ESDD/<nome>` → `dev` no GitHub (`gh pr create --base dev`).
3. Outro integrante revisa. Ele precisa conseguir explicar o código na arguição, porque o enunciado proíbe a "caixa-preta".
4. Faça o merge do PR.
5. Todos rodam `/atualizar-branch` para trazer a `dev` nova.
6. Marque a tarefa como concluída no quadro **e** no [contexto/TAREFAS.md](contexto/TAREFAS.md), **só depois da revisão**.

---

## 6. Registros obrigatórios

### 6.1 `AI_LOG.md`: registro de prompts (o enunciado exige)
- **Automático:** o hook `UserPromptSubmit` roda o mesmo [.claude/hooks/log_prompt.py](.claude/hooks/log_prompt.py) no Claude ([.claude/settings.json](.claude/settings.json)) e no Codex ([.codex/hooks.json](.codex/hooks.json)). A cada prompt, ele cria uma entrada `## #NNN — <Dia>, DD/MM/AAAA` com o autor (`git config user.name`), a ferramenta (`Claude Code` ou `Codex`) e o prompt literal. E-mails viram `[removido]`. O assistente recebe o aviso `[AI_LOG] Este prompt foi registrado automaticamente como #NNN`.
- **O que o assistente faz** (o texto diz "pelo Claude", mas vale também para o Codex): ao final da resposta, troca os três `_(a preencher pelo Claude ao final da resposta)_` da entrada #NNN por **Objetivo**, **Resposta da IA (resumo)** (o que foi feito, arquivos, commit) e **Adaptações / correções** (o que o usuário escolheu diferente da recomendação, o que foi corrigido, números medidos). Ele **não** cria outra entrada.
- Sem o aviso (hook desligado ou sem Python), o Claude cria a entrada à mão, no mesmo formato, antes do `---` que precede o bloco `<!-- MODELO ... -->`.
- Entradas antigas não se apagam nem se reescrevem. A única exceção é atualizar "Adaptações / correções" quando o usuário corrigir uma resposta anterior.
- **Filtros do hook (desde 18/11/2026):** ele tira do prompt os blocos injetados pelas extensões (`<browser_instruction>`, `<ide_opened_file>`, `<ide_selection>`, `<system-reminder>`). Os avisos automáticos (`<task-notification>` de tarefa em segundo plano, `<agent-message>` de subagente) não são registrados: o assistente recebe o aviso "não é um prompt do usuário" e não cria entrada. As entradas antigas com esses blocos (até a #059) ficaram como estavam.
- **Conflito de numeração entre branches:** se duas pessoas criarem entradas ao mesmo tempo, as duas branches terão, por exemplo, um `#050`. No merge, mantenha **as duas** entradas e renumere as que vieram da sua branch para continuar depois da última da `dev`. Essa é a única mudança permitida numa entrada antiga. Convenção ainda a confirmar com a equipe.

### 6.2 Notas de sessão: `contexto/memory/`
- No fim de cada sessão, rode **`/salvar-memoria`**. A skill cria (ou atualiza, se rodar de novo na mesma sessão) a nota `AAAA-MM-DD_sessao-NN_<assunto>.md`, com as seções *O que foi feito*, *Decisões / observações*, *Pendências* e *Próximos passos sugeridos*.
- A nota guarda o que **não** dá para tirar do código nem do git: por que cada decisão foi tomada, armadilhas, números medidos e combinados da equipe. É o material de estudo da arguição individual.
- Se dois integrantes criarem notas com o mesmo `sessao-NN` em branches diferentes, mantenha as duas e renumere a sua no merge (mesma convenção do AI_LOG).

---

## 7. Mapa rápido do código (`src/`)

| Módulo | O que faz |
|---|---|
| `main.c` | menu (cliente dos TADs): ordenar o vetor, mostrar, comparar todos, redimensionar, trocar o tipo dos dados, ordenar listas, comparativo vetor × listas |
| `memory.h/.c` | contador de bytes alocados (`mem_alloc`/`mem_realloc`/`mem_free`, `mem_current`, `mem_peak`) |
| `metrics.h/.c` | struct `Metrics` (nome, comparações, trocas, tempo, memória extra) e impressão do relatório |
| `vector.h/.c` | vetor dinâmico: criar, `realloc`, preencher (aleatório 1..N sem repetição, ordenado, invertido), destruir |
| `sort.h/.c` | 7 ordenações do vetor + tabela de algoritmos (`sort_name`, `sort_run`) |
| `search.h/.c` | busca sequencial |
| `singly_list.h/.c` | lista simplesmente encadeada + Insertion/Merge mexendo só nos ponteiros |
| `doubly_list.h/.c` | lista duplamente encadeada (`head` + `tail`) + Insertion/Merge |
| `circular_list.h/.c` | lista circular simples (só `tail`) + Insertion/Merge (abre o ciclo, ordena e fecha) |
| `benchmark.h/.c` | T09: comparativo vetor × listas, N = 1.000/10.000/50.000 nos 3 tipos de dados |

Material de referência: [contexto/codigo-exemplos/](contexto/codigo-exemplos/) (o estilo das aulas, que o código deve seguir) e `contexto/slides/` (um `.md` por PDF; leia esses em vez dos PDFs). A pasta `contexto/slides/` fica fora do git, só na cópia de cada integrante (veja a seção 1).

---

## 8. Checklist para o assistente (Claude ou Codex) no início de cada sessão

1. Confirmar a branch atual (`git branch --show-current`). Se for `main` ou `dev`, avisar o usuário antes de qualquer commit. Se a `ESDD/<nome>` do usuário ainda não existir, criá-la (seção 4.2).
2. Ler a nota de sessão mais recente em `contexto/memory/`.
3. Abrir o quadro e listar as tarefas abertas do usuário (caixa no topo deste guia).
4. Olhar o `git status` e o `git log --oneline -5` para ver o que não foi commitado (é comum o `AI_LOG.md` e a nota ficarem para um commit separado).
5. Responder sempre em português do Brasil. Código em inglês e `printf` em português sem acento.
6. A cada prompt com o aviso `[AI_LOG] ... #NNN`, preencher a entrada #NNN no fim da resposta.
7. Pedir confirmação antes de push, merge na `dev`/`main` ou qualquer ação difícil de desfazer, a menos que o usuário já tenha pedido.
8. No fim da sessão, sugerir o `/salvar-memoria` (no Codex, a skill `salvar-memoria`) e o commit dos registros.
