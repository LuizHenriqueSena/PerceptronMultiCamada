#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define xn 2
#define tamanhoAmostras 48
#define n 0.5


int entradas[xn];
float pesosSinapticos[xn + 1];
int amostras[xn][tamanhoAmostras];
int saidaDesejada[tamanhoAmostras];
const char separadorEntradas[2] = ";";
const char separadorSaida[2] = "-";
int funcaoSaida(float u) {
	if (u<=0) return -1;
	else return 1;
}

void geraPesosAleatorios(){
int cont = 0;
	for(cont = 0; cont < xn; cont++) {
		pesosSinapticos[cont] = ((float)(rand()%100))/100; 
		printf("PESOS ALEATORIO: %d com valor: %.2f \n", cont, pesosSinapticos[cont]);
	}
}

void imprimeRedeResultante() {
int cont = 0;
	for(cont = 0; cont < xn; cont++) {
		printf("PESO resultante: %d com valor: %.2f \n", cont, pesosSinapticos[cont]);
	}
	printf("limiar de ativacao da posicao: %d com valor: %.2f \n", cont, pesosSinapticos[xn]);
}

void treinaRede() {
	pesosSinapticos[0]=0.5;
	pesosSinapticos[1]=0.5;
	pesosSinapticos[2]= 1;
	int contAmostras = 0;
	int cont = 0;
	int cont2 = 0;
	float resultado = 0;
	int saida;
	//computa resposta para entradas
	for (contAmostras = 0; contAmostras < tamanhoAmostras;contAmostras++) {
		resultado = 0;
		for(cont = 0; cont < xn; cont++) {
			resultado += pesosSinapticos[cont]*amostras[cont][contAmostras];	
		}
		resultado = resultado + pesosSinapticos[xn];
		saida = funcaoSaida(resultado);
		printf("para a amostra: %d , tem-se  saida: %d e saidaDesejada: %d \n", contAmostras, saida, saidaDesejada[contAmostras]);
		if(saida != saidaDesejada[contAmostras]) {
			//ajusta pesos
			for(cont2 = 0; cont2 < xn; cont2++) {
				pesosSinapticos[cont2] = pesosSinapticos[cont2] + ((n)*(saidaDesejada[contAmostras] + 
				(-1)*saida)*(amostras[cont2][contAmostras]));	
			}
			pesosSinapticos[xn] = pesosSinapticos[xn] + ((saidaDesejada[contAmostras] + 
			(-1)*saida));	
}
		else {
			//nao ajusta
		}
	printf("para a amostra: %d , tem-se \n", contAmostras);
	imprimeRedeResultante();
	}
	
}

void parserAmostras(char *strn, int linha) {
   char copia[20];
   char *token;
   strcpy(copia, strn);
   int contx = 0;
   /* get the first token */
   token = strtok(copia, ";");
   amostras[contx][linha] = atoi(token);
	printf("VALOR DO PRIMEIRO CAST : %d \n",amostras[contx][linha]);
   contx++;

   /* walk through other tokens */
   while( token != NULL ) {
      if(contx >= xn - 1) {
        token = strtok(NULL, separadorSaida);
	amostras[contx][linha] = atoi(token);
	printf("VALOR DO ultimo CAST : %d \n",amostras[contx][linha]);
	token = strtok(NULL, separadorSaida);
  	if (atoi(token) == 0) {
	saidaDesejada[linha] = -1;
	}
	else saidaDesejada[linha] = 1;
	printf("VALOR Da primeira saida: %d \n",saidaDesejada[linha]);
	token = strtok(NULL, separadorSaida);
      }
      else {
	 token = strtok(NULL, separadorEntradas);
         amostras[contx][linha] = atoi(token);
	 printf("VALOR DO segundo CAST : %d \n",amostras[contx][linha]);
         contx++;
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
		printf("para a saida numero %d temos: %d \n", j, saidaDesejada[j]);
	}
}

int main() {
	preencheVetorDeAmostras();
	imprimeVetores();
	treinaRede();
	return 0;
}
