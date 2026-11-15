#include <stdio.h>
#define TAM 10

void imprimirVetor(char mensagem[], int vetor[]);
void QuickSort(int numeros[], int inicio, int fim);
int particionar(int vetor[], int inicio, int fim);

int main(){
    // declaração da variáveis composta e inicialização
    int numeros[TAM] = {32, 27, 64, 18, 95, 14, 90, 70, 60, 37};
    imprimirVetor("\n Vetor antes da ordencao: [", numeros );
    QuickSort( numeros, 0, TAM-1 );

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

void QuickSort(int numeros[], int inicio, int fim){
    if (inicio < fim) {
        int pivo = particionar(numeros, inicio, fim);
        QuickSort(numeros, inicio, pivo - 1);
        QuickSort(numeros, pivo + 1, fim);
    }
}

// Função de particionamento usando apenas índices do vetor
int particionar(int vetor[], int inicio, int fim) {
    int pivo = vetor[fim];
    int i = (inicio - 1);

    for (int j = inicio; j <= fim - 1; j++) {
        if (vetor[j] < pivo) {
            i++;
            // Troca direta usando uma variável temporária e índices
            int temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
        }
    }
    // Troca o pivovô para a posição correta
    int temp = vetor[i + 1];
    vetor[i + 1] = vetor[fim];
    vetor[fim] = temp;

    return (i + 1);
}
