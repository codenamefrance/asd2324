#include <stdio.h>
#include <stdlib.h>

// Contenuto del file list.h
typedef struct lista *list;


// Contenuto del file list.c
typedef struct listnode *link;

struct listnode{
    int val;
    link next;
    link prev;
};

struct lista{
    link head;
    link tail;
    int size;
};

// funzioni di servizio
link NEWnode(int val, link next, link prev);
void swap(list L, int k);
list LISTinit();
void LISTinsTail(list lista, int val);
void LISTprint(list lista);

list LISTinit(){
    list lista;
    lista = malloc(sizeof(*lista));

    lista->head = NULL;
    lista->tail = NULL;

    lista->size = 0;

    return lista;
}

void LISTinsTail(list lista, int val){
    link x;
    if(lista->size == 0){
        lista->head = NEWnode(val, NULL, NULL);
        lista->tail = lista->head;
        lista->size++;
        return;
    }
    
    x = NEWnode(val, NULL, lista->tail);
    lista->tail->next = x;

    lista->tail = x;
    lista->size++;
    return;
}

void LISTprint(list lista){
    link x;

    for(x=lista->head; x!=NULL; x=x->next) printf("%d ", x->val);
    printf("\n");
    return;

}

void swap(list L, int k){
    link a, b;
    link x;
    int cnt, tmp;
    
    if(k>=L->size) return;
    
    for(x=L->head, cnt=0; cnt<k; cnt++, x=x->next);
    a = x;
    for(x=L->tail, cnt=0; cnt<k; cnt++, x=x->prev);
    b = x;

    
    tmp = a->val;
    a->val = b->val;
    b->val = tmp;
    
    return;
}


link NEWnode(int val, link next, link prev){
    link node = malloc(sizeof(*node));
    node->val = val;
    node->next = next;
    node->prev = prev;

    return node;
}

int main(){
    list lista;
    lista = LISTinit();

    LISTinsTail(lista, 10);
    LISTinsTail(lista, 20);
    LISTinsTail(lista, 30);
    LISTinsTail(lista, 40);
    LISTinsTail(lista, 50);
    LISTinsTail(lista, 60);
    LISTinsTail(lista, 70);
    LISTprint(lista);
    swap(lista, 6);
    LISTprint(lista);


}