/* Determinare il massimo numero di stringhe appartenenti ad S mutuamente disgiunte.
    - Non ci interessa l'ordine delle stringhe ma solo la loro presenza -> combinazioni semplici
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int valid(char **table, int rows);
void combSemplici(char **stringhe, int n, int k, int pos, int start, char **sol, int *found);
int disgiunte(char **stringhe, int n);


int disgiunte(char **stringhe, int n){
    int found=0;
    int k;
    char **sol;
    sol = malloc(n*sizeof(char *));
    
    for(k=n; k>0 && found == 0; k--){
        combSemplici(stringhe, n, k, 0,0, sol, &found);
    }
    
    return k+1;
}

void combSemplici(char **stringhe, int n, int k, int pos, int start, char **sol, int *found){
    int i;
    if(pos>=k){
        if(valid(sol, k)){
            printf("SOLUZIONE:\n");
            *found = 1;
            for(i=0; i<k; i++) printf("%s\n", sol[i]);
        }
        return;
    }
    
    for(i=start; i<n && (*found)==0; i++){
        sol[pos] = strdup(stringhe[i]);
        combSemplici(stringhe, n, k, pos+1, start+1, sol, found);
    }
    
    return;
}

int valid(char **table, int rows){
    int i, c;
    int mark[26];
    int flag=1;

    for(i=0; i<26; i++) mark[i] = 0;

    for(i=0; i<rows && flag==1; i++){
        for(c=0; c<strlen(table[i]) && flag==1; c++){
            if(mark[(int)(table[i][c])-65] != 0){
                flag = 0;
            }
            else
                mark[(int)(table[i][c])-65] = 1;
        }
    }

    return flag;
}

int main(){
    int n=7, i;
    char *table[7];

    table[0] = strdup("ABGCIEF");
    table[1] = strdup("BA");
    table[2] = strdup("CD");
    table[3] = strdup("FE");
    table[4] = strdup("GHBD");
    table[5] = strdup("JKLGHI");
    table[6] = strdup("FK");

    printf("%d è la tua risposta...\n", disgiunte(table, n));


}


