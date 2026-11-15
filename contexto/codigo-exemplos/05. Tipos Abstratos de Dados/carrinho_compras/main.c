#include <stdio.h>
#include "carrinho.h"

int main() {
    Carrinho* meu_carrinho = carrinho_criar();

    // Simulando o usuário adicionando produtos no site
    carrinho_adicionar(meu_carrinho, 101, 29.90); // Camiseta
    carrinho_adicionar(meu_carrinho, 202, 89.90); // Tenis

    printf("Total do Checkout: R$ %.2f\n", carrinho_calcular_total(meu_carrinho));

    carrinho_esvaziar(meu_carrinho);
    return 0;
}
