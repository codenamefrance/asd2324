#include <stdio.h>
#include <stdlib.h>

void f(int **M, int r, int c, float ***mDest);

int **readMatrix(FILE *fp, int *r, int *c);
void printMatrix(float **m, int r, int c);

void f(int **M, int r, int c, float ***mDest){
    int i, j, l, m;
    float **rM;
    rM = malloc(r*sizeof(float *));
    for(i=0; i<r; i++) rM[i] = malloc(c*sizeof(float));
    
    float tmp_sum=0;
    float tmp_cnt=0;

    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            for(l = i-1; l<=i+1; l++){
                for(m = j-1; m<=j+1; m++){
                    printf("Provo con %d/%d\n", l, m);
                    if(l >=0 && l<r && m>=0 && m<c){
                        tmp_cnt++;
                        tmp_sum += M[l][m];
                    }
                }
            }
            
            rM[i][j] = (float) (tmp_sum / tmp_cnt);
                tmp_sum = 0;
            tmp_cnt = 0;
        }
    }
    
    *mDest = rM;
}

// Funzioni non richieste dall'esame

int **readMatrix(FILE *fp, int *r, int *c){
    int rc, cc;

    fscanf(fp, "%d %d", &rc, &cc);
    *r = rc; *c = cc;

    int **M = malloc(rc*sizeof(int *));
    for(int i=0; i<rc; i++){
        M[i] = malloc(cc*sizeof(int));
        for(int j=0; j<cc; j++){
            fscanf(fp, "%d ", &M[i][j]);
        }
    }

    return M;
}

void printMatrix(float **m, int r, int c){

    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            printf("%.2f ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}

int main(){
    FILE *fp = fopen("matrix.txt", "r");
    int r, c;
    int **m = readMatrix(fp, &r, &c);
    float **mf;

    f(m, r, c, &mf);


    printMatrix(mf, r, c);

}