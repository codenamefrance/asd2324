#include <stdio.h>
#include <string.h>

#define MAXLEN 30
#define FILENAME "corse.txt"

typedef enum{
    r_stampa, 
    r_data, 
    r_codice, 
    r_partenza, 
    r_destinazione, 
    r_ricerca,
    r_fine
}comando_e;

typedef struct{
    char codice[MAXLEN];
    char partenza[MAXLEN];
    char destinazione[MAXLEN];
    char data[MAXLEN];
    char ora_partenza[MAXLEN], ora_arrivo[MAXLEN];
    int ritardo;
}log_s;

 /* 
    Functions' Prototypes
 */
comando_e leggiComando();

void printLogs(log_s **logs, int size);
void printLog(log_s *log);
void fprintLogs(FILE *fout, log_s **logs, int size);

int leggiFile(char *filename, log_s *table);

void insertionSort(log_s **vp, int size, int (*cmpFz)(log_s *s1, log_s *s2));
void searchLogs(log_s **vp, int size);

void linearSearch(log_s **vp, int size, char *src);
void binarySearch(log_s **vp, int size, char *src);
int isOrderedByTerminal(log_s **vp, int size);

int cmpDate(log_s *s1, log_s *s2);
int cmpCode(log_s *s1, log_s *s2);
int cmpTerminal(log_s *s1, log_s *s2);
int cmpDestination(log_s *s1, log_s *s2);

/*
    Functions' codes
*/

comando_e leggiComando(){
    char input[10];
    int valido=1;
    comando_e comando;

    puts("Inserire il comando: ");
    do{
        scanf("%s", input);
        valido=1;

        if(strcmp(input, "data")==0){
            comando = r_data;
        }
        else if(strcmp(input, "partenza")==0){
            comando = r_partenza;
        }
        else if(strcmp(input, "destinazione")==0){
            comando = r_destinazione;
        }
        else if(strcmp(input, "codice")==0){
            comando = r_codice;
        }
        else if(strcmp(input, "stampa")==0){
            comando = r_stampa;
        }
        else if(strcmp(input, "ricerca")==0){
            comando = r_ricerca;
        }
        else if(strcmp(input, "fine")==0){
            comando = r_fine;
        }
        else{
            valido=0;
            printf("Comando non valido.\n");
        }
    }while (!valido);

    return comando;
}

void printLogs(log_s **logs, int size){
    for(int i=0; i<size;i++){
        printf("%s %s %s %s %s %s %d\n", 
            logs[i]->codice,
            logs[i]->partenza,
            logs[i]->destinazione,
            logs[i]->data,
            logs[i]->ora_partenza,
            logs[i]->ora_arrivo,
            logs[i]->ritardo);
    }
    puts("\n");
}
void fprintLogs(FILE *fout, log_s **logs, int size){
    for(int i=0; i<size;i++){
    fprintf(fout, "%s %s %s %s %s %s %d\n", 
        logs[i]->codice,
        logs[i]->partenza,
        logs[i]->destinazione,
        logs[i]->data,
        logs[i]->ora_partenza,
        logs[i]->ora_arrivo,
        logs[i]->ritardo);
    }
}
void printLog(log_s *log){
    printf("%s %s %s %s %s %s %d\n", 
            log->codice,
            log->partenza,
            log->destinazione,
            log->data,
            log->ora_partenza,
            log->ora_arrivo,
            log->ritardo);
}


int leggiFile(char *filename,log_s *table){   

    int size, i;

    FILE *fin=fopen(filename, "r");
    if(fin==NULL) return 0;

    fscanf(fin, "%d", &size);
    for(i=0; i<size; i++){
        fscanf(fin, "%s %s %s %s %s %s %d",
            table[i].codice,
            table[i].partenza,
            table[i].destinazione,
            table[i].data,
            table[i].ora_partenza,
            table[i].ora_arrivo,
            &table[i].ritardo
        );
    }
    fclose(fin);

    return size;

}

int cmpDate(log_s *s1, log_s *s2){
    int res=strcmp(s1->data, s2->data);
    if(res==0){
        return strcmp(s1->ora_partenza, s2->ora_partenza);
    }
    else return res;
}
int cmpCode(log_s *s1, log_s *s2){
    return strcmp(s1->codice, s2->codice);
}
int cmpTerminal(log_s *s1, log_s *s2){
    return strcmp(s1->partenza, s2->partenza);
}
int cmpDestination(log_s *s1, log_s *s2){
    return strcmp(s1->destinazione, s2->destinazione);
}




void searchLogs(log_s **vp, int size){
    char src[MAXLEN];

    printf("Input departure station's name: "); scanf("%s", src);
    if(isOrderedByTerminal(vp, size)){
        puts("Terminals are ordered by name -> using Binary Search");
        binarySearch(vp, size, src);
    }
    else{
        puts("Terminals are NOT ordered by name -> using Linear Search");
        linearSearch(vp, size, src);
    }
}

int isOrderedByTerminal(log_s **vp, int size){
    for(int i=0; i<size-1; i++){
        if(cmpTerminal(vp[i], vp[i+1])>0)
            return 0;
    }
    return 1;
}
void linearSearch(log_s **vp, int size, char *src){
    for(int i=0; i<size; i++){
        if(strncmp((vp[i]->partenza), src, strlen(src))==0) printLog(vp[i]);
    }
}
void binarySearch(log_s **vp, int size, char *src){
    int c, l=0, r=size-1;
    int found=0;
    while(l<=r && found==0){
        c=(l+r)/2;
        if(strncmp(src, (vp[c]->partenza), strlen(src))>0) l=c+1;
        if(strncmp(src, (vp[c]->partenza), strlen(src))<0){
            r=c-1;
        }
        else{
            puts("La ricerca ha prodotto i seguenti risultati: \n");
            found=1;
            linearSearch(&vp[l], r-l+1, src);
        }
    }
}


void insertionSort(log_s **vp, int size, int (*cmpFz)(log_s *s1, log_s *s2)){
    int i,j;
    log_s *ps;

    for(i=1; i<size; i++){
        ps=vp[i];
        j=i-1;
        while(j>=0 && (*cmpFz)(ps, vp[j])<0){
            vp[j+1]=vp[j];
            j--;
        }
        vp[j+1]=ps;
    }
    printLogs(vp, size);
}
void selezionaDati(log_s **vp, int size, comando_e cmd){
    
    switch(cmd){
        case r_data:
            insertionSort(vp, size, cmpDate);
            break;
        case r_partenza:
            insertionSort(vp, size, cmpTerminal);
            break;
        case r_destinazione:
            insertionSort(vp, size, cmpDestination);
            break;
        case r_codice:
            insertionSort(vp, size, cmpCode);
            break;
        case r_stampa:
            printLogs(vp, size);
            break;
        case r_ricerca:
            searchLogs(vp, size);
            break;
        case r_fine:
            printf("Uscita...\n");
            break;
    }

}

int main(){
    log_s logs[1000];
    log_s *plogs[1000];
    int size;
    comando_e cmd;

    size = leggiFile(FILENAME, logs);
    for(int i=0; i<size; i++){
        plogs[i]=&logs[i];
    }
    do{
    cmd = leggiComando();
    selezionaDati(plogs, size, cmd);
    }while(cmd!=r_fine);
}
