#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _node Node;
typedef struct _set Set;

typedef struct _node {
  int data;
  Node *n;
  Set *s;
} Node;

typedef struct _set{
  Node *rep;
  Set *n,*p;
  size_t count;
} Set;

typedef struct _unionFind{
  size_t setCount;
  Set *sets;
} UnionFind;

Set *_createSet(Node *n){
  Set *s = (Set*)malloc(sizeof(Set));
  s->rep = n;
  s->n = s->p = NULL;
  s->count = 1;
  return s;
}

Node *_createNode(int data){
  Node *n = (Node*)malloc(sizeof(Node));

  n->n = NULL;
  n->s = NULL;
  n->data = data;

  return n;
}

UnionFind *createUnionFind(){
  UnionFind *uf = (UnionFind*)malloc(sizeof(UnionFind));
  uf->setCount = 0;
  uf->sets = NULL;

  return uf;
}

Set *makeSet(int data, UnionFind *u){
  Node *n = _createNode(data);
  Set *s = _createSet(n);
  n->s = s;

  ++u->setCount;

  if(u->sets == NULL){
      u->sets = s;
  }else{
    Set *tmp = u->sets;
    while(tmp->n != NULL) tmp = tmp->n;
    s->p = tmp;
    tmp->n = s;
  }

  return s;
}

void printSets(UnionFind *u){
  Set *tmp = u->sets;
  while(tmp != NULL) {
    printf("Rep: %i\tElem: ", tmp->rep->data);
    Node *t = tmp->rep;
    while(t != NULL){
      printf("%i (%i), ", t->data, t->s->rep->data);
      t = t->n;
    }
    printf("\n");
    tmp = tmp->n;
  }
  printf("======================\n");
}

Set *findSets(UnionFind *u, int a){
    Set *tmp = u->sets;
    while(tmp != NULL) {
      Node *t = tmp->rep;
      while(t != NULL){
        if(t->data == a) return tmp;
        t = t->n;
      }
      tmp = tmp->n;
    }
    return NULL;
}

bool unionSet(UnionFind *u, Set *setA, Set *setB){
  if(setA == NULL || setB == NULL) return false;
  if(setA == setB) return true;

  if(setA->count < setB->count){
    Set *t = setA;
    setA = setB;
    setB = t;
  }

  Node *tmp = setB->rep;
  Node *lastA = setA->rep;

  while(lastA->n != NULL) lastA = lastA->n;
  lastA->n = tmp;

  while(tmp != NULL){
    tmp->s = lastA->s;
    ++setA->count;
    tmp = tmp->n;
  }

  if(setB->n != NULL) setB->n->p = setB->p;
  if(setB->p != NULL) setB->p->n = setB->n;

  free(setB);

  --u->setCount;

  return true;
}

bool unionSetByNum(UnionFind *u, int a, int b){
  Set *setA = findSets(u, a),
      *setB = findSets(u, b);

  return unionSet(u, setA, setB);
}

int main(int argc, char const *argv[]) {
  UnionFind *u = createUnionFind();
  //
  // makeSet(7, u);
  // makeSet(8, u);
  // makeSet(14, u);
  // makeSet(9, u);
  // makeSet(10, u);
  // makeSet(11, u);
  // makeSet(79, u);
  // makeSet(24, u);
  // makeSet(36, u);
  // makeSet(12, u);
  //
  // unionSetByNum(u, 7, 8);
  // unionSetByNum(u, 8, 14);
  // printSets(u);
  //
  // unionSetByNum(u, 9, 10);
  // unionSetByNum(u, 10, 11);
  // printSets(u);
  //
  // unionSetByNum(u, 79, 24);
  //
  // unionSetByNum(u, 453, 36);
  // unionSetByNum(u, 36, 12);
  // unionSetByNum(u, 79, 36);


  for(int i = 0; i < 500; ++i){
    makeSet(i,u);
  }
  printSets(u);
  unionSetByNum(u, 0, 264);
  unionSetByNum(u, 0, 262);
  unionSetByNum(u, 0, 265);
  unionSetByNum(u, 0, 268);


  for(int i = 0; i < 400000; ++i){
    int a = 0;
    int b = rand() % 5000;
    //if(a == 0 || b == 0) continue;
    printf("%i %i\n", a, b);
    unionSetByNum(u, a, b);
  }

  printSets(u);


  return 0;
}
