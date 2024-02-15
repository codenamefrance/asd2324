#include <stdio.h>
#include <stdlib.h>

void f(int **M, int r, int c, int ***Mdest, int *rdest, int *cdest);
int isIndexInList(int index, int *v,  int vsize);
void printMatrix(int **m, int r, int c);
int **readMatrix(FILE *fp, int *r, int *c);

int main(){
    FILE *fp=fopen("matrice.txt", "r");
    int r, c;
    int **fM, rf, cf;
    int **M = readMatrix(fp, &r, &c);
    printMatrix(M, r, c);

    f(M, r, c, &fM, &rf, &cf);
    printMatrix(fM, rf, cf);

}

void f(int **M, int r, int c, int ***Mdest, int *rdest, int *cdest){

    int delRows[r], delCols[c];
    int c_rows=0, c_cols=0;
    int posr=0, posc=0;

    int i,j;

    for(i=0; i<r; i++)
        for(j=0; j<c; j++)
             if(M[i][j] == 0){
            		if(!isIndexInList(i, delRows, c_rows))
				delRows[c_rows++] = i;
            		if(!isIndexInList(j, delRows, c_cols))
				delCols[c_cols++] = j;
             }

	*rdest = r-c_rows;
	*cdest = c-c_cols;

    int riga, colonna;


	*Mdest = malloc(*rdest*sizeof(int *));
	for(i=0; i<*rdest; i++)
		(*Mdest)[i] = malloc(*cdest*sizeof(int));

	for(i=0; i<r; i++)
		for(j=0; j<c; j++)
			if(!isIndexInList(i, delRows, c_rows) && !isIndexInList(j, delCols, c_cols)){         
                if(posc == *cdest){
                    posr++;
                    posc = 0; 
                }
                (*Mdest)[posr][posc++] = M[i][j];
            }
				

}

int isIndexInList(int index, int *v,  int vsize){
	int i;
	for(i=0; i<vsize; i++)
  		if(v[i] == index)
                 return 1;
	return 0;
}

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

void printMatrix(int **m, int r, int c){

    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            printf("%d", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}