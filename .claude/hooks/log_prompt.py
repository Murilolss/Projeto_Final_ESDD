"""UserPromptSubmit hook: appends every user prompt to AI_LOG.md.

Claude Code runs this script each time a prompt is submitted. It receives the
hook payload as JSON on stdin, creates a numbered entry (weekday + date +
author + literal prompt) in AI_LOG.md and tells Claude which entry number it
must complete (objective, AI answer summary, adaptations).

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


def build_entry(number, author, prompt):
    today = datetime.date.today()
    title_date = f"{WEEKDAYS_PT[today.weekday()]}, {today.strftime('%d/%m/%Y')}"
    clean_prompt = EMAIL_RE.sub("[removido]", prompt.strip())
    quoted = "\n".join(
        "  > " + line if line.strip() else "  >"
        for line in clean_prompt.splitlines()
    )
    return (
        f"## #{number:03d} — {title_date}\n\n"
        f"- **Autor:** {author}\n"
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
    prompt = payload.get("prompt", "")
    if not prompt.strip():
        return

    project_dir = os.environ.get("CLAUDE_PROJECT_DIR") or payload.get("cwd") or os.getcwd()
    log_path = os.path.join(project_dir, "AI_LOG.md")
    if not os.path.isfile(log_path):
        return

    with open(log_path, "r", encoding="utf-8") as f:
        content = f.read()

    number = next_entry_number(content)
    entry = build_entry(number, git_author(project_dir), prompt)

    with open(log_path, "w", encoding="utf-8", newline="\n") as f:
        f.write(insert_entry(content, entry))

    message = (
        f"[AI_LOG] Este prompt foi registrado automaticamente como #{number:03d} em AI_LOG.md. "
        f"Ao final da resposta, preencha os campos Objetivo, Resposta da IA (resumo) e "
        f"Adaptações / correções da entrada #{number:03d} (não crie outra entrada)."
    )
    sys.stdout.buffer.write(json.dumps({
        "hookSpecificOutput": {
            "hookEventName": "UserPromptSubmit",
            "additionalContext": message,
        }
    }, ensure_ascii=False).encode("utf-8"))


if __name__ == "__main__":
    try:
        main()
    except Exception:
        pass
    sys.exit(0)
