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
const stepInfo = document.querySelector("#step-info");
const formatNumber = new Intl.NumberFormat("pt-BR");
const MAX_LOG_SIZE = 1000; /* same limit as EXPORT_MAX_SIZE in src/export.h */
const MAX_FRAMES = 1800;   /* T15: a long log applies several steps per frame */
const MAX_DURATION_MS = 30000; /* the animation of a log lasts about 30 s at most */
let latestRequest = 0; /* number of the last file read; older reads are ignored */
let currentLog = null; /* log on screen */
let barElements = [];  /* the .bar element of each index, filled by drawVector */
let scaleMax = 1;      /* value that fills the whole height of the plot */
let highlighted = [];  /* indices painted with the color of the current step */
let playback = null;   /* state of the animation while it runs (see playLog) */

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

/* Applies one step to array and to the bars. compare does not change the array. */
function applyStep(array, step) {
    if (step.type === "swap") {
        const aux = array[step.i];
        array[step.i] = array[step.j];
        array[step.j] = aux;
        setBarValue(step.i, array[step.i]);
        setBarValue(step.j, array[step.j]);
    } else if (step.type === "write") {
        array[step.i] = step.value;
        setBarValue(step.i, step.value);
    }
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

/* Starts the animation of currentLog from initial. Each frame applies stepsPerFrame steps
   (1 in small logs) and paints only the last one, so a long log still ends in about
   MAX_DURATION_MS. */
function playLog() {
    stopPlayback();
    drawVector(currentLog);
    const total = currentLog.steps.length;
    const stepsPerFrame = Math.max(1, Math.ceil(total / MAX_FRAMES));
    const frames = Math.max(1, Math.ceil(total / stepsPerFrame));
    playback = {
        array: currentLog.initial.slice(), /* copy: the log keeps its initial vector */
        next: 0,                           /* index of the next step to apply */
        stepsPerFrame,
        delay: Math.min(300, Math.max(16, Math.round(MAX_DURATION_MS / frames))),
        timer: 0
    };
    playButton.disabled = true;
    chartTitle.textContent = "Ordenando";
    playFrame();
}

function playFrame() {
    const steps = currentLog.steps;
    if (playback.next >= steps.length) {
        finishPlayback();
        return;
    }
    const end = Math.min(playback.next + playback.stepsPerFrame, steps.length);
    let step = null;
    while (playback.next < end) {
        step = steps[playback.next];
        applyStep(playback.array, step);
        playback.next++;
    }
    const text = showStep(playback.array, step);
    stepInfo.textContent = `Passo ${formatNumber.format(playback.next)} de ` +
                           `${formatNumber.format(steps.length)}: ${text}`;
    playback.timer = setTimeout(playFrame, playback.delay);
}

/* Last frame: checks the replayed vector against log.final. If they match, every bar turns
   green; if not (log cut short by a failure in C, or a bug), the user is warned. */
function finishPlayback() {
    const array = playback.array;
    const matches = array.every((value, index) => value === currentLog.final[index]);
    highlight([], "");
    stopPlayback();
    chartTitle.textContent = "Vetor final";
    if (matches) {
        for (const bar of barElements) bar.classList.add("sorted");
        stepInfo.textContent = `${formatNumber.format(currentLog.steps.length)} passos ` +
                               "reaplicados. O vetor bate com o final do log.";
    } else {
        stepInfo.textContent = "O vetor reaplicado não bate com o final do log " +
                               "(o log pode estar incompleto).";
    }
    playButton.textContent = "Reproduzir de novo";
}

/* Stops the animation, if it is running (new file chosen or end of the log). */
function stopPlayback() {
    if (playback !== null) {
        clearTimeout(playback.timer);
        playback = null;
    }
    playButton.disabled = false;
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
        stopPlayback();
        currentLog = log;
        drawVector(log);
        status.textContent = `Arquivo aberto: ${name}`;
        playButton.textContent = "Reproduzir";
        stepInfo.textContent = `${formatNumber.format(log.steps.length)} passos no log.`;
        playbackBox.hidden = false;
    } catch (error) {
        if (request !== latestRequest) return;
        status.classList.add("error");
        status.textContent = error.message;
    }
}

openButton.addEventListener("click", () => fileInput.click());
playButton.addEventListener("click", playLog);
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
