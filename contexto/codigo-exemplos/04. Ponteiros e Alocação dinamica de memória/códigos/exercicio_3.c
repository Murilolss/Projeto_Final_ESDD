#include <stdio.h>
#include <stdlib.h> // Necessária para malloc e free

int main() {
    int tamanho = 5;
    int *vetor;

    // Aloca memória dinamicamente para 5 números inteiros
    vetor = (int *) malloc(tamanho * sizeof(int));

    // Verifica se a alocação foi bem-sucedida
    if (vetor == NULL) {
        printf("Erro: Memória insuficiente.\n");
        return 1; 
    }

    // Preenche o vetor dinâmico
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = (i + 1) * 100; // Guarda 100, 200, 300, 400, 500
    }

    // Exibe os valores
    printf("Valores no vetor alocado dinamicamente:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    // Libera a memória alocada para evitar vazamento de memória (memory leak)
    free(vetor);
    vetor = NULL; // Boa prática: limpa o ponteiro após liberar

    printf("Memoria liberada com sucesso.\n");

    return 0;
}
