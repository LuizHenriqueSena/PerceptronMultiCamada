#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define xn 25
#define camadas 3
#define l1 5  //quantidade de neuronios na camada 1
#define l2 4  //quantidade de neuronios na camada 2
#define l3 5  //quantidade de neuronios na camada 3
#define tamanhoAmostras 20
#define n 0.5
#define e 0.1

int entradas[xn + 1];

//Escolher sempre a maior camada para os parametros entre l1, l2, l3 de [x][y][z] das matrizes


float wl[xn + 1][l1][camadas];
float Il[l1][l1];
float Yl[l1][l1];
int amostras[xn][tamanhoAmostras];
int saidaDesejada[l3][tamanhoAmostras];
const char separadorGenerico[2] = ";";
const char separadorSaida[2] = "-";
float saida1;
float saida2;
float saida3;
float saida4;
float saida5;


int funcaoDeAtivacao(float u) {
	if (u<=0) return -1;
	else return 1;
}

void geraPesosAleatorios(){
int cont = 0;
int limite1 = 0;
int limite2 = 0;
int contx = 0;
int conty = 0;
	for(cont = 0; cont < camadas; cont++) {
		//pesosSinapticos[cont] = ((float)(rand()%100))/100; 
		//printf("PESOS ALEATORIO: %d com valor: %.2f \n", cont, pesosSinapticos[cont]);
		if (cont == 0) {
			limite1 = xn;
			limite2 = l1;
		}
		else if (cont == 1) {
			limite1 = l1;
			limite2 = l2;
		}
		else if (cont == 2){
			limite1 = l2;
			limite2 = l3;
		}
		for(conty = 0; conty < limite2; conty++) {
			for(contx = 0; contx < limite1; contx++) {
				wl[contx][conty][cont] = 1;
			}
	}
}
}


void obtemResultadosPorCamadas(int teste[xn][tamanhoAmostras], int amostra) {
int cont = 0;
int limite1 = 0;
int limite2 = 0;
int contx = 0;
int conty = 0;
float resultado = 0.0;


	for(cont = 0; cont < camadas; cont++) {
		//pesosSinapticos[cont] = ((float)(rand()%100))/100; 
		//printf("PESOS ALEATORIO: %d com valor: %.2f \n", cont, pesosSinapticos[cont]);
		if (cont == 0) {
			limite1 = xn;
			limite2 = l1;
		}
		else if (cont == 1) {
			limite1 = l1;
			limite2 = l2;
		}
		else if (cont == 2){
			limite1 = l2;
			limite2 = l3;
		}
		for(conty = 0; conty < limite2; conty++) {
			resultado = 0.0;
		if (cont == 0) {
			for(contx = 0; contx < limite1; contx++) {
				resultado += teste[contx][amostra]*wl[contx][conty][cont];
				//printf("resultado : %.2f \n", resultado);
			}
			Il[conty][cont] = resultado;
			printf("valor do primeiro resultado do %d neuronio da %d camada: %.2f \n ",conty,cont, Il[conty][cont]);
			Yl[conty][cont] = Il[conty][cont];	
		}
		else {
			for(contx = 0; contx < limite1; contx++) {
				resultado += Il[contx][cont-1]*wl[contx][conty][cont];
				//printf("resultado : %.2f \n ", resultado);
			}
			Il[conty][cont] = resultado;
			printf("valor do primeiro resultado do %d neuronio da %d camada: %.2f \n ",conty,cont, Il[conty][cont]);
			
			Yl[conty][cont] = Il[conty][cont];
		}
	}
}
	//printf("valor do peso do segundo neuronio da segunda camada %.2f \n ", wl[0][1][0]);
	saida1 = Yl[camadas - 1][0];
	saida2 = Yl[camadas - 1][1];
	saida3 = Yl[camadas - 1][2];
	saida4 = Yl[camadas - 1][3];
	saida5 = Yl[camadas - 1][4];
}

void imprimeRedeResultante() {
int cont = 0;
	for(cont = 0; cont < xn; cont++) {
		//printf("PESO resultante: %d com valor: %.2f \n", cont, pesosSinapticos[cont]);
	}
	//printf("limiar de ativacao da posicao: %d com valor: %.2f \n", cont, pesosSinapticos[xn]);
}

void treinaRede() {
	int contAmostras = 0;
	int cont = 0;
	int cont2 = 0;
	float resultado = 0;
	int saida;
	//computa resposta para entradas
	for (contAmostras = 0; contAmostras < tamanhoAmostras;contAmostras++) {
		resultado = 0;
		for(cont = 0; cont < xn; cont++) {
			//resultado += pesosSinapticos[cont]*amostras[cont][contAmostras];	
		}
		//resultado = resultado + pesosSinapticos[xn];
		//saida = funcaoSaida(resultado);
		printf("para a amostra: %d , tem-se  saida: %d e saidaDesejada: %d \n", contAmostras, saida, saidaDesejada[contAmostras][contAmostras]);
		if(saida != saidaDesejada[contAmostras][contAmostras]) {
			//ajusta pesos
			for(cont2 = 0; cont2 < xn; cont2++) {
				//pesosSinapticos[cont2] = pesosSinapticos[cont2] + ((n)*(saidaDesejada[contAmostras] + 
				//(-1)*saida)*(amostras[cont2][contAmostras]));	
			}
			//pesosSinapticos[xn] = pesosSinapticos[xn] + ((saidaDesejada[contAmostras] + 
			//(-1)*saida));	
}
		else {
			//nao ajusta
		}
	printf("para a amostra: %d , tem-se \n", contAmostras);
	imprimeRedeResultante();
	}
	
}

void parserAmostras(char *strn, int linha) {
   char copia[100];
   char *token;
   strcpy(copia, strn);
   int contx = 0;
   int conty = 0;
   int jaEncontreiASaida = 0;
   /* get the first token */
   token = strtok(copia, ";");
   amostras[contx][linha] = atoi(token);
	printf("VALOR DO PRIMEIRO CAST : %d \n",amostras[contx][linha]);
   contx++;

   /* walk through other tokens */
   while( token != NULL ) {
   if (!jaEncontreiASaida) {
      if(contx >= xn - 1) {
        token = strtok(NULL, separadorSaida);
	amostras[contx][linha] = atoi(token);
	printf("VALOR DO ultimo CAST : %d \n",amostras[contx][linha]);
	token = strtok(NULL, separadorGenerico);
	jaEncontreiASaida = 1;
  	if (atoi(token) == 0) {
	saidaDesejada[conty][linha] = -1;
	}
	else saidaDesejada[conty][linha] = atoi(token);
	conty++;
      }
      else {
	 token = strtok(NULL, separadorGenerico);
         amostras[contx][linha] = atoi(token);
	 printf("VALOR DO segundo CAST : %d \n",amostras[contx][linha]);
         contx++;
      }
   } else if (jaEncontreiASaida) {
		token = strtok(NULL, separadorGenerico);
         	if (atoi(token) == 0) {
			saidaDesejada[conty][linha] = -1;
		}
		else saidaDesejada[conty][linha] = atoi(token);
	 		printf("VALOR DO segundo CAST : %d \n",saidaDesejada[conty][linha]);
         		conty++;
		if (conty == l3) token = NULL;
	}

}
}

void preencheVetorDeAmostras() {
	    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int linha = 0;

    fp = fopen("teste.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu :\n", read);
        printf("%s", line);
	parserAmostras(line, linha);
	linha++;
    }

    fclose(fp);
    if (line)
        free(line);
}

void imprimeVetores(void) {
	int i = 0;
	int j = 0;
	for(j = 0; j < tamanhoAmostras; j++) {
	printf("para a amostra numero %d temos: \n", j);
		for(i = 0; i < xn; i++){
		printf("entrada numero %d de valor %d \n", i, amostras[i][j]);
		}
		for(i = 0; i < l3; i++){
		printf("para a saida numero %d temos: %d \n", j, saidaDesejada[i][j]);
		}	
	}

}

int main() {
	preencheVetorDeAmostras();
	geraPesosAleatorios();
	obtemResultadosPorCamadas(amostras, 1);
	//imprimeVetores();
	//treinaRede();
	return 0;
}
	
