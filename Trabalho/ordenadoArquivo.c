#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct{
	int codBarra;
	int qntd;
}Cod;

int codAutomatico(FILE *file){
	Cod novo;
	int auxCod, rep;
	do{
		auxCod = 1 + rand () % 999999999999999;
		rep = 0;
		fseek(file,0,SEEK_SET);
		while(fread(&novo,sizeof(Cod),1,file))
			if (auxCod == novo.codBarra || auxCod < 0){
				rep = 1;
				break;
			}
		if(rep)
			continue;
		//debug qnt cadastro
		printf(" OK ");
		return auxCod;
	}while(1);
	return 0;	
}

void setCod(FILE* file){
	Cod novo;
	novo.codBarra = codAutomatico(file);
	novo.qntd = rand () % 50;	
	fseek(file,0,SEEK_END);
	fwrite(&novo,sizeof(Cod),1,file);	
}

void getCod(FILE * file){
	Cod novo;
	fseek(file,0,SEEK_SET);
	while(fread(&novo,sizeof(Cod),1,file))
		printf("CodBarra: %d \t\t qntd: %d\n",novo.codBarra,novo.qntd);
}

int cadAutomatico(){
	int unid;
	printf("Digite a quantidade de cadastros automáticos:\t");
	scanf(" %d",&unid);
	return unid;	
}

int qtdCad(){
	FILE * file = fopen ("Arquivo.txt","r+");
	Cod novo;
	int cont=0;
	//fseek(file,0,SEEK_SET);
	while(fread(&novo,sizeof(Cod),1,file)){
		//debug qnt cadastro
		//printf("%d ",cont);
		cont++;
	}
	return cont;
}

//funções para medir o tempo de clock
// obs: essa implementação foi pedida na fase II e implementada em TODOS OS ALGORITMOS DE ORDENAÇÃO

double calculaInicio(){
	clock_t t0;
	t0 = clock();
	return t0;
}

double calculaFim(double t0){
	clock_t tf;
	tf = clock();
	return tf;
}

//inicio dos metodos de ordenação

void ordenarSelecao(){
	int n = qtdCad();
	//debug valor de n
	//printf(" N: %d",n);
	FILE *file = fopen("Arquivo.txt","r+"); 
	Cod t, dados[n];
	int cont=0;
	fseek(file,0, SEEK_SET);
	while(fread(&t,sizeof(Cod),1,file)){
		dados[cont] = t;
		printf("CodB: %d\n", dados[cont].codBarra);
		cont++;
	}
	
	//clock
	clock_t comeco = calculaInicio();
	
	Cod temp;
	int indiceMenor = 0;	
	//ord por seleção	
	for(int i=0; i< n-1; i++){
		indiceMenor = i;
		for(int j = i+1; j< n; j++)
			if (dados[j].codBarra < dados[indiceMenor].codBarra)
				indiceMenor = j;
		temp = dados[indiceMenor];
		dados[indiceMenor] = dados[i];
		dados[i] = temp;			
	}
	clock_t fim = calculaFim(comeco);
	//fechar arq. as informações estão ordenadas em dados[n]
	fclose(file);
	
	//"apagando" o arq para salvar ordenado 
	FILE *fileOrd = fopen("Arquivo.txt","w");
	Cod dadosOrd;
	printf("\n\n\t\tORDENAÇÃO POR QUANTIDADE (SELEÇÃO)\n\n");
	for (int i=0; i<n; i++){
		dadosOrd = dados[i];
		fwrite(&dadosOrd,sizeof(Cod),1,fileOrd);
		printf("CodBarra: %d \t\t qntd: %d\n",dadosOrd.codBarra,dadosOrd.qntd);
		
	}
	printf("\n\n\t-----------------------------------------------------\n\n");
	printf("O tempo de resposta em ciclos de clock foi: %lf milissegundos",((double) comeco - fim / (CLOCKS_PER_SEC/1000)));
	printf("\n\n\t-----------------------------------------------------\n");	
	fclose(fileOrd);
}

void ordenarInsercao(){
	int n =  qtdCad();
	FILE *file =fopen("Arquivo.txt","r+"); 
	Cod t;
	Cod dados[n];
	int cont=0;
	fseek(file,0, SEEK_SET);
	while(fread(&t,sizeof(Cod),1,file)){
		dados[cont] = t;
		cont++;
	}
	
	//ord INSERÇÃO
	clock_t comeco = calculaInicio();
	Cod temp;
	int j=0;
	for(int i=1; i<n; i++){
		temp = dados[i];
		j = i-1;
		while(j>=0 && (temp.codBarra < dados[j].codBarra)){
			dados[j+1] = dados[j];
			j--;
		}
		dados[j+1] = temp;
	}	
	clock_t fim = calculaFim(comeco);
	fclose(file);
	
	//"apagando" o arq para salvar ordenado 
	FILE *fileOrd = fopen("Arquivo.txt","w");
	Cod dadosOrd;
	printf("\n\n\t\tORDENAÇÃO POR QUANTIDADE (INSERÇÃO)\n\n");
	for (int i=0; i<n; i++){
		dadosOrd = dados[i];
		fwrite(&dadosOrd,sizeof(Cod),1,fileOrd);
		printf("CodBarra: %d \t\t qntd: %d\n",dadosOrd.codBarra,dadosOrd.qntd);
		
	}
	printf("\n\n\t-----------------------------------------------------\n\n");
	printf("O tempo de resposta em ciclos de clock foi: %lf milissegundos",((double) comeco - fim / (CLOCKS_PER_SEC/1000)));
	printf("\n\n\t-----------------------------------------------------\n");
	fclose(fileOrd);
}

// alterações da Parte II  - Inicio
void ordenarShell(){
	int n = qtdCad();
	FILE *file = fopen("Arquivo.txt","r+"); 
	Cod t;
	Cod dados[n];
	int cont=0;
	fseek(file,0, SEEK_SET);
	while(fread(&t,sizeof(Cod),1,file)){
		dados[cont] = t;
		cont++;
	}
	
	clock_t comeco = calculaInicio();
	//ord SHELL SORT
	Cod temp;
	int i , j;
    int h = 1;
    while(h < n) {
        h = 3*h+1;
    }
    while ( h > 1) {
        h = h/3;
        //debug altura do salto
        //printf("altura = %d\n",h);
        for(i = h; i < n; i++) {
            temp = dados[i];
            j = i;
            while ((j >= h) && (temp.codBarra < dados[j - h].codBarra)) {
                dados[j] = dados[j - h];
                j = j - h;
            }
            dados[j] = temp;
        }
    }
    clock_t fim = calculaFim(comeco);
    fclose(file);
	
	//"apagando" o arq para salvar ordenado 
	FILE *fileOrd = fopen("Arquivo.txt","w");
	Cod dadosOrd;
	printf("\n\n\t\tORDENAÇÃO POR QUANTIDADE (SHELL SORT)\n\n");
	for (int i=0; i<n; i++){
		dadosOrd = dados[i];
		fwrite(&dadosOrd,sizeof(Cod),1,fileOrd);
		printf("CodBarra: %d \t\t qntd: %d\n",dadosOrd.codBarra,dadosOrd.qntd);
		
	}
	printf("\n\n\t-----------------------------------------------------\n\n");
	printf("O tempo de resposta em ciclos de clock foi: %lf milissegundos",((double) comeco - fim / (CLOCKS_PER_SEC/1000)));
	printf("\n\n\t-----------------------------------------------------\n");
	fclose(fileOrd);
}

void particao(int esquerda, int direita, int *i, int *j, Cod dados[], int tam){ 
	//quick
	Cod pivo, temp;
	*i = esquerda;  
	*j = direita;
	pivo = dados[(*i + *j)/2];
	do{ 
		while(pivo.codBarra > dados[*i].codBarra)
			(*i)++;				
		while(pivo.codBarra < dados[*j].codBarra) 
			(*j)--;		
		if(*i <= *j) { 
			temp = dados[*i]; 
			dados[*i] = dados[*j]; 
			dados[*j] = temp;
			(*i)++; 
			(*j)--;
		}		
    }while(*i <= *j);
}
 
void ordena(int esq, int direita, Cod dados[], int tam){
	//quick
	int i, j;
	particao(esq, direita, &i, &j, dados, tam);
	if (esq < j)
		ordena(esq, j, dados, tam);
	if (i < direita)
		ordena(i, direita, dados, tam);	
}

void ordenaQuick(){
	int n = qtdCad();
	FILE * file = fopen("Arquivo.txt","r+"); 
	Cod t;
	Cod dados[n];
	int cont=0;
	fseek(file,0, SEEK_SET);
	while(fread(&t,sizeof(Cod),1,file)){
		dados[cont] = t;
		cont++;
	}
	
	clock_t comeco = calculaInicio();
	//ord Quick
    ordena(0,(n-1),dados,n);
    
    clock_t fim = calculaFim(comeco);
    fclose(file);
	
	//"apagando" o arq para salvar ordenado 
	FILE *fileOrd = fopen("Arquivo.txt","w");
	Cod dadosOrd;
	printf("\n\n\t\tORDENAÇÃO POR QUANTIDADE (QUICK SORT)\n\n");
	for (int i=0; i<n; i++){
		dadosOrd = dados[i];
		fwrite(&dadosOrd,sizeof(Cod),1,fileOrd);
		printf("CodBarra: %d \t\t qntd: %d\n",dadosOrd.codBarra,dadosOrd.qntd);
	}
	printf("\n\n\t-----------------------------------------------------\n\n");
	printf("O tempo de resposta em ciclos de clock foi: %lf milissegundos",((double) comeco - fim / (CLOCKS_PER_SEC/1000)));
	printf("\n\n\t-----------------------------------------------------\n");
	fclose(fileOrd);	
}

void trocarPosicoes(Cod *dados, int i, int j){ 
	//heap
	Cod temp = dados[i];
	dados[i] = dados[j];
	dados[j] = temp;
}

void construirHeap(Cod *dados, int n){ 
	//heap
	int i, pai, filho;	
	for(i = 0; i < (n - 1); i++){		
		filho = i + 1;
		pai = (filho - 1) / 2;
		while(filho > 0 && dados[pai].codBarra < dados[filho].codBarra){
			trocarPosicoes(dados, pai, filho);
			filho = pai;
			pai = (filho - 1) / 2;
		}		
	}
}

void refazerHeap(Cod *dados, int n){ 
	//heap
	int pai, filhoEsquerdo, filhoDireito, filhoMaior;	
	pai = 0;	
	while(pai <= (n / 2 - 1)){	
		filhoEsquerdo = 2 * pai + 1;
		filhoDireito = 2 * pai + 2;
		
		filhoMaior = filhoEsquerdo;
		if(filhoDireito < n && dados[filhoDireito].codBarra > dados[filhoEsquerdo].codBarra){
			filhoMaior = filhoDireito;
		}
		
		if(dados[filhoMaior].codBarra > dados[pai].codBarra){
			trocarPosicoes(dados, pai, filhoMaior);
			pai = filhoMaior;			
		}else{
			break;
		}
	}
}

void extrairRaizHeap(Cod *dados, int n){ 
	//heap
	trocarPosicoes(dados, 0, (n - 1));	
}

void ordenaHeap(){
	int n = qtdCad();
	FILE * file = fopen("Arquivo.txt","r+"); 
	Cod t;
	Cod dados[n];
	int cont=0;
	fseek(file,0, SEEK_SET);
	while(fread(&t,sizeof(Cod),1,file)){
		dados[cont] = t;
		cont++;
	}
	int tam = n;
	
	clock_t comeco = calculaInicio();
	//ord Heap
    construirHeap(dados,n);
    while(n > 1){
		extrairRaizHeap(dados, n);
		n--;
		refazerHeap(dados, n);
	}
	clock_t fim = calculaFim(comeco);
    fclose(file);
	
	//"apagando" o arq para salvar ordenado 
	FILE *fileOrd = fopen("Arquivo.txt","w");
	Cod dadosOrd;
	printf("\n\n\t\tORDENAÇÃO POR QUANTIDADE (HEAPSORT)\n\n");
	for (int i=0; i < tam ; i++){
		dadosOrd = dados[i];
		fwrite(&dadosOrd,sizeof(Cod),1,fileOrd);
		printf("CodBarra: %d \t\t qntd: %d\n",dadosOrd.codBarra,dadosOrd.qntd);
	}
	printf("\n\n\t-----------------------------------------------------\n\n");
	printf("O tempo de resposta em ciclos de clock foi: %lf milissegundos",((double) comeco - fim / (CLOCKS_PER_SEC/1000)));
	printf("\n\n\t-----------------------------------------------------\n");
	fclose(fileOrd);	
}

//finalização das alterações da Parte II - Fim

//alterações parte III

int busca(){
	printf("Insira o código de barras a ser buscado: ");
	int cod;
	scanf(" %d",&cod);
	printf("\n\n");
	return cod;	
}

void pesquisaSequencial(){
	int n = qtdCad();
	FILE * file = fopen("Arquivo.txt","r+"); 
	Cod t;
	Cod dados[n];
	int cont=0;
	fseek(file,0, SEEK_SET);
	while(fread(&t,sizeof(Cod),1,file)){
		dados[cont] = t;
		cont++;
	}
	
	int alvo = busca();
	
	clock_t comeco = calculaInicio();
	int valida = 0;
	for (int i=0; i < cont; i ++)
		if( alvo == dados[i].codBarra){
			printf("O codBarra: %d\t qtd %d\t foi encontrado na %dº posição\n",dados[i].codBarra, dados[i].qntd, i+1);
			valida = 1;
			break;
		}
	if (!valida)
		printf("Registro não encontrado!\n");

	clock_t fim = calculaFim(comeco);
	
	printf("\n\n\t-----------------------------------------------------\n\n");
	printf("O tempo de resposta em ciclos de clock foi: %lf milissegundos",((double) comeco - fim / (CLOCKS_PER_SEC/1000)));
	printf("\n\n\t-----------------------------------------------------\n");	
    fclose(file);
}

void pesquisaBinaria(){
	FILE * file = fopen("Arquivo.txt","r+"); 
	int cont = 0, tam = qtdCad();
//	int loc = 0;
	//int vet[tam];
	Cod vetor[tam],a;
	
	fseek(file,0, SEEK_SET);
	
	int alvo = busca();	
	
	while(fread(&a,sizeof(Cod),1,file)){
		vetor[cont] = a;
		cont++;
	}
	
	ordenaQuick();

	int centro = 0,fim = tam-1, inicio = 0;
	
	while( inicio <= fim){
		centro = (inicio + fim)/2;
		if(alvo == vetor[centro].codBarra){
			printf("O dado foi encontrado!!\n");	
			printf("O numero buscado foi: %d\t Qtd. %d\n",alvo, vetor[centro].qntd);	
		}
		if (alvo > vetor[centro].codBarra)
			inicio = centro + 1;
		else
			fim = centro - 1;
	}
	fclose(file);
}

int printMenu(){
	printf("\n==========================================================\n");
	printf("\n\t\t\tMENU PRINCIPAL\n\n");
	printf("1 - Escolher a quantidade de cadastros automáticos\n");
	printf("2 - Exibir cadastros automáticos\n");
	printf("3 - Consultar quantidade de cadastros existentes\n");
	printf("4 - Ordenar por Seleção (COD BARRA)\n");
	printf("5 - Ordenar por Inserção (COD BARRA)\n");
	printf("6 - Ordenar pelo Shellsort (COD BARRA)\n");
	printf("7 - Ordenar pelo Quicksort (COD BARRA)\n");
	printf("8 - Ordenar pelo Heapsort (COD BARRA)\n");
	printf("9 - Pesquisa sequencial\n");
	printf("10 - Pesquisa binária\n");
	
	printf("11 - EXIT\n");
	printf("Opc:	");
	int opc;
	scanf(" %d",&opc);
	printf("\n==========================================================\n\n");
	return opc;
}

int menuGeral(){
	FILE* file = NULL;
	srand(time(NULL));
	int i;
	
	file= fopen("Arquivo.txt","r+");
	if(!file)
		file = fopen("Arquivo.txt","w+");
	if(!file){
		printf("Programa não conseguiu abrir o arquivo!!\n");
		return 0;
	}
	
	int auxCad = 0;
	int qtd = 0;
	do{
		switch(printMenu()){
			case 1: auxCad = cadAutomatico();
					if( auxCad > 0 )
						for (int i=0; i<auxCad; i++)
							setCod(file);
					break;
					auxCad = 0;
			case 2: getCod(file);
					break;
			case 3: qtd = qtdCad();
					if (qtd > 0){
						printf("\n\t %d cadastros armazenados!\n",qtd);
						break;
					}
					printf("\n\t Nenhum cadastro");
					qtd = 0;
					break;
			case 4: ordenarSelecao(); 
					break;
			case 5: ordenarInsercao();
					break;
			case 6: ordenarShell();
					break;
			case 7: ordenaQuick();	
					break;
			case 8: ordenaHeap();
					break;
			case 9: pesquisaSequencial();
					break;
			case 10:pesquisaBinaria();	
					break;
					
			case 11: i = fclose(file);
					if (!i)
						printf("\n\t\tArquivo Fechado com SUCESSO!\n");
					return 0;
		}
	}while(1);
	
	return 0;
}

int main(){
	menuGeral();
	return 0;
}

