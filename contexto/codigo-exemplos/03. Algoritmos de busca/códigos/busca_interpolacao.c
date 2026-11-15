#include <stdio.h>
#define TAM 10

int buscaInterpolacao(int v[], int chave);

int main() {
    // Vetor ordenado e uniformemente distribuído
    int vetor[TAM] = {14, 18, 27, 32, 37, 60, 64, 70, 90, 95};
    int chave = 90;
    int posicao = buscaInterpolacao(vetor, chave);
    if (posicao != -1) {
        printf("\n Elemento %d encontrado na posicao: %d\n", chave, posicao);
    } else {
        printf("\n Elemento %d nao encontrado no vetor.\n", chave);
    }
    return 0;
}

// Função que implementa a Busca por Interpolação
int buscaInterpolacao(int v[], int chave) {
    int ini = 0, fim = TAM - 1, meio;

    // O valor procurado deve estar entre os limites do vetor
    while (ini <= fim && chave >= v[ini] && chave <= v[fim]) {
       
        // Aplicação da fórmula de interpolação
        meio = ini + ((fim-ini)*(chave-v[ini])) / (v[fim]-v[ini]);

        if(v[meio]==chave) return meio; // se achei o número, retorno o valor de meio
		if(v[meio]<chave) ini=meio+1; // se o número está na frente, olho para a metade depois de meio
		if(v[meio]>chave) fim=meio-1; // se o número está atrás, olho para a metade antes de meio
    }
    return -1; // Elemento não encontrado
}
