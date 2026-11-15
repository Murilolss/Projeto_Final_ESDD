#include <stdio.h>

int main() {
    int numero = 10;
    int *ponteiro = &numero; // O ponteiro recebe o endereço da variável numero

    printf("Valor original: %d\n", numero);

    *ponteiro = 42; // Modifica o valor na memória apontada

    printf("Valor alterado por ponteiro: %d \n", numero);

    return 0;
}
