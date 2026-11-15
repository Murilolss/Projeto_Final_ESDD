#include <stdio.h>

int fatorial_iterativo(int num);
int fatorial_recursivo(int num);

int main()
{
  int numero;

  printf("Informe um numero: ");
  scanf("%d",&numero);

  printf("Fatorial iterativo de %d = %d \n", numero, fatorial_iterativo(numero));
  printf("Fatorial recursivo de %d = %d \n", numero, fatorial_iterativo(numero));
  return 0;
}

int fatorial_iterativo(int num) {
  int fatorial = 1;
  // Multiplica o número por seus antecessores até 1
  for (int i = 2; i <= num; i++) {
    fatorial = fatorial * i;
  }
  return fatorial;
}

int fatorial_recursivo(int num){
  // implementa a regra n! = n * (n-1)!
  if ( num <= 1 ){
    return num;
  }
  return num * fatorial_recursivo(num-1);
}

