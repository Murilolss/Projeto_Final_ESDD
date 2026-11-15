#include <stdio.h>

void monitorarBateria(int porcentagem_bateria) {
    // Caso base: bateria zerada
    if (porcentagem_bateria <= 0) {
        printf("Bateria: 0%% - Celular desligado!\n");
        return;
    }

    // Ação: mostra o status atual
    printf("Bateria atual: %d%%\n", porcentagem_bateria);

    // Passo recursivo: reduz 10% e avança "1 hora" no tempo
    monitorarBateria(porcentagem_bateria - 10);
}

int main() {
    int bateria_inicial = 40;
    printf("--- Monitor de Bateria ---\n");
    monitorarBateria(bateria_inicial);
    return 0;
}