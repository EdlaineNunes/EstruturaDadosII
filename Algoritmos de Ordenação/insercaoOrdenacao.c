#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


typedef struct Cliente {
  int codigo;
  char *nome;
  char sexo;
} Cliente;

void carregarDadosIniciais(Cliente *dados){
	dados[0].codigo = 9;
	dados[0].nome = "Agatha"; 
	dados[0].sexo = 'F';
	
	dados[1].codigo = 6;
	dados[1].nome = "Alice"; 
	dados[1].sexo = 'F';
	
	dados[2].codigo = 5;
	dados[2].nome = "Alícia"; 
	dados[2].sexo = 'F';
	
	dados[3].codigo = 10;
	dados[3].nome = "Allana"; 
	dados[3].sexo = 'F';
	
	dados[4].codigo = 8;
	dados[4].nome = "Amanda"; 
	dados[4].sexo = 'F';
	
	dados[5].codigo = 7;
	dados[5].nome = "Ana"; 
	dados[5].sexo = 'F';
	
	dados[6].codigo = 90;
	dados[6].nome = "Agatha"; 
	dados[6].sexo = 'F';
	
	dados[7].codigo = 60;
	dados[7].nome = "Alice"; 
	dados[7].sexo = 'F';
	
	dados[8].codigo = 50;
	dados[8].nome = "Alícia"; 
	dados[8].sexo = 'F';
	
	dados[9].codigo = 100;
	dados[9].nome = "Allana"; 
	dados[9].sexo = 'F';
	
	dados[10].codigo = 80;
	dados[10].nome = "Amanda"; 
	dados[10].sexo = 'F';
	
	dados[11].codigo = 70;
	dados[11].nome = "Ana"; 
	dados[11].sexo = 'F';
	
	dados[12].codigo = 15;
	dados[12].nome = "Alícia"; 
	dados[12].sexo = 'F';
	
	dados[13].codigo = 110;
	dados[13].nome = "Allana"; 
	dados[13].sexo = 'F';
	
	dados[14].codigo = 18;
	dados[14].nome = "Amanda"; 
	dados[14].sexo = 'F';
	
	dados[15].codigo = 17;
	dados[15].nome = "Ana"; 
	dados[15].sexo = 'F';
}

void imprimirTela(Cliente *dados, int n){
	for (int i = 0; i < n; i++)
		printf("%d \t %s \t ( %c ) \n", dados[i].codigo, dados[i].nome, dados[i].sexo);			
}

#define TAMANHO_MAXIMO 6

typedef Cliente VetorClientes[TAMANHO_MAXIMO]; 

void ordendarPorInsercao(Cliente *dados, int n)
{ 	
	Cliente temporario;
	int i, j;
	for (i = 1; i < n; i++) { 
		temporario = dados[i];  
		j = i - 1;		
		while (j >= 0 && temporario.codigo < dados[j].codigo) { 
			dados[j+1] = dados[j];  
			j--;
		}
		dados[j+1] = temporario;
	} 
}


int main(int argc, char *argv[])
{
	printf("Ordenação por inserção\n");
	VetorClientes dados;
	
	carregarDadosIniciais(dados);	
	 
	printf("Desordenado: \n");
	imprimirTela(dados, TAMANHO_MAXIMO);
		
	ordendarPorInsercao(dados, TAMANHO_MAXIMO);
	
	printf("Ordenado: \n");
	imprimirTela(dados, TAMANHO_MAXIMO);
	
  return 0;
}

