#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

typedef struct Set{
  int size;
  int * numeros;
  int * pai;
}set;

set * new_set(int * entradas, int size){
  int maior = 0;
  for (int i = 0; i< size; i++) if(entradas[i] > size) size = entradas[i];

  set * new = (set*)malloc(sizeof(set));

  new->size = size;
  new->numeros = (int)malloc(sizeof(int)*size);
  new->pai = (int)malloc(sizeof(int)*maior);
  return new;
}

void make_set(set * s){
  for(int i = 0; i < s->size; i++){
    s->parent[numeros[i]] = 0;
  }
}


int main(){
  int entradas[SIZE];

  for(int i = 0; i < 10; i++){
    scanf("%d", &temp);
    entradas[i] = temp;
  }

  set * s = new_set();
  make_set(s);

  return 0;
}
