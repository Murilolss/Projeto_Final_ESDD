"use strict";

/* T17: comparison page. Reads the JSON written by export_report (src/export.c) after
   "Comparar todos os algoritmos" and shows one horizontal bar per algorithm for the
   chosen metric, grouped by structure (Vetor, Lista Simples, ...), plus a table with
   every metric. The format is described in contexto/formato_comparativo.md. */

const fileInput = document.querySelector("#report-file");
const openButton = document.querySelector("#open-report");
const exampleLink = document.querySelector("#example");
const status = document.querySelector("#status");
const source = document.querySelector("#source");
const count = document.querySelector("#count");
const reportBox = document.querySelector("#report");
const metricNote = document.querySelector("#metric-note");
const hbars = document.querySelector("#hbars");
const tableBody = document.querySelector("#table-body");
const tooltip = document.querySelector("#tooltip");
const formatNumber = new Intl.NumberFormat("pt-BR", { maximumFractionDigits: 3 });

/* The four metrics, in the order of the table. unit is written after the value. */
const METRICS = [
    { key: "time_ms", name: "Tempo", unit: " ms",
      note: "Tempo de execução em ms. O C mede com clock(), que no Windows avança de cerca " +
            "de 10 em 10 ms: tempos pequenos aparecem como 0. Use vetores grandes para comparar." },
    { key: "comparisons", name: "Comparações", unit: "",
      note: "Número de comparações entre elementos." },
    { key: "swaps", name: "Trocas", unit: "",
      note: "Número de trocas. Nas listas, conta os nós religados em outra posição " +
            "(nenhum valor é copiado)." },
    { key: "memory_bytes", name: "Memória extra", unit: " B",
      note: "Pico de memória extra alocada pelo algoritmo, em bytes, além do vetor ou da lista." }
];

let latestRequest = 0; /* number of the last file read; older reads are ignored */
let currentReport = null;

/* Converts the file text into the report object. Throws an Error with the message shown
   to the user if the file is not a comparison exported by the program. */
function parseReport(text) {
    let report;
    try {
        report = JSON.parse(text.replace(/^﻿/, ""));
    } catch {
        throw new Error("O arquivo não contém um JSON válido.");
    }

    if (report && Array.isArray(report.steps)) {
        throw new Error("Este arquivo é um log de passos. Abra-o na página Animação.");
    }
    if (!report || report.report !== "comparativo" || typeof report.data_kind !== "string" ||
        !Number.isInteger(report.size) || report.size < 1 ||
        !Array.isArray(report.results) || report.results.length === 0 ||
        !report.results.every(isValidResult)) {
        throw new Error("O JSON não corresponde a um comparativo exportado pelo programa.");
    }
    return report;
}

/* One result needs the names and the four metrics as numbers >= 0. */
function isValidResult(result) {
    return result !== null && typeof result === "object" &&
           typeof result.algorithm === "string" && typeof result.structure === "string" &&
           METRICS.every(metric => Number.isFinite(result[metric.key]) && result[metric.key] >= 0);
}

function formatValue(metric, value) {
    return formatNumber.format(value) + metric.unit;
}

function selectedMetric() {
    const key = document.querySelector('input[name="metric"]:checked').value;
    return METRICS.find(metric => metric.key === key);
}

/* Draws one group per structure, in the order they appear in the file. All bars share
   the same scale (the largest value of the metric), so groups can be compared. */
function drawChart(report, metric) {
    const max = Math.max(...report.results.map(result => result[metric.key]));
    const groups = new Map(); /* structure -> results of that structure */
    for (const result of report.results) {
        if (!groups.has(result.structure)) groups.set(result.structure, []);
        groups.get(result.structure).push(result);
    }

    const items = document.createDocumentFragment();
    for (const [structure, results] of groups) {
        const group = document.createElement("section");
        group.className = "hbar-group";
        const title = document.createElement("h3");
        title.textContent = structure;
        const list = document.createElement("ol");
        list.className = "hbar-list";

        for (const result of results) {
            const value = result[metric.key];
            const row = document.createElement("li");
            row.className = "hbar-row";
            row.tabIndex = 0; /* keyboard users get the tooltip with focus */
            row.setAttribute("aria-label",
                `${result.algorithm}, ${structure}: ${formatValue(metric, value)}`);

            const label = document.createElement("span");
            label.className = "hbar-label";
            label.textContent = result.algorithm;

            const track = document.createElement("div");
            track.className = "hbar-track";
            track.setAttribute("aria-hidden", "true");
            const bar = document.createElement("div");
            bar.className = "hbar";
            /* A value above 0 always gets at least a thin bar, so it is not confused with 0 */
            const width = max > 0 ? value / max * 100 : 0;
            bar.style.width = value > 0 ? `max(${width}%, 3px)` : "0";
            track.append(bar);

            const text = document.createElement("span");
            text.className = "hbar-value";
            text.textContent = formatValue(metric, value);

            row.append(label, track, text);
            addTooltip(row, result);
            list.append(row);
        }
        group.append(title, list);
        items.append(group);
    }
    hbars.replaceChildren(items);

    metricNote.textContent = max === 0
        ? `${metric.note} Todos os valores desta métrica são 0.`
        : metric.note;
}

/* Shows every metric of result while the mouse is over the row or the row has focus. */
function addTooltip(row, result) {
    const show = () => {
        const lines = METRICS.map(metric =>
            `<div><span>${metric.name}</span><strong>${formatValue(metric, result[metric.key])}</strong></div>`);
        tooltip.innerHTML = "";
        const heading = document.createElement("p");
        heading.className = "tooltip-title";
        heading.textContent = `${result.algorithm} · ${result.structure}`;
        tooltip.append(heading);
        tooltip.insertAdjacentHTML("beforeend", lines.join(""));
        tooltip.hidden = false;
        /* Below the row, starting where the bar starts, so the names stay visible */
        const box = row.getBoundingClientRect();
        const trackLeft = row.querySelector(".hbar-track").getBoundingClientRect().left;
        const left = Math.min(trackLeft + window.scrollX,
                              window.scrollX + document.documentElement.clientWidth - tooltip.offsetWidth - 8);
        tooltip.style.left = `${Math.max(8, left)}px`;
        tooltip.style.top = `${box.bottom + window.scrollY + 6}px`;
    };
    const hide = () => { tooltip.hidden = true; };
    row.addEventListener("mouseenter", show);
    row.addEventListener("focus", show);
    row.addEventListener("mouseleave", hide);
    row.addEventListener("blur", hide);
}

/* Table with every metric. The smallest value of each numeric column is in bold. */
function drawTable(report) {
    const minimums = {};
    for (const metric of METRICS) {
        minimums[metric.key] = Math.min(...report.results.map(result => result[metric.key]));
    }

    const rows = document.createDocumentFragment();
    for (const result of report.results) {
        const row = document.createElement("tr");
        const name = document.createElement("th");
        name.scope = "row";
        name.textContent = result.algorithm;
        const structure = document.createElement("td");
        structure.textContent = result.structure;
        row.append(name, structure);

        for (const metric of METRICS) {
            const cell = document.createElement("td");
            cell.className = "number";
            const value = result[metric.key];
            if (value === minimums[metric.key]) {
                const strong = document.createElement("strong");
                strong.textContent = formatNumber.format(value);
                cell.append(strong);
            } else {
                cell.textContent = formatNumber.format(value);
            }
            row.append(cell);
        }
        rows.append(row);
    }
    tableBody.replaceChildren(rows);
}

function drawReport(report) {
    const dataKind = report.data_kind === "Aleatorio" ? "Aleatório" : report.data_kind;
    source.textContent = `${dataKind} · N = ${formatNumber.format(report.size)}`;
    source.hidden = false;
    count.textContent = `${report.results.length} algoritmos`;
    count.hidden = false;
    drawChart(report, selectedMetric());
    drawTable(report);
    reportBox.hidden = false;
}

/* Same behavior as loadLog in app.js: a newer file wins, and on error the last valid
   report stays on screen with the message in the status line. */
async function loadReport(readText, name) {
    const request = ++latestRequest;
    status.classList.remove("error");
    status.textContent = `Lendo ${name}…`;

    try {
        const report = parseReport(await readText());
        if (request !== latestRequest) return;
        currentReport = report;
        drawReport(report);
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
    loadReport(() => file.text(), file.name);
    fileInput.value = "";
});
for (const input of document.querySelectorAll('input[name="metric"]')) {
    input.addEventListener("change", () => {
        if (currentReport !== null) drawChart(currentReport, selectedMetric());
    });
}

/* Opened from disk (file://) the browser blocks fetch, so the example link only downloads
   the file. Served over HTTP the same link loads the example directly. */
if (location.protocol === "http:" || location.protocol === "https:") {
    exampleLink.textContent = "Carregar exemplo";
    exampleLink.addEventListener("click", event => {
        event.preventDefault();
        const url = new URL(exampleLink.href);
        const name = url.pathname.split("/").pop();
        loadReport(async () => {
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
