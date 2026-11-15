#ifndef LISTA_H
#define LISTA_H

typedef struct Lista Lista;

Lista *criarLista(void);

int inserirInicio(Lista *lista, int valor);
int inserirFim(Lista *lista, int valor);

int buscar(Lista *lista, int valor);
int remover(Lista *lista, int valor);

void imprimir(Lista *lista);
void destruirLista(Lista *lista);

#endif