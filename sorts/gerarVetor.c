#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE * p;

void gerar(int size){
	int i;
	for (int i = 0; i < size; ++i)
		fprintf(p, (i!=size-1)?"%d,":"%d\n", rand()%1000);
}

int main(){
	srand((unsigned)time(NULL));
	int size, qnt, i;
	char nome[20];

	printf("Tamanho do vetor: ");
	scanf("%d", &size);
	printf("Nome do Arquivo: ");
	scanf(" %s", nome);

	p = fopen(nome, "w");

	printf("Qnt de vetores: ");
	scanf("%d", &qnt);

	for (int i = 0; i < qnt; ++i)
		gerar(size);

	fclose(p);

	return 0;
}
