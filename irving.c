# include <stdio.h>
# include "doubly_linked_list.h"

void purpose(int n,struct list * choice_list,int * next_to_propose, int i);
void reject(int n,struct list* choice_list,int to, int by);
void stage1(int n,struct list * choice_list);
void stage2(int n, struct choice * choice_list);
void stage3(int n, struct choice * choice_list);

int main(){
    int n;
    scanf("%d",&n);
    struct list choices[n];
    int temp;
    for(int i=0;i<n;i++){
        choices[i]=create_list();
        for(int j=0;j<n-1;j++){
            scanf("%d",&temp);
            insert(choices[i],temp);
        }
    }
    stage1(n,choices);
    return 0;
}

void purpose(int n,struct list * choice_list,int * next_to_propose, int i){

}

void reject(int n,struct list* choice_list,int to,int by){

}

void stage1(int n,struct list * choice_list){
    int next_to_propose[n];
    for(int i=0;i<n;i++){
        next_to_propose[i] = choice_list[i].head->person;
    }
    for(int i=0;i<n;i++)purpose(n,choice_list,next_to_propose,i);
}

void stage2(int n, struct choice * choice_list){

}

void stage3(int n, struct choice * choice_list){

}