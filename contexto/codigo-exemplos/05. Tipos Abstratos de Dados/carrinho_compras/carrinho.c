#include <stdlib.h>
#include "carrinho.h"

#define MAX_ITENS 100

struct item {
    int id_produto;
    float preco;
};

struct carrinho {
    Item itens[MAX_ITENS];
    int qtd_atual;
};

Carrinho* carrinho_criar() {
    Carrinho* c = (Carrinho*) malloc(sizeof(Carrinho));
    if (c != NULL) {
        c->qtd_atual = 0;
    }
    return c;
}

void carrinho_adicionar(Carrinho* c, int id, float preco) {
    if (c->qtd_atual < MAX_ITENS) {
        c->itens[c->qtd_atual].id_produto = id;
        c->itens[c->qtd_atual].preco = preco;
        c->qtd_atual++;
    }
}

float carrinho_calcular_total(Carrinho* c) {
    float total = 0.0;
    for (int i = 0; i < c->qtd_atual; i++) {
        total += c->itens[i].preco;
    }
    return total;
}

void carrinho_esvaziar(Carrinho* c) {
    free(c);
}
