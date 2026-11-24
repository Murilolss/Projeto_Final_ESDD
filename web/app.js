"use strict";

const fileInput = document.querySelector("#log-file");
const openButton = document.querySelector("#open-log");
const exampleLink = document.querySelector("#example");
const status = document.querySelector("#status");
const chart = document.querySelector("#chart");
const bars = document.querySelector("#bars");
const source = document.querySelector("#source");
const length = document.querySelector("#length");
const chartTitle = document.querySelector("#chart-title");
const playbackBox = document.querySelector("#playback");
const playButton = document.querySelector("#play");
const backButton = document.querySelector("#step-back");
const forwardButton = document.querySelector("#step-forward");
const resetButton = document.querySelector("#reset");
const speedInput = document.querySelector("#speed");
const speedName = document.querySelector("#speed-name");
const stepInfo = document.querySelector("#step-info");
const formatNumber = new Intl.NumberFormat("pt-BR");
const MAX_LOG_SIZE = 1000; /* same limit as EXPORT_MAX_SIZE in src/export.h */
const MAX_FRAMES = 1800;   /* T15: a long log applies several steps per frame */
/* T16: pause between frames (ms) and name of each position of the speed slider (1 to 5).
   At the fastest one a log takes about MAX_FRAMES * 16 ms = 30 s at most. */
const SPEED_DELAYS = [1000, 400, 150, 50, 16];
const SPEED_NAMES = ["Muito lenta", "Lenta", "Normal", "Rápida", "Muito rápida"];
let latestRequest = 0; /* number of the last file read; older reads are ignored */
let currentLog = null; /* log on screen */
let barElements = [];  /* the .bar element of each index, filled by drawVector */
let scaleMax = 1;      /* value that fills the whole height of the plot */
let highlighted = [];  /* indices painted with the color of the current step */
let sortedShown = false; /* true while the bars are green (end of the log checked) */
/* Replay of currentLog: position = number of steps already applied (0 = initial vector,
   steps.length = end), array = vector after those steps, timer = 0 when paused. */
let replay = { array: [], position: 0, timer: 0 };

/* Converts the file text into the log object written by src/export.c.
   Throws an Error with the message shown to the user if the file is not a valid log. */
function parseLog(text) {
    let log;
    try {
        log = JSON.parse(text.replace(/^\uFEFF/, ""));
    } catch {
        throw new Error("O arquivo não contém um JSON válido.");
    }

    if (!log || typeof log.algorithm !== "string" || typeof log.data_kind !== "string" ||
        !Number.isInteger(log.size) || log.size < 1 || log.size > MAX_LOG_SIZE ||
        !Array.isArray(log.initial) || log.initial.length !== log.size ||
        !log.initial.every(value => Number.isSafeInteger(value) && value > 0) ||
        !Array.isArray(log.steps) ||
        !Array.isArray(log.final) || log.final.length !== log.size) {
        throw new Error("O JSON não corresponde a um log de ordenação do projeto.");
    }
    const badStep = log.steps.findIndex(step => !isValidStep(step, log.size));
    if (badStep !== -1) {
        throw new Error(`O passo ${badStep + 1} do log é inválido (tipo ou posição fora do vetor).`);
    }
    return log;
}

/* Checks one step against contexto/formato_log.md: compare and swap need two positions
   inside the array; write needs a position, j = -1 or a position, and a positive value. */
function isValidStep(step, size) {
    const inArray = index => Number.isInteger(index) && index >= 0 && index < size;
    if (step === null || typeof step !== "object") return false;
    if (step.type === "compare" || step.type === "swap") {
        return inArray(step.i) && inArray(step.j);
    }
    if (step.type === "write") {
        return inArray(step.i) && (step.j === -1 || inArray(step.j)) &&
               Number.isSafeInteger(step.value) && step.value > 0;
    }
    return false;
}

/* Draws one bar per value of log.initial, in array order, with height proportional
   to the largest value. With more than 24 values (dense mode) the bars get thinner,
   the value labels are hidden and only every 10th index is shown. The animation (T15)
   changes these same bars through barElements. */
function drawVector(log) {
    const values = log.initial;
    const max = Math.max(...values);
    const dense = values.length > 24;
    const items = document.createDocumentFragment();

    scaleMax = max;
    barElements = [];
    highlighted = [];
    bars.classList.toggle("dense", dense);
    bars.style.minWidth = `${values.length * (dense ? 6 : 28)}px`;

    for (const [index, value] of values.entries()) {
        const item = document.createElement("li");
        const screenReaderLabel = document.createElement("span");
        screenReaderLabel.className = "sr-only";
        item.append(screenReaderLabel);

        const track = document.createElement("div");
        track.className = "bar-track";
        track.setAttribute("aria-hidden", "true");
        const bar = document.createElement("div");
        bar.className = "bar";

        if (!dense) {
            const label = document.createElement("span");
            label.className = "bar-value";
            bar.append(label);
        }

        track.append(bar);
        item.append(track);
        barElements.push(bar);
        setBarValue(index, value);

        if (!dense || index === 0 || index === values.length - 1 || index % 10 === 0) {
            const tick = document.createElement("span");
            tick.className = "bar-index";
            tick.textContent = index;
            tick.setAttribute("aria-hidden", "true");
            item.append(tick);
        }
        items.append(item);
    }

    bars.replaceChildren(items);
    bars.parentElement.scrollLeft = 0;
    document.querySelector("#scale-max").textContent = formatNumber.format(max);
    document.querySelector("#scale-mid").textContent = formatNumber.format(max / 2);
    const dataKind = log.data_kind === "Aleatorio" ? "Aleatório" : log.data_kind;
    source.textContent = `${log.algorithm} · ${dataKind}`;
    source.hidden = false;
    length.textContent = log.size === 1 ? "1 elemento" : `${formatNumber.format(log.size)} elementos`;
    length.hidden = false;
    chart.hidden = false;
    chartTitle.textContent = "Vetor inicial";
}

/* Gives the bar at index the height, label and description of value. Values above the
   scale (they should not exist: the scale is the largest value of initial) are capped. */
function setBarValue(index, value) {
    const bar = barElements[index];
    const ratio = Math.min(value / scaleMax, 1);
    const description = `Índice ${index}, valor ${value}`;
    const item = bar.closest("li");

    bar.style.setProperty("--height", `${ratio * 100}%`);
    const label = bar.querySelector(".bar-value");
    if (label) {
        label.textContent = formatNumber.format(value);
        bar.classList.toggle("short", ratio < 0.12);
    }
    item.title = description;
    item.querySelector(".sr-only").textContent = description;
}

/* Removes the step colors and paints the bars of indices with className. */
function highlight(indices, className) {
    for (const index of highlighted) {
        barElements[index].classList.remove("comparing", "swapping", "writing");
    }
    for (const index of indices) barElements[index].classList.add(className);
    highlighted = indices;
}

/* Changes array as step says and returns the indices that changed: none for compare,
   i and j for swap, i for write. The bars are redrawn by whoever called it. */
function applyStep(array, step) {
    if (step.type === "swap") {
        const aux = array[step.i];
        array[step.i] = array[step.j];
        array[step.j] = aux;
        return [step.i, step.j];
    }
    if (step.type === "write") {
        array[step.i] = step.value;
        return [step.i];
    }
    return [];
}

/* Paints the bars of step and returns the text that describes it. In compare, value_i and
   value_j are the values the algorithm compared, which are not always the bar heights
   (Insertion and Merge Sort, see contexto/formato_log.md). */
function showStep(array, step) {
    if (step.type === "compare") {
        highlight([step.i, step.j], "comparing");
        const a = Number.isSafeInteger(step.value_i) ? step.value_i : array[step.i];
        const b = Number.isSafeInteger(step.value_j) ? step.value_j : array[step.j];
        return `compara ${a} e ${b} (índices ${step.i} e ${step.j})`;
    }
    if (step.type === "swap") {
        highlight([step.i, step.j], "swapping");
        return `troca os índices ${step.i} e ${step.j}`;
    }
    highlight([step.i], "writing");
    const origin = step.j === -1 ? "de fora do vetor" : `do índice ${step.j}`;
    return `escreve ${step.value} no índice ${step.i} (valor vindo ${origin})`;
}

/* Turns the green of the end of the log on or off. */
function showSorted(on) {
    if (sortedShown === on) return;
    for (const bar of barElements) bar.classList.toggle("sorted", on);
    sortedShown = on;
}

/* Shows the screen of replay.position: the vector at the start, the last step applied in
   the middle, or the check against log.final at the end. If the replayed vector matches
   log.final every bar turns green; if not (log cut short by a failure in C, or a bug),
   the user is warned. */
function showPosition() {
    const total = currentLog.steps.length;
    highlight([], "");
    if (replay.position === total) {
        const matches = replay.array.every((value, index) => value === currentLog.final[index]);
        chartTitle.textContent = "Vetor final";
        showSorted(matches);
        if (matches) {
            stepInfo.textContent = `${formatNumber.format(total)} passos reaplicados. ` +
                                   "O vetor bate com o final do log.";
        } else {
            stepInfo.textContent = "O vetor reaplicado não bate com o final do log " +
                                   "(o log pode estar incompleto).";
        }
        return;
    }
    showSorted(false);
    if (replay.position === 0) {
        chartTitle.textContent = "Vetor inicial";
        stepInfo.textContent = `Passo 0 de ${formatNumber.format(total)}: vetor inicial.`;
        return;
    }
    chartTitle.textContent = "Ordenando";
    const text = showStep(replay.array, currentLog.steps[replay.position - 1]);
    stepInfo.textContent = `Passo ${formatNumber.format(replay.position)} de ` +
                           `${formatNumber.format(total)}: ${text}`;
}

/* Applies the next count steps (fewer at the end of the log), redraws only the bars that
   changed and shows the new position. */
function forward(count) {
    const steps = currentLog.steps;
    const end = Math.min(replay.position + count, steps.length);
    const changed = new Set();
    while (replay.position < end) {
        for (const index of applyStep(replay.array, steps[replay.position])) {
            changed.add(index);
        }
        replay.position++;
    }
    for (const index of changed) setBarValue(index, replay.array[index]);
    showPosition();
}

/* T16: goes back one step. The steps have no "undo", so the vector is rebuilt from
   initial applying the steps up to the previous position, and then all bars are redrawn
   once. */
function stepBack() {
    pauseReplay();
    if (replay.position === 0) return;
    const target = replay.position - 1;
    replay.array = currentLog.initial.slice();
    for (let k = 0; k < target; k++) applyStep(replay.array, currentLog.steps[k]);
    replay.position = target;
    for (let index = 0; index < replay.array.length; index++) {
        setBarValue(index, replay.array[index]);
    }
    showPosition();
    updateButtons();
}

/* T16: goes forward exactly one step, even in long logs. */
function stepForward() {
    pauseReplay();
    forward(1);
    updateButtons();
}

/* One frame of the animation. Each frame applies stepsPerFrame steps (1 in logs with up
   to MAX_FRAMES steps) and paints only the last one. The speed is read at every frame,
   so moving the slider changes an animation that is already running. */
function playFrame() {
    const total = currentLog.steps.length;
    forward(Math.max(1, Math.ceil(total / MAX_FRAMES)));
    if (replay.position >= total) {
        replay.timer = 0;
    } else {
        replay.timer = setTimeout(playFrame, SPEED_DELAYS[speedInput.value - 1]);
    }
    updateButtons();
}

/* The play button: pauses if running; at the end of the log starts again from initial;
   otherwise continues from the current position. */
function togglePlay() {
    if (replay.timer !== 0) {
        pauseReplay();
        return;
    }
    if (replay.position === currentLog.steps.length) resetReplay();
    playFrame();
}

/* Stops the timer of the animation, if it is running. The position is kept. */
function pauseReplay() {
    if (replay.timer !== 0) {
        clearTimeout(replay.timer);
        replay.timer = 0;
    }
    updateButtons();
}

/* T16: back to the initial vector of currentLog, paused. */
function resetReplay() {
    pauseReplay();
    drawVector(currentLog);
    sortedShown = false;
    replay.array = currentLog.initial.slice(); /* copy: the log keeps its initial vector */
    replay.position = 0;
    stepInfo.textContent = `${formatNumber.format(currentLog.steps.length)} passos no log.`;
    updateButtons();
}

/* Text of the play button and which buttons can be used at the current position. */
function updateButtons() {
    if (currentLog === null) return;
    const total = currentLog.steps.length;
    const running = replay.timer !== 0;

    if (running) {
        playButton.textContent = "Pausar";
    } else if (replay.position === total && total > 0) {
        playButton.textContent = "Reproduzir de novo";
    } else if (replay.position === 0) {
        playButton.textContent = "Reproduzir";
    } else {
        playButton.textContent = "Continuar";
    }
    backButton.disabled = replay.position === 0;
    forwardButton.disabled = replay.position === total;
    resetButton.disabled = replay.position === 0;
}

/* Shows the name of the speed chosen on the slider. */
function showSpeed() {
    speedName.textContent = SPEED_NAMES[speedInput.value - 1];
}

/* Reads a log with readText (file or fetch) and draws it. If another file was chosen
   while this one was being read, the result of this one is discarded. On error the
   last valid chart stays on screen and the message appears in the status line. */
async function loadLog(readText, name) {
    const request = ++latestRequest;
    status.classList.remove("error");
    status.textContent = `Lendo ${name}…`;

    try {
        const log = parseLog(await readText());
        if (request !== latestRequest) return;
        if (currentLog !== null) pauseReplay();
        currentLog = log;
        resetReplay();
        status.textContent = `Arquivo aberto: ${name}`;
        playbackBox.hidden = false;
    } catch (error) {
        if (request !== latestRequest) return;
        status.classList.add("error");
        status.textContent = error.message;
    }
}

openButton.addEventListener("click", () => fileInput.click());
playButton.addEventListener("click", togglePlay);
backButton.addEventListener("click", stepBack);
forwardButton.addEventListener("click", stepForward);
resetButton.addEventListener("click", resetReplay);
speedInput.addEventListener("input", showSpeed);
showSpeed();
fileInput.addEventListener("change", () => {
    const [file] = fileInput.files;
    if (!file) return;
    loadLog(() => file.text(), file.name);
    fileInput.value = "";
});

/* Opened from disk (file://) the browser blocks fetch, so the example link only downloads
   the file. Served over HTTP the same link loads the example directly. */
if (location.protocol === "http:" || location.protocol === "https:") {
    exampleLink.textContent = "Carregar exemplo";
    exampleLink.addEventListener("click", event => {
        event.preventDefault();
        const url = new URL(exampleLink.href);
        const name = url.pathname.split("/").pop();
        loadLog(async () => {
            try {
                const response = await fetch(url);
                if (!response.ok) throw new Error();
                return await response.text();
            } catch {
                throw new Error("Não foi possível abrir o exemplo. Selecione o JSON pela opção Abrir JSON.");
            }
        }, name);
    });
}
