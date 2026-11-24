"use strict";

const fileInput = document.querySelector("#log-file");
const openButton = document.querySelector("#open-log");
const exampleLink = document.querySelector("#example");
const status = document.querySelector("#status");
const chart = document.querySelector("#chart");
const bars = document.querySelector("#bars");
const source = document.querySelector("#source");
const length = document.querySelector("#length");
const formatNumber = new Intl.NumberFormat("pt-BR");
let latestRequest = 0;

function parseLog(text) {
    let log;
    try {
        log = JSON.parse(text.replace(/^\uFEFF/, ""));
    } catch {
        throw new Error("O arquivo não contém um JSON válido.");
    }

    if (!log || typeof log.algorithm !== "string" || typeof log.data_kind !== "string" ||
        !Number.isInteger(log.size) || log.size < 1 || log.size > 1000 ||
        !Array.isArray(log.initial) || log.initial.length !== log.size ||
        !log.initial.every(value => Number.isSafeInteger(value) && value > 0) ||
        !Array.isArray(log.steps)) {
        throw new Error("O JSON não corresponde a um log de ordenação do projeto.");
    }
    return log;
}

function drawVector(log) {
    const values = log.initial;
    const max = Math.max(...values);
    const dense = values.length > 24;
    const items = document.createDocumentFragment();

    bars.classList.toggle("dense", dense);
    bars.style.minWidth = `${values.length * (dense ? 6 : 28)}px`;

    for (const [index, value] of values.entries()) {
        const item = document.createElement("li");
        const description = `Índice ${index}, valor ${value}`;
        item.title = description;

        const screenReaderLabel = document.createElement("span");
        screenReaderLabel.className = "sr-only";
        screenReaderLabel.textContent = description;
        item.append(screenReaderLabel);

        const track = document.createElement("div");
        track.className = "bar-track";
        track.setAttribute("aria-hidden", "true");
        const bar = document.createElement("div");
        bar.className = "bar";
        bar.style.setProperty("--height", `${value / max * 100}%`);

        if (!dense) {
            if (value / max < 0.12) bar.classList.add("short");
            const label = document.createElement("span");
            label.className = "bar-value";
            label.textContent = formatNumber.format(value);
            bar.append(label);
        }

        track.append(bar);
        item.append(track);

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
}

async function loadLog(readText, name) {
    const request = ++latestRequest;
    status.classList.remove("error");
    status.textContent = `Lendo ${name}…`;

    try {
        const log = parseLog(await readText());
        if (request !== latestRequest) return;
        drawVector(log);
        status.textContent = `Arquivo aberto: ${name}`;
    } catch (error) {
        if (request !== latestRequest) return;
        status.classList.add("error");
        status.textContent = error.message;
    }
}

openButton.addEventListener("click", () => fileInput.click());
fileInput.addEventListener("change", () => {
    const [file] = fileInput.files;
    if (!file) return;
    loadLog(() => file.text(), file.name);
    fileInput.value = "";
});

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
