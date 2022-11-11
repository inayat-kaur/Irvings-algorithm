# include <stdio.h>
# include "doubly_linked_list.h"

struct list create_list(int i){
struct list s1;
s1 = (struct list*)malloc(sizeof(struct list));
s1.list_for=i;
s1.head->NULL;
s1.tail->NULL;
return s1;
}

void insert(struct list choice,int person_number){
struct list_node* p;
p = (struct list_node*)malloc(sizeof(struct list_node));
p.id.person_number=p_number;
p.id.proposed=false;
p.id.accepted=false;
p.id.rejected=false;

p->prev=NULL;
p->next=NULL;

if(head==NULL && tail==NULL){
    choice->head=p;
    choice->tail=p;
}
else{
   tail->next=p;
   p->prev=tail;
   tail=p;
}
}

void delete_first(struct list choice){
 choice.head=choice.head->next;
    free(choice.head->prev);
    choice.head->prev=NULL;
}

void delete_last(struct list choice){
    choice.tail=choice.tail->prev;
    free(choice.tail->next);
    choice.tail->naet=NULL;
}

void delete_current(struct list choice,int curr_p_num){
 struct list_node *t =choice.head;
    while(t.id->person_number!=curr_per_num){
        t=t->next;
    }
    t->prev=t->next;
    t->next=t->prev;
    free(t);
}
