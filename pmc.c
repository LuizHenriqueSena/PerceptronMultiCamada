#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

#define xn 25
#define camadas 3
#define l1 5  //quantidade de neuronios na camada 1
#define l2 4  //quantidade de neuronios na camada 2
#define l3 5  //quantidade de neuronios na camada 3
#define tamanhoAmostras 200
#define n 0.5
#define e 0.1
#define eta 0.5
#define erro 0.001
#define pesoInicial 0.2
#define treinamento 170
#define validacao 199

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
const char separadorFim[2] = ".";
double saidas[l3];


double funcaoDeAtivacao(double u) {
	double retorno;
	retorno = (1/(1 + pow(2.718281,(u*(-1)))));
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
				wl[contaNeuronio][contaPeso][cont] = pesoInicial;
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
			}
			resultado += (wl[contaNeuronio][contaPeso][contaCamada] * (-1));
			Il[contaNeuronio][contaCamada] = resultado;
			Yl[contaNeuronio][contaCamada] = funcaoDeAtivacao(Il[contaNeuronio][contaCamada]);	
		}
		else {
			for(contaPeso = 0; contaPeso < limite1; contaPeso++) {
				resultado += Yl[contaPeso][contaCamada-1]*wl[contaNeuronio][contaPeso][contaCamada];
			}
			resultado += (wl[contaNeuronio][contaPeso][contaCamada] * (-1));
			Il[contaNeuronio][contaCamada] = resultado;
			Yl[contaNeuronio][contaCamada] = funcaoDeAtivacao(Il[contaNeuronio][contaCamada]);
		}
	}
}
	saidas[0] = Yl[0][camadas - 1];
	saidas[1] = Yl[1][camadas - 1];
	saidas[2] = Yl[2][camadas - 1];
	saidas[3] = Yl[3][camadas - 1];
	saidas[4] = Yl[4][camadas - 1];
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

void atualizaPesos(int amostra) {
	int contaPeso, contaNeuronio, contaCamada;
	int limite1, limite2;
	double resultado = 0;
	for(contaCamada = 0; contaCamada < camadas; contaCamada++) {
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
			resultado = 0;
			if (contaCamada == 0) {
				for(contaPeso = 0; contaPeso < limite1; contaPeso++) {
					wl[contaNeuronio][contaPeso][contaCamada] = wl[contaNeuronio][contaPeso][contaCamada] + eta*
					vetorDelta[contaNeuronio][contaCamada]*amostras[contaPeso][amostra];
				}
					wl[contaNeuronio][contaPeso][contaCamada] = wl[contaNeuronio][contaPeso][contaCamada] + eta*
					vetorDelta[contaNeuronio][contaCamada]*(-1);
			}
			else {
				for(contaPeso = 0; contaPeso < limite1; contaPeso++) {
					wl[contaNeuronio][contaPeso][contaCamada] = wl[contaNeuronio][contaPeso][contaCamada] + eta*
					vetorDelta[contaNeuronio][contaCamada]*Yl[contaPeso][contaCamada - 1];
				}
					wl[contaNeuronio][contaPeso][contaCamada] = wl[contaNeuronio][contaPeso][contaCamada] + eta*
					vetorDelta[contaNeuronio][contaCamada]*(-1);
			}				
		}
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
 	saidaDesejada[conty][linha] = atoi(token);
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
         	saidaDesejada[conty][linha] = atoi(token);
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
	//printf("erro quadratico: %.6f \n ",retorno);
	return retorno;
}

double erroQuadraticoMedio(int inicial, int final){
	double retorno = 0;
	int k = inicial;
	double em = 0;
	for(k = inicial; k <= final; k++) {
		em += erroQuadratico(k);
}
	retorno = em/tamanhoAmostras;
}


void imprimeSaidasEDesejadas(int amostra) {
	int contador = 0;	
	for(contador =0; contador < 5; contador++) {
		printf(" Saida%d : %.9f e saidaDesejada%d: %d \n", contador, saidas[contador], contador, saidaDesejada[contador][amostra]);
	}
}

void imprimeVetoresDelta(){
	int contaCamada = 0;
	int contaNeuronio = 0;	
	int tamanhoNeuronios = 0;
	for(contaCamada = 0; contaCamada < camadas; contaCamada++) {
		if (contaCamada == 0) {
			tamanhoNeuronios = l1;
		}
		else if (contaCamada == 1) {
			tamanhoNeuronios = l2;
		}
		else if (contaCamada == 2) {
			tamanhoNeuronios = l3;
		}
		printf("VetorDelta%d%d \n", contaNeuronio +1, contaCamada + 1);
		for(contaNeuronio = 0; contaNeuronio < tamanhoNeuronios; contaNeuronio++) {
			printf("%.6f \t",vetorDelta[contaNeuronio][contaCamada]);
		}
		printf("\n");
}	
}

void imprimeVetoresEntradaESaida(){
	int contaCamada = 0;
	int contaNeuronio = 0;	
	int tamanhoNeuronios = 0;
	for(contaCamada = 0; contaCamada < camadas; contaCamada++) {
		if (contaCamada == 0) {
			tamanhoNeuronios = l1;
		}
		else if (contaCamada == 1) {
			tamanhoNeuronios = l2;
		}
		else if (contaCamada == 2) {
			tamanhoNeuronios = l3;
		}
		printf("Entrada%d%d \n", contaNeuronio +1, contaCamada + 1);
		printf("\t");
		for(contaNeuronio = 0; contaNeuronio < tamanhoNeuronios; contaNeuronio++) {
			printf("%.6f \t",Il[contaNeuronio][contaCamada]);
		}
		printf("\n");
		contaNeuronio = 0;
		printf("Saida%d%d \n", contaNeuronio +1, contaCamada + 1);
		printf("\t");
		for(contaNeuronio = 0; contaNeuronio < tamanhoNeuronios; contaNeuronio++) {
			printf("%.6f \t",Yl[contaNeuronio][contaCamada]);
		}
		printf("\n");
}	
}


void imprimeVetorDePesos() {
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
		for(contaNeuronio = 0; contaNeuronio < limite2; contaNeuronio++){
			printf("Matrix %d%d \n ", contaNeuronio + 1, contaCamada + 1);
			for(contaPeso = 0; contaPeso < limite1; contaPeso++){
				printf("%0.3f  ", wl[contaNeuronio][contaPeso][contaCamada]);
			}
			printf("\n");
		}
		printf("\n");
	}
}
	

void randomizaPixel(int k){
	int aux = 0;
	int random = 0;
	srand(clock());
	srand(time(NULL));
	random = rand()%25;
	aux = amostras[random][k];
	if(aux == 1) {
		amostras[random][k]=0;
	}
	else {
		amostras[random][k]=1;
	}
}

void poluiAmostras(){
	int contadorAmostrasCorretas = 5;
	int contadorAmostrasErradas = 126;
	for(contadorAmostrasCorretas = 5; contadorAmostrasCorretas < 100; contadorAmostrasCorretas++){
		randomizaPixel(contadorAmostrasCorretas);
	}
	for(contadorAmostrasErradas = 126; contadorAmostrasErradas < 200; contadorAmostrasErradas++){
		randomizaPixel(contadorAmostrasErradas);
	}
}

void treinaRede() {
	int contAmostras = 0;
	int nEpocas = 0;
	//double erroAtual = 0;
	//double erroAnterior = 0;
	//double erroValidacao = 1;
	printf("erro quadratico medio %.6f \n ",fabs(erroQuadraticoMedio(0, 199)));
	while (fabs(erroQuadraticoMedio(0, 199)) > fabs((double)erro)) {
	//erroAnterior = erroAtual;
	for (contAmostras = 0; contAmostras < tamanhoAmostras ;contAmostras++) {
		//imprimeVetorDePesos();
		obtemResultadosPorCamadas(amostras, contAmostras);
		//imprimeSaidasEDesejadas(contAmostras);
		//imprimeVetoresEntradaESaida();
		preencheVetorDelta(amostras,contAmostras);
		//imprimeVetoresDelta();
		atualizaPesos(contAmostras);
		//imprimeSaidasEDesejadas(contAmostras);
		//printf("erro quadratico medio %.6f \n ",fabs(erroQuadraticoMedio()));
		//usleep(500000);
	}
	//erroAtual = erroQuadraticoMedio(0,199);
	//erroValidacao = erroAtual - erroAnterior;
	printf("erro quadratico medio %.6f \n ",fabs(erroQuadraticoMedio(0,199)));
	fflush(stdout);
	nEpocas++;	
	}
	printf("NUMERO DE EPOCAS: %d \n", nEpocas);

}

void parserEntradaParaVetor(char entrada[100], int linha) {
   char copia[100];
   char *token;
   strcpy(copia, entrada);
   int contx = 0;
   /* get the first token */
   token = strtok(copia, ";");
   amostras[contx][linha] = atoi(token);
   contx++;
   /* walk through other tokens */
   while( token != NULL ) {
      if(contx >= xn - 1) {
        token = strtok(NULL, separadorFim);
	amostras[contx][linha] = atoi(token);
	token = NULL;
      }
      else {
	 token = strtok(NULL, separadorGenerico);
         amostras[contx][linha] = atoi(token);
	 //printf("VALOR DO segundo CAST : %d \n",amostras[contx][linha]);
         contx++;
      }


}
}

void imprimePrimeiroVetor(){
	int contador = 0;
	for(contador = 0; contador < xn; contador++) {
		printf("entrada %d : %d \n ", contador, amostras[contador][0]);
	}
}

void imprimePoluidos(){
	int contador = 0;
	int contadorx = 0;
	for(contador = 0; contador < tamanhoAmostras; contador++) {
		printf("Amostra%d \n", contador);
		for(contadorx = 0; contadorx < xn; contadorx++) {
			printf("%d;", amostras[contadorx][contador]);
		}
		printf("\n");
	}
}


void imprimeResultado() {
	printf("\n\n\n-------------------RESULTADO-----------------\n");
	printf("\t\tLetra A: %.5f \n", saidas[0]);
	printf("\t\tLetra E: %.5f \n", saidas[1]);
	printf("\t\tLetra I: %.5f \n", saidas[2]);
	printf("\t\tLetra O: %.5f \n", saidas[3]);
	printf("\t\tLetra U: %.5f \n", saidas[4]);
	printf("----------------------------------------------\n\n\n");
}

void desordenaVetoresAmostrasESaidas() {
	int contador1, contador2;
	int contador3;
	int random = 0;
	int aux = 0;
	int aux1 = 0;
	int fixo = 0;
	for(contador1 = 0; contador1 < 200; contador1++){
		srand(clock());
		srand(time(NULL));
		random = rand()%198;
		if (random == fixo) {
			random++;
		}
		for(contador2 = 0; contador2 <xn; contador2++) {
		aux = amostras[contador2][random];
		amostras[contador2][random] = amostras[contador2][fixo];
		amostras[contador2][fixo] = aux;
		}
		for(contador3 = 0; contador3 <l3; contador3++){
		aux1 = saidaDesejada[contador3][random];
		saidaDesejada[contador3][random] = saidaDesejada[contador3][fixo];
		saidaDesejada[contador3][fixo] = aux1;
		}
		fixo++;
	}
}

int main() {
	char entrada[100];
	preencheVetorDeAmostras();
	poluiAmostras();
	//desordenaVetoresAmostrasESaidas();
	geraPesosAleatorios();
	treinaRede();
	printf("O processo de treinamento acabou. \n");
	//imprimePoluidos();
	printf("Digite a imagem a ser classificada, ou \"q\" para sair: (Cada entrada deve ser separada por \";\" )\n");
	scanf("%s", &entrada[0]); 
	while(strstr(entrada, "q") == NULL){
		parserEntradaParaVetor(entrada, 0);
		obtemResultadosPorCamadas(amostras, 0);
		imprimeResultado();
		printf("Digite a imagem a ser classificada. (Cada entrada deve ser separada por \";\" \n");
		scanf("%s", &entrada[0]); 
	}
	return 0;
}
	
