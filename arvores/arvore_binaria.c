#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>

/*
    BIBLIOTECA TULIO PAIM
    ARVORES BINARIAS
*/


//------------------------------------------------------
//STRUCTS

struct Node{
    int value;
    struct Node * right;
    struct Node * left;
};

typedef struct Node node;
typedef node * tree;

/*DECLARAÇÕES*/

//aux
int maior(int a, int b);
node * menorNo(tree * no);

//iniciar
tree * tree_start();
node * node_start();

//operações em arvores
void tree_inserir(tree * root, int value);
void tree_remove(tree * root, int value);
int tree_altura(tree * root);
int larguraLvl(node * root, int level);
int tree_largura(node * root);

//percursos
void tree_preOrdem(tree * root);
void tree_inOrdem(tree * root);
void tree_posOrdem(tree * root);
void tree_print_lvl(tree * root, int lvl);


//MAIN

int main(){

    int tmp;
    tree * root1 = tree_start();
    srand(time(NULL));

    for(int i=0;i<30;i++){
      tree_inserir(root1, rand() % 1000);
    }
    printf("Arvore 1:\n");
    tree_print_lvl(root1,0);

    tree * root2 = tree_start();

    for(int i=0;i<30;i++){
      tree_inserir(root2, rand() % 1000);
    }
    printf("\n\n\nArvore 2:\n");
    tree_print_lvl(root2,0);
    

    return 0;
}

//FUNÇÕES AUXILIARES
//------------------------------------------------------

int maior(int a, int b){
    return (a > b) ? a : b;
}

//------------------------------------------------------
//INICIADORES

//nova arvore
tree * tree_start(){
  tree * new = (tree*)malloc(sizeof(tree));
  *new = NULL;
  return new;
}

//novo nó
node * node_start(){
  node * new = (node*)malloc(sizeof(node));
  new->right = NULL;
  new->left = NULL;
  return new;
}

//-----------------------------------------------------
//FUNÇÕES

//Inserir em ordem

void tree_inserir(tree * root, int value){
  if((*root) == NULL){
      node * new = node_start();
      new->value = value;
      (*root) = new;
      //printf("%d adicionado!\n",(*root)->value );
      return ;
  }
  else if(value < (*root)->value){
      tree_inserir((&(*root)->left), value);
  }else if(value > (*root)->value){
      tree_inserir((&(*root)->right), value);
  }
}

//remover

node * menorNo(tree * no);

void tree_remove(tree * root, int value){
  if((*root) == NULL) return ;
  //PERCORRE ATÉ ACHAR O NÓ
  if(value < (*root)->value){
      tree_remove((&(*root)->left), value);
  }
  if(value > (*root)->value){
      tree_remove((&(*root)->right), value);
  }
  //QUANDO ACHAR
  else if(value == (*root)->value){
      node * aux = (*root);
      //FOLHA (nenhum filho)
      if((*root)->left == NULL && (*root)->right == NULL){
          free(aux);
          (*root) = NULL;
      }
      //APENAS FILHO DA ESQUERDA
      else if ((*root)->left != NULL && (*root)->right == NULL){
          (*root) = aux->left;
          aux->left = NULL;
          free(aux);
          aux = NULL;
      }
      //APENAS FILHO DA DIREITA
      else if ((*root)->left == NULL && (*root)->right != NULL){
          (*root) = aux->right;
          aux->right = NULL;
          free(aux);
          aux = NULL;
      }
      //SE TIVER OS DOIS FILHOS
      else{
          //pegar o maior nó da esquerda, ou o menor da direita
          //ou seja, o numero mais próximo do valor removido
          (*root) = menorNo(&(*root)->right);
          (*root)->left = aux->left;
          (*root)->right = aux->right;
          aux->left = aux->right = NULL;
          free(aux);
          aux = NULL;
      }
  }
}

node * menorNo(tree * no){
  //chegar até o final da perna esquerda (menor valor)
  if((*no)->left != NULL){
      return menorNo(&(*no)->left);
  }else{
      node * aux = (*no);
      //verificar se há filhos à direita
      if((*no)->right != NULL){
          (*no) = (*no)->right;
      }else (*no) = NULL;
      return aux;
  }
}

//altura da arvore

int tree_altura(tree * root){
  if(*root == NULL) return 0;
  else{
    return 1 + maior(tree_altura(&(*root)->left), tree_altura(&(*root)->right));
  }
}


//LARGURA
int larguraLvl(node * root, int level){
  if(root == NULL) return 0;
  if(level == 1) return 1;
  else{
    return(larguraLvl(root->left, level-1) + larguraLvl(root->right, level-1));
  }
}

int tree_largura(node * root){
  int i, largura = 0;
  int h = tree_altura(&root);

  for(i=1;i<=h;i++){
    int temp = larguraLvl(root, i);
    //printf("Largura lvl %d: %d\n", i, temp);
    largura = maior(largura, temp);
  }
  return largura;
}


//IMPRIMIR
//PERCURSO PRE-ORDEM

void tree_preOrdem(tree * root){
  if((*root)!=NULL){
    printf("%d ", (*root)->value);
    tree_preOrdem(&(*root)->left);
    tree_preOrdem(&(*root)->right);
  }
}

//IN-ORDEM

void tree_inOrdem(tree * root){
  if((*root)!=NULL){
    tree_inOrdem(&(*root)->left);
    printf("%d ",(*root)->value);
    tree_inOrdem(&(*root)->right);
  }
}

//POS-ORDEM

void tree_posOrdem(tree * root) {
  if((*root)!=NULL){
    tree_posOrdem(&(*root)->left);
    tree_posOrdem(&(*root)->right);
    printf("%d ", (*root)->value);
  }
}

//IMPRIMIR POR NIVEIS

void tree_print_lvl(tree * root, int lvl){
  if((*root) != NULL){

    /*chama direita*/
    tree_print_lvl(&(*root)->right, lvl+1);

    /*imprime*/
    int i;
    for(i = 0; i < lvl; i++) printf((i==0) ? "  " : "-- ");
    printf("%d\n",(*root)->value);

    /*chama esquerda*/
    tree_print_lvl(&(*root)->left, lvl+1);

  }
}



//FREE
//LIBERAR MEMORIA ALOCADA

void tree_free(tree * root){
  if(*root != NULL){
    tree_free(&(*root)->left);
    tree_free(&(*root)->right);
    free(*root);
  }
}

//------------------------------------------------------
//------------------------------------------------------
//SEM RECURSÃO
//------------------------------------------------------
//------------------------------------------------------



//INSERIR SEM RECURSÃO
//------------------------------------------------------


void tree_insert_sem_recursao(tree * root, int value){
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
