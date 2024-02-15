
int **flatten(int R, int C, int D, int ***3dmatrix){
    int **ans;
    int i, j, k;
    int di=0, dj=0;
    
    ans = (int **)malloc(D*R*sizeof(int *));
    for(i=0; i<D*R; i++) ans[i] = (int *)malloc(D*C*sizeof(int));
    
    for(k=0; k<D; k++){
        for(i=0; i<R; i++){
            for(j=0; j<C; j++){
                ans[i+di][j+dj] = 3dmatrix[i][j];
            }
        }
        
        dj+=C;
        if( dj>=(D*C) ){
            dj=0;
            di+=R;
        }
    }
    
    
    return ans;
    
}