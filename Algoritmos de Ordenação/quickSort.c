#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TAM 5

void preencheVetor(int vet[]){
	for (int i = 0; i < TAM; i++)
		vet[i] = rand() % 200;
}

void imprime(int vet[]){
	for (int i = 0; i < TAM; i++)
		printf("%d\t",vet[i]);
	printf("\n\n");	
}

void ordenaQuick(int vet[],int inicio, int fim){
   
   int pivo, aux, i, j, meio;
   
   i = inicio;
   j = fim;
   
   meio = (int) ((i + j) / 2);
   pivo = vet[meio];
   
   do{
      while (vet[i] < pivo)
		i = i + 1;
      while (vet[j] > pivo) 
		j = j - 1;
      
      if(i <= j){
         aux = vet[i];
         vet[i] = vet[j];
         vet[j] = aux;
         i = i + 1;
         j = j - 1;
      }
   }while(j > i);
   
   if(inicio < j) 
	ordenaQuick(vet, inicio, j);
   if(i < fim) 
	ordenaQuick(vet, i, fim);   

}

int main(int argc, char **argv){
	srand(time(NULL));
	int vet[TAM];
	preencheVetor(vet);
	imprime(vet);
	ordenaQuick(vet,0,(TAM-1));
	printf("ORDENADO:\n");
	imprime(vet);	
	return 0;
}

