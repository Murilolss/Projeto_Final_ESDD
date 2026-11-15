#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct No {
    int dado;
    struct No *prox;
} No;

struct Lista {
    No *inicio;
};

Lista *criarLista(void) {
    Lista *lista = malloc(sizeof(Lista));

    if (lista == NULL) {
        return NULL;
    }

    lista->inicio = NULL;

    return lista;
}

int inserirInicio(Lista *lista, int valor) {
    if (lista == NULL) {
        return 0;
    }

    No *novo = malloc(sizeof(No));

    if (novo == NULL) {
        return 0;
    }

    novo->dado = valor;
    novo->prox = lista->inicio;
    lista->inicio = novo;

    return 1;
}

int inserirFim(Lista *lista, int valor) {
    if (lista == NULL) {
        return 0;
    }

    No *novo = malloc(sizeof(No));

    if (novo == NULL) {
        return 0;
    }

    novo->dado = valor;
    novo->prox = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        No *atual = lista->inicio;

        while (atual->prox != NULL) {
            atual = atual->prox;
        }

        atual->prox = novo;
    }

    return 1;
}

int buscar(Lista *lista, int valor) {
    if (lista == NULL) {
        return 0;
    }

    No *atual = lista->inicio;

    while (atual != NULL) {
        if (atual->dado == valor) {
            return 1;
        }

        atual = atual->prox;
    }

    return 0;
}

int remover(Lista *lista, int valor) {
    if (lista == NULL) {
        return 0;
    }

    No *atual = lista->inicio;
    No *anterior = NULL;

    while (atual != NULL && atual->dado != valor) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        return 0;
    }

    if (anterior == NULL) {
        lista->inicio = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);

    return 1;
}

void imprimir(Lista *lista) {
    if (lista == NULL) {
        return;
    }

    No *atual = lista->inicio;

    printf("Lista: ");

    while (atual != NULL) {
        printf("%d -> ", atual->dado);
        atual = atual->prox;
    }

    printf("NULL\n");
}

void destruirLista(Lista *lista) {
    if (lista == NULL) {
        return;
    }

    No *atual = lista->inicio;

    while (atual != NULL) {
        No *temp = atual;
        atual = atual->prox;
        free(temp);
    }

    free(lista);
}