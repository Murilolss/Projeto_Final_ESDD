#include <stdio.h>
#include <stdlib.h>
#include "ListaSequencial.h" //Prototipos

Lista* criaLista(){
    Lista *list; //cria ponteiro
    list = (Lista*) malloc(sizeof(Lista)); //aloca espaco
    if(list != NULL)
        list->prox = 0; //se criou, indico que a proxima posicao vazia
    return list;
}

int insereFinal(Lista* list, Aluno al){
    if(list == NULL)//ha algo de errado com a lista (nao foi criada, p. ex.)
        return 0;
    if(list->prox == MAX)//lista cheia
        return 0;
    list->alunos[list->prox] = al;
    list->prox++;
    return 1;
}

int insereInicio(Lista* list, Aluno al){
    if(list == NULL)
        return 0;
    if(list->prox == MAX)//lista cheia
        return 0;
    int i;
    for(i=list->prox-1; i>=0; i--) 
        list->alunos[i+1] = list->alunos[i];
    list->alunos[0] = al;
    list->prox++;
    return 1;
}

int insereOrdenada(Lista* list, Aluno al){
    if(list == NULL)//lista invalida
        return 0;
    if(list->prox == MAX)//lista cheia
        return 0;
    int k,i = 0;
    while(i<list->prox && list->alunos[i].matricula < al.matricula) //busca onde inserir
        i++; //posicao a ser ocupada

    for(k=list->prox-1; k >= i; k--) //liberar pos: desloca elem (p/ frente) do final ate
        list->alunos[k+1] = list->alunos[k];						//posicao encontrada.

    list->alunos[i] = al; //insere na pos encontrada
    list->prox++;
    return 1;
}

int removeMatricula(Lista* list, int mat){//remove elemento (aluno) informado
    if(list == NULL)//lista invalida
        return 0;
    if(list->prox == 0)//lista vazia
        return 0;
    int k,i = 0;
    while(i<list->prox && list->alunos[i].matricula != mat)//percorro a lista e at� encontrar o
		i++;													//aluno ou at� chegar no final.
    if(i == list->prox)//chegou no final e n�o encontrou elemento na lista
        return 0;

    for(k=i; k< list->prox-1; k++) //desloca todos os elementos seguintes para a posi��o anterior
        list->alunos[k] = list->alunos[k+1];
    list->prox--; //atualiza pr�x
    return 1;
}

int removeInicio(Lista* list){
    if(list == NULL)//lista inv�lida
        return 0;
    if(list->prox == 0)//lista vazia
        return 0;
    int k = 0;
    for(k=0; k< list->prox-1; k++)//desloca todos os elementos para posi��o anterior
        list->alunos[k] = list->alunos[k+1];
    list->prox--;//decrementa pr�x
    return 1;
}

int removeFinal(Lista* list){
    if(list == NULL)//lista inv�lida
        return 0;
    if(list->prox == 0) //lista vazia - n�o pode remover
        return 0;
    list->prox--; //n�o precisa de realoca��o, apenas atualiza pr�x
    return 1;
}

int tamLista(Lista* list){
    if(list == NULL)
        return -1;
    else
        return list->prox; //se ok, retorno o tamanho - semelhante a (*list).prox
}

int listaCheia(Lista* list){
    if(list == NULL) //problema na lsita
        return -1;
    return (list->prox == MAX); //MAX posi��es preenchidas, prox = MAX; retorna 1 (cheia)
}

int listaVazia(Lista* list){
    if(list == NULL)
        return -1;
    return (list->prox == 0);//se VERDADE (prox � == 0) --> retorna 1 (vazia)
}

//passo ponteiro p/ struct aluno que � onde vou guardar os dados encontrados
int consultaPosicao(Lista* list, int pos, Aluno *estudante){
    if(list == NULL || pos <= 0 ||  pos > list->prox)//lista inv�lida, pos inv�lida
        return 0;
    *estudante = list->alunos[pos]; //devolvo os dados que est�o na posi��o informada
    return 1;
}

int consultaMatricula(Lista* list, int nroMat, Aluno *estudante){//consulta pelo nroMatricula
    if(list == NULL)//lista invalida
        return 0;
    int i = 0;
    while(i<list->prox && list->alunos[i].matricula != nroMat)//busca o elemento e recupera sua pos
        i++;
    if(i == list->prox)//final da lista e elemento nao encontrado
        return 0;

    *estudante = list->alunos[i];//devolvo os dados da posicao encontrada dentro da estrutura auxiliar.
    return 1;
}

void imprimeLista(Lista* list){
    if(list == NULL)
        return;
    int i;
    printf("\n Alunos cadastrados");
	for(i=0; i< list->prox; i++){
		printf("\n Matricula: %d, Nome: %s, Notas: N1: %4.2f, N2: %4.2f, N3: %4.2f", 
            list->alunos[i].matricula, list->alunos[i].nome,
            list->alunos[i].n1, list->alunos[i].n2, list->alunos[i].n3);
    }
}

void apagaLista(Lista* list){
    free(list);
}
