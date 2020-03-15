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
	printf("%d - %d\n",novo.codBarra, novo.qntd);		
	fseek(file,0,SEEK_END);
	fwrite(&novo,sizeof(Cod),1,file);	
}

void getCod(FILE * file){
	Cod novo;
	fseek(file,0,SEEK_SET);
	while(fread(&novo,sizeof(Cod),1,file))
		printf("CodBarra: %d\t qntd: %d\n",novo.codBarra,novo.qntd);
}

int cadastroAutomatico(){
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
	printf("\n\tQUANTIDADE DE CADASTROS: %d\n",cont);
	return cont;
}

void ordenarSelecao(){
	int n = qtdCad();
	FILE *file =fopen("Arquivo.txt","r+"); 
	printf("%d\n",n);
	Cod t, dados[n];
	int cont=0;
	fseek(file,0, SEEK_SET);
	while(fread(&t,sizeof(Cod),1,file)){
		dados[cont] = t;
		cont++;
	}
	Cod temp;
	int indiceMenor = 0;	
	//ord por seleção	
	for(int i=0; i< n-1; i++){
		indiceMenor = i;
		for(int j = i+1; j< n; j++)
			if (dados[j].qntd < dados[indiceMenor].qntd)
				indiceMenor = j;
		temp = dados[indiceMenor];
		dados[indiceMenor] = dados[i];
		dados[i] = temp;			
	}
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
	fclose(fileOrd);
}

void ordenarInsercao(){
	int n = qtdCad();
	FILE *file =fopen("Arquivo.txt","r+"); 
	printf("%d\n",n);
	Cod t;
	Cod dados[n];
	int cont=0;
	fseek(file,0, SEEK_SET);
	while(fread(&t,sizeof(Cod),1,file)){
		dados[cont] = t;
		cont++;
	}
	
	//ord INSERÇÃO
	Cod temp;
	int j=0;
	for(int i=1; i<n; i++){
		temp = dados[i];
		j = i-1;
		while(j>=0 && (temp.qntd < dados[j].qntd)){
			dados[j+1] = dados[j];
			j--;
		}
		dados[j+1] = temp;
	}	
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
	fclose(fileOrd);
}

int printMenu(){
	printf("\n=====MENU PRINCIPAL======\n");
	printf("1 - Esolher numero de cadastros automáticos\n");
	printf("2 - Exibir cadastros automáticos\n");
	printf("3 - Ordenar por seleção\n");
	printf("4 - Ordenar por inserção\n");
	printf("5 - EXIT\n");
	int opc;
	scanf(" %d",&opc);
	return opc;
}

int main(){
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
	do{
		switch(printMenu()){
			case 1: auxCad = cadastroAutomatico();
					while (auxCad != 0){
						setCod(file);
						auxCad --;
					}
					break;
			case 2: getCod(file);
					break;
			case 3: ordenarSelecao();
					break;
			case 4: ordenarInsercao();
					break;
			case 5: i=fclose(file);
					if (!i)
						printf("\n\t\t\tArquivo Fechado com SUCESSO!\n");
					return 0;
		}
	}while(1);
	return 0;
}
