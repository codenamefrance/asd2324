#include <stdio.h>
#include <stdlib.h>

#define FILENAME "mat.txt"

int **malloc2dR(char *filename, int *rows, int *cols);
void separa(int **mat, int nr, int nc, int **v1, int **v2, int *v1_sz, int *v2_sz);

typedef enum{white, black} color_e;

int main(){

    int **m;
    int *white, *black;
    int w_size, b_size;
    int nr, nc;

    int i;

    m=malloc2dR(FILENAME, &nr, &nc);
    separa(m, nr, nc, &white, &black, &w_size, &b_size);

    printf("White vector: \n");
    for(i=0; i<w_size; i++) printf("%d ", white[i]);
    printf("\nBlack vector: \n");
    for(i=0; i<b_size; i++) printf("%d ", black[i]);
    printf("\n");

    return 0;

}
int **malloc2dR(char *filename, int *rows, int *cols){
    int nr, nc;
    int **mat;

    FILE *fp=fopen(filename, "r");
    fscanf(fp, "%d %d", &nr, &nc);
    *rows = nr; *cols = nc;

    mat = (int**)malloc(nr*sizeof(int*));

    for(int i=0; i<nr; i++){
        mat[i] = (int *)malloc(nc*sizeof(int ));
        for(int j=0; j<nc; j++){
            fscanf(fp, "%d", &mat[i][j]);
        }
    }
    return mat;
}

void separa(int **mat, int nr, int nc, int **v1, int **v2, int *v1_sz, int *v2_sz){
    // In this script is assumed top-left corner cell as white

    int *vv1, *vv2;
    int flag; // 0 for white, 1 for black
    int v1size=0, v2size=0;

    int maxsize = (nr*nc)/2 + 1;

    vv1 = (int*)malloc(maxsize*sizeof(int)); // white
    vv2 = (int*)malloc(maxsize*sizeof(int)); // black

    for(int i=0; i<nr; i++){
        
        // Decide first cell's colour
        if(i%2==0) flag=white;
        else flag=black;

        for(int j=0; j<nc; j++){
            if(flag==white){
                flag=black;
                vv1[v1size] = mat[i][j];
                v1size++;
            }
            else{
                flag=white;
                vv2[v2size] = mat[i][j];
                v2size++;
            }
        }
    }

    *v1_sz = v1size;
    *v2_sz = v2size;

    *v1 = vv1;
    *v2 = vv2;

    return;
    
}