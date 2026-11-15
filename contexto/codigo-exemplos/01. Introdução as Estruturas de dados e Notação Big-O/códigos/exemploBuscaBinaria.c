#include <stdio.h>

// Retorna o índice do elemento se encontrado, ou -1 caso não exista no array.
int busca_binaria(int arr[], int tamanho, int alvo) {
    int inicio = 0;
    int fim = tamanho - 1;

    // Enquanto o espaço de busca contiver pelo menos um elemento
    while (inicio <= fim) {
        // Calcula o ponto médio para dividir o array ao meio
        int meio = inicio + (fim - inicio) / 2;

        // Caso Perfeito: O elemento está exatamente no meio
        if (arr[meio] == alvo) {
            return meio; 
        }

        // Se o alvo for menor que o elemento do meio, descarta a metade direita
        if (alvo < arr[meio]) {
            fim = meio - 1;
        } 
        // Se o alvo for maior, descarta a metade esquerda
        else {
            inicio = meio + 1;
        }
    }

    // Elemento não foi encontrado no array
    return -1;
}

int main() {
    // Array obrigatoriamente ORDENADO
    int dados[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int n = sizeof(dados) / sizeof(dados[0]);
    int elemento_procurado = 23;

    int resultado = busca_binaria(dados, n, elemento_procurado);

    if (resultado != -1) {
        printf("Elemento %d encontrado no indice: %d\n", elemento_procurado, resultado);
    } else {
        printf("Elemento %d nao encontrado no array.\n", elemento_procurado);
    }

    return 0;
}
