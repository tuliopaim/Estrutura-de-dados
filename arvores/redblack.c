#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


struct Node{
	int key;
	bool color;
	struct Node * parent;
	struct Node * left;
	struct Node * right;
};

typedef struct Node _node;
typedef struct Node * node;
typedef struct Node ** tree;

tree new_tree();

tree new_tree(){
	tree new = (tree)malloc(sizeof(_node));
	return new;
}


node new_node(int key);

node new_node(int key){
	node new = (node)malloc(sizeof(_node));
	new->key = key;
	new->color = true;
	new->left = NULL;
	new->right = NULL;
	return new;
}

void left_rotate(tree root, node pt);


void left_rotate(tree root, node pt){
	node pt1 = pt;
	node pt2 = pt->right;

	pt1->right = pt2->left;

	if(pt1->right!=NULL){
		pt1->right->parent = pt1; //att pai
	}

	pt2->parent = pt1->parent; //att pai

	//verificar se pai é a raiz
	if(pt1->parent == NULL){
		*root = pt2;
	}

	//conectar o pai de p1 a p2
	else if(pt1->parent->left == pt1){
		pt1->parent->left = pt2;
	}else{
		pt1->parent->right = pt2;
	}

	//p2 vira pai de p1
	pt2->left = pt1;
	pt1->parent = pt2; //att pai
}

void right_rotate(tree root, node pt);

void right_rotate(tree root, node pt){
	node pt1 = pt;
	node pt2 = pt->left;

	//esquerda de pt1 pega direita de pt2

	pt1->left = pt2->right;


	if(pt1->left != NULL)
		pt1->left->parent = pt1;

	pt2->parent = pt1->parent;

	//verificar se pai é a raiz
	if(pt1->parent == NULL)
		*root = pt2;

	//conectar o pai de p1 a p2
	else if(pt1->parent->left == pt1){
		pt1->parent->left = pt2;
	}else{
		pt1->parent->right = pt2;
	}

	//p2 vira pai de p1
	pt2->right = pt1;
	pt1->parent = pt2;


}

void fix_dat_shit(tree root, node pt);

void fix_dat_shit(tree root, node pt){
	node gparent = NULL;
	node parent = NULL;

	//pt é diferente da raiz
	//pt é vermelho
	//pai de pt é vermelho

	while(pt != (*root) && pt->color && pt->parent->color){
		parent = pt->parent;		//nó pai
		gparent = pt->parent->parent;	//nó avô
		//primeiro caso
		//o pai é o filho da esquerda
		if(parent == gparent->left){
			//tio
			node uncle = gparent->right;
			//se o tio for vermelho
			//trocar as cores
			if(uncle!=NULL && uncle->color){
				gparent->color = true;	//avo = red
				parent->color = false;	//pai = preto
				uncle->color = false;	//tio = preto
				pt = gparent;			//pt aponta pro vo
			}
			//se o tio for preto (ou nulo)
			else{
				//filho for a direita
				if(pt == parent->right){
					left_rotate(root, parent);
					pt = parent;
					parent = pt->parent;
				}

				//filho for a esquerda
				right_rotate(root, gparent);
				gparent->color = true;
				parent->color = false;
				pt = parent;
			}
		}
		//segundo caso
		//o pai é o filho da direita
		else{
			node uncle = gparent->left;
			//se o tio for vermelho, trocar as cores
			if(uncle!=NULL && uncle->color){
				gparent->color = true;
				parent->color = false;
				uncle->color = false;
				pt = gparent;
			}
			//se o tio for preto	
			else{
				//se for filho esquerdo
				if(pt == parent->left){
					right_rotate(root, parent);
					pt = parent;
					parent = pt->parent;
				}
				//se for filho direito
				left_rotate(root, gparent);
				gparent->color = true;
				parent->color = false;
				pt = parent;
			}
		}
	}
	(*root)->color = false;
}


void rb_print_lvl(node root, int lvl){
	if(root != NULL){

		/*chama direita*/
		rb_print_lvl(root->right, lvl+1);

		/*imprime*/
		int i;
		for(i = 0; i < lvl; i++) printf((i==0) ? "  " : "-- ");
		printf("%d - %s\n",root->key,
			(root->color) ? "red" : "black");

		/*chama esquerda*/
		rb_print_lvl(root->left, lvl+1);

	}
}


node rb_insert(tree root, node new, node parent, int key); 

node rb_insert(tree root, node new, node parent, int key){

	if((*root) == NULL){
		new->parent = parent;
		(*root) = new;	
		return (*root);
	}

	else if(key < (*root)->key)
		rb_insert(&(*root)->left, new, (*root), key);

	else if(key > (*root)->key)
		rb_insert(&(*root)->right, new, (*root), key);
}


void insert(tree root, int key);

void insert(tree root, int key){
	node new = new_node(key);
	node temp = rb_insert(root, new, NULL, key);
	fix_dat_shit(root, temp);
}



int main(){
	

	int temp, i;
	tree root1 = new_tree();
	srand(time(NULL));

	for(i=0;i<30;i++){
		insert(root1,rand() % 1000);
	}
	printf("Arvore 1: \n");
	rb_print_lvl(*root1,0);


	tree root2 = new_tree();

	for(i=0;i<30;i++){
		insert(root2,rand() % 1000);
	}
	printf("\n\n\nArvore 2: \n");
	rb_print_lvl(*root2,0);


	return 0;
}
