#include <stdio.h>
#include <stdbool.h>

struct person{
    int person_number;
    bool proposed;
    bool accepted;
    bool rejected;
};

struct list_node{
    struct list_node* next;
    struct list_node* prev;
    struct person id;
};

struct list{
    int list_for;
    struct list_node * head;
    struct list_node * tail;
};

struct list create_list();
void insert(struct list choice,int person_number);
void delete_first();
void delete_last();
void delete_current();
