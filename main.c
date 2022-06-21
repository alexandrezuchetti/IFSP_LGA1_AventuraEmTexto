#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>


//estrutura player (contem nome, vida, variaveis de itens)
typedef struct {
	int dado;
	int cristais;
	int vida;
	char  nome[11];
} PLAYER;

//funcoes do programa
int interageEstado(int *opcoes, int *destinos, int *lutas, PLAYER *ptjogador);
int demonstraEstado(int estado_destino, PLAYER *ptjogador);
int processaLuta(int estadoluta, PLAYER *ptjogador);



int main(){
	
	//variaveis
	int gameover=0, estado_destino=1;
	PLAYER jogador;
	PLAYER *ptjogador=&jogador;
	
	//inventario inicial
	jogador.dado = 0;
	jogador.vida = 20;
	jogador.cristais = 0;
	
	
	//escolha do nome
	printf("*Voce caminha em direcao ao vilarejo, sua luta com o dragao esta proxima* \n");
	printf("*Aquele velho rabujento so precisa te apontar na direcao certa* \n");
	printf("*Voce pensa que em breve sera um heroi. Herois tem nomes Heroicos. Qual o seu?*\n");
	scanf("%9s", &jogador.nome);

	
	printf("%s, um nome de heroi!\n", jogador.nome);
	
	//loop do jogo
	while (gameover==0){
	estado_destino = demonstraEstado(estado_destino, ptjogador);	
	if (estado_destino == 0){
		gameover = 1;		
	}
} 	
	return 0;
}




int demonstraEstado(int estado_destino, PLAYER *ptjogador){
	
	//AQUI ELE CHECA SE O ITEM JA FOI CONSEGUIDO e tira o player da interacao se necessario
	
	switch(estado_destino){
		case 3:
			if (ptjogador->cristais == 1){
				return 98;
			}
		case 10:
            if (ptjogador->dado == 1){
				return 97;
			}
		
	}
	
	//variaveis
	
	int *opcoes, *destinos, *lutas;
	FILE *fp;
	char linha[500], strTexto[200];
	int i=0, estado, procurando=1, achou=0;
	char *strp;
	
	
	//abre o arquivo se der ruim da erro e mata o player
	fp = fopen("leitura.txt", "r");
	if (fp == NULL){
		printf("erro");
		return 0;
		
	}
	
	//abre espacos e endereca os ponteiros declarados
	
	opcoes = (int *) malloc(10 * sizeof(int));
	destinos = (int *) malloc(10 * sizeof(int));
	lutas = (int *) malloc(10 * sizeof(int));	
	
	while (fgets(linha, 500, fp) != NULL && procurando == 1){
		
		
		//PEGA ESTADO
		strp = strtok(linha, ";");
		estado = atoi(strp);
		
		if (estado == estado_destino){
			achou = 1;
			
			//LE A OPCAO
			strp = strtok(NULL, ";");
			if (atoi(strp) == 0){
				//SE A OPCAO FOR 0, DIALOGO DO PERSONAGEM É PRINTADO
				strp = strtok(NULL, ";");
				printf("%s\n", strp);
			}
			else {
				//SE NAO FOR, É ARMAZENADA A OPCAO e o destino E PRINTADA A OPCAO E O TEXTO
				
				
				//ARMAZENA A OPCAO
				opcoes[i] = atoi(strp);
				
				//ARMAZENA O TEXTO
				strp = strtok(NULL, ";");
				strcpy(strTexto, strp);
				
				//ARMAZENA O DESTINO
				strp = strtok(NULL, ";");
				destinos[i] = atoi(strp);
				
				//ARMAZENA SE HÁ LUTA
				strp = strtok(NULL, ";");
				lutas[i] = atoi(strp);
				
				
				
				//PRINTA OPCAO E TEXTO
				printf("%d) ", opcoes[i]);
				printf("%s\n", strTexto);	
				i++;	
			}
		}
		else if(achou==1){
			procurando = 0;
		}
	}
	
	estado_destino = interageEstado(opcoes, destinos, lutas, ptjogador);
	free(opcoes);
	free(destinos);
	fclose(fp);
	return estado_destino;
	
}


int processaLuta(int estadoluta, PLAYER *ptjogador){
	//variaveis
	FILE *fp;
	char linha[500], strTexto[200];
	int estadodestino=99, estado, procurando=1, achou=0, chancerand, chancevar;
	char *strp;
	
	//gera numero aleatorio para essa luta (emtre 0 e 100)
	unsigned seed = time(0);
   	srand(seed);
	chancerand = rand() % 100 + 1;

	printf("Chance: %d\n", chancerand);
	
	
	//abre o arquivo se der ruim da erro e mata o player
	fp = fopen("lutas.txt", "r");
	if (fp == NULL){
		printf("erro");
		return 0;
		
	}
	
	while (fgets(linha, 500, fp) != NULL){		
		//PEGA ESTADO
		strp = strtok(linha, ";");
		estado = atoi(strp);
		
		if (estado == estadoluta){
			achou = 1;
			//LE CHANCE
			strp = strtok(NULL, ";");
			chancevar = atoi(strp);
			// LE DADO
			strp = strtok(NULL, ";");
			//se o dado esta no inventario, checa se e a melhor opcao e printa se for o caso
			if (atoi(strp) == 1 && ptjogador->dado == 1){
				strp = strtok(NULL, ";");
				printf("%s\n", strp);
				strp = strtok(NULL, ";");
				estadodestino = atoi(strp);
				fclose(fp);
				break;

			}
			//se nao, vai na sorte
			else if (chancerand<=chancevar && ptjogador->dado == 0){
				strp = strtok(NULL, ";");
				printf("%s\n", strp);
				strp = strtok(NULL, ";");
				estadodestino = atoi(strp);
				fclose(fp);	
				break;	
		
			}	
		}
	}
	//checa se o estado destino referencia um acontecimento que altera o inventario, adiciona o irem de acordo
	switch(estadodestino){
		case 80:
			ptjogador->cristais = 1;
		case 7:
			ptjogador->dado = 1;
			
	}
	return estadodestino;
}




int interageEstado(int *opcoes, int *destinos, int *lutas, PLAYER *ptjogador){


	//variaveis
	int inter_opcao, i;
	
	
	start:
	scanf("%d", &inter_opcao);
	
	
	//fica no loop ate acabarem as opcao do array recebido, ou a opcao for encontrada
	//se a opcao nao e encontrada, ocorre o goto start que reinicia o processo de captura e interpretacao da variavel
	for (i = 0; i < sizeof(opcoes); i++){
		if (opcoes[i] == inter_opcao){
			printf("%d - %d - %d\n", opcoes[i], destinos[i], lutas[i]);
			if (lutas[i] == 1){
				printf("====================================================\n");
				return processaLuta(destinos[i], ptjogador);
			}
			printf("====================================================\n");
			return destinos[i];
		}
	}
	goto start;
	
}




