#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _node{
	int key;
	int height;
	struct _node * left;
	struct _node * right;
}Node;

//nó
typedef Node * node;
//arvore
typedef Node ** tree;

//novo nó
node new_node(int key);

node new_node(int key){
	node new = (node)malloc(sizeof(Node));
	new->key = key;
	new->height = 1;
	new->left = new->right = NULL;
	return new;
}

//maximo de a e b
int getMax(int a, int b){ return (a > b) ? a : b;}

//pegar altura

int getHeight(node n);

int getHeight(node n){
	if(n == NULL)
		return 0;
	return n->height;
}

//balanceamento
int getBalance(node n);

int getBalance(node n){
	if(n == NULL)
		return 0;
	return getHeight(n->left) - getHeight(n->right);
}

//-------------------
//rotacionar para direita

node right_rotate(node p);

node right_rotate(node p){
	node f = p->left;
	node temp = f->right;

	//rotacionar
	p->left = temp;
	f->right = p;

	//atualizar alturas
	p->height = 1 + getMax(getHeight(p->left), getHeight(p->right));
	f->height = 1 + getMax(getHeight(f->left), getHeight(f->right));

	//retorna a nova raiz
	return f;
}

node left_rotate(node p);

//rotacionar para esquerda
node left_rotate(node p){
	node f = p->right;
	node temp = f->left;

	//rotacionar
	p->right = temp;
	f->left = p;

	//atualizar alturas
	p->height = 1 + getMax(getHeight(p->left), getHeight(p->right));
	f->height = 1 + getMax(getHeight(f->left), getHeight(f->right));

	//retornar a nova raiz
	return f;
}

//---------------------
//inserir

node avl_insert(node root, int key);

node avl_insert(node root, int key){
	//inserir
	if(root == NULL)
		return (new_node(key));
	//se for menor
	if(key < root->key)
		root->left = avl_insert(root->left, key);
	else if(key > root->key)
		root->right = avl_insert(root->right, key);
	else
		return root;

	//atualizar altura do nó
	root->height = 1 + getMax(getHeight(root->left), getHeight(root->right));

	//balancear
	int balance = getBalance(root);	

	//left
	if(balance > 1){
		//left left{
		if(key < root->left->key)
			return right_rotate(root);

		//left right
		else if(key > root->left->key){
			root->left = left_rotate(root->left);
			return right_rotate(root);
		}
	}
	//right
	else if(balance < -1){
		//right left
		if(key < root->right->key){
			root->right = right_rotate(root->right);
			return left_rotate(root);
		}
		
		//right right
		else if(key > root->right->key)
			return left_rotate(root);
	}

	//retorna a raiz
	return root;

}

//imprime a arvore em niveis
void avl_print_lvl(node root, int lvl){
	if(root != NULL){
		/*chama direita*/
		avl_print_lvl(root->right, lvl+1);

		/*imprime*/
		int i;
		for(i = 0; i < lvl; i++) printf((i==0) ? "  " : "-- ");
		printf("%d\n",root->key);

		/*chama esquerda*/
		avl_print_lvl(root->left, lvl+1);

	}
}


int main(){

	int temp, i;
	node root1 = NULL;

	srand(time(NULL));

	for(i=0;i<20;i++){
		int temp = rand() % 1000;
		//scanf("%d", &temp);
		//if(!temp) break;
		printf("%d ", temp);
		root1 = avl_insert(root1,temp);
	}
	printf("\n\nArvore 1: \n");
	avl_print_lvl(root1,0);

	return 0;
}


