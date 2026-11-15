#include <stdio.h>
#define TAM 10

int buscaSequencial(int numeros[], int x);

int main(){
    // declaração da variáveis composta e inicialização
    int vetor[TAM] = {32, 27, 64, 18, 95, 14, 90, 70, 60, 37};
    int chave = 90;
    int posicao = buscaSequencial(vetor, chave);
    if(posicao == -1)
       printf("Valor nao encontrado");
    else
       printf("Valor encontrado na posicao %d", posicao+1);
    return 0;
}

int buscaSequencial(int v[], int chave){
    int i = 0;
    while ((v[i] != chave) && (i < TAM))
        i = i + 1;
    if (i < TAM)
        return i;
    else
        return -1;
}