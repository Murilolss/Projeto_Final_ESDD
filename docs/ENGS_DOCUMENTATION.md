# Data Structures and Algorithms Analysis Platform

**Software Engineering Documentation (ENGS)**

Integrated Final Project — Data Structures (ESDD), Web Interfaces, Software Engineering and English

Federal Institute of São Paulo (IFSP) — Araraquara Campus — 2nd semester of 2026

**Team members:**

- Murilo Leandro
- Lucas Cruz
- Liliane Perim Vigetta
- Matheus Miasaki

Repository: <https://github.com/Murilolss/Projeto_Final_ESDD>

Document version: 1.0 — 11/25/2026

<div style="page-break-after: always;"></div>

## Table of Contents

1. Introduction
2. System scope
3. Functional requirements
4. Non-functional requirements
5. System architecture
6. C program modules
7. Web interface
8. Data exchange formats
9. Design decisions
10. Version control and workflow
11. Task management
12. Use of generative AI
13. How to build and run
14. Known limitations and future work

<div style="page-break-after: always;"></div>

## 1. Introduction

The **Data Structures and Algorithms Analysis Platform** is a *benchmarking* and visualization system for data structures. Its core is a program written in the **C language** that sorts dynamically allocated arrays and linked lists, measures the performance of each algorithm (time, comparisons, swaps and memory) and exports every sorting step to a **JSON** file. A **Web** interface (HTML, CSS and JavaScript) reads this file and animates the sorting bars, and also displays comparison charts of the metrics.

This document covers the Software Engineering part required by the project assignment: the gathering of functional and non-functional requirements, the architecture documentation and the description of team version control with Git and GitHub.

### 1.1 Goals

- Compare, with measured numbers, sorting algorithms on a contiguous array and on three kinds of linked list.
- Make the inner workings of the algorithms visible, both in the console (step-by-step mode) and in the browser (animation).
- Put into practice the structures studied in the course: dynamic allocation, lists, stack and queue.

### 1.2 Target audience

Data Structures students and teachers who want to observe how sorting algorithms behave and compare the cost of each structure.

### 1.3 Glossary

| Term | Meaning |
|---|---|
| ADT | Abstract Data Type: a structure whose content is only accessed through the functions of its module |
| N | Number of elements in the array or list |
| Step | A comparison, swap or write performed by the algorithm while sorting |
| Step log | JSON file with the initial array, every step and the final array of one sort |
| Comparison report | JSON file with the metrics of every algorithm on the same array |
| Batch | A set of tests queued and run in sequence |
| Peak extra memory | Largest amount of *heap* memory the algorithm allocated beyond the array or list itself |

<div style="page-break-after: always;"></div>

## 2. System scope

**In scope:**

- Generation of arrays of a user-chosen size, with random (non-repeating), sorted or reversed data.
- Seven sorting algorithms on the array: Bubble Sort, Insertion Sort, iterative Merge Sort, recursive Merge Sort, Quick Sort with the pivot at the start, Quick Sort with the pivot at the end, and Selection Sort.
- Insertion Sort and Merge Sort on singly linked, doubly linked and circular lists, manipulating pointers only.
- Time, comparison, swap and memory metrics.
- Step-by-step mode in the console, with Undo (stack).
- Batch test queue.
- Export of the step log and of the metrics comparison report in JSON.
- Web interface to animate the log and display the comparison report.

**Out of scope:**

- Database persistence and network access: the program and the page work with local files.
- Native graphical interface (the Java Swing/JavaFX alternative was not adopted).
- CSV export (the assignment allows JSON **or** CSV; the team chose JSON).

**Planned (extra item of the assignment, not yet implemented):** Hash Table with separate chaining, indexed by algorithm name, to retrieve reports of previous tests (tasks T18 and T19).

<div style="page-break-after: always;"></div>

## 3. Functional requirements

Priority: **E** = essential (required by the assignment), **D** = desirable (improvement proposed by the team), **X** = extra item of the assignment.

### 3.1 Array and metrics

| ID | Requirement | Priority | Status |
|---|---|---|---|
| FR01 | The system shall ask for the size N and create the array with dynamic allocation (`malloc`). | E | Implemented |
| FR02 | The system shall fill the array with random non-repeating, sorted or reversed data, as chosen by the user. | D | Implemented |
| FR03 | The system shall allow the array size to be changed at run time, using `realloc`. | E | Implemented |
| FR04 | The system shall allow the data kind to be changed without recreating the array. | D | Implemented |
| FR05 | The system shall sort the array with any of the 7 algorithms, always on a copy, so that the original array remains available. | E | Implemented |
| FR06 | For each run, the system shall display time (ms), number of comparisons, number of swaps and peak extra memory (bytes). | E | Implemented |
| FR07 | The system shall run every algorithm on the same array and display a comparison table. | E | Implemented |
| FR08 | The system shall display the current array when the user asks for it. | D | Implemented |

### 3.2 Linked lists

| ID | Requirement | Priority | Status |
|---|---|---|---|
| FR09 | The system shall copy the array values into a singly linked, doubly linked or circular list. | E | Implemented |
| FR10 | The system shall sort each list with Insertion Sort and Merge Sort by changing only the node pointers, without copying values or allocating new nodes. | E | Implemented |
| FR11 | The system shall run an array × lists comparison for N = 1,000, 10,000 and 50,000, with the three data kinds, displaying time, comparisons, swaps, structure memory and extra memory. | E | Implemented |

### 3.3 Stack, queue and step-by-step mode

| ID | Requirement | Priority | Status |
|---|---|---|---|
| FR12 | The system shall offer a step-by-step mode in which the screen is redrawn at each sorting step and waits for the user. | E | Implemented |
| FR13 | In step-by-step mode, the user shall be able to choose whether the program also stops at comparisons or only at swaps and writes. | D | Implemented |
| FR14 | In step-by-step mode, the system shall record each swap and write on a **stack** and allow Undo (`u`), Redo (ENTER) and finishing the sort without pauses (`f`). | E | Implemented |
| FR15 | The system shall allow up to 10 tests (algorithm + size, with N up to 50,000) to be enqueued in a **queue** and run them in sequence, in the order they were entered. | E | Implemented |
| FR16 | The user shall be able to discard the batch before running it. | D | Implemented |

### 3.4 Export and Web interface

| ID | Requirement | Priority | Status |
|---|---|---|---|
| FR17 | The system shall export every comparison, swap and write of a sort to a JSON file, together with the initial array, the final array and the metrics. | E | Implemented |
| FR18 | The system shall refuse to export the step log when N > 1,000 and explain the reason to the user. | D | Implemented |
| FR19 | The system shall export the comparison table (FR07) to a JSON file. | D | Implemented |
| FR20 | The Web interface shall open a local step log and draw one bar per element, with height proportional to its value. | E | Implemented |
| FR21 | The Web interface shall animate the log with distinct colors for comparison (yellow), swap (red) and write (blue), and check the result against the final array (green). | E | Implemented |
| FR22 | The Web interface shall offer Play/Pause, step forward and back, Restart and five speeds. | D | Implemented |
| FR23 | The Web interface shall open the comparison report and display one bar chart per metric, grouped by structure, and a table with every metric. | D | Implemented |
| FR24 | The Web interface shall reject invalid files with a message, keeping the last valid visualization. | D | Implemented |

### 3.5 Extra

| ID | Requirement | Priority | Status |
|---|---|---|---|
| FR25 | The system shall store test reports in a Hash Table with separate chaining, using the algorithm name as the key. | X | Planned (T18) |
| FR26 | The user shall be able to look up, through the menu, the previous reports of an algorithm. | X | Planned (T19) |

<div style="page-break-after: always;"></div>

## 4. Non-functional requirements

| ID | Category | Requirement |
|---|---|---|
| NFR01 | Language | The core shall be written in C (C99 standard), compiled with gcc (MinGW) with no *warnings* under `-Wall -Wextra`. |
| NFR02 | Course standard | Each structure shall be an ADT in three files (`.h` with the opaque struct and the prototypes, `.c` with the implementation, `main.c` as the client), with *include guards*. |
| NFR03 | Robustness | Every `malloc`/`realloc` shall have its return value checked; all allocated memory shall be released with `free` and the pointer set to `NULL`. Functions that can fail return 1 (success) or 0 (failure). |
| NFR04 | Language of the code | Names, code comments and the `README.md` in English. Texts shown in the console in Portuguese without accents, because the Windows console does not display accents correctly. |
| NFR05 | Platform | The program shall run on Windows 11 from the project root. The Web interface shall work in current browsers, opening local files without a server. |
| NFR06 | Performance | The array × lists comparison shall run with N = 50,000 without stack overflow, even in the Quick Sort worst case. |
| NFR07 | Usability | Invalid menu input shall not terminate the program; the system shows a message and asks again. |
| NFR08 | File size | The step log is limited to N ≤ 1,000 (about 100 MB in the worst case). The Web viewer accepts logs of up to N = 100. |
| NFR09 | Accessibility | Charts shall not depend on color alone to tell structures apart; the structure is written in the title of each group. |
| NFR10 | Maintainability | The code shall be simple and didactic: each team member must be able to explain its inner workings in the oral examination. |
| NFR11 | Traceability | Every prompt sent to AI tools shall be recorded in `AI_LOG.md`. |

<div style="page-break-after: always;"></div>

## 5. System architecture

### 5.1 Overview

The system has two independent applications that communicate **through files**. The C program writes the JSON files to the `logs/` folder; the Web interface reads them through the browser's file picker. There is no direct call between the two parts.

```
+--------------------------------------------------+
|              C program (console)                 |
|                                                  |
|   main.c  (menu, reading user options)           |
|     |                                            |
|     +--> vector / sort / singly, doubly and      |
|     |    circular_list   (structures, sorting)   |
|     +--> benchmark       (array x lists)         |
|     +--> step_view + stack   (step by step,      |
|     |                         undo)              |
|     +--> queue           (batch tests)           |
|     +--> export          (writing the JSON)      |
|     |                                            |
|   metrics / memory  (measurements, used by all)  |
+-------------------------+------------------------+
                          |
                          |  writes
                          v
              +-----------------------+
              |     logs/ folder      |
              |  <algorithm>_n<N>_... |
              |  comparativo_n<N>_... |
              +-----------+-----------+
                          |
                          |  user opens the file
                          v
+--------------------------------------------------+
|             Web interface (browser)              |
|                                                  |
|   index.html + app.js        -> animation        |
|   comparativo.html + .js     -> charts           |
|   styles.css                 -> shared style     |
+--------------------------------------------------+
```

### 5.2 Layers of the C program

| Layer | Modules | Responsibility |
|---|---|---|
| Presentation | `main.c`, `step_view` | Menus, reading options, printing the tables and the step-by-step mode |
| Services | `benchmark`, `export`, `queue`, `stack` | Comparison, writing files, test batch, Undo history |
| Structures and algorithms | `vector`, `sort`, `singly_list`, `doubly_list`, `circular_list`, `search` | Data structures and sorting and searching algorithms |
| Infrastructure | `metrics`, `memory` | Metrics recording and the memory counter used by every module |

Each layer only uses the layers below it. The structure and algorithm modules do not `printf` menus or write files.

### 5.3 Observer pattern in the sorting algorithms

The same sorting algorithm serves three different uses: the *benchmark* (no interruptions), the step-by-step mode (draws the screen and waits for the user) and the export (writes one line per step). To avoid three copies of each algorithm, every sorting function receives a **function pointer** (`StepObserver`, defined in `sort.h`) and calls it after each comparison, swap or write:

```
sort (e.g. bubble_sort)
   |
   |  at each step: observer->function(kind, i, j, ..., context)
   v
+-----------------+-----------------+-------------------+
| NULL            | step_view_show  | export_step       |
| (benchmark:     | (redraws and    | (writes one line  |
|  nobody looks)  |  pushes swap)   |  to the JSON)     |
+-----------------+-----------------+-------------------+
```

When the user asks for step-by-step mode **and** export at the same time, `main.c` uses an intermediate function (`step_both`) that forwards the step to both observers. The algorithm does not know who is observing: it only receives a pointer and a `void *context`.

### 5.4 Algorithm table

The 7 array algorithms are stored in a table of function pointers (`SortFunction`) in `sort.c`, accessed by index with `sort_name(i)` and `sort_run(i, ...)`. Each list has a similar table with its 2 algorithms. This way the menu, the comparison, the batch and the export walk through the table instead of repeating a `case` block per algorithm, and a new algorithm is added in a single place.

### 5.5 Memory measurement

C does not report the size of an allocated block. For this reason every allocation in the project goes through `mem_alloc`, `mem_realloc` and `mem_free` (`memory.h`), which call the standard library functions and add or subtract the bytes from a global counter. Before each algorithm the program resets the peak (`mem_reset_peak`) and, at the end, reads `mem_peak()`: the difference is the algorithm's extra memory. The same counter detects leaks: the array × lists comparison prints any memory that was not released at the end.

### 5.6 Flow of a sort with export

```
User              main.c            sort.c            export.c        logs/
  | picks algorithm   |                 |                  |              |
  |------------------>|                 |                  |              |
  | "Export? Yes"     |                 |                  |              |
  |------------------>| export_open --------------------->| creates file |
  |                   |                 |                  |------------->|
  |                   | sort_run_steps->|                  |              |
  |                   |                 | export_step ---->| writes step  |
  |                   |                 | (at each step)   |------------->|
  |                   |<-- metrics -----|                  |              |
  |                   | export_close ---------------------->| final+metric|
  |<-- table and      |                 |                  |------------->|
  |    file name      |                 |                  |              |
```

<div style="page-break-after: always;"></div>

## 6. C program modules

All files are in `src/`. Each module has a `.h` (public contract) and a `.c` (implementation).

| Module | Structure / role | Key points |
|---|---|---|
| `memory` | Memory counter | Wraps `malloc`, `realloc` and `free`; keeps current and peak memory |
| `metrics` | `Metrics` (public struct) | Name, comparisons, swaps, time (ms) and memory; report and table printing |
| `vector` | Dynamic array of `int` | Creation, `realloc` to change the size, random fill (shuffle of 1..N), sorted and reversed |
| `sort` | 7 array algorithms | Function pointer table; step notification (`StepObserver`); Merge Sort with auxiliary arrays on the *heap*; Quick Sort recursing on the smaller side |
| `singly_list` | `SinglyList` (opaque): `head`, `size` | Nodes with `value` and `next`; Insertion and Merge Sort relinking `next` |
| `doubly_list` | `DoublyList` (opaque): `head`, `tail`, `size` | Nodes with `prev` and `next`; consistency rule `A->next == B` ⇒ `B->prev == A` |
| `circular_list` | `CircularList` (opaque): `tail`, `size` | The last node points to the first (`tail->next`); sorting opens the circle, sorts and closes it again |
| `benchmark` | Array × lists comparison | N = 1,000, 10,000 and 50,000; three data kinds; every algorithm on the same values |
| `stack` | `Stack` (opaque), dynamic array | `top` = next free position; grows with `realloc`; stores swaps and writes; Undo and Redo |
| `queue` | `Queue` (opaque), circular queue | `start` + `count` and index `% capacity`; each item is a `BatchTest` (algorithm + size) |
| `step_view` | Step-by-step mode | Horizontal bars in the console; arrays with more than 20 items only show the lines near the current step |
| `export` | `Exporter` (opaque) | Writes the step log and the comparison report in JSON; file name with date and time, never overwriting |
| `search` | Sequential search | Inherited from the initial prototype |
| `main.c` | Client | Main menu with 9 options and submenus |

### 6.1 Main menu

The menu texts are in Portuguese, as the program displays them, in the order they appear on screen:

| Option | Menu text | Translation |
|---|---|---|
| 1 | `Metodos de ordenacao` | Sorting methods |
| 2 | `Mostrar vetor` | Show array |
| 3 | `Comparar todos os algoritmos` | Compare all algorithms |
| 4 | `Alterar tamanho do vetor` | Change array size |
| 5 | `Alterar tipo dos dados` | Change data kind |
| 6 | `Ordenar listas encadeadas` | Sort linked lists |
| 7 | `Comparativo vetor x listas (N = 1000, 10000 e 50000)` | Array × lists comparison |
| 9 | `Fila de testes em lote` | Batch test queue |
| 8 | `Encerrar programa` | Exit program |

### 6.2 Memory cost per structure

Values measured with the reference compiler (MinGW GCC 6.3.0, 32 bits, 4-byte pointer):

| Structure | Bytes per element | Merge Sort extra memory |
|---|---|---|
| Array | 4 (`int`) | N × 4 bytes (auxiliary arrays) |
| Singly linked list | 8 (`int` + 1 pointer) | 0 (only relinks pointers) |
| Doubly linked list | 12 (`int` + 2 pointers) | 0 |
| Circular list | 8 (`int` + 1 pointer) | 0 |

<div style="page-break-after: always;"></div>

## 7. Web interface

Files in `web/`, written in plain HTML, CSS and JavaScript, with no external libraries.

| Page | Files | Role |
|---|---|---|
| Sorting viewer | `index.html`, `app.js` | Opens a step log and animates the bars |
| Metrics comparison | `comparativo.html`, `comparativo.js` | Opens a comparison report and shows a chart and a table |
| (shared) | `styles.css` | Style of both pages |

**Log playback.** The page does not receive the array at every step. It starts from the `initial` array and replays the steps in order: `swap` exchanges two heights, `write` changes the height of one bar and `compare` only highlights the bars. At the end, the replayed array is compared with the file's `final` array. To go back one step, the page rebuilds the array from `initial` up to the previous position; with N ≤ 100 this is instantaneous and avoids keeping an "undo" history in the browser.

**Speed.** Five settings, from 1 s to 16 ms per frame. At the fastest one, a log with more than 1,800 steps groups several steps per frame, so that the animation finishes in about 30 s.

**Comparison.** Buttons choose the metric (time, comparisons, swaps or extra memory). The bars are grouped by structure and drawn on the same scale, and the table highlights in bold the smallest value of each column. The page warns that times below about 10 ms show up as zero, because of the resolution of `clock()` on Windows.

**Validation.** Each page recognizes its own file type. If the user opens a comparison report in the viewer (or vice versa), the page points to the correct page. Files with invalid JSON, steps of an unknown type or positions outside the array are rejected with a message.

<div style="page-break-after: always;"></div>

## 8. Data exchange formats

### 8.1 Step log

Name: `logs/<algorithm>_n<N>_<YYYYMMDD>_<HHMMSS>.json`. If a file with the same name already exists, the program appends `_2`, `_3`, and so on.

```json
{
  "algorithm": "Bubble Sort",
  "data_kind": "Aleatorio",
  "size": 5,
  "initial": [3, 1, 5, 2, 4],
  "steps": [
    {"type": "compare", "i": 0, "j": 1, "value_i": 3, "value_j": 1},
    {"type": "swap", "i": 0, "j": 1},
    {"type": "write", "i": 2, "j": -1, "value": 4}
  ],
  "final": [1, 2, 3, 4, 5],
  "metrics": {"comparisons": 10, "swaps": 4,
              "time_ms": 0.0, "memory_bytes": 0}
}
```

| Step type | Fields | Effect on the animation |
|---|---|---|
| `compare` | `i`, `j`, `value_i`, `value_j` | Highlights the bars; the array does not change |
| `swap` | `i`, `j` | Swaps the heights of bars `i` and `j` |
| `write` | `i`, `j`, `value` | Bar `i` receives `value`; `j = -1` when the value came from outside the array |

**Why the N ≤ 1,000 limit.** The number of steps grows with N². Bubble Sort with N = 1,000 produces about 1.2 million steps (85 MB) with random data; with N = 10,000 it would be about 120 million steps (9 GB), too large to write and for the browser to open.

<div style="page-break-after: always;"></div>

### 8.2 Metrics comparison report

Name: `logs/comparativo_n<N>_<YYYYMMDD>_<HHMMSS>.json` (*comparativo* is Portuguese for "comparison"). It has no N limit, because it stores only one line per algorithm (13 in total: 7 for the array and 2 for each list).

```json
{
  "report": "comparativo",
  "data_kind": "Aleatorio",
  "size": 10000,
  "results": [
    {"algorithm": "Bubble Sort", "structure": "Vetor",
     "comparisons": 98860113, "swaps": 25050577,
     "time_ms": 333.000, "memory_bytes": 0}
  ]
}
```

The values of `data_kind` and `structure` are written in Portuguese, as the program displays them: `Aleatorio` (random), `Ordenado` (sorted), `Invertido` (reversed); `Vetor` (array), `Lista Simples`, `Lista Dupla`, `Lista Circular` (singly linked, doubly linked, circular list).

Generated files are not added to the repository (`.gitignore`). Two samples are kept under version control in `logs/` so that the interface can be tested without running the program.

<div style="page-break-after: always;"></div>

## 9. Design decisions

| # | Decision | Alternatives considered | Reason |
|---|---|---|---|
| D1 | Interface in plain HTML/CSS/JS | Java Swing/JavaFX; chart libraries | Opens directly in the browser, with no installation; the code stays explainable in the oral examination |
| D2 | Export in JSON | CSV | Steps have different fields depending on their type; JSON is read natively by JavaScript |
| D3 | Record only the steps, not the whole array at each step | A snapshot of the array per step | File N times smaller; the page replays the steps |
| D4 | Function pointer (`StepObserver`) in the algorithms | One copy of each algorithm per mode | A single algorithm serves the *benchmark*, step-by-step mode and export |
| D5 | Algorithm table | 7 repeated `case` blocks (prototype) | Less duplicated code; a new algorithm is added in a single place |
| D6 | Custom memory counter (`memory.h`) | External operating system tools | C does not report block sizes; the counter measures the peak of each algorithm and detects leaks |
| D7 | Quick Sort recursing on the smaller side | Increasing the gcc stack; limiting N | With sorted data and N = 50,000 the old version overflowed the stack; the new one limits the depth to log₂ N without changing the counts |
| D8 | Merge Sort with auxiliary arrays on the *heap* | Variable-length arrays (VLA) on the stack, as in the prototype | VLAs overflow the stack with large arrays |
| D9 | List sorting with pointers only | Copy to an array, sort and copy back | Required by the assignment; shows the real difference between the structures |
| D10 | Stack that stores swaps and writes, with Undo and Redo | Stack of swaps only | Insertion Sort and Merge Sort change the array by writing, not by swapping |
| D11 | Console texts without accents | Configuring the console code page | The Windows console garbles accents; the solution is the same on any machine |

<div style="page-break-after: always;"></div>

## 10. Version control and workflow

### 10.1 Branches

| Branch | Role |
|---|---|
| `main` | Production: delivery version |
| `dev` | Integration: receives the reviewed work of the team members |
| `ESDD/murilo`, `ESDD/lucas`, `ESDD/liliane` | Individual work of each team member |

```
ESDD/<member>  --commits-->  Pull Request  --review-->  dev  --stable-->  main
```

Rules agreed upon by the team:

1. Nobody commits directly to `main` or `dev`.
2. Each member works on their own branch and opens a *Pull Request* to `dev`.
3. A PR is only accepted after being reviewed by **another** member. Review comments are fixed on the same branch, before the *merge*.
4. Before starting a task, the member updates their branch with `dev` (`git pull origin dev`).
5. `dev` goes to `main` when it is stable, for delivery.

*Commit* messages in English, in the imperative mood and citing the task, for example: `Add circular linked list with insertion and merge sort (T08)`.

### 10.2 Pull Request history

| PR | Task | Author (branch) | *Merge* date |
|---|---|---|---|
| #1 | T12 — circular queue for batch tests | `ESDD/lucas` | 11/19/2026 |
| #2 | T26 + T10 — step-by-step mode and JSON log | `ESDD/liliane` | 11/21/2026 |
| #3 | Prompt log and task board update | `ESDD/murilo` | 11/23/2026 |
| #4 | T11 — Undo integrated into step-by-step mode | `ESDD/lucas` | 11/24/2026 |
| #5 | T13 + T14 — Web log viewer | `ESDD/lucas` | 11/24/2026 |
| #6 | Prompt log of the reviews | `ESDD/murilo` | 11/24/2026 |
| #7 | T15 — animation with distinct colors | `ESDD/liliane` | 11/24/2026 |
| #8 | T16 — playback controls | `ESDD/liliane` | 11/24/2026 |
| #9 | T17 — comparison export and page | `ESDD/liliane` | 11/25/2026 |

Phases 1 and 2 (array, metrics and lists, tasks T01 to T09 and T25) were done before *Pull Requests* were adopted and were integrated directly into `dev`.

<div style="page-break-after: always;"></div>

## 11. Task management

Tasks are kept on a board with owner, status and dependencies, mirrored in the repository file `contexto/TAREFAS.md`. A task is only marked as done after being reviewed by another member.

| Phase | Tasks | Owners | Status on 11/25/2026 |
|---|---|---|---|
| 1. Array and metrics | T01–T05, T25: refactoring the prototype into ADTs, fixing *bugs*, memory measurement, algorithm table, sorted and reversed data | Murilo | Done |
| 2. Lists | T06–T09: singly, doubly and circular lists with Insertion and Merge Sort; array × lists comparison | Murilo | Done |
| 3. Stack, queue and export | T26, T10, T11, T12: step-by-step mode, JSON export, Undo stack, batch queue | Liliane, Lucas | Done |
| 4. Visual interface | T13–T17: interface decision, log reading, animation, controls, comparison | Lucas, Liliane | Done (T17 under review) |
| 5. Extra: hash | T18–T19: hash table and report lookup | — | Pending |
| 6. Review | T20–T21: course standard and `AI_LOG.md` | — | Pending |
| 7. Tests and oral exam | T22–T24: edge cases, oral exam rehearsal, delivery (12/02/2026) | — | Pending |

### 11.1 Starting point

The project started from a handmade prototype (a sorting menu with metrics on an array). The first task was to refactor it, fixing the problems found:

- Inclusion of `.c` files instead of `.h`, which broke the ADT pattern.
- Names and comments in Portuguese (the assignment requires English).
- `srand()` never called, producing the same numbers on every run.
- Array filling that generated unique values and then overwrote them with repeated ones.
- Variable-length arrays in Merge Sort, causing stack overflow with large arrays.
- `malloc` return value not checked, and seven duplicated `case` blocks.
- No memory measurement, lists, stack, queue or export.

<div style="page-break-after: always;"></div>

## 12. Use of generative AI

The assignment allows and encourages the use of AI, with three rules: record the prompts, refactor the generated code to the course standard and explain the code in the individual oral examination. The team met these rules as follows:

- **Automatic logging.** A *hook* (`.claude/hooks/log_prompt.py`) records every prompt in `AI_LOG.md` with number, date, author and tool, and removes personal data such as e-mail addresses. At the end of each answer, the assistant fills in the goal, the summary of the answer and the adaptations made.
- **Tools.** Each member used the tool they preferred (Claude Code, Codex or Claude Web). The project rules are kept in a single file (`CLAUDE.md`), read by all of them, so that the generated code follows the same standard.
- **Against the "black box".** The rules require the style of the class examples (ADT in three files, 1/0 return values, `if (p == NULL)` after every `malloc`, `free` followed by `p = NULL`). All code was reviewed by another member in the *Pull Request*.
- **Session memory.** At the end of each work session, a note in `contexto/memory/` records what was done, the decisions and the pending items, which also serves as study material for the oral examination.

<div style="page-break-after: always;"></div>

## 13. How to build and run

**Requirements:** Windows 10 or 11, gcc (MinGW) on the PATH and a current browser.

**Build** (from the project root):

```
mkdir src\output
gcc -Wall -Wextra src/*.c -o src/output/main.exe
```

**Run** (also from the root, so that the `logs/` folder is found):

```
src\output\main.exe
```

The program asks for the array size and the data kind and opens the main menu.

**Viewing a log:**

1. In the menu, choose **1 - Metodos de ordenacao** (sorting methods) and an algorithm, and answer **Sim** (yes) to "Exportar log das comparacoes e trocas?" (export the log of comparisons and swaps?) (N ≤ 1,000; for the animation, N ≤ 100).
2. Open `web/index.html` in the browser.
3. Click **Abrir JSON** (open JSON) and select the file created in `logs/`.
4. Use **Reproduzir** (play), the step buttons and the speed control.

**Viewing the comparison report:** choose **3 - Comparar todos os algoritmos** (compare all algorithms), answer **Sim** to the export question and open the file `logs/comparativo_...json` in `web/comparativo.html` (the **Comparativo** link at the top of the page).

## 14. Known limitations and future work

- **Time resolution.** Time is measured with `clock()`, which on Windows advances in steps of about 10 ms. With a small N, almost every time shows up as zero; to compare times, N ≥ 10,000 is recommended.
- **Time in step-by-step mode and export.** In these modes the time includes the pauses and the file writing, so it is not suitable for comparing algorithms. The comparison report is used for that.
- **Log size.** Export limited to N ≤ 1,000 and animation to N ≤ 100 (section 8.1).
- **Hash Table.** The extra item of the assignment (FR25 and FR26) is planned in tasks T18 and T19.
- **CSV.** Only JSON export was implemented.
- **Automated tests.** Testing was manual, with edge cases (1-element array, sorted and reversed data, invalid files on the Web). Task T22 covers the systematic review of these cases.
