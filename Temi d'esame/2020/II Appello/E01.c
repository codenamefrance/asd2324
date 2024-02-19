#include <stdio.h>
#include <string.h>

typedef enum{HORIZONTAL, VERTICAL} dir;

/* Controllare colonne e righe. Stringa valida solo letta da sinistra a destra e alto verso basso */

int conta(char matrice[4][5], int n, int m, char *stringa);
void contaR(char M[4][5], int n, int m, int i, int j, char *word, int pos, int *cnt, dir direction);
int valid(int n, int m, int i, int j);

int conta(char matrice[4][5], int n, int m, char *stringa){
    int i, j;
    int cnt=0;

    for(i=0; i<n; i++){
        for(j=0; j<m; j++){
            contaR(matrice, n, m, i, j, stringa, 0, &cnt, VERTICAL);
            contaR(matrice, n, m, i, j, stringa, 0, &cnt, HORIZONTAL);
        }
    }
    return cnt;
}

int valid(int n, int m, int i, int j){
    if(i>=0 && i<n && j>=0 && j<m) return 1;
    return 0;
}

void contaR(char M[4][5], int n, int m, int i, int j, char *word, int pos, int *cnt, dir direction){
    int l, p;
    //int cnt = 0
    if(pos>=strlen(word)){
        (*cnt)++;
        return;
    }
    
    if(!valid(n, m, i, j) || M[i][j]!=word[pos]) return;
    
    if(direction == HORIZONTAL)
        contaR(M, n, m, i, j+1, word, pos+1, cnt, HORIZONTAL);
    else
        contaR(M, n, m, i+1, j, word, pos+1, cnt, VERTICAL);
    
    return;
}

int main(){

    char M[4][5] = {
        {'x', 'c', 'e', 'd', 'a'},
        {'w', 'a', 'e', 'o', 'q'},
        {'d', 'o', 'g', 'g', 'z'},
        {'p', 'c', 'a', 't', 'f'},
    };

    int n = 4;
    int m = 5;

    printf("Found %d occurrences of word.\n", conta(M, n, m, "dog"));


}