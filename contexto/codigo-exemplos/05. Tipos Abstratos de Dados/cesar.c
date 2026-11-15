#include <stdio.h>
#include <string.h>

int main() {
    char texto[100];
    int chave, i;

    printf("Digite o texto a ser criptografado: ");
    fgets(texto, sizeof(texto), stdin);
    texto[strcspn(texto, "\n")] = '\0';

    printf("Digite o valor do deslocamento (chave): ");
    scanf("%d", &chave);

    // Garante que chaves grandes ou negativas fiquem no escopo de 0-25
    chave = (chave % 26 + 26) % 26;

    for (i = 0; texto[i] != '\0'; i++) {
        // Trata letras maiúsculas
        if (texto[i] >= 'A' && texto[i] <= 'Z') {
            texto[i] = ((texto[i] - 'A' + chave) % 26) + 'A';
        }
        // Trata letras minúsculas
        else if (texto[i] >= 'a' && texto[i] <= 'z') {
            texto[i] = ((texto[i] - 'a' + chave) % 26) + 'a';
        }
        // Números, espaços e pontuações permanecem inalterados
    }

    printf("Texto criptografado: %s\n", texto);
    return 0;
}