#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int verSoma(int vet[], int n){
	int soma = vet[n-1];
	printf("\n%d\t",soma);
	if(n == 1)
		return soma;
	//printf("\n%d\n",soma);
	soma += verSoma(vet,n-1);
	printf("\n%d\t",soma);
	return soma;
	
}


int main(int argc, char **argv)
{
	int n=5;
	int vet[n];
	srand(time(NULL));
	for(int i=0; i<n; i++)
		vet[i] = rand() % 10;
	printf("Vetor:\n\n");
	for(int i=0; i<n; i++)
		printf("%d\t",vet[i]);
	int r = verSoma(vet,n);
	printf("\n\n%d",r);
	
	//interativo
	int aux=0;
	for(int i=0; i<n; i++)
		aux +=vet[i];
	printf("\n\nAux: \t%d",aux);
	
	return 0;
}

