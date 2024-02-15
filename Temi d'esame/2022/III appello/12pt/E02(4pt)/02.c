#define N ...

/* Contenuto del file TREE.h */

typedef struct ntree *nTREE;

/* Contenuto del file TREE.c */

struct node {
    char *key;
    struct node *children[N];
}

struct ntree{
    struct node *root;
    struct node *z;
}


int countIf(nTREE t){
    int cnt=1, i;
    
    if(t->root == NULL) return 0;

    int rootDegree = count(t->children);
    
    for(i=0; i<N; i++){
       countIfR(t->root->children[i], &cnt, rootSons);        
    }

    return cnt;
}

void countIfR(struct node *treeNode, int *cnt, int fatherDegree){
    int nodeDegree;
    if(treeNode == NULL) return;
    
    nodeDegree = count(treeNode->children);
    
    if(nodeDegree > fatherDegree) (*cnt)++;
    
    for(i=0; i<N; i++)
       countIfR(treeNode->children[i], &cnt, rootSons);        
    
    
    return;

}

int count(struct node *children){
    int i, cnt=0;
    for(i=0; i<N; i++){
        if(children[i]!=NULL) cnt++;
    }
    return cnt;
}
