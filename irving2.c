# include <stdio.h>
# include <stdbool.h>

bool stage1(int n,int** choices,int ** rejected,int * set_proposed_to,int *accepted);

int main(){
    int n;
    scanf("%d",&n);
    int choices[n][n-1];
    bool rejected[n][n];
    int set_proposed_to[n];
    int accepted[n];
    int temp;
    for(int i=0;i<n;i++){
        for(int j=0;j<n-1;j++){
            scanf("%d",&temp);
            choices[i][j]=temp;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j)rejected[i][j]=true;
            rejected[i][j]=false;
        }
    }
    for(int i=0;i<n;i++){
        set_proposed_to[i]=-1;
        accepted[i]=-1;
    }
    bool matching_exists=stage1(n,choices,rejected,set_proposed_to,accepted);
    return 0;
}

bool stage1(int n,int** choices,int ** rejected,int * set_proposed_to,int *accepted){
    int proposer,next_choice;
    for(int person=0;person<n;person++){
        proposer=person;
        next_choice=0;
        // set_proposed_to[choices[proposer][next_choice]] == -1
        while(1){
            next_choice=0;
            while(rejected[proposer][choices[proposer][next_choice]]==true)next_choice++;
            if(next_choice==n){
                return false;
            }
            if(accepted[choices[proposer][next_choice]]!=-1){
                int j = 0;
                while(choices[choices[proposer][next_choice]][j] != proposer) {
                    if(accepted[choices[proposer][next_choice]] == choices[choices[proposer][next_choice]][j]){
                        rejected[proposer][choices[proposer][next_choice]] = true;
                        break;
                    }
                    j++;
                }
                if(choices[choices[proposer][next_choice]][j] == proposer){
                    while(accepted[choices[proposer][next_choice]] != choices[choices[proposer][next_choice]][j]) j++;
                    accepted[choices[proposer][next_choice]]=proposer;
                    set_proposed_to[proposer]=choices[proposer][next_choice];
                    proposer = choices[choices[proposer][next_choice]][j];
                }
            }
            else{
                accepted[choices[proposer][next_choice]]=proposer;
                set_proposed_to[proposer]=choices[proposer][next_choice];
                break;
            }
        }
    }
    return true;
}
