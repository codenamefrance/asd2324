#include <stdio.h>
#include <string.h>

#define FILENAME "corse.txt"
#define MAX_ROW 1000
#define MAXLEN 30+1

typedef struct{
    char codice[MAXLEN];
    char partenza[MAXLEN];
    char destinazione[MAXLEN];
    char data[MAXLEN];
    char ora_partenza[MAXLEN], ora_arrivo[MAXLEN];
    int ritardo;
}corsa;

typedef enum{
    r_date, 
    r_partenza, 
    r_capolinea, 
    r_ritardo, 
    r_ritardo_tot, 
    r_fine
}comando_e;

comando_e leggiComando();
int leggiFile(char *filename, corsa *table);
void selezionaDati(corsa *table, int size, comando_e cmd);
void stampaCorsa(corsa corsa_sel);
void searchBetweenDates(corsa *table, int size);
void searchByStop(corsa *table, int size);
void searchByArrive(corsa *table, int size);
void searchByLateBetweenDate(corsa *table, int size);
void sumLate(corsa *table, int size);



comando_e leggiComando(){
    char input[10];
    int valido;
    comando_e comando;

    puts("Please, input: \n");
    scanf("%s", input);
    do{
        valido=1;

        if(strcmp(input, "date")==0){
            comando = r_date;
        }
        else if(strcmp(input, "partenza")==0){
            comando = r_partenza;
        }
        else if(strcmp(input, "capolinea")==0){
            comando = r_capolinea;
        }
        else if(strcmp(input, "ritardo")==0){
            comando = r_ritardo;
        }
        else if(strcmp(input, "pippo")==0){
            comando = r_ritardo_tot;
        }
        else if(strcmp(input, "fine")==0){
            comando = r_fine;
        }
        else{
            valido=0;
            printf("Comando non valido.");
        }
    }while (!valido);

    return comando;
};


int leggiFile(char *filename, corsa *table){   

    int rows, i;

    FILE *fin=fopen(filename, "r");
    if(fin==NULL) return 0;

    fscanf(fin, "%d", &rows);
    for(i=0; i<rows; i++){
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

    return rows;

}

void stampaCorsa(corsa corsa_sel){
    printf("%s %s %s %s %s %s %d \n", 
        corsa_sel.codice,
        corsa_sel.partenza,
        corsa_sel.destinazione,
        corsa_sel.data,
        corsa_sel.ora_partenza,
        corsa_sel.ora_arrivo,
        corsa_sel.ritardo
    );
}

void selezionaDati(corsa *table, int size, comando_e cmd){
    
    switch(cmd){
        case r_date:
            searchBetweenDates(table, size);
            break;
        case r_partenza:
            searchByStop(table, size);
            break;
        case r_capolinea:
            searchByArrive(table, size);
            break;
        case r_ritardo:
        searchByLateBetweenDate(table, size);
            break;
        case r_ritardo_tot:
            sumLate(table, size);
            break;
        case r_fine:
            printf("Uscita...");
            break;
    }

}

void searchBetweenDates(corsa *table, int size){
    int i;
    char date1[20], date2[20];

    printf("Input the two dates separated by a space: \n");
    if(scanf("%s %s", date1, date2)==2){
        for(i=0; i<size; i++){
            if(strcmp(table[i].data, date1)>0 && strcmp(table[i].data, date2)<0){
                stampaCorsa(table[i]);
            }
        }
    }
    else{
        printf("Error.");
    }
}

void searchByStop(corsa *table, int size){
    int i;
    char stopname[30];
    printf("Input stop's name: \n");

    if(scanf("%s", stopname)==1){
        for(i=0; i<size; i++){
            if(strcmp(table[i].partenza, stopname)==0){
                stampaCorsa(table[i]);
            }
        }
    }
    else{
        printf("Error.");
    }
}
void searchByArrive(corsa *table, int size){
    int i;
    char arriveName[30];
    printf("Input stop's name: \n");

    if(scanf("%s", arriveName)==1){
        for(i=0; i<size; i++){
            if(table[i].destinazione == arriveName){
                stampaCorsa(table[i]);
            }
        }
    }
    else{
        printf("Error.");
    }
}
void searchByLateBetweenDate(corsa *table, int size){
    int i;
    char date1[20], date2[20];

    printf("Input the two dates separated by a space: \n");
    if(scanf("%s %s", date1, date2)==2){
        for(i=0; i<size; i++){
            if(strcmp(table[i].data, date1)>0 && strcmp(table[i].data, date2)<0 && table[i].ritardo>0){
                stampaCorsa(table[i]);
            }
        }
    }
    else{
        printf("Error.");
    }
}
void sumLate(corsa *table, int size){
    int i, late=0;
    char code[10];
    scanf("%s", code);
    for(i=0; i<size; i++){
        if(strcmp(code, table[i].codice)==0){
            late+=table[i].ritardo;
        }
    }
    printf("Total late gained by selected route: %d\n", late);
}

int main(){
    corsa table[MAX_ROW];
    comando_e cmd;
    int rows;

    rows = leggiFile(FILENAME, table);
    if(rows==0) return 0;

    cmd=leggiComando();
    selezionaDati(table, rows, cmd);

}