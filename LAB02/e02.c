#include <stdio.h>
#include <stdlib.h>

#define FILENAME "mat.txt"

int **malloc2dR(char *filename, int *rows, int *cols);
void separa(int **mat, int nr, int nc, int **v1, int **v2);

typedef enum{white, black} color_e;

int main(){

    int **m;
    int *white, *black;
    int nr, nc;

    m=malloc2dR(FILENAME, &nr, &nc);
    separa(m, nr, nc, &white, &black);

    int maxsize = (nr*nc)/2 + 1;
    for(int i=0; i<maxsize; i++){
        printf("%d", white[i]);
    }

}
int **malloc2dR(char *filename, int *rows, int *cols){
    int nr, nc;
    int **mat;

    FILE *fp=fopen(filename, "r");
    fscanf(fp, "%d %d", &nr, &nc);
    *rows = nr; *cols = nc;

    mat = (int**)malloc(nr*sizeof(int**));

    for(int i=0; i<nr; i++){
        mat[i] = (int *)malloc(nc*sizeof(int *));
        for(int j=0; j<nc; j++){
            fscanf(fp, "%d", &mat[i][j]);
        }
    }
    return mat;
}

void separa(int **mat, int nr, int nc, int **v1, int **v2){
    //if a row starts with white, the following one starts with black
    // if 3x3 5 whites, 4 blacks

    int *vv1, *vv2;

    int flag=white;

    int v1size=0, v2size=0;
    int maxsize = (nr*nc)/2 + 1;
    vv1 = (int*)malloc(maxsize*sizeof(int*)); // white
    vv2 = (int*)malloc(maxsize*sizeof(int*)); // black

    for(int i=0; i<nr; i++){
        for(int j=0; j<nc; j++){
            if(flag==white){
                flag=black;
                vv1[v1size] = mat[i][j];
                v1size++;
            }
            else{
                flag=white;
                vv2[v2size] = mat[i][j];
            }
        }
    }

    *v1 = vv1;
    *v2 = vv2;

    return;
    
}