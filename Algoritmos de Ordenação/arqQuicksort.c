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
	int cont=0;
	fseek(file,0,SEEK_SET);
	while(fread(&novo,sizeof(Cod),1,file))
		cont++;
	return cont;
}
 
void particao(int esquerda, int direita, int *i, int *j, Cod dados[], int tam){ 
	Cod pivo, temp;
	*i = esquerda;  
	*j = direita;
	pivo = dados[(*i + *j)/2];
	do{ 
		while(pivo.qntd > dados[*i].qntd)
			(*i)++;				
		while(pivo.qntd < dados[*j].qntd) 
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
	
	//ord Quick
    ordena(0,n-1,dados,n);
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
	fclose(fileOrd);	
}

int printMenu(){
	printf("\n=====MENU PRINCIPAL======\n");
	printf("1 - Escolher o número de cadastros automáticos\n");
	printf("2 - Exibir cadastros automáticos\n");
	printf("3 - Consultar quantidade de cadastros existentes\n");
	printf("4 - Ordenar pelo quick sort (QUANTIDADE)\n");
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
	do{
		switch(printMenu()){
			case 1: auxCad = cadAutomatico();
					while (auxCad != 0){
						setCod(file);
						auxCad --;
					}
					break;
			case 2: getCod(file);
					break;
			case 3: qtd = qtdCad();
					printf("\n\t %d cadastros armazenados!\n",qtd);
					break;
			case 4: ordenaQuick();		
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
