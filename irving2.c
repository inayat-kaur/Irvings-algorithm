#include <stdio.h>
#include <stdbool.h>

struct list_node
{
    struct list_node *next;
    struct list_node *prev;
    int person;
};

struct list
{
    int list_for;
    struct list_node *head;
    struct list_node *tail;
};

struct list create_list();
void insert(struct list* choice, int person_number);
void delete_current();
bool stage1(int n, int **choices, bool **rejected, int *set_proposed_to, int *accepted);
struct list* stage2(int n, int **choices, bool **rejected, int *accepted);
void stage3();

int main()
{
    int n;
    scanf("%d", &n);
    int choices[n][n - 1];
    bool rejected[n][n];
    int set_proposed_to[n];
    int accepted[n];
    int temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            scanf("%d", &temp);
            choices[i][j] = temp;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                rejected[i][j] = true;
            rejected[i][j] = false;
        }
    }
    for (int i = 0; i < n; i++)
    {
        set_proposed_to[i] = -1;
        accepted[i] = -1;
    }
    bool matching_exists = stage1(n, choices, rejected, set_proposed_to, accepted);
    if (matching_exists == false)
    {
        printf("No stable matching exists for the given preferences.\n");
    }
    else
    {
        struct list ** result = stage2(n, choices, rejected, accepted);
    }
    return 0;
}

bool stage1(int n, int **choices, bool **rejected, int *set_proposed_to, int *accepted)
{
    int proposer, next_choice;
    for (int person = 0; person < n; person++)
    {
        proposer = person;
        next_choice = 0;
        // set_proposed_to[choices[proposer][next_choice]] == -1
        while (1)
        {
            next_choice = 0;
            while (rejected[proposer][choices[proposer][next_choice]] == true)
                next_choice++;
            if (next_choice == n)
            {
                return false;
            }
            if (accepted[choices[proposer][next_choice]] != -1)
            {
                int j = 0;
                while (choices[choices[proposer][next_choice]][j] != proposer)
                {
                    if (accepted[choices[proposer][next_choice]] == choices[choices[proposer][next_choice]][j])
                    {
                        rejected[proposer][choices[proposer][next_choice]] = true;
                        rejected[choices[proposer][next_choice]][proposer] = true;
                        break;
                    }
                    j++;
                }
                if (choices[choices[proposer][next_choice]][j] == proposer)
                {
                    while (accepted[choices[proposer][next_choice]] != choices[choices[proposer][next_choice]][j])
                        j++;
                    accepted[choices[proposer][next_choice]] = proposer;
                    set_proposed_to[proposer] = choices[proposer][next_choice];
                    proposer = choices[choices[proposer][next_choice]][j];
                }
            }
            else
            {
                accepted[choices[proposer][next_choice]] = proposer;
                set_proposed_to[proposer] = choices[proposer][next_choice];
                break;
            }
        }
    }
    return true;
}

struct list* stage2(int n, int **choices, bool **rejected, int *accepted)
{
    for (int i = 0; i < n; i++)
    {
        int end = n - 1;
        while (choices[i][end] != accepted[i])
        {
            if (rejected[i][choices[i][end]] != true)
            {
                rejected[i][choices[i][end]] = true;
                rejected[choices[i][end]][i] = true;
            }
        }
    }

    struct list * result = (struct list*)malloc(n*sizeof(struct list));
    for(int i=0;i<n;i++){
        result[i] = create_list(i);
        for(int j=0;j<n-1;j++){
            if(rejected[i][choices[i][j]]==false)insert(&result[i],choices[i][j]);
        }
    }
    return result;
}

void stage3(){

}

struct list create_list(int i)
{
    struct list s1;
    s1.list_for = i;
    s1.head=NULL;
    s1.tail=NULL;
    return s1;
}

void insert(struct list * choice, int person_number)
{
    struct list_node *l = (struct list_node *)malloc(sizeof(struct list_node));

    l->prev = NULL;
    l->next = NULL;
    l->person = person_number;

    if (choice->head == NULL && choice->tail == NULL)
    {
        choice->head = l;
        choice->tail = l;
    }
    else
    {
        choice->tail->next = l;
        l->prev = choice->tail;
        choice->tail = l;
    }
}

void delete_current(struct list choice, int curr_p_num)
{
    struct list_node *t = choice.head;
    while (t.id->person_number != curr_per_num)
    {
        t = t->next;
    }
    t->prev = t->next;
    t->next = t->prev;
    free(t);
}
