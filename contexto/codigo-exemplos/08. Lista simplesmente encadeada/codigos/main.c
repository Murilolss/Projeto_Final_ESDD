#include <stdio.h>
#include "lista.h"

int main() {

    Lista *lista = criarLista();

    if (lista == NULL) {
        printf("Erro ao criar lista!\n");
        return 1;
    }

    inserirInicio(lista, 20);
    inserirInicio(lista, 10);
    inserirFim(lista, 30);
    inserirFim(lista, 40);

    imprimir(lista);

    if (buscar(lista, 30)) {
        printf("Valor 30 encontrado!\n");
    } else {
        printf("Valor nao encontrado!\n");
    }

    remover(lista, 20);

    printf("Lista apos remocao:\n");
    imprimir(lista);

    destruirLista(lista);

    return 0;
}