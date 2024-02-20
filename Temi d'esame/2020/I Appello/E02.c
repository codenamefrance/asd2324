/* IN-ORDER VISIT

    2
   / \
  1   3

*/


#include <stdio.h>
#include <stdlib.h>

typedef struct node* link;

struct node { int item; link left; link right; } ;

link NEW(int chiave, link left, link  right) {
  link x = malloc(sizeof *x);
  x->item = chiave; x->left = left; x->right = right;
  return x;
}

link buildTree(int inorder[], int preorder[], int N);
link buildR(int inorder[], int preorder[], int l, int r, int *preid);
int search(int val, int *array, int start, int end);
void visitTree(link root);

link buildR(int inorder[], int preorder[], int l, int r, int *preid){
    int m;
    if(l>r) return NULL;
    
    link tRoot = NEW(preorder[(*preid)++], NULL, NULL);
    
    if(l==r) return tRoot;
    
    m = search(tRoot->item, inorder, l, r);
    
    tRoot->left = buildR(inorder, preorder, l, m-1, preid);
    tRoot->right = buildR(inorder, preorder, m+1, r, preid);
    
    
    return tRoot;    
}

link buildTree(int inorder[], int preorder[], int N){
    int preid=0;
    return buildR(inorder, preorder, 0, N-1, &preid);
}



void visitTree(link root){
    if (root == NULL) return;

    visitTree(root->left);
    visitTree(root->right);
    printf("%d ", root->item);
}


int main() {
    int pre[] = {100, 10, 55, 25, 13, 3, 30, 14, 0, 20, 90};
    int in[] = {10, 100, 13, 25, 3, 55, 0, 14, 20, 30, 90};
    link  p = buildTree(in,pre,11);


    visitTree(p);

    return 0;
}

int search(int val, int *array, int start, int end){
    int i;
    for(i=start; i<=end && array[i]!=val; i++);
    printf("Found at %d\n", i);
    return i;
}