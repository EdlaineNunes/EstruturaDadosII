#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct Nomes{
	int mat;
	char nome[100];
	int dia;
	int mes;
	int ano;
	char curso[50];	
	struct Nomes *prox,*ant;
}Nomes;

/*
void getBubble(Nomes * inicio){
	for(int i=0; i<cont; i++)
		for (int j=0; j<cont-i-1;j++)
			if (inicio->mat[j] > inicio->mat[j+1]){
				int aux = vet[j];
				vet[j] = vet[j+1];
				vet[j+1] = aux;
			}
}
*/

void getNome(Nomes * i){
	printf("Nome: %s\t Nº matrícula %d\t DNasc: %d/%d/%d\t Curso %s\n", i->nome, i->mat, i->dia, i->mes, i->ano, i->curso);
}

void getFila(Nomes * i){
	while (i){
		getNome(i);
		i = i -> prox;
	}
	getchar();	
}

void getPilha(Nomes * fim){
	while(fim){
		getNome(fim);
		fim = fim->ant;
	}	
	getchar();
}

int geraMat(Nomes * inicio, int cont){
	srand(time(NULL));
	int aux, rep;
	do{
		aux = rand() % 4;
		rep = 0;
		for(int i=0; i<cont; i++){
			if(aux == inicio->mat){
				rep = 1;
				break;
			}
			else
				inicio = inicio->prox;
		}
		if (rep)
			continue;		
		printf("%d\n", aux);
		return aux;
	}while(1);
}

Nomes* getFim(Nomes* i){
	while(i->prox)
		i = i->prox;
	return i;	
}

Nomes* setNome(Nomes * i){
	int cont=0;
	Nomes *novo = malloc(sizeof(Nomes));
	printf("\nCADASTRO\n");
	printf("Nº de matrícula:\t");
	novo->mat = geraMat(i,cont);
	cont++;
	printf("Insira o nome: ");
	scanf(" %[^\n]s",novo->nome);
	printf("Insira o dia do nascimento: ");
	scanf(" %d",&novo->dia);
	printf("Insira o mês do nascimento: ");
	scanf(" %d",&novo->mes);
	printf("Insira o ano do nascimento: ");
	scanf(" %d",&novo->ano);
	printf("Insira o nome do curso: ");
	scanf(" %[^\n]s",novo->curso);
	novo->ant = novo->prox = NULL;
	if (i){
		Nomes * fim = getFim(i);
		novo->ant = fim;
		fim->prox = novo;
		getchar();
		return i;
	}
	getchar();
	return novo;
}

int menu(){
	int opc;
	system("clear");
	printf("\n\t\t\tMENU PRINCIPAL\n");
	printf("\t1- Cadastro\n");
	printf("\t2- Listar PILHA\n");
	printf("\t3- Listar FILA\n");
	printf("\t4- Ordenação por INSERÇÃO\n");
	printf("\t5- Ordenação por SELEÇÃO\n");
	printf("\t6- Ordenação por BUBBLE SORT\n");
	printf("\t7- EXIT\n");
	printf("Opc:");
	scanf(" %d",&opc);
	getchar();
	return opc;
}

int menuOpc(){
	Nomes *inicio = NULL;
	do{
		switch(menu()){
			case 1: inicio = setNome(inicio);
					break;
			case 2: getPilha(getFim(inicio));
					break;
			case 3: getFila(inicio);
					break;
			case 4: 
					break;
			case 5: 
					break;
			//case 6: getBubble(inicio);
					break;
			case 7: printf("\n\tFINALIZADO COM SUCESSO!");
					return 0;
			default: printf("\n\nOpção Inválida!!!\n\n");
		}
	}while(1);
	return 0;
}

int main(int argc, char **argv)
{
	menuOpc();
	return 0;
}

