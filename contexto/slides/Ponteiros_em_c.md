# Ponteiros em linguagem C

> Fonte: `contexto/pdfs/Ponteiros_em_c.pdf` (set/2026)
> Código: `contexto/codigo-exemplos/04. Ponteiros e Alocação dinamica de memória/códigos/` (`ponteiro.c`, `exercicio_1.c`, `exercicio_2.c`, `exercicio_3.c`, `alocacao_vetor_dinamico.c`, `imc.c`)

## Analogia

A RAM é uma sequência gigante de "gavetas" numeradas. **Variável** guarda o conteúdo da gaveta; **ponteiro** guarda o número da gaveta (endereço). Base para arrays, strings, funções, structs e alocação dinâmica.

## Variável × endereço × ponteiro

- `x` → valor (42); `&x` → endereço de `x`; `p` → contém o endereço de `x`; `*p` → valor no endereço apontado.

```c
int x = 42;
int *p = &x;
printf("%d\n", x);          // 42
printf("%p\n", (void*)&x);
printf("%d\n", *p);         // 42
*p = 100;                   // altera x
printf("%d\n", x);          // 100
```

`&` obtém endereço · `*` (uso) = indireção · `*` (declaração) = declara ponteiro.

## Tipos importam

`int *`, `double *`, `char *` (strings), `struct Aluno *`, `void *` (genérico, exige cuidado).

## Ponteiros e funções (passagem por referência)

```c
void dobrar(int *n) { *n = *n * 2; }
int main(void) { int x = 10; dobrar(&x); printf("%d", x); } // 20
```

## Arrays e aritmética de ponteiros

- Nome do array = endereço do primeiro elemento.
- `p + 1` avança `sizeof(*p)` bytes.

```c
int v[] = {10, 20, 30, 40};
int *p = v;
printf("%d\n", *p);       // 10
printf("%d\n", *(p + 1)); // 20
printf("%d\n", p[2]);     // 30
```

## Ponteiros e strings

String = sequência de `char` terminada em `'\0'`. Percorrer com `while (*p != '\0') { putchar(*p); p++; }`. Não modificar memória não gravável (literais).

## NULL e ponteiros inválidos

- Inicialize ponteiros (`int *p = NULL;`) e cheque antes de desreferenciar.
- `int *q; *q = 10;` → **ERRADO** (não inicializado).

## Alocação dinâmica

```c
int *v = malloc(5 * sizeof *v);
if (v != NULL) {
    for (int i = 0; i < 5; i++) v[i] = i * 10;
}
free(v);
v = NULL;   // boa prática
```

- `malloc` solicita memória; `free` devolve. Após `free`, não usar o ponteiro.
- O enunciado do projeto pede também **`realloc`** (crescer/encolher vetor).

## Ponteiro para ponteiro

```c
int x = 42; int *p = &x; int **pp = &p;
printf("%d %d %d\n", x, *p, **pp);
```

## Erros clássicos

| Erro | Exemplo |
|---|---|
| Ponteiro não inicializado | `int *p; *p = 5;` |
| NULL desreferenciado | `int *p = NULL; *p;` |
| Use-after-free | `free(p); *p = 5;` |
| Buffer overflow | acessar além dos limites do array |
| Tipo incompatível | tratar endereço como outro tipo sem justificativa |
| Esquecer `free` | vazamento de memória (memory leak) |

## Depuração

- `printf("%p", (void*)p)` para imprimir endereços.
- Conferir `NULL` antes de desreferenciar.
- Ferramentas como **AddressSanitizer**.
- Perguntar sempre: **quem alocou? quem libera? por quanto tempo a memória é válida?**

## Computador × humano

| Expressão | Significado |
|---|---|
| `valor` | o número guardado lá |
| `&valor` | onde fica a gaveta de `valor` |
| `ptr` | o endereço que estou guardando |
| `&ptr` | onde fica a gaveta do próprio ponteiro |
| `*ptr` | vá até o endereço guardado e veja o valor |

## Exercícios

- Troca de dois valores: `void troca(int *a, int *b) { int temp = *a; *a = *b; *b = temp; }`
- (1) alterar variável por ponteiro; (2) percorrer array com ponteiro; (3) alocar e liberar vetor dinâmico.
- Estudo de código: `imc.c` — vetor de `struct tipoPessoa` (nome, peso, altura), cadastrar e exibir IMC.

## Relevância para o projeto

O enunciado exige substituir vetores estáticos por `malloc/realloc/free` e **medir consumo de memória** — ex.: contador global de bytes alocados/liberados via funções wrapper.
