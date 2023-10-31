
/*  E01 L01 Algoritmi e Strutture Dati 2023-24
    Matricola: s310687 

    Strategia: consiste nel far scorrere un indice all'interno della stringa principale
    (indicata come source) ed eseguire la verifica della regexp in sottostringhe di dimensione
    minore.
*/


#include <stdio.h>
#include <string.h>

char *cercaRegexp(char *src, char *regexp);
int checkSub(char * source, char * exp); 
int searchCompare(char *startPos, char cur_char);
int searchBetweenBrackets(char *startPos, char cur_char);

int main(){

    char src[]="rgrgrhrhrBe5t1efefeinfeinfie";
    char regexp[]="\bA[aeiou]5t[123]";

    puts(cercaRegexp(src, regexp));

    return 0;

}


char *cercaRegexp(char *src, char *regexp){
    int srclen = strlen(src);

    for(int i=0; i<srclen; i++){
        if(checkSub(src+i, regexp)==1)
            return src+i;
    }
    return NULL;
}


int checkSub(char * subSource, char * exp){
    int i=0, j=0;
    int found;
    while(exp[i]!='\0'){
        switch(exp[i]){
            case '.':
                i++;
                break;
            case '\b': // Backslash
                switch(exp[i+1]){
                    case 'a': // Lettera minuscola
                        if(subSource[j]<'a' || subSource[j] >'z') return 0;
                        break;
                    case 'A': // Lettera maiuscola
                        if(subSource[j]<'A' || subSource[j]>'Z') return 0;
                        break;
                }
                i+=2; // va al prossimo carattere dopo \a nella exp
                break;

            case '[': 
                found = searchBetweenBrackets(exp+i, subSource[j]);
                if(found && exp[i+1]=='^') return 0;
                if(!found && exp[i+1]!='^') return 0;
                while(exp[i]!=']') i++; //advance to next char in regexp
                i++;
                break;


            default: // Lettera dell'alfabeto
                if(exp[i]!=subSource[j]) return 0;
                i++;
                break;
        }
        j++; // passa al carattere successivo della stringa src
    }
    return 1;

}

int searchBetweenBrackets(char *startPos, char cur_char){ 
    int i=0, found=0, mode; //mode 0 is for ^
    mode=(startPos[i+1]=='^')?0:1;
    while(startPos[i]!=']'){
        if(cur_char==startPos[i]) found=1;
        i++;
    }
    return found;
}
