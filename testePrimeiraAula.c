#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int main(int argc, char **argv)
{
	int vet[10];
	//int maior=0;
	int aux;
	srand(time(NULL));
	
	for(int i=0; i<10; i++)
		vet[i] = 1 + rand() % 20;
	printf("Vetor completo:\n");
	for(int i=0; i<10; i++)
		printf("%d\t",vet[i]);
	/*
	//questão 1, achar o maior elemento do vetor	
	for(int i=0; i<10; i++)
	* 	//operação mais relevante é o if
		if(maior <= vet[i])
			maior = vet[i];
				
	printf("\n\nMaior: %d",maior);
	*/
	
	// questão 2, fazer a busca de um elemento do vetor
	printf("\n\nDigite um número de 1 a 20\t");
	scanf(" %d",&aux);
	
	for(int i=1; i<10; i++)
		if(aux == vet[i]){
			printf("\n\t\tO número %d, está na posição %d.\n",aux, i);
			return 0;
		}
	printf("\n\t\tO número %d, NÃO está no vetor.\n",aux);
	return 0;
}

