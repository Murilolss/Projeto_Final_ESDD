# Tabelas Hash (Tabela de Espalhamento)

> Fonte: `contexto/pdfs/8-TabelasHash.pdf` (12 slides, set/2026)
> Código: `contexto/codigo-exemplos/03. Tabelas hash/hash_enderecamento_aberto.c`

## Ideia

- As buscas vistas têm limite (binária = O(log n)).
- Tabela Hash permite busca em **tempo constante O(1)** (em média).
- Calcula-se o **endereço** do elemento com uma **função hash** e acessa-se diretamente.

## Função hash

- Transforma uma chave em um índice do vetor (tabela).
- **Modular hashing** (chaves inteiras positivas): `h(chave) = chave MOD m`, onde `m` = tamanho da tabela.
- Características esperadas: fácil de calcular; distribuir uniformemente as chaves; poucas colisões.
- **Colisão:** chaves diferentes geram o mesmo índice.

## Fator de carga

- `α = n / m` — `n` = elementos armazenados, `m` = posições da tabela.
- α baixo → poucas colisões, desperdício de memória.
- α alto → muitas colisões, busca mais lenta.

## Tratamento de colisões

### Encadeamento externo (separado) — **o que o enunciado pede no EXTRA**

- Cada posição da tabela guarda uma **lista encadeada** com todos os elementos que colidiram naquele índice.
- Busca: calcula o hash → percorre a lista daquela posição.
- (Diagrama do slide: chaves S,E,A,R,C,H,X,M,P,L com hash 0–4; cada `st[i]` aponta para uma lista `first → ...`.)

### Endereçamento aberto

- Todos os elementos ficam na própria tabela.
- Na colisão, procura a próxima posição livre seguindo uma **sequência de sondagem** (probing).
- **Sondagem linear:** incrementa o índice em 1 (circular).
- Busca: calcula hash → se a chave bate, achou; se posição vazia, não existe; senão, próxima posição.

```c
#define M 10
int tabela_hash[M];                       // -1 = vazio

int funcao_hash(int chave) { return chave % M; }

int inserir(int chave) {
    int indice = funcao_hash(chave);
    int tentativa = 0;
    while (tabela_hash[indice] != -1) {
        indice = (indice + 1) % M;
        tentativa++;
        if (tentativa == M) return 0;      // tabela cheia
    }
    tabela_hash[indice] = chave;
    return 1;
}

int buscar(int chave) {
    int indice = funcao_hash(chave);
    int tentativa = 0;
    while (tabela_hash[indice] != -1) {
        if (tabela_hash[indice] == chave) return indice;
        indice = (indice + 1) % M;
        if (++tentativa == M) break;
    }
    return -1;
}
```

## Relevância para o projeto (EXTRA)

- Chave = **nome do algoritmo** (string) → precisa de função hash para strings (ex.: somatório/polinomial dos caracteres `MOD m`).
- Cada bucket = lista encadeada de relatórios (`Metricas`) daquele algoritmo; permite recuperar testes anteriores.
