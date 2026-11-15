#include <stdio.h>

void entregarTroco(int valor_saque) {
    // Caso base: o valor restante não dá para uma nota de 50
    if (valor_saque < 50) {
        if (valor_saque > 0) {
            printf("Restou R$ %d (Procure um caixa com notas menores).\n", valor_saque);
        }
        return;
    }

    // Ação: entrega uma nota
    printf("Entregando 1 nota de R$ 50\n");

    // Passo recursivo: subtrai 50 do total e chama a função novamente
    entregarTroco(valor_saque - 50);
}

int main() {
    int valor = 230;
    printf("--- Saque de R$ %d ---\n", valor);
    entregarTroco(valor);
    return 0;
}