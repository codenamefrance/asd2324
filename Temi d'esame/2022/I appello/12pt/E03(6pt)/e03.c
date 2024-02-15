// vogliamo minimizzare il numero di gruppi

#include <stdlib.h>
#include <stdio.h>

void erAlgo(int M[4][4], int *sol, int n, int m, int pos, int *flag);
void partitioningWrapper(int M[4][4], int dim);
void checkSolution(int M[4][4], int *sol, int n, int *flag, int m);

int main(){
    int M[4][4] = {
    {1,1,0,1},
    {1,1,0,1},
    {0,0,1,0},
    {1,1,0,1}
    };
    int N=4;
    
    partitioningWrapper(M, N);


}

void partitioningWrapper(int M[4][4], int dim){
    int *sol = malloc(dim*sizeof(int));
    int flag=0;

    erAlgo(M, sol, dim, 0, 0, &flag);
}

void erAlgo(int M[4][4], int *sol, int n, int m, int pos, int *flag){
    int i, j;
    
    if((*flag)==1) return;
    
    if(pos>=n){
        checkSolution(M, sol, n, flag, m);
        return;
    }
    
    for(i=0; i<m; i++){
        sol[pos] = i;
        erAlgo(M, sol, n, m, pos+1, flag);
    }
    sol[pos] = m;
    erAlgo(M, sol, n, m+1, pos+1, flag);


}

void checkSolution(int M[4][4], int *sol, int n, int *flag, int m){
    int i, j;
    int ok=1;
    for(i=0; i<n; i++){
        for(j=i; j<n; j++){
            if(sol[i]==sol[j]){
                if(M[i][j] !=1 || M[j][i] !=1 )
                    ok=0;
            }
        }
    }
    if(ok==1){
        *flag = 1;
        for(i=0; i<m; i++){
            printf("Block no. %d\n", i);
            for(j=0; j<n; j++){
                if(sol[j]==i){
                    printf("%d ", j);
                }
            }
            printf("\n");
        }
    }
}
