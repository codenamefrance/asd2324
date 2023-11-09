#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 20
typedef struct{
    int N;
    int *others; // 0 not linked, 1 linked
} vertex_t;

int readFile(vertex_t **vs);
FILE *finput();
vertex_t *allocaVertici(int n_vertici);
void printVertexVec(vertex_t *v, int size);
int powersetWithVertex_w(vertex_t *vec, int vec_size, vertex_t *sol);
int powersetWithVertex_r(vertex_t *vec, vertex_t *sol, int j, int vec_size, int start, int pos);
int oneInCommon(int *v1, int v1sz, vertex_t *v2, int v2sz);
int checkSolution(vertex_t *all_vert, int all_size, vertex_t *sol, int sol_size);


int main(){

    vertex_t *vert_vec;
    int n_vertici;

    n_vertici = readFile(&vert_vec);

    vertex_t *sol=malloc(n_vertici*sizeof(vertex_t));

    int cnt = powersetWithVertex_w(vert_vec, n_vertici, sol);

    return 0;
}

int readFile(vertex_t **vs){
    int size, n_vertici, n_archi;
    int u,v;
    vertex_t *svec; //auxiliary for return

    FILE *fp=finput();
    if(fp==NULL) return 0;

    fscanf(fp, "%d%d", &n_vertici, &n_archi);
    svec = allocaVertici(n_vertici);


    //  0 <= u,v <= N-1
    for(int i=0; i<n_archi; i++){
        fscanf(fp, "%d%d", &u, &v);
        svec[u].others[v] = 1;
        svec[v].others[u] = 1;
    }

    *vs = svec;
    return n_vertici;
}

FILE *finput(){
    char *str=malloc(MAXLEN*sizeof(char));
    FILE *fin;

    printf("Input filename:\n"); scanf("%s", str);

    fin=fopen(str, "r");
    
    return fin;
}

vertex_t *allocaVertici(int n_vertici){
    vertex_t *v;
    v = (vertex_t *)malloc(n_vertici*sizeof(vertex_t));
    for(int i=0; i<n_vertici; i++){
        v[i].N = i;
        v[i].others = (int *)calloc(n_vertici, sizeof(int));
    }

    return v;
}

int powersetWithVertex_w(vertex_t *vec, int vec_size, vertex_t *sol){
    int cnt=0;
    for(int j=1; j<=vec_size; j++){
        cnt += powersetWithVertex_r(vec, sol, j, vec_size, 0, 0);
    }
    return cnt;
}

int powersetWithVertex_r(vertex_t *vec, vertex_t *sol, int j, int vec_size, int start, int pos){
    int i, cnt;
    if(pos>=j){
        for(i=0; i<j; i++){
            if(checkSolution(vec, vec_size, sol, j)!=0){
                printVertexVec(sol, j);
                return 1;         
            }
            return 0;
        }
    }
    for(i=start; i<vec_size; i++){
        sol[pos] = vec[i];
        cnt += powersetWithVertex_r(vec, sol, j, vec_size, i+1, pos+1);
    }
    return cnt;

}

void printVertexVec(vertex_t *v, int size){
        printf("(");
    for(int i=0;i<size;i++){
        printf("%d ", v[i].N);
    }
    printf(")\n");
}

int checkSolution(vertex_t *all_vert, int all_size, vertex_t *sol, int sol_size){
    // intersezione fra ciascun *link e *sol deve essere diversa da 0
    for(int i=0; i<all_size; i++){
        if(oneInCommon(all_vert[i].others, all_size, sol, sol_size)==0) return 0;
    }
    return 1;
}

int oneInCommon(int *v1, int v1sz, vertex_t *v2, int v2sz){

    for(int i=0; i<v2sz; i++){
        if(v1[v2[i].N]==1) return 1;
    }
    return 0;
}