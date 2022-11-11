# include <stdio.h>
# include "doubly_linked_list.h"

void stage1(int n,struct choice * choice_list){

}

void stage2(int n,struct choice * choice_list){

}

void stage3(int n,struct choice * choice_list){

}

int main(){
    int n;
    scanf("%d",&n);
    struct list choices[n];
    int next_to_propose[n];
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