#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TAM 5

void particao(int esquerda, int direita, int *i, int *j, int *dados){ 
	int pivo, temporario;
	*i = esquerda;  
	*j = direita;
	pivo = dados[(*i + *j)/2];
	do{ 
		while(pivo > dados[*i])
			(*i)++;				
		while(pivo < dados[*j]) 
			(*j)--;		
		if(*i <= *j) { 
			temporario = dados[*i]; 
			dados[*i] = dados[*j]; 
			dados[*j] = temporario;
			(*i)++; 
			(*j)--;
		}		
    }while(*i <= *j);
}

void ordena(int esquerda, int direita, int *dados)
{ 
	int i, j;
	particao(esquerda, direita, &i, &j, dados);
	if(esquerda < j) 
		ordena(esquerda, j, dados);
	if(direita>i) 
		ordena(i, direita, dados);
}

void quicksort(int *dados){ 
	ordena(0, TAM-1, dados); 
}


int main(int argc, char *argv[])
{
	srand(time(NULL));
	printf("====================Quicksort=====================\n");
	int vet[TAM];
	
	for(int i=0; i< TAM; i++){
		vet[i] = rand()%20;
	}
	
	printf("\n\t\tDesordenado: \n");
	for (int i=0; i<TAM; i++)
		printf("ID: %d\n",vet[i]);
	
	quicksort(vet);
	
	printf("\n\t\tOrdenado: \n");
	for (int i=0; i<TAM; i++)
		printf("ID: %d\n",vet[i]);
  return 0;
}

