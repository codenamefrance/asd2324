#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 30
#define MAXORD 5 //original order included

typedef enum{
    r_stampa, 
    r_data, 
    r_codice, 
    r_partenza, 
    r_destinazione, 
    r_ricerca,
    r_fine
}comando_e;

typedef enum{
    o_originale,
    o_data,
    o_partenza,
    o_destinazione,
    o_codice
}ordine_t;

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

int leggiFile(char *filename, log_s **table);

void insertionSort(log_s **src, int size, int (*cmpFz)(log_s *s1, log_s *s2));
void searchLogs(log_s **vp, int size);

void linearSearch(log_s **vp, int size, char *src);
void binarySearch(log_s **vp, int size, char *src);
//int isOrderedByTerminal(log_s **vp, int size);

int cmpDate(log_s *s1, log_s *s2);
int cmpCode(log_s *s1, log_s *s2);
int cmpTerminal(log_s *s1, log_s *s2);
int cmpDestination(log_s *s1, log_s *s2);

void log_s_cpy(log_s **src, int size, log_s **dest);

void orderEverything(log_s ***dest, log_s **src, int size);
/*
    Functions' codes
*/
void log_s_cpy(log_s **src, int size, log_s **dest){
    for(int i=0; i<size; i++){
        dest[i] = src[i];
    }
}

void orderEverything(log_s ***dest, log_s **src, int size){

    dest[o_originale] = (log_s**)malloc(size*sizeof(log_s**));
    log_s_cpy(src, size, dest[o_originale]);
    //crea funzione orderAndCopy(...)
    insertionSort(src, size, cmpDestination);
    dest[o_destinazione] = (log_s**)malloc(size*sizeof(log_s**));
    log_s_cpy(src, size, dest[o_destinazione]); // copio lo stato di src in dest.arrivo
    
    insertionSort(src, size, cmpCode);
    dest[o_codice] = (log_s**)malloc(size*sizeof(log_s**));
    log_s_cpy(src, size, dest[o_codice]);

    insertionSort(src, size, cmpTerminal);
    dest[o_partenza] = (log_s**)malloc(size*sizeof(log_s**));
    log_s_cpy(src, size, dest[o_partenza]);

    insertionSort(src, size, cmpDate);
    dest[o_data] = (log_s**)malloc(size*sizeof(log_s**));
    log_s_cpy(src, size, dest[o_data]);
}

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


int leggiFile(char *filename, log_s **table){   

    int size, i;
    log_s *table_a;

    FILE *fin=fopen(filename, "r");
    if(fin==NULL) return 0;

    fscanf(fin, "%d", &size);

    table_a = (log_s *)malloc(size*sizeof(log_s *));
    //aggiungere controllo memoria

    for(i=0; i<size; i++){
        fscanf(fin, "%s %s %s %s %s %s %d",
            table_a[i].codice,
            table_a[i].partenza,
            table_a[i].destinazione,
            table_a[i].data,
            table_a[i].ora_partenza,
            table_a[i].ora_arrivo,
            &table_a[i].ritardo
        );
    }
    fclose(fin);

    *table = table_a; // Return implicita al chiamante
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
    binarySearch(vp, size, src);
}

/*int isOrderedByTerminal(log_s **vp, int size){
    for(int i=0; i<size-1; i++){
        if(cmpTerminal(vp[i], vp[i+1])>0)
            return 0;
    }
    return 1;
}*/
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
void insertionSort(log_s **src, int size, int (*cmpFz)(log_s *s1, log_s *s2)){
    int i,j;
    log_s *ps;

    for(i=1; i<size; i++){
        ps=src[i];
        j=i-1;
        while(j>=0 && (*cmpFz)(ps, src[j])<0){
            src[j+1]=src[j];
            j--;
        }
        src[j+1]=ps;
    }
}
void selezionaDati(log_s ***allorders, int size, comando_e cmd){
    
    switch(cmd){
        case r_data:
            printLogs(allorders[o_data], size);
            break;
        case r_partenza:
            printLogs(allorders[o_partenza], size);
            break;
        case r_destinazione:
            printLogs(allorders[o_destinazione], size);
            break;
        case r_codice:
            printLogs(allorders[o_codice], size);
            break;
        case r_stampa:
            printLogs(allorders[o_originale], size);
            break;
        case r_ricerca:
            searchLogs(allorders[o_partenza], size);
            break;
        case r_fine:
            printf("Uscita...\n");
            break;
    }

}

void freeEverything(log_s *logs, log_s **plogs, int size, log_s ***allords){
    free(logs);
    free(plogs);
    for(int i=0; i<MAXORD; i++){
        free(allords[i]);
    }
    return;
}

void loop(char *filename);
/*
    Main run
*/
int main(){
    char str[30];
    do{
    printf("Input filename or type exit: "); scanf("%s", str);
    loop(str);
    }while(strcmp(str, "exit")!=0);

    return 0;
}

void loop(char *filename){
    log_s *logs;
    log_s **plogs;
    int size;
    comando_e cmd;

    log_s **all_orders[MAXORD];
    size = leggiFile(filename, &logs);

    plogs = (log_s **)malloc(size*sizeof(log_s **));
    for(int i=0; i<size; i++){
        plogs[i]=&logs[i];
    }
    printLogs(plogs, size);

    orderEverything(all_orders, plogs, size);
    do{ //aggiustare per skippare subito con fine
    cmd = leggiComando();
    selezionaDati(all_orders, size, cmd);
    }while(cmd!=r_fine);

    freeEverything(logs, plogs, size, all_orders);

    return;
}


