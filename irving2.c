#include <stdio.h>
#include <stdlib.h>
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
void insert(struct list *choice, int person_number);
struct list_node *delete_tail(struct list_node *tail);
void delete (struct list *result, int from, int person);
bool stage1(int n, int **choices, bool **rejected, int *set_proposed_to, int *accepted);
struct list *stage2(int n, int **choices, bool **rejected, int *accepted);
void stage3(struct list *result, int n);


int main()
{
    int n;
    printf("How many members? (Enter a positive even number)\n");
    scanf("%d", &n);
    int *choices[n];

    for (int i = 0; i < n; i++)
    {
        choices[i] = (int *)malloc(sizeof(int) * (n - 1));
    }

    // rejected[i][j] tells if member i has been rejected by member j or vice versa
    bool *rejected[n];

    for (int i = 0; i < n; i++)
    {
        rejected[i] = (bool *)malloc(sizeof(bool) * (n));
    }

    // set_proposed_to[i] tells if member i has proposed to anyone and if yes then to which member
    int set_proposed_to[n];
    // accepted[i] tells if member i has accepted any proposal and if yes then from which member
    int accepted[n];
    int temp;

    printf("Enter the preference order for each member, starting with member 0 in increasing order: \n");

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
            else
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
        // If there is a member i who is rejected by all, then no stable matching will exist
        printf("No stable matching exists for the given preferences.\n");
    }

    else
    {
        struct list *result = stage2(n, choices, rejected, accepted);
        stage3(result, n);
        printf("Resultant matching is :\n");
        for (int i = 0; i < n; i++)
        {
            printf("%d   -   %d\n", i, result[i].head->person);
        }
    }

    return 0;
}



/************************************    Various stages of the algorithm    ************************************/

bool stage1(int n, int **choices, bool **rejected, int *set_proposed_to, int *accepted)
{
    // current proposer
    int proposer;
    // current proposer's next most preferred member 
    int next_choice;

    for (int person = 0; person < n; person++)
    {
        proposer = person;
        next_choice = 0;

        while (true)
        {
            next_choice = 0;

            while (next_choice < n - 1 && rejected[proposer][choices[proposer][next_choice]] != false)
            {
                // Find the next most preffered member
                next_choice++;
            }

            if (next_choice == n - 1)
            {
                // If some member has already been rejected by everyone, the no stable matching will exist
                return false;
            }

            // If the proposed member already hols a proposal from someone
            if (accepted[choices[proposer][next_choice]] != -1)
            {
                int j = 0;

                // If the proposed member already hols a proposal from someone of higher preference, then we reject the current
                // the incoming proposal
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
                    {
                        j++;
                    }

                    // If the proposed member already hols a proposal from someone of lower preference, then we reject the low 
                    // preference proposal and accept the incoming proposal
                    accepted[choices[proposer][next_choice]] = proposer;
                    set_proposed_to[proposer] = choices[proposer][next_choice];
                    rejected[choices[choices[proposer][next_choice]][j]][choices[proposer][next_choice]] = true;
                    rejected[choices[proposer][next_choice]][choices[choices[proposer][next_choice]][j]] = true;
                    // The one being rejected becomes the next proposer
                    proposer = choices[choices[proposer][next_choice]][j];
                }
            }

            // If the proposed member has not already been proposed, then we simply accept the incoming proposal
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

struct list *stage2(int n, int **choices, bool **rejected, int *accepted)
{
    // Reject all members from each members preference list who have lower priority than the accepted proposal as
    // they can never form a pair in a stable matching 
    for (int i = 0; i < n; i++)
    {
        int end = n - 2;

        while (end >= 0 && choices[i][end] != accepted[i])
        {
            if (rejected[i][choices[i][end]] != true)
            {
                rejected[i][choices[i][end]] = true;
                rejected[choices[i][end]][i] = true;
            }
            end--;
        }
    }

    // Initialize the array of struct lists for third phase 
    struct list *result = (struct list *)malloc(n * sizeof(struct list));

    for (int i = 0; i < n; i++)
    {
        result[i].head = NULL;
        result[i].tail = NULL;
        result[i].list_for = i;
        for (int j = 0; j < n - 1; j++)
        {
            if (rejected[i][choices[i][j]] == false)
            {
                insert(&result[i], choices[i][j]);
            }
        }
    }

    return result;
}

void stage3(struct list *result, int n)
{
    int p[n + 1];
    int q[n + 1];
    int exists[n];

    for (int i = 0; i < n; i++)
    {
        exists[i] = -1;
    }

    int i;
    int at_level1;
    int at_level2;

    while (1)
    {
        for (i = 0; i < n; i++)
        {
            // Find a member who has more than one choice 
            if (result[i].head != result[i].tail)
            {
                p[0] = result[i].list_for;
                break;
            }
        }

        if (i == n)
        {
            break;
        }

        at_level1 = p[0];
        i = 0;

        do
        {
            // Find the second preference of member at level one, and then the last preference of member at level 2
            // Repeat until, any member repeats at level one
            exists[p[i]] = i;
            at_level2 = result[at_level1].head->next->person;
            at_level1 = result[at_level2].tail->person;
            q[i] = at_level2;
            p[i + 1] = at_level1;
            i++;
    
        } while (exists[at_level1] == -1);

        int cycle_node = p[i];

        // Every second preference and every last preference then reject each other symmetrically 
        while (i > exists[cycle_node])
        {
            at_level1 = p[i];
            at_level2 = q[i - 1];
            result[at_level2].tail = delete_tail(result[at_level2].tail);
            delete (result, at_level1, at_level2);
            i--;
        }
    }
}



/************************************    Operations for doubly linked list    ************************************/

// Inserts a node into the doubly linked list
void insert(struct list *choice, int person_number)
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

// Deletes the tail node from a doubly linked list
struct list_node *delete_tail(struct list_node *tail)
{
    struct list_node *temp;
    temp = tail->prev;
    tail->prev->next = NULL;
    free(tail);
    return temp;
}

// Deletes a specified node from the doubly linked list
void delete (struct list *result, int from, int id)
{
    struct list_node *temp;
    temp = result[from].head;

    while (temp->person != id)
    {
        temp = temp->next;
    }

    if (result[from].head == temp)
    {
        result[from].head = temp->next;
        temp->next->prev = NULL;
        free(temp);
    }

    else if (result[from].tail == temp)
    {
        result[from].tail = delete_tail(result[from].tail);
    }

    else
    {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        free(temp);
    }
}

/*
6
3 5 1 4 2
5 2 4 0 3
3 4 0 5 1
1 5 4 0 2
3 1 2 5 0
4 0 3 1 2
*/
