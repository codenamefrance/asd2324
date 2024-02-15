#include <stdio.h>
#include <stdlib.h>

int isLowercase(char a);
char lower(char a);
void generateR(char *letters, int letterSize, int p, int k, int pos, char *sol, int *streak, int *cntlower);
void generateSequences(char *letters, int letterSize, int p, int k);


int main(){
    printf("Hello World!\n");
    char *letters; int lettersize = 26*2;

    letters = malloc(lettersize*sizeof(char));

    int i, j=0;

    for(i=0; i<26; i++) letters[j++] = (char)('a' + i);
    for(i=0; i < 26; i++) letters[j++] = (char)('A' + i);
    printf("\n");


    for(int k=0; k<lettersize; k++){
        printf("%c ", letters[k]);
    }

    generateSequences(letters, lettersize, 3, 6);

}

void generateSequences(char *letters, int letterSize, int p, int k){

    int streak = 1;
    int cntlower = 0;
    
    char *sol;
    
    sol = malloc(26*2*sizeof(char));

    generateR(letters, letterSize, p, k, 0, sol, &streak, &cntlower);
}


void generateR(char *letters, int letterSize, int p, int k, int pos, char *sol, int *streak, int *cntlower){

    int i;

    if(pos>=k){
        printf("%s\n", sol);
        return;
    }
    
    for(i=0; i<letterSize; i++){
        if(isLowercase(letters[i]) && (*cntlower) > k/2) continue;
        if(pos>0){
            if( lower(letters[i]) == lower(sol[pos-1]))
                (*streak)++;
            else
                (*streak)=1;
        }
        
        if( (*streak) > p ) continue;
        
        sol[pos] = letters[i];
        generateR(letters, letterSize, p, k, pos+1, sol, streak, cntlower);
    }
}

int isLowercase(char a){
    return (a>='a' && a<='z');
}

char lower(char a){
    if(isLowercase(a)) return a;
    else
        return (char) ( 'a' - 32);
}