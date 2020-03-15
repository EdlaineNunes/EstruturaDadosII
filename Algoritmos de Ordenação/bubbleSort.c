#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TAM 20

int main(int argc, char **argv)
{
	int vet[TAM],dif=0;
	srand (time(NULL));
	printf("\t\tVETOR:\n\n");
	for(int i=0; i<TAM; i++){
		vet[i] = rand() %10;
		printf(" %d |",vet[i]);
	}
	printf("\n\n\n\t\tVETOR ORDENADO:\n\n");
	for(int i=0; i<TAM; i++)
		for (int j=0; j<TAM-i-1; j++)
			if (vet[j] > vet[j+1]){
				int aux = vet[j];
				vet[j] = vet[j+1];
				vet[j+1] = aux;
			}
	for(int i=0; i<TAM; i++){
		printf(" %d |",vet[i]);
		if(vet[i] != vet[i+1])
			dif++;			
	}
	if(dif){
		printf("\n\n\n\n%d número(s) diferente(s), sendo ele(s): ",dif);
		for(int i=0; i<TAM; i++)
			if(vet[i] != vet[i+1])
				printf("%d\t",vet[i]);
	}
	else
		printf("\n\n\nNenhum número diferente foi encontrado, pois todos são iguais.");
			
	return 0;
}

