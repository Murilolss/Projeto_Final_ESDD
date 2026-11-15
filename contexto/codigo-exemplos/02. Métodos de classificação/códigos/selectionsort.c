#include <stdio.h>
#define TAM 10

void imprimirVetor(char mensagem[], int vetor[]);
void SelectionSort(int numeros[]);

int main(){
    // declaração da variáveis composta e inicialização
    int numeros[TAM] = {32, 27, 64, 18, 95, 14, 90, 70, 60, 37};
    imprimirVetor("\n Vetor antes da ordencao: [", numeros );
    SelectionSort( numeros );

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

void SelectionSort(int numeros[]){
    int i, j, posMenor, aux;
    for(i=0;i<TAM-1;i++){
        posMenor = i;
        for(j=i+1;j<TAM;j++){
            if(numeros[j]<numeros[posMenor])
                posMenor = j;
        }
        if(i!= posMenor){
            printf("\n Passo %d, troca %d por %d", i, numeros[i], numeros[posMenor] );
            aux=numeros[i];
            numeros[i]=numeros[posMenor];
            numeros[posMenor]=aux;
        }
    }
}

