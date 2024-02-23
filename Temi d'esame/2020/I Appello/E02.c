/* n tipi di monete -> val[n] = valore di n
disp[n] = quante monete di tipo n ho
r resto intero

Calcolare numero di monete minimo per erogare tale resto -> visualizzare la soluzione. (No greedy)

IDEA 1: powerset con disposizioni ripetute -> esco appena ne trovo una

*/

void resto(){
    int k; status=0;
    int val[] = {1,10,25};
    int disp[] = {10,3,2};
    
    int tmp=0; int r=30;
        
        
    for(k=1; k<n && status==0; k++)
        powerSet(val, disp, 0, k, sol, &tmp, &status, r);
    
    return;
}

void powerSet(int val[], int mark[], int pos, int k, int sol[], int *tmp, int *status, int r){
    int i;
    
    if(pos>=k){
        if(tmp==cnt){
            printf("HELL YEAH! UTILIZZO UN PO' DI MONETE : %d\n", k);
            *status = 1
            return;            
        }
    }
    
    if((*status) == 1) return;
    
    for(i=0; i<n; i++){
        if(mark[i]!=0 && cnt+val[i]<=r){
            mark[i]--; 
            sol[pos] = val[i]; (*tmp) = (*tmp)+val[i];
            powerSet(val, mark, pos+1, k, sol, tmp, status);
            mark[i]++; (*tmp) = (*tmp)-val[i];
        }
    }
    return;
}

