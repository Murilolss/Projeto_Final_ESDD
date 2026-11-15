#ifndef CARRINHO_H
#define CARRINHO_H

typedef struct item Item;
typedef struct carrinho Carrinho;

Carrinho* carrinho_criar();
void carrinho_adicionar(Carrinho* c, int id, float preco);
float carrinho_calcular_total(Carrinho* c);
void carrinho_esvaziar(Carrinho* c);

#endif
