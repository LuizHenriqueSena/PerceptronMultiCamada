#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define xn 25
#define camadas 3
#define l1 5  //quantidade de neuronios na camada 1
#define l2 4  //quantidade de neuronios na camada 2
#define l3 5  //quantidade de neuronios na camada 3
#define tamanhoAmostras 20
#define n 0.5
#define e 0.1
#define eta 0.5

int entradas[xn + 1];

//Escolher sempre a maior camada para os parametros entre l1, l2, l3 de [x][y][z] das matrizes


double wl[xn + 1][l1][camadas];
double Il[l1][l1];
double Yl[l1][l1];
int amostras[xn][tamanhoAmostras];
int saidaDesejada[l3][tamanhoAmostras];
double vetorDelta[l1][camadas];
const char separadorGenerico[2] = ";";
const char separadorSaida[2] = "-";
double saidas[l3];


double funcaoDeAtivacao(double u) {
	double retorno;
	retorno = (1/(1 - pow(2.718281,u)));
	return retorno;
}

double derivadaFuncaoDeAtivacao(double u) {
	double retorno;
	retorno = funcaoDeAtivacao(u)*(1 - funcaoDeAtivacao(u));
	return retorno;
}

void geraPesosAleatorios(){
int cont = 0;
int limite1 = 0;
int limite2 = 0;
int contaPeso = 0;
int contaNeuronio = 0;
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
		for(contaNeuronio = 0; contaNeuronio < limite2; contaNeuronio++) {
			for(contaPeso = 0; contaPeso <= limite1; contaPeso++) {
				wl[contaNeuronio][contaPeso][cont] = 0.5;
			}
	}
}
}


void obtemResultadosPorCamadas(int teste[xn][tamanhoAmostras], int amostra) {
int contaCamada = 0;
int limite1 = 0;
int limite2 = 0;                                                                                                                                                               
int contaPeso = 0;
int contaNeuronio = 0;
double resultado = 0.0;


	for(contaCamada = 0; contaCamada < camadas; contaCamada++) {
		//pesosSinapticos[cont] = ((float)(rand()%100))/100; 
		//printf("PESOS ALEATORIO: %d com valor: %.2f \n", cont, pesosSinapticos[cont]);
		if (contaCamada == 0) {
			limite1 = xn;
			limite2 = l1;
		}
		else if (contaCamada == 1) {
			limite1 = l1;
			limite2 = l2;
		}
		else if (contaCamada == 2){
			limite1 = l2;
			limite2 = l3;
		}
		for(contaNeuronio = 0; contaNeuronio < limite2; contaNeuronio++) {
			resultado = 0.0;
		if (contaCamada == 0) {
			for(contaPeso = 0; contaPeso < limite1; contaPeso++) {
				resultado += teste[contaPeso][amostra]*wl[contaNeuronio][contaPeso][contaCamada];
				//printf("resultado : %.2f \n", resultado);
			}
			printf("resultado : %d \n", contaPeso);
			resultado += wl[contaNeuronio][contaPeso + 1][contaCamada] * (-1);
			Il[contaNeuronio][contaCamada] = resultado;
			printf("valor antes da fa %.2f \n ",Il[contaNeuronio][contaCamada]);
			Yl[contaNeuronio][contaCamada] = funcaoDeAtivacao(Il[contaNeuronio][contaCamada]);	
			printf("valor do primeiro resultado do %d neuronio da %d camada: %.6f \n ",contaNeuronio,contaCamada, Yl[contaNeuronio][contaCamada]);
		}
		else {
			for(contaPeso = 0; contaPeso < limite1; contaPeso++) {
				resultado += Il[contaPeso][contaCamada-1]*wl[contaNeuronio][contaPeso][contaCamada];
				//printf("resultado : %.2f \n ", resultado);
			}
			Il[contaNeuronio][contaCamada] = resultado;
			printf("valor antes da fa %.2f \n ",Il[contaNeuronio][contaCamada]);
			Yl[contaNeuronio][contaCamada] = funcaoDeAtivacao(Il[contaNeuronio][contaCamada]);
			printf("valor do primeiro resultado do %d neuronio da %d camada: %.6f \n ",contaNeuronio,contaCamada, Yl[contaNeuronio][contaCamada]);
		}
	}
}
	//printf("valor do peso do segundo neuronio da segunda camada %.2f \n ", wl[0][1][0]);
	saidas[0] = Yl[camadas - 1][0];
	saidas[1] = Yl[camadas - 1][1];
	saidas[2] = Yl[camadas - 1][2];
	saidas[3] = Yl[camadas - 1][3];
	saidas[4] = Yl[camadas - 1][4];
}


void preencheVetorDelta(int teste[xn][tamanhoAmostras], int amostra) {
	int contaPeso, contaNeuronio, contaCamada;
	int limite1, limite2;
	double resultado = 0;
	for(contaCamada = (camadas - 1); contaCamada >= 0; contaCamada--) {
		if (contaCamada == 0) {
			limite1 = l1;
			limite2 = l2;
			for(contaNeuronio = 0; contaNeuronio < limite1; contaNeuronio++) {
				resultado = 0;
				for(contaPeso = 0; contaPeso < limite2; contaPeso++) {
					resultado += vetorDelta[contaPeso][contaCamada + 1]*wl[contaPeso][contaNeuronio][contaCamada + 1];
				}
			vetorDelta[contaNeuronio][contaCamada] = resultado * derivadaFuncaoDeAtivacao(Il[contaNeuronio][contaCamada]);
		}		
		}
		else if (contaCamada == 1) {
			limite1 = l3;
			limite2 = l2;
			for(contaNeuronio = 0; contaNeuronio < limite2; contaNeuronio++) {
				resultado = 0;
				for(contaPeso = 0; contaPeso < limite1; contaPeso++) {
					resultado += vetorDelta[contaPeso][contaCamada + 1]*wl[contaPeso][contaNeuronio][contaCamada + 1];
				}
			vetorDelta[contaNeuronio][contaCamada] = resultado * derivadaFuncaoDeAtivacao(Il[contaNeuronio][contaCamada]);
		}		
		}
		else if (contaCamada == 2){
			limite2 = l3;
			for(contaNeuronio = 0; contaNeuronio < limite2; contaNeuronio++) {
			//for(contaPeso = 0; contaPeso < limite1; contaPeso++) {
				vetorDelta[contaNeuronio][contaCamada] = (saidaDesejada[contaNeuronio][amostra] - saidas[contaNeuronio])
				*derivadaFuncaoDeAtivacao(Il[contaNeuronio][contaCamada]);
		
			}
		}

}
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
	double resultado = 0;
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
	//printf("VALOR DO PRIMEIRO CAST : %d \n",amostras[contx][linha]);
   contx++;

   /* walk through other tokens */
   while( token != NULL ) {
   if (!jaEncontreiASaida) {
      if(contx >= xn - 1) {
        token = strtok(NULL, separadorSaida);
	amostras[contx][linha] = atoi(token);
	//printf("VALOR DO ultimo CAST : %d \n",amostras[contx][linha]);
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
	 //printf("VALOR DO segundo CAST : %d \n",amostras[contx][linha]);
         contx++;
      }
   } else if (jaEncontreiASaida) {
		token = strtok(NULL, separadorGenerico);
         	if (atoi(token) == 0) {
			saidaDesejada[conty][linha] = -1;
		}
		else saidaDesejada[conty][linha] = atoi(token);
	 		//printf("VALOR DO segundo CAST : %d \n",saidaDesejada[conty][linha]);
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
        //printf("Retrieved line of length %zu :\n", read);
        //printf("%s", line);
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

double erroQuadratico(int amostra){
	double retorno;
	int j;
	double resultado = 0;
	obtemResultadosPorCamadas(amostras, amostra);
	for(j = 0; j < l3; j++){
		resultado += saidaDesejada[j][amostra] - saidas[j];
	}
	retorno = resultado;
	return retorno;
}

double erroQuadraticoMedio(){
	double retorno;
	int k = 0;
	double em = 0;
	for(k = 0; k < tamanhoAmostras; k++) {
		em += erroQuadratico(k);
}
	retorno = em/tamanhoAmostras;
}
	

int main() {
	//double resultado = funcaoDeAtivacao(25);
	//printf("resultado : %.6f \n ", resultado);
	preencheVetorDeAmostras();
	geraPesosAleatorios();
	obtemResultadosPorCamadas(amostras, 0);
	//imprimeVetores();
	//treinaRede();
	return 0;
}
	
