#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int fatorial(int n){
	if ( n <= 0)
		return 1;
	return (n * fatorial(n-1));	
}

int main(int argc, char **argv)
{
	int n;
	scanf(" %d",&n);
	int r = fatorial (n);
	printf("O fatorial de %d é: %d",n,r);
	return 0;
}

