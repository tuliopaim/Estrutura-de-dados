#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
  int value;
  struct Node * left;
  struct Node * right;
}node;

typedef node * tree;

tree * tree_start();
node * node_start(int value);
void tree_insert(tree * root, int value);
void tree_inOrdem(tree * root);

int main(){

  int tmp;
  tree * root = tree_start();
  while(1){
    scanf("%d", &tmp);
    if(tmp == 0) break;
    tree_insert(root,tmp);
  }
  tree_inOrdem(root);

  return 0;
}

tree * tree_start(){
  tree * new = (tree*)malloc(sizeof(tree));
  *new = NULL;
  return new;
}

node * node_start(int value){
  node * new = (node*)malloc(sizeof(node));
  new->value = value;
  new->left = NULL;
  new->right = NULL;
  return new;
}

//INSERIR

void tree_insert(tree * root, int value){
  printf("Passou aqui");
  tree * aux = root;
  while(value < (*aux)->value && (*aux)!=NULL){
    printf("Passou em %d\n", ((*aux))->value);
    (*aux) = (*aux)->left;
  }
  while(value > (*aux)->value && (*aux)!=NULL){
    printf("Passou em %d\n", ((*aux))->value);
    (*aux) = (*aux)->right;
  }
  node * new = node_start(value);
  (*aux) = new;
  printf("%d inserido\n", (*root)->value);
}


//IN-ORDEM

void tree_inOrdem(tree * root){
  if((*root)!=NULL){
    tree_inOrdem(&(*root)->left);
    printf("%d\n",(*root)->value);
    tree_inOrdem(&(*root)->right);
  }
}
