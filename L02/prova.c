#include <stdio.h>
#include <stdlib.h>

#define FILENAME "matrice.txt"

int **malloc2dR(char *filename);

int main(){

    int **m;
    m=malloc2dR(FILENAME);

    for(int i=0; i<3; i++){
        for(int j=0; j<4; j++){
            printf("%d", m[i][j]);
        }
        printf("\n");
    }
}

int **malloc2dR(char *filename){
    int nr, nc;
    int **mat;

    FILE *fp=fopen(filename, "r");
    fscanf(fp, "%d %d", &nr, &nc);

    mat = (int**)malloc(nr*sizeof(int**));

    for(int i=0; i<nr; i++){
        mat[i] = (int *)malloc(nc*sizeof(int *));
        for(int j=0; j<nc; j++){
            fscanf(fp, "%d", &mat[i][j]);
        }
    }
    return mat;
}