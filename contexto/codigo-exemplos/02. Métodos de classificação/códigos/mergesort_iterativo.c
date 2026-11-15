#include <stdio.h>

// Função auxiliar para encontrar o menor entre dois números
int menor(int a, int b) {
    return (a < b) ? a : b;
}

// Função para intercalar (mesclar) duas partes adjacentes do vetor
void intercalar(int vetor[], int esquerda, int meio, int direita) {
    int i, j, k;
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    // Vetores temporários locais
    int V_Esquerda[n1];
    int V_Direita[n2];

    // Copia os dados usando apenas índices
    for (i = 0; i < n1; i++)
        V_Esquerda[i] = vetor[esquerda + i];
    for (j = 0; j < n2; j++)
        V_Direita[j] = vetor[meio + 1 + j];

    i = 0;
    j = 0;
    k = esquerda;

    // Junta as duas partes de forma ordenada no vetor original
    while (i < n1 && j < n2) {
        if (V_Esquerda[i] <= V_Direita[j]) {
            vetor[k] = V_Esquerda[i];
            i++;
        } else {
            vetor[k] = V_Direita[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes, se houver
    while (i < n1) {
        vetor[k] = V_Esquerda[i];
        i++;
        k++;
    }
    while (j < n2) {
        vetor[k] = V_Direita[j];
        j++;
        k++;
    }
}

// Função principal do Mergesort Iterativo (Sem Recursão)
void mergesortIterativo(int vetor[], int tamanho) {
    // tamanho_atual controla o tamanho dos subvetores que serão mesclados (1, 2, 4, 8...)
    for (int tamanho_atual = 1; tamanho_atual <= tamanho - 1; tamanho_atual = 2 * tamanho_atual) {
        
        // esquerda identifica o início do subvetor da esquerda que será mesclado
        for (int esquerda = 0; esquerda < tamanho - 1; esquerda += 2 * tamanho_atual) {
            
            // Encontra o ponto médio e o ponto final dos dois subvetores adjacentes
            int meio = menor(esquerda + tamanho_atual - 1, tamanho - 1);
            int direita = menor(esquerda + 2 * tamanho_atual - 1, tamanho - 1);

            // Junta as duas partes criadas
            intercalar(vetor, esquerda, meio, direita);
        }
    }
}

// Função auxiliar para imprimir o vetor
void imprimirVetor(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++)
        printf("%d ", vetor[i]);
    printf("\n");
}

int main() {
    int vetor[] = {12, 11, 13, 5, 6, 7, 2, 9};
    int n = sizeof(vetor) / sizeof(vetor[0]);

    printf("Vetor original: \n");
    imprimirVetor(vetor, n);

    mergesortIterativo(vetor, n);

    printf("Vetor ordenado: \n");
    imprimirVetor(vetor, n);
    return 0;
}
