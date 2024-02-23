/* vettore paste di n struct.
struct formata da
    - codice
    - peso
    - quantità
    
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct pasta_T{
    int code;
    float weight;
    int quantity;
} pasta;

// Global variables
int bSolution[50];
int bSum=0;
int bSize=0;

// Prototypes
int *generaVassoio(pasta *selezione, int n, int target);
void powerSet(pasta *selezione, int n, int target, int k, int *disp, int pos, int *solution);

int *generaVassoio(pasta *selezione, int n, int target){
    int *solution;
    int k;
    int total=0;
    int *disp = malloc(n*sizeof(int));
    for(k=0; k<n; k++){
        disp[k] = selezione[k].quantity;
        total += disp[k];
    }
    solution = malloc(total*sizeof(int));
    
    for(k=0; k<total; k++)
        powerSet(selezione, n, target, k, disp, 0, solution);
    
    return solution;
}

void powerSet(pasta *selezione, int n, int target, int k, int *disp, int pos, int *solution){
    int sum=0, i;
    if(pos>=k){
        for(i=0; i<k; i++)
            sum += selezione[solution[i]].weight;
        if(sum > bSum && sum <= target){
            bSum = sum;
            bSize = k;
            for(i=0; i<bSize; i++) 
                bSolution[i] = solution[i];
        }
        return;
    }
    
    for(i=0; i<n; i++){
        if(disp[i]>0){
            disp[i]--;
            solution[pos] = i;
            powerSet(selezione, n, target, k, disp, pos+1, solution);
            disp[i]++;
        }
    }
}

/* 
croissant 50 5
brioche 30 5
crostatina 80 5
bigne 15 5
mousse 20 5
*/

int main(){
    pasta selezione[3];

    selezione[0].code = 0;
    selezione[0].quantity = 5;
    selezione[0].weight = 20;

    selezione[1].code = 1;
    selezione[1].quantity = 3;
    selezione[1].weight = 14;

    selezione[2].code = 2;
    selezione[2].quantity = 4;
    selezione[2].weight = 15;

    generaVassoio(selezione, 3, 200);

    for(int i=0; i<bSize; i++) printf("%d ", bSolution[i]);
    printf("\n");
    printf("Best weight %d\n", bSum);


}
