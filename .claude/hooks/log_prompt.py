"""UserPromptSubmit hook: appends every user prompt to AI_LOG.md.

Claude Code (.claude/settings.json) and Codex (.codex/hooks.json) both run this
script each time a prompt is submitted. It receives the hook payload as JSON on
stdin, creates a numbered entry (weekday + date + author + tool + literal
prompt) in AI_LOG.md and tells the assistant which entry number it must
complete (objective, AI answer summary, adaptations).

Blocks injected by editor extensions (<browser_instruction>, <ide_opened_file>,
<ide_selection>, <system-reminder>) are removed from the prompt. Messages that
are not typed by the user (<task-notification>, <agent-message>) are not logged.

It never blocks the prompt: any error is swallowed and the script exits 0.
"""

import datetime
import json
import os
import re
import subprocess
import sys

WEEKDAYS_PT = [
    "Segunda-feira", "Terça-feira", "Quarta-feira", "Quinta-feira",
    "Sexta-feira", "Sábado", "Domingo",
]
TEMPLATE_MARKER = "<!--\nMODELO DE ENTRADA"
PENDING = "_(a preencher pelo Claude ao final da resposta)_"
EMAIL_RE = re.compile(r"[\w.+-]+@[\w-]+\.[\w.-]+")
INJECTED_BLOCK_RE = re.compile(
    r"<(browser_instruction|ide_opened_file|ide_selection|system-reminder)\b[^>]*>.*?</\1>",
    re.DOTALL,
)
AUTOMATIC_PREFIXES = ("<task-notification", "<agent-message")


def clean_prompt_text(prompt):
    """Remove the blocks injected by extensions, keeping only what the user typed."""
    return INJECTED_BLOCK_RE.sub("", prompt).strip()


def is_automatic_message(prompt):
    return prompt.startswith(AUTOMATIC_PREFIXES)


def find_project_dir(payload):
    """Claude Code sets CLAUDE_PROJECT_DIR; Codex only sends cwd, so use the git root."""
    env_dir = os.environ.get("CLAUDE_PROJECT_DIR")
    if env_dir:
        return env_dir
    cwd = payload.get("cwd") or os.getcwd()
    try:
        result = subprocess.run(
            ["git", "rev-parse", "--show-toplevel"], cwd=cwd,
            capture_output=True, text=True, encoding="utf-8", timeout=5,
        )
        root = result.stdout.strip()
        if result.returncode == 0 and root:
            return root
    except Exception:
        pass
    return cwd


def tool_name(payload):
    """Codex adds turn_id to the UserPromptSubmit payload; Claude Code does not."""
    return "Codex" if "turn_id" in payload else "Claude Code"


def send_context(message):
    sys.stdout.buffer.write(json.dumps({
        "hookSpecificOutput": {
            "hookEventName": "UserPromptSubmit",
            "additionalContext": message,
        }
    }, ensure_ascii=False).encode("utf-8"))


def git_author(project_dir):
    try:
        result = subprocess.run(
            ["git", "config", "user.name"], cwd=project_dir,
            capture_output=True, text=True, encoding="utf-8", timeout=5,
        )
        name = result.stdout.strip()
        return name if name else "desconhecido"
    except Exception:
        return "desconhecido"


def next_entry_number(content):
    numbers = [int(n) for n in re.findall(r"^## #(\d+)", content, re.MULTILINE)]
    return max(numbers, default=0) + 1


def build_entry(number, author, tool, prompt):
    today = datetime.date.today()
    title_date = f"{WEEKDAYS_PT[today.weekday()]}, {today.strftime('%d/%m/%Y')}"
    clean_prompt = EMAIL_RE.sub("[removido]", prompt)
    quoted = "\n".join(
        "  > " + line if line.strip() else "  >"
        for line in clean_prompt.splitlines()
    )
    return (
        f"## #{number:03d} — {title_date}\n\n"
        f"- **Autor:** {author}\n"
        f"- **Ferramenta:** {tool}\n"
        f"- **Prompt:**\n{quoted}\n"
        f"- **Objetivo:** {PENDING}\n"
        f"- **Resposta da IA (resumo):** {PENDING}\n"
        f"- **Adaptações / correções:** {PENDING}\n\n"
    )


def insert_entry(content, entry):
    """Insert the entry after the last one, before the '---' that precedes the template."""
    marker_pos = content.find(TEMPLATE_MARKER)
    if marker_pos == -1:
        return content.rstrip("\n") + "\n\n" + entry
    separator_pos = content.rfind("\n---\n", 0, marker_pos)
    insert_pos = separator_pos + 1 if separator_pos != -1 else marker_pos
    return content[:insert_pos] + entry + content[insert_pos:]


def main():
    payload = json.loads(sys.stdin.buffer.read().decode("utf-8"))
    prompt = clean_prompt_text(payload.get("prompt", ""))
    if not prompt:
        return

    if is_automatic_message(prompt):
        send_context(
            "[AI_LOG] Esta mensagem é um aviso automático (task-notification ou "
            "relatório de subagente), não um prompt do usuário: nada foi registrado "
            "e não é preciso criar entrada no AI_LOG.md."
        )
        return

    project_dir = find_project_dir(payload)
    log_path = os.path.join(project_dir, "AI_LOG.md")
    if not os.path.isfile(log_path):
        return

    with open(log_path, "r", encoding="utf-8") as f:
        content = f.read()

    number = next_entry_number(content)
    entry = build_entry(number, git_author(project_dir), tool_name(payload), prompt)

    with open(log_path, "w", encoding="utf-8", newline="\n") as f:
        f.write(insert_entry(content, entry))

    send_context(
        f"[AI_LOG] Este prompt foi registrado automaticamente como #{number:03d} em AI_LOG.md. "
        f"Ao final da resposta, preencha os campos Objetivo, Resposta da IA (resumo) e "
        f"Adaptações / correções da entrada #{number:03d} (não crie outra entrada)."
    )


if __name__ == "__main__":
    try:
        main()
    except Exception:
        pass
    sys.exit(0)
