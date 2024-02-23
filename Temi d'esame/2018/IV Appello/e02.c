/* Lista di interi -> generare lista "compressa"*/

#include <stdio.h> 
#include <stdlib.h>

typedef struct link1_t *link1;
typedef struct link2_t *link2;

struct link1_t{
    int val;
    link1 next;
};

struct link2_t{
    int val;
    int reps;
    link2 next;
};

link1 NEW1(int val, link1 next);
link2 NEW2(int val, int reps, link2 next);
link2 comprimi(link1 head);
link1 listInsTail(link1 head, int val);

link1 NEW1(int val, link1 next){
    link1 link = malloc(sizeof(*link));
    link->val = val;
    link->next = next;

    return link;
}

link1 listInsTail(link1 head, int val){
    link1 x, p;
    if(head==NULL) return NEW1(val, NULL);

    for(x=head; x!=NULL; p=x, x=x->next);

    p->next = NEW1(val, NULL);
    return head;

}

link2 NEW2(int val, int reps, link2 next){
    link2 link = malloc(sizeof(*link));
    link->val = val;
    link->reps = reps;
    link->next = next;

    return link;
}

link2 comprimi(link1 head){
    if(head==NULL) return NULL;

    link2 h2=NULL;
    link2 p=NULL, cur;
    link1 x;
    int val=0, occ=0;
    
    val = head->val; occ=1;
    
    for(x=head->next; x!=NULL; x=x->next){
        printf("Sto guardando il valore %d\n", x->val);
        //Terminazione
        if(x->val != val){
            cur = NEW2(val, occ, NULL);
            if(!h2) h2=cur;
            printf("Ora elaboro %d\n", cur->val);
            if(p){
                p->next = cur;
                printf("Ora il prossimo di %d è %d\n", p->val, cur->val);
            }
            p = cur;
            
            val = x->val;
            occ=1;
        }
        else
            occ++;
    }

    p->next = NEW2(val, occ, NULL);

    return h2;

}

int main(){
    link1 x; link2 y;
    link1 head = NULL;
    head = listInsTail(head, 3);
    head = listInsTail(head, 3);
    head = listInsTail(head, 3);
    head = listInsTail(head, 3);
    head = listInsTail(head, 2);
    head = listInsTail(head, 2);
    head = listInsTail(head, 3);
    head = listInsTail(head, 5);
    head = listInsTail(head, 5);
    head = listInsTail(head, 5);

    for(x=head; x!=NULL; x=x->next) printf("%d ", x->val);
    printf("\n");

    link2 h2 = comprimi(head);

    for(y=h2; y!=NULL; y=y->next) printf("(%d %d) ", y->val, y->reps);
    printf("\n");

}