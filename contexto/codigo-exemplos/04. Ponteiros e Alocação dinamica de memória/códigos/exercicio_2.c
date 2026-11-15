#include <stdio.h>

int main() {
    int array[5] = {10, 20, 30, 40, 50};
    int *ponteiro = array; // Aponta para o primeiro elemento do array

    printf("Elementos do array percorridos por ponteiro:\n");
    for (int i = 0; i < 5; i++) {
        printf("Elemento %d: %d\n", i, *ponteiro);
        ponteiro++; // Avança para o próximo endereço de memória do tipo int
    }

    return 0;
}