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
		auxCod = 1000 + rand () % 9999999;
		rep = 0;
		fseek(file,0,SEEK_SET);
		while(fread(&novo,sizeof(Cod),1,file))
			if (auxCod == novo.codBarra){
				rep = 1;
				break;
			}
		if(rep)
			continue;
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
	int cont=1;
	fseek(file,0,SEEK_SET);
	while(fread(&novo,sizeof(Cod),1,file))
		cont++;
	return cont;
}

int calculaInicio(){
	clock_t t0;
	t0 = clock();
	return t0;
}

int calculaFim(){
	clock_t tf;
	tf = clock();
	double tempo = (((double)(tf-0))/(((double)CLOCKS_PER_SEC)/1000));
	return tempo;
}


 
void trocarPosicoes(Cod *dados, int i, int j){ 
	Cod temp = dados[i];
	dados[i] = dados[j];
	dados[j] = temp;
}

void construirHeap(Cod *dados, int n){ 
	int i, pai, filho;	
	for(i = 0; i < (n - 1); i++){		
		filho = i + 1;
		pai = (filho - 1) / 2;
		while(filho > 0 && dados[pai].qntd < dados[filho].qntd){
			trocarPosicoes(dados, pai, filho);
			filho = pai;
			pai = (filho - 1) / 2;
		}		
	}
}

void refazerHeap(Cod *dados, int n){ 
	int pai, filhoEsquerdo, filhoDireito, filhoMaior;	
	pai = 0;	
	while(pai <= (n / 2 - 1)){	
		filhoEsquerdo = 2 * pai + 1;
		filhoDireito = 2 * pai + 2;
		
		filhoMaior = filhoEsquerdo;
		if(filhoDireito < n && dados[filhoDireito].qntd > dados[filhoEsquerdo].qntd){
			filhoMaior = filhoDireito;
		}
		
		if(dados[filhoMaior].qntd > dados[pai].qntd){
			trocarPosicoes(dados, pai, filhoMaior);
			pai = filhoMaior;			
		}else{
			break;
		}
	}
}

void extrairRaizHeap(Cod *dados, int n){ 
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
	
	calculaInicio();
	/*	
	//calc tempo
	clock_t t0,tf;
	t0 = clock();
	*/
	//clone de n
	int tam = n;

	//ord Heap
    construirHeap(dados,n);
    while(n > 1){
		extrairRaizHeap(dados, n);
		n--;
		refazerHeap(dados, n);
	}
	/*
	//finalizar tempo
	tf = clock();
	double tempo = (((double) (tf-0))/(((double)CLOCKS_PER_SEC)/1000))
	return tempo;
	*/
	
	double tempo = calculaFim();
    fclose(file);
	
	//"apagando" o arq para salvar ordenado 
	FILE *fileOrd = fopen("Arquivo.txt","w");
	Cod dadosOrd;
	printf("\n\n\t\tORDENAÇÃO POR QUANTIDADE (HEAPSORT)\n\n");
	for (int i=0; i < tam; i++){
		dadosOrd = dados[i];
		fwrite(&dadosOrd,sizeof(Cod),1,fileOrd);
		printf("CodBarra: %d \t\t qntd: %d\n",dadosOrd.codBarra,dadosOrd.qntd);
	}
	printf("\n\n----------------------\nO tempo de resposta foi: %lf milisegundos\n\n-------------------------\n",tempo);
	fclose(fileOrd);	
}

int printMenu(){
	printf("\n=====MENU PRINCIPAL======\n");
	printf("1 - Escolher o número de cadastros automáticos\n");
	printf("2 - Exibir cadastros automáticos\n");
	printf("3 - Consultar quantidade de cadastros existentes\n");
	printf("4 - Ordenar pelo heapsort (QUANTIDADE)\n");
	printf("5 - EXIT\n");
	int opc;
	scanf(" %d",&opc);
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
		printf("Programa não conseguiu abrir o arquivo FILME!!\n");
		return 0;
	}
	
	int auxCad = 0;
	int qtd=0;
	int verifica = 0;
	do{
		switch(printMenu()){
			case 1: auxCad = cadAutomatico();
					while (auxCad != 0){
						setCod(file);
						auxCad --;
						verifica = 1;
					}
					break;
			case 2: getCod(file);
					break;
			case 3: if (verifica == 0){
						printf("Nenhum cadastro existente!\n");
						break;
					}else {
						qtd = qtdCad();
						printf("\n\t %d cadastro(s) armazenado(s)!\n",qtd);
						break;
					}
			case 4: ordenaHeap();		
					break;
			case 5: i = fclose(file);
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
