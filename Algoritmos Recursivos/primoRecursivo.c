#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int verificaPrimo(int n, int divisor){
	// n é o numero verificado e divisor (começa em 2) é o quanto vamos dividir n; (n/divisor)
	if (divisor == n)
		return 1;
	else if(n%divisor == 0)
		return 0;
	else 
		return (verificaPrimo(n, divisor+1));	
}

int verificaPrimoInterativo(int n){
	for (int i=2; i<n; i++)
		if(n%i == 0)
			return 0;
	return 1;	
}

int main(int argc, char **argv)
{
	int n;
	scanf(" %d",&n);
	/*int primoRecursivo = verificaPrimo(n,2);
	if (primoRecursivo == 0){
		printf("Não primo");
		return 0;
	} 
	printf("Primo");*/  
	int primoInterativo = verificaPrimoInterativo(n);
	if (primoInterativo == 0){
		printf("Não primo");
		return 0;
	} 
	printf("Primo");	
	return 0;
}

