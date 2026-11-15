#include <stdio.h>
#include <stdlib.h>

int main() {
    int n = 5;
    int *vetor = (int *) malloc(n * sizeof(int));

    // Verificação de Segurança OBRIGATÓRIA
    if (vetor == NULL) {
        printf("Erro: Memória insuficiente!\n");
        return 1; 
    }

    // Uso do vetor alocado
    for(int i = 0; i < n; i++) {
        vetor[i] = (i + 1) * 10;
    }

    // exibe o vetor
   for(int i = 0; i < n; i++) {
        printf("\n %d ", *(vetor+i));
    }

    // Liberação e Boa Prática
    free(vetor);
    vetor = NULL; 

    return 0;
}