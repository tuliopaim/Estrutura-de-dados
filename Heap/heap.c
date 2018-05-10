#include <stdio.h>
#include <stdlib.h>

/////////////////////////////////////////////////////////
//ESTRUTURA HEAP
/////////////////////////////////////////////////////////

typedef struct HEAP{
  int size;
  int length;
  int * values;
}heap;


/////////////////////////////////////////////////////////
//CARDAPIO
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
heap * heap_start(int size);
/////////////////////////////////////////////////////////

heap * heap_start(int size){
  heap * h = malloc(sizeof(heap));
  h->size = size;
  h->length = 0;
  h->values = malloc(sizeof(int) * size);
  return h;
}


/////////////////////////////////////////////////////////
void heap_up(heap * h, int i);
/////////////////////////////////////////////////////////

void heap_up(heap * h, int i){
  int parent = (i-1)/2;
  while((parent >= 0) && h->values[parent] < h->values[i]){
    int temp = h->values[parent];
    h->values[parent] = h->values[i];
    h->values[i] = temp;

    i = parent;
    parent = (i-1)/2;
  }
}


/////////////////////////////////////////////////////////
void heap_down(heap * h, int i);
/////////////////////////////////////////////////////////

void heap_down(heap * h, int i){
  int l = 2*i+1;
  int r = 2*i+2;
  int maior;

  if(l >= h->length) return; // SE NÃO HOUVER FILHOS
  //FILHO DA ESQUERDA
  if(h->values[l] > h->values[i]) maior = l;
  else maior = i;
  //FILHO DA DIREITA SE HOUVER
  if(r < h->length && h->values[r] > h->values[maior]) maior = r;
  //SWAP
  if(i!=maior){
    int temp = h->values[maior];
    h->values[maior] = h->values[i];
    h->values[i] = temp;
    heap_down(h,maior);
  }
}


/////////////////////////////////////////////////////////
void heap_insert(heap * h, int value);
/////////////////////////////////////////////////////////

void heap_insert(heap * h, int value){
  if(h->length>=h->size) return ;
  h->values[h->length] = value;
  heap_up(h, h->length++);
}

/////////////////////////////////////////////////////////
int get_index_of(heap * h, int value);
/////////////////////////////////////////////////////////

int get_index_of(heap * h, int value){
  for(int i = 0; i < h->length; i++){
    if(h->values[i] == value) return i;
  }
}


/////////////////////////////////////////////////////////
void heap_remove(heap * h, int value);
/////////////////////////////////////////////////////////

void heap_remove(heap * h, int value){
  int i = get_index_of(h,value);
  int temp = h->values[i];
  h->values[i] = h->values[--h->length];
  h->values[h->length] = temp;

  heap_down(h,i);
  heap_up(h,i);
}

/////////////////////////////////////////////////////////
void heap_print(heap * h, int i, int lvl);
/////////////////////////////////////////////////////////

void heap_print(heap * h, int i, int lvl){
  if(i < h->length){
    heap_print(h, 2*i+2,lvl+1);

    for(int i = 0; i < lvl; i++) printf((i==0) ? "  " : "-- ");
    printf("%d\n", h->values[i]);

    heap_print(h, 2*i+1,lvl+1);
  }
}


/////////////////////////////////////////////////////////
void heap_sort(heap * h, int size);
/////////////////////////////////////////////////////////

void heap_sort(heap * h, int size){
  for (int i = (size/2)-1; i >= 0 ; i--){
    heap_down(h, i);
  }

  while(h->length-- > 1){
    int temp = h->values[h->length];
    h->values[h->length] = h->values[0];
    h->values[0] = temp;
    heap_down(h,0);
    // PASSO A PASSO
    // for(int i = 0; i< size; i++) printf("%d ", h->values[i]);
    // printf("\n" );
  }




}




/////////////////////////////////////////////////////////
//MAIN
/////////////////////////////////////////////////////////

int main(){

  int temp = 1, size = 10, i = 0;
  int numeros[size];
  heap * h = heap_start(size);
  while(1){
    scanf("%d", &temp);
    if(temp == 0) break;
    // heap_insert(h,temp);
    // printf("\n\n");
    // heap_print(h,0,0);
    h->values[h->length++] = temp;
  }

  //heap_print(h,0,0);

  printf("Numeros[] = ");
  for (size_t j = 0; j < size; j++) {
    printf("%d ", h->values[j]);
  }printf("\n");

  heap_sort(h, size);

  printf("Numeros[] = ");
  for (size_t j = 0; j < size; j++) {
    printf("%d ", h->values[j]);
  }printf("\n");

  // printf("Remover: \n" );
  //
  // while(1){
  //   scanf("%d\n", &temp);
  //   if(temp == 0) break;
  //   heap_remove(h,temp);
  //   printf("\n\n");
  //   heap_print(h,0,0);
  // }
}
