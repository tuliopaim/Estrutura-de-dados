#include <stdio.h>
#include <stdlib.h>

typedef struct NODE{
  int value;
  struct NODE * root;
  struct NODE * prox;
}node;

typedef node * set;

set make_set(int value);
int set_size(set a);
node * set_union(set a, set b);
void set_print(set a);
set find(set a);


int main(){

  int temp;

  set a = make_set(1);
  set b = make_set(2);
  set c = make_set(3);
  set d = make_set(4);
  set e = make_set(5);

  set_print(a);
  set_print(b);
  set_print(c);
  set_print(d);
  set_print(e);

  //printf("%d %d\n", set_size(a), set_size(b));
  set ab = set_union(a,b);
  set_print(ab);
  set ac = set_union(ab,c);
  set_print(ac);
  set bd = set_union(b,d);
  set_print(bd);
  set be = set_union(b,e);
  set_print(be);
  //set_print(b);


  return 0;
}

set make_set(int value){
  set new = (node*)malloc(sizeof(node));
  new->value = value;
  new->root = new;
  new->prox = NULL;
  return new;
}

int set_size(set a){
  int count = 0;
  set temp = a;
  while(temp!=NULL){
    count++;
    temp = temp->prox;
  }
  return count;
}

node * set_union(set a, set b){
  set new, temp1, temp2;
  temp1 = find(a);
  temp2 = find(b);
  if(set_size(temp1) >= set_size(temp2)){
    new = temp1;
    temp1 = a;
    temp2 = b;
  }else{
    new = temp2;
    temp1 = b;
    temp2 = a;
  }
  while(temp1->prox!=NULL){
    temp1 = temp1->prox;
  }

  temp1->prox = temp2;

  while(temp1=NULL){
    temp1->root = new;
    temp1 = temp1->prox;
  }
  return new;
}

void set_print(set a){
  set temp = a;
  printf("[%d]->", temp->value);
  temp = temp->prox;
  while (temp!=NULL) {
    printf("%d->", temp->value);
    temp = temp->prox;
  }printf("NULL\n");
}

set find(set a){
  return a->root;
}
