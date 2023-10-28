#include <stdio.h>


int majority(int *a, int N){
    if(N==1) return a[0];
    int cnt, m=N/2;
    printf("%d", cnt);

    int left, right;
    
    left = majority(a, m);
    right = majority(a+m, N-m);
    if(left==-1 && right==-1) return -1;

    if(left==right) return left;

    if(left!=-1){
        for(int i=0, cnt=0; i<N; i++){
            if(a[i]==left) cnt++;
            printf("%d contato\n", cnt);
        }
        printf("%d verificato", cnt);
        if(cnt>N/2) return left;
    }


    if(right!=-1){
        for(int i=0, cnt=0; i<N; i++){
            if(a[i]==right) cnt++;
        }
        if(cnt>N/2) return right;
    }
    return -1;

}


int main(){
    int v[5]={3,3,3,4,5};
    int N=5;

    int x=majority(v, N);
    printf("%d\n", x);

}