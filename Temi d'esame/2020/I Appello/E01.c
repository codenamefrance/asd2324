/* Numbers input format (x,y) where x says "put y for x times". Vector -> matrix -> row major */

#define R 3
#define C 5
#define n 14

#include <stdio.h>
#include <stdlib.h>


void buildAndPrint(int *V, int N, int M[R][C], int r, int c);


void buildAndPrint(int *V, int N, int M[R][C], int r, int c){
    int rx=0, rj=0, i;
    int cnt;
    
    for(i=0; i<N; i+=2){
        cnt = V[i];
        while(cnt!=0){
            if(rj==c){
                rj=0;
                rx++;
            }
            // Ricorda di incrementare la colonna
            M[rx][rj++] = V[i+1];
            cnt--;
        }
    }
    
    for(rx=0; rx<r; rx++){
        for(rj=0; rj<c; rj++){
            printf("%d ", M[rx][rj]);            
        }
        puts("\n");
    }
    puts("\n");

    
    return;
}

int main(){
    int V[n] = {2,1,2,17,1,3,4,8,1,6,3,7,2,5};
    
    int M[R][C];

    for(int i=0; i<R; i++)
        for(int j=0; j<C; j++)
            M[i][j] = 0;
    
    buildAndPrint(V, n, M, R, C);
    
}
