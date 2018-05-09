#include <stdio.h>
#include <stdlib.h>
#define MAIOR(a,b) (a > b) ? a : b;

/////////////////////////////////////////////////////////
//ESTRUTURA HEAP

typedef struct HEAP{
  int size;
  int length;
  int * values;
}heap;



/////////////////////////////////////////////////////////
//CARDAPIO

int compare(int a, int b);

heap * heap_start(int size);
int get_parent(int i);
void heap_up(heap * h, int i);
void heap_down(heap * h, int i);
void heap_insert(heap * h, int value);
void heap_remove(heap * h, int value);
int get_index_of(heap * h, int value);

void heap_print(heap * h, int i, int lvl);
void heap_sort(int * numeros, int size);


/////////////////////////////////////////////////////////
//MAIN
/////////////////////////////////////////////////////////

int main(){

  int temp = 1, size = 10;

  heap * h = heap_start(size);

  while(1){
    scanf("%d", &temp);
    if(temp == 0) break;
    heap_insert(h,temp);
    printf("\n\n");
    heap_print(h,0,0);
  }

  printf("Remover: \n" );

  while(1){
    scanf("%d\n", &temp);
    if(temp == 0) break;
    heap_remove(h,temp);
    printf("\n\n");
    heap_print(h,0,0);
  }


}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////
//FUNÇÕES

int compare(int a, int b){
  return (a > b) ? 1 : 0;
}


heap * heap_start(int size){
  heap * h = malloc(sizeof(heap));
  h->size = size;
  h->length = 0;
  h->values = malloc(sizeof(int) * size);
  return h;
}


int get_parent(int i){
  return (i-1)/2;
}


void heap_insert(heap * h, int value){

  if(h->length >= h->size) return;

  h->values[h->length] = value;

  heap_up(h, h->length++);

}

void heap_up(heap * h, int i){
  int parent = get_parent(i);

  while( i > 0 && (h->values[i] > h->values[parent]) ){
    //SWAP
    int temp = h->values[i];
    h->values[i] = h->values[parent];
    h->values[parent] = temp;

    i = parent;
    parent = get_parent(i);
  }
}

int maior(int a, int b){
  return (a > b) ? a : b;
}

void heap_down(heap * h, int pai){
  int filho;
  if(h->values[2*pai+1] > h->values[2*pai+2])
    filho = 2*pai+1;
  else
    filho = 2*pai+2;

  while(filho <= h->length-1 && (h->values[pai] < h->values[filho])){

    //SWAP
    int temp = h->values[pai];
    h->values[pai] = h->values[filho];
    h->values[filho] = temp;

    pai = filho;

    if(h->values[2*pai+1] > h->values[2*pai+2])
      filho = 2*pai+1;
    else
      filho = 2*pai+2;
  }
}


void heap_remove(heap * h, int value){
  int i = get_index_of(h, value);
  int valor = h->values[i];
  h->values[i] = h->values[h->length-1];
  h->values[h->length-1] = -1;
  h->length--;

  printf("\n\nRemovido: %d\n", valor);

  heap_down(h, i);

  heap_up(h, i);

}


int get_index_of(heap * h, int value){
  for(int i = 0; i < h->length; i++)
    if(h->values[i] == value) return i;
}


void heap_print(heap * h, int i, int lvl){
    if(i < h->length){
      //left
      heap_print(h,2*i + 1, lvl+1);
      //printf
      for(int i = 0; i < lvl; i++) printf("-- ");
      printf("%d\n",h->values[i]);
      //right
      heap_print(h,2*i+2,lvl+1);
    }
}


void heap_sort(int * numeros, int size){
  heap * h = heap_start(size);
  for(int i = 0; i < size; i++){
    heap_insert(h,numeros[i]);
  }
  for(int i = 0; i < size; i++){
    //printf("\n\n");
    //heap_print(h,0,0);
    int valor = h->values[0];
    h->values[0] = h->values[h->length-1];
    h->values[--(h->length)] = -1;
    heap_down(h,0);
    printf((h->length==0) ? "%d\n" : "%d ",valor);
  }
}
