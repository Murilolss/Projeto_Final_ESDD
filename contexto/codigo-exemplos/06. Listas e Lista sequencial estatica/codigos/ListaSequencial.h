#ifndef LISTASEQUENCIAL_H_INCLUDED
    #define LISTASEQUENCIAL_H_INCLUDED
#endif 
#define MAX 5

typedef struct aluno{
    int matricula;
    char nome[40];
    float n1, n2, n3;
} Aluno;

typedef struct lista{ //definicao da lista
    int prox;
    Aluno alunos[MAX];//MAX posicoes no vetor
} Lista;

Lista* criaLista();

int insereFinal(Lista* list, Aluno al);

int insereInicio(Lista* list, Aluno al);

int insereOrdenada(Lista* list, Aluno al);

int removeMatricula(Lista* list, int mat);

int removeInicio(Lista* list);

int removeFinal(Lista* list);

int consultaPosicao(Lista* list, int pos, Aluno *estudante);

int consultaMatricula(Lista* list, int nroMat, Aluno *estudante);

int tamLista(Lista* list);

int listaCheia(Lista* list);

int listaVazia(Lista* list);

void imprimeLista(Lista* list);

void apagaLista(Lista* list);



