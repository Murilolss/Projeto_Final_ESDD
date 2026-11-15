#include <stdio.h>

void contarPaginas(int pagina_atual, int pagina_final) {
    // Caso base: chegou na última página
    if (pagina_atual > pagina_final) {
        printf("Fim do livro! Leitura concluida.\n");
        return; 
    }

    // Ação: lê e exibe a página atual
    printf("Lendo a pagina %d...\n", pagina_atual);

    // Passo recursivo: avança para a próxima página
    contarPaginas(pagina_atual + 1, pagina_final);
}

int main() {
    int inicio = 1, fim = 5;
    printf("--- Iniciando Leitura ---\n");
    contarPaginas(inicio, fim);
    return 0;
}