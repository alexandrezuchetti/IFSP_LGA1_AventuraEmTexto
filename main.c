#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int main(){
  char name[15], i;
  printf("INSIRA TEXTO DE AMBIENTACAO AQUI \n");
  printf("Ei camarada, preciso do seu nome pro formulario. \n"); 
  scanf("%s", &name);
	
  printf("Okay %s, voce precisa que eu te explique como interagir com as coisas e falar com pessoas? \n", name);  
  printf("1) Nao, isso seria estupido. \n");
  printf("2) Que? \n");
  scanf("%d", &i);
  switch (i){
  	case 1:
  		printf("Voce ficaria surpreso com a quantidade de \"estupido\" que eu vejo por aqui. \n");
		break;
  	case 2:
  		printf("Alguns de voces sao meio cabeca oca, mas acho que voce ja entendeu o conceito geral da coisa. \n");
  		printf("Vamos so continuar e torcer pra tudo dar certo! \n");
		break;
  	default:
  		printf("... \n");
  		getch();
  		printf("Eu realmente vou ter que te explicar como isso funciona? \n");
  		printf("Eu te dou as opcoes, voce escolhe uma delas. Simples assim. \n");
  		break;
  }
  getch();
  return 0;
}