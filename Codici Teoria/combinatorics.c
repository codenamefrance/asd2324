/* Ripasso calcolo combinatorio */

#include <stdio.h>
#include <stdlib.h>

// Mark 0/1
void permutations(int *v, int n);
void dispositions(int *v, int n, int k);

// Mark by quantity
void permutationsRep(int *v, int n);
void dispositionsRep(int *v, int n, int k);

// Start index to force order (start = i+1)
void combinations(int *v, int n, int k);

void printArray(int *a, int size);

int permuteR(int *v, int n, int k, int pos, int cnt, int *sol, int *mark);
int combineR(int *v, int n, int k, int pos, int start, int cnt, int *sol);


int permuteR(int *v, int n, int k, int pos, int cnt, int *sol, int *mark){
    if(pos>=k){
        printArray(sol, k);
        return cnt+1;
    }

    for(int i=0; i<n; i++){
        if(!mark[i]){
            mark[i] = 1;
            sol[pos] = v[i];
            cnt = permuteR(v, n, k, pos+1, cnt, sol, mark);
            mark[i] = 0;
        }
    }
    return cnt;
}

void permutations(int *v, int n){
    int *sol = malloc(n*sizeof(int));
    int *mark = malloc(n*sizeof(int));
    for(int i=0; i<n; i++) mark[i] = 0;
    printf("Successfully generated %d permutations.\n", permuteR(v, n, n, 0, 0, sol, mark));
    free(sol);
    free(mark);
    return;
}

void dispositions(int *v, int n, int k){
    int *sol = malloc(k*sizeof(int));
    int *mark = malloc(n*sizeof(int));
    for(int i=0; i<n; i++) mark[i] = 0;
    printf("Successfully generated %d dispositions.\n", permuteR(v, n, k, 0, 0, sol, mark));
    free(sol);
    free(mark);
    return;
}

int combineR(int *v, int n, int k, int pos, int start, int cnt, int *sol){
    int i;
    if(pos>=k){
        printArray(sol, k);
        return cnt+1;
    }

    for(i=start; i<n; i++){
        sol[pos] = v[i];
        cnt = combineR(v, n, k, pos+1, i+1, cnt, sol);
    }

    return cnt;

}

void combinations(int *v, int n, int k){
    int *sol = malloc(k*sizeof(int));
    printf("Successfully generated %d combinations.\n", combineR(v, n, k, 0, 0, 0, sol));
    free(sol);
}

void printArray(int *a, int size){
    for(int i=0; i<size; i++) printf("%d ", a[i]);
    printf("\n");
}


int main(){
    int v[5] = {1,2,3,4,5};

    //permutations(v, 5);
    //dispositions(v, 5, 3);
    combinations(v, 5, 3);

}
