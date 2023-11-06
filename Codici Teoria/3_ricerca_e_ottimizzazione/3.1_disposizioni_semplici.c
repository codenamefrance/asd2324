#include <stdio.h>
#include <stdlib.h>

int disp_semplici(int pos, int *val, int *sol, int *mark, int n, int k, int cnt);
void printSol(int *v, int size);

int main(){
    int n=4,k=2;
    int val[]={4,9,1,0};
    int sol[2];
    int mark[]={0,0,0,0}; //c-alloc

    printf("Ho trovato %d soluzioni.\n", disp_semplici(0, val, sol, mark, 4, 2, 0));

    return 0;
}

/*
pos: ci tiene traccia del livello della ricorsione
*val: insieme di numeri (senza ripetizioni)
*mark: tiene traccia degli elementi utilizzati. stessa lunghezza di val
*sol: conterrà la soluzione
n lunghezza di val
k dimensione della soluzione
cnt numero delle soluzioni
*/


int disp_semplici(int pos, int *val, int *sol, int *mark, int n, int k, int cnt){
    /*Caso terminale: pos>=k. Soluzione troppo grande*/
    if(pos>=k){
        printSol(sol, k);
        return cnt+1; // quando trovi una soluzione, aumenta il cnt di uno
    }
    for(int i=0; i<n; i++){ // Itero sul vettore principale
        if(mark[i]==0){
            mark[i]=1;
            sol[pos] = val[i];
            // Trovami tutte le disposizioni che iniziano per il primo (poi secondo, terzo ...) numero
            cnt = disp_semplici(pos+1, val, sol, mark, n, k, cnt);
            // Liberamelo tanto guardo il successivo (con il for). Nel futuro mi servirà libero.
            mark[i]=0; // Backtracking
        }
    }
    return cnt;
}

void printSol(int *v, int size){
    for(int i=0; i<size; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}