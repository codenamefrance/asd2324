#include <stdio.h>
#include <stdlib.h>

/* Inserire token all'interno di un buffer. 
Griglia -> Matrice NxN
Ogni token -> una sola volta

1 token -> sempre sulla prima riga
2 token -> colonna del precedente
3 token -> riga del precedente
4 token -> colonna del precedente 
 ....

Bonus : intero positivo

*/

token **gridScan(char *filename, int *size);
token **bonusScan(char *filename, int *size);

typedef struct token_t{
    char val[2];
} token;

typedef struct buffer_t{
    token *array;
    int len;
} buffer;

int main(){

    int bufferSize;
    token **bonus; int nBonus;
    token **grid; int N;

    grid = gridScan("grid.txt", &N);
    bonus = bonusScan("bonus.txt", &nBonus);

}

token **gridScan(char *filename, int *size){
    FILE *fp = fopen(filename, "r");
    if(fp==NULL) return NULL;

    token **grid;
    int sz, i, j;

    fscanf(fp, "%d ", &sz);

    for(i=0; i<size; i++)
        for(j=0; j<size; j++)




    *size = sz;
}


token **bonusScan(char *filename, int *size);

