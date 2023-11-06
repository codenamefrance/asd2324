#include <stdlib.h>
#include <stdio.h>

#define MAXLEN 256

/* Si applica il principio di moltiplicazione*/

typedef struct{
    int *scelte;
    char **songs;
    int size;
} level;

int readFile(char *filename, level **plevels);
void fill_level(level *sp, int lsize);
void printSong(level user, int song);
void printsol(level *all_levels, int *v, int size);
int princ_molt(level *plevels, int levels_n, int *solution, int pos, int cnt);
void freeLevels(level *plevels, int size);

int main(){
    level *levels;

    int levels_n = readFile("brani2.txt", &levels);
    int *solution = (int *)malloc(levels_n*sizeof(int));

    printf("Successfully printed %d solutions.\n", princ_molt(levels, levels_n, solution, 0, 0));

    freeLevels(levels, levels_n);
}

void fill_level(level *sp, int lsize){

    sp->size = lsize;
    sp->scelte = (int *)malloc(lsize*sizeof(int));
    sp->songs = (char **)malloc(lsize*sizeof(char*));

    for(int i=0; i<lsize; i++){
        (sp->scelte)[i] = i;
    }
    return;
}

int readFile(char *filename, level **plevels){
    int scelte_sz, levels_n, songs_n, cnt=0;
    level *plv;


    FILE *fin=fopen(filename, "r");
    if(fin==NULL) return 0;

    fscanf(fin, "%d", &levels_n);
    plv = (level *)malloc(levels_n*sizeof(level));

    for(int i=0; i<levels_n; i++){ // Itero su ciascun livello
        fscanf(fin, "%d", &songs_n);
        fill_level(plv+i, songs_n);
        for(int j=0; j<songs_n; j++){
            (plv[i].songs)[j] = (char *)malloc(MAXLEN*sizeof(char));
            fscanf(fin, "%s", (plv[i].songs)[j]);
        }

    }
    *plevels = plv;

    return levels_n;

}

int princ_molt(level *levels, int n, int *sol, int pos, int cnt){
    int i;
    if(pos>=n){
        printsol(levels, sol, n);
        return cnt+1;
    }
    for(i=0; i<levels[pos].size; i++){
        sol[pos] = levels[pos].scelte[i];
        cnt = princ_molt(levels, n, sol, pos+1, cnt);
    }
    return cnt;
}

void printsol(level *all_levels, int *v, int size){
    for(int i=0; i<size; i++){ //i indica il livello, v[i] mi indica la canzone del livello
        printSong(all_levels[i], v[i]); // i è il cantante, v[i] la canzone
    }
    printf("\n");
}

void printSong(level user, int song){
    printf("%s\n", user.songs[song]);
}

void freeLevels(level *plevels, int size){
    int level_size;

    for(int i=0; i<size; i++){
        level_size = plevels[i].size;
        for(int j=0; j<level_size; j++){
            free(plevels[i].songs[j]);
        }
        free(plevels[i].songs);
        free(plevels[i].scelte);
    }
    printf("DEBUG: memory correctly freed.\n");
    return;
}