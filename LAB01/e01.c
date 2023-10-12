#include <stdio.h>
#include <string.h>

int checkSub(char * source, char * exp); // gli faccio controllare sottostringe che partono da i
char *cercaRegexp(char *src, char *regexp);
int searchCompare(char *startPos, char cur_char);



char *cercaRegexp(char *src, char *regexp){
    int srclen = strlen(src);

    for(int i=0; i<srclen; i++){
        if(checkSub(&src[i], regexp)==1){
            return &src[i];
        }
    }
    return NULL;
}

int search(char *startPos, char cur_char){ // returns [] len, else 0
    int i=0, found=0, mode; //mode 0 is for ^
    mode=(startPos[i+1]=='^')?0:1;
    while(startPos[i]!=']'){
        if(cur_char==startPos[i]) found=1;
        i++;
    }
    return found;
}

int checkSub(char * subSource, char * exp){
    int i=0, j=0;
    int found;
    while(exp[i]!='\0'){
        switch(exp[i]){
            case '.':
                i++;
                break;
            case '\b':
                switch(exp[i+1]){
                    case 'a':
                        if(subSource[j]<'a' || subSource[j] >'z') return 0;
                        break;
                    case 'A':
                        if(subSource[j]<'A' || subSource[j]>'Z') return 0;
                        break;
                }
                i+=2; // va al prossimo carattere dopo \a nella exp
                break;

            case '[':
                found = search(&exp[i], subSource[j]);
                if(found && exp[i+1]=='^') return 0;
                if(!found && exp[i+1]!='^') return 0;
                while(exp[i]!=']') i++; //advance to next char in regexp
                i++;
                break;


            default: //lettera fissa
                if(exp[i]!=subSource[j]) return 0;
                i++;
        }
        j++; // passa al carattere successivo della stringa source
    }
    return 1;

}


int main(){

    char src[]="fefegergrrmotogrbvrvr";
    char regexp[]="[mn]oto";

    puts(cercaRegexp(src, regexp));

}