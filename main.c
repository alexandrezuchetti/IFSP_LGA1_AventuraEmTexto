#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>


int main(){
	
	FILE *fp;
	int gameover=0, estado_destino=1;
	

	while (gameover==0){
	fp = fopen("leitura.txt", "r");
	if (fp == NULL){
		printf("erro");
		return 1;
		
	}
	estado_destino = demonstraEstado(fp, estado_destino);	
	if (estado_destino == 0){
		
		gameover = 1;		
	}
} 	

	return 0;
}




int demonstraEstado(FILE *fp, int estado_destino){
	int *opcoes, *destinos;
	char linha[500], strTexto[200];
	int i=0, estado, procurando=1, achou=0;
	char *strp;
	
	opcoes = (int *) malloc(10 * sizeof(int));
	destinos = (int *) malloc(10 * sizeof(int));	
	
	while (fgets(linha, 500, fp) != NULL && procurando == 1){
		strp = strtok(linha, ";");
		estado = atoi(strp);
		if (estado == estado_destino){
			achou = 1;
			strp = strtok(NULL, ";");
			if (atoi(strp) == 0){
				strp = strtok(NULL, ";");
				printf("%s\n", strp);
			}
			else {
				opcoes[i] = atoi(strp);
				strp = strtok(NULL, ";");
				strcpy(strTexto, strp);
				strp = strtok(NULL, ";");
				destinos[i] = atoi(strp);
				
				printf("%d) ", opcoes[i]);
				printf("%s\n", strTexto);	
				i++;	
			}
		}
		else if(achou==1){
			procurando = 0;
		}
	}
	
	estado_destino = interageEstado(opcoes, destinos);
	free(opcoes);
	free(destinos);
	fclose(fp);
	return estado_destino;
	
}


int interageEstado(int *opcoes, int *destinos){

	int inter_opcao, i;
	
	start:
	scanf("%d", &inter_opcao);
	
	for (i = 0; i < sizeof(opcoes); i++){
		if (opcoes[i] == inter_opcao){
			printf("%d - %d\n", opcoes[i], destinos[i]);
			return destinos[i];
		}
	}
	goto start;
	
}