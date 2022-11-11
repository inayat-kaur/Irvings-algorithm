# include <stdio.h>
# include <stdbool.h>

struct choice{
    int person;
    bool proposed;
    bool accepted;
    bool rejected;
};

void stage1(struct choice ** choice_list){

}

void stage2(){

}

int main(){
    int n;
    scanf("%d",&n);
    struct choice choice_list[n][n-1];
    int next_to_propose[n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n-1;j++){
            scanf("%d",&choice_list[i][j].person);
            choice_list[i][j].proposed=false;
            choice_list[i][j].accepted=false;
            choice_list[i][j].rejected=false;
        }
    }
    stage1(choice_list);
    return 0;
}