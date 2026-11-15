#include <stdio.h>
#include <stdlib.h>

#define TOTALPESSOAS 10

 //declaração do registro
 struct tipoPessoa{
        char nome[20];
        float altura;
        float peso;
 };

 //assinaturas das funções
 void cadastrar(struct tipoPessoa p[], int *pos);
 void exibirIMC(struct tipoPessoa p[], int pos);
 float imc(float peso, float altura); 


 int main()
 {
     struct tipoPessoa pessoas[TOTALPESSOAS];
     int posicao = 0, opcao;
    
     do{   
         printf("-------Menu-------\n");
         printf("[1] cadastrar pessoa \n");
         printf("[2] exibir pessoas e seus IMC \n");
         printf("[3] sair \n\n");
         printf("Opcao desejada: ");
         scanf("%d",&opcao);
         switch(opcao){        
              case 1: //cadastrar novas pessoas
                     cadastrar(pessoas,&posicao);
                     break;           
              case 2: //calcular e exibir IMC das pessoas
                     exibirIMC(pessoas,posicao);
                     break;            
              case 3:
                     printf("\nPrograma finalizado.\n");
                     break;         
              default:
                     printf("Opcao invalida.");
                     break;
       }
    }while ( opcao != 3 );
    return 0;
 }

// adiciona uma nova pessoa ao vetor
 void cadastrar(struct tipoPessoa p[], int *pos)
 {
     if ( *pos < TOTALPESSOAS ){
         fflush(stdin);
         printf("Nome: ");
         gets(p[*pos].nome);
         printf("Peso (kg): ");
         scanf("%f",&p[*pos].peso);
         printf("Altura (cm): ");
         scanf("%f",&p[*pos].altura);
        
         *pos = *pos + 1;
    }else{
           printf("\n O limite de pessoas foi atingido!\n");
     }
 }    
 
 // exibe o IMC das pessoas
 void exibirIMC(struct tipoPessoa p[], int pos)
 {
       for (int i = 0; i < pos; i++){
              printf("Nome: %s \n", p[i].nome);
              printf("IMC.: %.2f \n\n", imc(p[i].peso, p[i].altura/100));                
       }
       getch();   
 }

 // calcula o IMC de 1 pessoa
float imc(float peso, float altura)
{
       return(peso/(altura*altura));
}
    