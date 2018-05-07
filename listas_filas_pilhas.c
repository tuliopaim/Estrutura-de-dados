#include <stdio.h>
#include <stdlib.h>

/*
    BIBLIOTECA TULIO PAIM
    LISTA PILHA FILA 
*/

//------------------------------------------------------
//STRUCTS

struct Node{
    int data;
    struct Node * prox;
};

typedef struct Node node;

//------------------------------------------------------
//NOVO NODE

node * node_start(){
    node * new = malloc(sizeof(node));
    new->prox = NULL;
    return new;
}

//------------------------------------------------------
//FUNÇÕES COMUNS A TODAS

//VERIFICAR SE LISTA ESTÁ VAZIA

int lista_isEmpty(node * lista){
    return (lista->prox == NULL) ? 1 : 0;
}

//At Index
//retorna um ponteiro para determinada posição

node * lista_atIndex(node * lista, int index){
    if(!lista_isEmpty(lista)){
        node * tmp = lista;
        for(int i = 0; i < index; i++){
            if(tmp==NULL){
                printf("Essa posição não existe animal lista_atIndex()\n");
                return 0;
            }
            tmp = tmp->prox;
        }
        return tmp;
    }
}

//Index Of
//retorna o indice de determinado item da lista e -1 se não houver

int lista_indexOf(node * lista, int data){
    if(!lista_isEmpty(lista)){
        node * tmp = lista->prox;
        for(int cont = 1; tmp!=NULL; cont++){
            if(tmp->data == data) return cont;
            tmp = tmp->prox;
        }
        return -1;
    }
}

//LISTA IMPRIME

void lista_imprime(node * lista){
    if(!lista_isEmpty(lista)){
        node * tmp = lista->prox;
        while(tmp!=NULL){
            printf("%d",tmp->data);
            tmp = tmp->prox;
        }
    }
}

//TAMANHO DA LISTA

int lista_size(node * lista){
    if(!lista_isEmpty(lista)){
        int cont;
        node * tmp = lista;
        for(cont = 0; tmp->prox!=NULL; cont++) tmp = tmp->prox;
        return cont;
    }
    return 0;
}

//------------------------------------------------------
//LISTA NORMAL

void lista_insere(node * lista, int data){
    node * tmp = lista;
    while(tmp->prox!=NULL) tmp = tmp->prox;
    node * new = node_start();
    new->data = data;
    tmp->prox = new;
}

//REMOVE UTILIZANDO FUNÇÕES ANTERIORES
//indexOf e atIndex

void lista_remove(node * lista, int data){
    int index = lista_indexOf(lista, data);
    node * atual = lista_atIndex(lista, index);
    node * anterior = lista_atIndex(lista,index-1);
    anterior->prox = atual->prox;
    free(atual);
}

//REMOVE NORMAL
//FAZENDO O SEARCH

void lista_remove2(node * lista, int data){
    node * anterior = lista;
    node * atual = anterior->prox;
    while(atual!=NULL){
        if(atual->data == data){
            anterior->prox = atual->prox;
            free(atual);
        }
        anterior = atual;
        atual = atual->prox;
    }
}


//------------------------------------------------------
//PILHA

//add
void pilha_insere(node * pilha, int data){  
    node * tmp = pilha;
    while(tmp->prox!=NULL) tmp = tmp->prox;
    node * new = node_start();
    new->data = data;
    tmp->prox = new;
    printf("%d inserido\n", tmp->prox->data);
}

//remove
void pilha_remove(node * pilha){
    node * back = pilha;
    node * tmp = back->prox;

    while(tmp->prox!=NULL){
        back = tmp;
        tmp = tmp->prox;
    }

    back->prox = NULL;
    free(tmp);
}

//------------------------------------------------------
//FILA

//add
void fila_insere(node * lista, int data){
    node * tmp = lista;
    while(tmp->prox!=NULL) tmp = tmp->prox;
    node * new = node_start();
    new->data = data;
    tmp->prox = new;
}

//remove
void fila_remove(node * lista){
    if(!lista_isEmpty(lista)){
        node * temp = lista;
        node * atual = temp->prox;
        temp->prox = atual->prox;
        free(atual);
    }
}




int main(){

    node * LISTA = node_start();
    int temp;
    while(1){
        printf("Digite o valor: ");
        scanf("%d", &temp);
        if(temp==0) break;
        pilha_insere(LISTA, temp);
    }
    while(1){
        printf("Valor para remover: \n");
        printf("(0 para sair)\n");
        scanf("%d", &temp);
        if(temp == 0) break;
        lista_remove(LISTA, temp);
    }
    printf("Size: %d\n", lista_size(LISTA));
    

}