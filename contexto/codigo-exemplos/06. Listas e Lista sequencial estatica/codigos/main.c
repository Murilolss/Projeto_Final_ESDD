#include <stdio.h>
#include <stdlib.h>
#include "ListaSequencial.h"
#define qtde 5

int main(){
    Aluno dados_entrada[qtde] = {
						 {3,"Lucas",8.2,7.5,7.8},
                         {4,"Beatriz",6.5,8.3,8.8},
                         {1,"Mariana",9.1,7.8,7.5},
                         {9,"Junior",7.6,8.1,6.4},
                         {7,"Carlos",7.6,8.1,6.4}
	};

    Lista* list = criaLista(); //Lista* list --> ponteiro para a lista

    for(int i=0; i < qtde; i++)
        insereFinal(list, dados_entrada[i]);

    imprimeLista(list);

    Aluno alunoBuscado;
	int nroMat;
    printf("\n Digite o numero de matricula a ser localizado: "); 
    scanf("%d", &nroMat);
    int achou = consultaMatricula(list, nroMat, &alunoBuscado); //consulta pelo nroMat. Devolve (ref) dados do aluno.
    if (achou == 1){
		printf("\n Dados do Aluno, Matricula: %d Nome: %s",alunoBuscado.matricula, alunoBuscado.nome);
	    printf("\n Notas: N1 = %4.2f; N2 = %4.2f e N3 = %4.2f",alunoBuscado.n1, alunoBuscado.n2, alunoBuscado.n3);
    }
    else{
    	printf("\n Aluno nao encontrado!");
	}

	apagaLista(list);
    return(0);
}


