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
    scanf("%d", &n);
    int *choices[n];
    for (int i = 0; i < n; i++)
    {
        choices[i] = (int *)malloc(sizeof(int) * (n - 1));
    }
    bool *rejected[n];
    for (int i = 0; i < n; i++)
    {
        rejected[i] = (bool *)malloc(sizeof(bool) * (n));
    }
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

bool stage1(int n, int **choices, bool **rejected, int *set_proposed_to, int *accepted)
{
    int proposer, next_choice;
    for (int person = 0; person < n; person++)
    {
        proposer = person;
        next_choice = 0;
        while (true)
        {
            next_choice = 0;
            while (next_choice < n - 1 && rejected[proposer][choices[proposer][next_choice]] != false)
                next_choice++;
            if (next_choice == n - 1)
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
                    rejected[choices[choices[proposer][next_choice]][j]][choices[proposer][next_choice]] = true;
                    rejected[choices[proposer][next_choice]][choices[choices[proposer][next_choice]][j]] = true;
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

struct list *stage2(int n, int **choices, bool **rejected, int *accepted)
{
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

    struct list *result = (struct list *)malloc(n * sizeof(struct list));
    for (int i = 0; i < n; i++)
    {
        result[i].head = NULL;
        result[i].tail = NULL;
        result[i].list_for = i;
        for (int j = 0; j < n - 1; j++)
        {
            if (rejected[i][choices[i][j]] == false)
                insert(&result[i], choices[i][j]);
        }
    }
    return result;
}

void stage3(struct list *result, int n)
{
    int p[n + 1], q[n + 1];
    int exists[n];
    for (int i = 0; i < n; i++)
    {
        exists[i] = -1;
    }
    int i, at_level1, at_level2;
    while (1)
    {
        for (i = 0; i < n; i++)
        {
            if (result[i].head != result[i].tail)
            {
                p[0] = result[i].list_for;
                break;
            }
        }
        if (i == n)
            break;
        at_level1 = p[0];
        i = 0;
        do
        {
            exists[p[i]] = i;
            at_level2 = result[at_level1].head->next->person;
            at_level1 = result[at_level2].tail->person;
            q[i] = at_level2;
            p[i + 1] = at_level1;
            i++;
        } while (exists[at_level1] == -1);
        int cycle_node = p[i];
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

struct list_node *delete_tail(struct list_node *tail)
{
    struct list_node *temp;
    temp = tail->prev;
    tail->prev->next = NULL;
    free(tail);
    return temp;
}

void delete (struct list *result, int from, int id)
{
    struct list_node *temp;
    temp = result[from].head;
    while (temp->person != id)
        temp = temp->next;
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
