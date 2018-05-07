#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>
#include "sorts.h"
#define RANGE 1000

void ler(FILE * p, int * vetor, int size){
	int temp=0, j=0, i;
	//LER VETORES DE ARQUIVO E ARMAZENAR
	for(i=0;i<size;i++){
		fscanf(p, "%d,", &temp);
		vetor[j++] = temp;
	}
}

int main(){
	int temp[1000000];
	int size;
	int i, j;
	long double tempo[20], media=0;
	clock_t c2, c1;
	char nome[20];
	FILE * p;

	//TAMANHO DO VETOR
	printf("Tamanho do vetor: ");
	scanf("%d", &size);

	//ABRIR ARQUIVO
	printf("Nome do Arquivo: ");
	scanf(" %s", nome);
	p = fopen(nome, "r");
	if(p == NULL) printf("TEM ESSE ARQUIVO AQUI NÃO, BURRO\n");

	//QUANTOS VETORES
	int qntV;
	printf("Quantos Vetores: ");
	scanf("%d", &qntV);

	//LER DO ARQUIVO
	for (i = 0; i < qntV; ++i){
		ler(p, temp, size);

		c1=clock(); //PEGA O CLOCK INICIAL DO PROCESSADOR
		heap_sort(temp, size);
		c2=clock(); //CLOCK FINAL
		tempo[i] = (c2-c1)*1000.0/CLOCKS_PER_SEC;
		printf("Tempo vetor %d: %Lf\n",i+1,tempo[i]);
		media+=tempo[i];
	}
	media/=qntV;
	printf("Media: %LF\n", media);
	fclose(p);

	//SALVAR MEDIAS EM ARQUIVO
	p = fopen("tempo.txt", "a");
	for(i=0;i<qntV;i++)
		fprintf(p, "Tempo Vetor %d: %LF\n", i+1, tempo[i]);
	fprintf(p, "------------\nMedia: %LF\n", media);
	fclose(p);

	return 0;
}
