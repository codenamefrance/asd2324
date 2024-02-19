#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

/* Si scriva una funzione wrapper int f(T t) (e la relativa funzione ricorsiva) che ricevuto in input 
un albero n-ario di interi t
di tipo T conti la lunghezza del cammino più lungo contenente solo valori positivi o nulli. 
Fornire la definizione del tipo T e del
tipo nodo al suo intero, come ADT di prima classe e come quasi ADT rispettivamente, indicando esplicitamente 
la divisione in
moduli adottata. Per rappresentare l'albero richiesto, ogni nodo tiene traccia dei figli mediante un vettore 
di puntatori a nodo e
il numero di figli.*/

#define N 5

typedef struct ntree *NTREE;

typedef struct treenode *treeNode;

struct treenode{
    int val;
    treeNode children[N];
    int nChildren;
};

struct ntree{
    treeNode root;
    treeNode z;
};


int f(NTREE tree){
    int max = INT_MIN;

    for(int i=0; i<N; i++){
        heightR(tree->root->children[i], tree->z, &max, tree->root->val, 1);
    }

    return max;

}


void heightR(treeNode root, treeNode z, int *max, int prev, int valpath){

    if(root == z || (root->val) * prev < 0){
        if(valpath > *max){
            *max = valpath; 
            valpath = 0;
        }
    }

    for(int i=0; i<N; i++){
        heightR(root->children[i], z, max, root->val, valpath);
    }

}