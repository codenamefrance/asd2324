#include <stdio.h>
#include <stdlib.h>

/* n squadre giocano per m giornate -> matrice n x m.(0,1,3)
Per ogni giornata, stampare squadra capolista
*/

void displayRanking(int C[4][3], int n, int m);


void displayRanking(int C[4][3], int n, int m){
    int *results;
    results = (int *)malloc(m*sizeof(int));

    int max=0, maxid, tmp;
    int sq, k, day;
    
    for(k=0, max=0; k<m; k++){
        for(sq=0, tmp=0; sq<n; sq++){
            for(day = 0; day<=k; day++)
                tmp = tmp + C[sq][day];
            if(tmp>max){
                max = tmp;
                maxid = sq;
            }
            tmp=0;
        }
        results[k] = maxid;
        max=0;
    }
    
    for(k=0; k<m; k++){
        printf("Capolista al giorno %d: %d\n", k+1, results[k]);
    }
    
    free(results);
    
}

int main(){
    int C[4][3] = {
        {3,1,0},
        {0,1,1},
        {1,1,1},
        {1,1,3}
    };
    displayRanking(C, 4, 3);


}