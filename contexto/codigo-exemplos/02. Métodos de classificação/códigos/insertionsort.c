#include <stdio.h>
#define TAM 10

void imprimirVetor(char mensagem[], int vetor[]);
void insertionSort(int numeros[]);

int main(){
    // declaração da variáveis composta e inicialização
    int numeros[TAM] = {32, 27, 64, 18, 95, 14, 90, 70, 60, 37};
    imprimirVetor("\n Vetor antes da ordencao: [", numeros );
    insertionSort( numeros );
    imprimirVetor( "\n Vetor depois da ordencao: [", numeros );
    return 0;
}

void imprimirVetor(char mensagem[], int vetor[]){
   printf("%s", mensagem);
   for(int i = 0; i < TAM; i++){
     printf("%d ", vetor[i]);
   }
   printf("]\n");
}

void insertionSort(int numeros[]) {
    for (int i = 1; i < TAM; i++) {
        int chave = numeros[i];
        int j = i - 1;

        // Desloca elementos maiores que a chave para abrir espaço
        while (j >= 0 && numeros[j] > chave) {
            numeros[j + 1] = numeros[j];
            j = j - 1;
        }
        numeros[j + 1] = chave; // Insere a chave na posição correta
    }
}

