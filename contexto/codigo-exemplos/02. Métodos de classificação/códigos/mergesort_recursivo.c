#include <stdio.h>

// Função para intercalar (mesclar) duas metades ordenadas
void intercalar(int vetor[], int esquerda, int meio, int direita) {
    int i, j, k;
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    // Vetores temporários para armazenar as duas metades
    int V_Esquerda[n1];
    int V_Direita[n2];

    // Copia os dados do vetor principal para os vetores temporários usando índices
    for (i = 0; i < n1; i++)
        V_Esquerda[i] = vetor[esquerda + i];
    for (j = 0; j < n2; j++)
        V_Direita[j] = vetor[meio + 1 + j];

    // Restaura os índices iniciais dos subvetores e do vetor principal
    i = 0; 
    j = 0; 
    k = esquerda; 

    // Intercala os elementos de volta no vetor original de forma ordenada
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

    // Copia os elementos restantes de V_Esquerda[], se houver
    while (i < n1) {
        vetor[k] = V_Esquerda[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de V_Direita[], se houver
    while (j < n2) {
        vetor[k] = V_Direita[j];
        j++;
        k++;
    }
}

// Função principal do Mergesort
void mergesort(int vetor[], int esquerda, int direita) {
    if (esquerda < direita) {
        // Encontra o ponto médio para dividir o vetor
        int meio = esquerda + (direita - esquerda) / 2;

        // Ordena a primeira e a segunda metade de forma recursiva
        mergesort(vetor, esquerda, meio);
        mergesort(vetor, meio + 1, direita);

        // Intercala as duas metades ordenadas
        intercalar(vetor, esquerda, meio, direita);
    }
}

// Função auxiliar para imprimir o vetor
void imprimirVetor(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++)
        printf("%d ", vetor[i]);
    printf("\n");
}

int main() {
    int vetor[] = {12, 11, 13, 5, 6, 8, 7};
    int n = 7;

    printf("Vetor original: \n");
    imprimirVetor(vetor, n);

    mergesort(vetor, 0, n - 1);

    printf("Vetor ordenado: \n");
    imprimirVetor(vetor, n);
    return 0;
}
