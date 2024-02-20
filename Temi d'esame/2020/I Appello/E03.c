/* n tipi di monete -> val[n] = valore di n
disp[n] = quante monete di tipo n ho
r resto intero

Calcolare numero di monete minimo per erogare tale resto -> visualizzare la soluzione. (No greedy)

IDEA 1: powerset con disposizioni ripetute -> esco appena ne trovo una

*/

#include <stdio.h>
#include <stdlib.h>

void powerSet(int val[], int mark[], int pos, int k, int sol[], int *tmp, int *status, int r);
void resto();


void resto(){
    int k, status=0;
    int val[] = {1,10,25};
    int disp[] = {10,3,2};
    
    int n=15;

    int sol[15];

    int tmp=0; int r=30;
        
        
    for(k=1; k<n && status==0; k++)
        powerSet(val, disp, 0, k, sol, &tmp, &status, r);
    
    return;
}

void powerSet(int val[], int mark[], int pos, int k, int sol[], int *tmp, int *status, int r){
    int i, restoattuale=0;
    
    if((*status) == 1) return;
    if(pos>=k){
        for(i=0; i<k; i++) restoattuale+=sol[i];

        if(restoattuale == r){
            *status=1;
            printf("Servono %d monete.\n", k);
            for(i=0; i<k; i++) printf("%d ", sol[i]);
            puts("\n");
            return;
        }
    }
    
    
    for(i=0; i<3; i++){
        if(mark[i]>0){
            mark[i]--; 
            sol[pos] = val[i];
            powerSet(val, mark, pos+1, k, sol, tmp, status, r);
            mark[i]++; 
        }
    }
    return;
}

int main(){
    resto();
}