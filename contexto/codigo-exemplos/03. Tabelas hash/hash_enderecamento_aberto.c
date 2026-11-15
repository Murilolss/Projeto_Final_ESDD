#include <stdio.h>

#define M 10        // Tamanho da tabela hash (m)

// Tabela Hash
int tabela_hash[M];

// Função para inicializar a tabela com valores vazios
void inicializar();
int funcao_hash(int chave);
int inserir(int chave);
int buscar(int chave);
void teste(int chave);
void imprimir(); 

int main() {
    inicializar(); // Inicializa a tabela hash

    // Inserindo elementos (com colisões propositais para teste)
    inserir(12); // 12 MOD 10 = índice 2
    inserir(22); // 22 MOD 10 = índice 2 -> Colisão! Vai para o índice 3
    inserir(42); // 42 MOD 10 = índice 2 -> Colisão! Vai para o índice 4
    inserir(15); // 15 MOD 10 = índice 5

    // Exibe a tabela atual em tela
    imprimir();

    // Testando as buscas
    teste(12);
    teste(22);
    teste(99);

    return 0;
}

// Função para inicializar a tabela com valores vazios
void inicializar() {
    for (int i = 0; i < M; i++) {
        tabela_hash[i] = -1;
    }
}

// Função Hash: h(chave) = chave MOD m
int funcao_hash(int chave) {
    return chave % M;
}

// Função para inserir um elemento usando Endereçamento Aberto (Sondagem Linear)
int inserir(int chave) {
    int indice = funcao_hash(chave);
    int tentativa = 0;

    // Procura a próxima posição livre incrementando o índice em 1 (circular com % M)
    while (tabela_hash[indice] != -1) {
        indice = (indice + 1) % M;
        tentativa++;

        // Se deu uma volta completa, a tabela está cheia
        if (tentativa == M) {
            printf("Erro: Tabela Hash cheia. Não foi possível inserir a chave %d.\n", chave);
            return 0; // Falha na inserção
        }
    }

    // Insere a chave na posição livre encontrada
    tabela_hash[indice] = chave;
    printf("Chave %d inserida com sucesso no índice %d.\n", chave, indice);
    return 1; // Sucesso
}

// Função para buscar um elemento na tabela
int buscar(int chave) {
    int indice = funcao_hash(chave);
    int tentativa = 0;

    // Percorre a tabela seguindo a sequência de sondagem
    while (tabela_hash[indice] != -1) {
        if (tabela_hash[indice] == chave) {
            return indice; // Elemento encontrado, retorna o índice
        }
        
        indice = (indice + 1) % M; // Verifica a próxima posição
        tentativa++;

        if (tentativa == M) {
            break; // Já buscou em todas as posições possíveis
        }
    }

    return -1; // Elemento não existe na tabela
}

// Função auxiliar para imprimir o estado atual da tabela
void imprimir() {
    printf("\n--- ESTADO DA TABELA HASH ---\n");
    for (int i = 0; i < M; i++) {
        printf("Posição [%d]: %d\n", i, tabela_hash[i]);
    }
    printf("-----------------------------\n\n");
}

void teste(int chave){
    int resultado = buscar(chave);
    if (resultado != -1) {
        printf("Chave %d encontrada no índice %d.\n", chave, resultado);
    } else {
        printf("Chave %d não encontrada.\n", chave);
    }
}