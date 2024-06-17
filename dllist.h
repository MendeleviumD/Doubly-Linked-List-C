#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

extern int alloc_count;

typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
} node;

typedef struct dllist
{
    int size;
    struct node *head;
    struct node *tail;
} dllist;

// List initialization and cleanup
dllist *dllist_init(void);
void dllist_free(dllist **_dllist);

// List properties
int dllist_is_empty(const dllist *_dllist);
int dllist_get_size(const dllist *_dllist);

// List utilities
void dllist_print(const dllist *_dllist);
void dllist_empty(dllist *_dllist);

// Node manipulation
node *__create_node(const int node_value);
void push_node_first(dllist *_dllist, const int node_value);
void push_node_last(dllist *_dllist, const int node_value);
void push_node_at_index(dllist *_dllist, const int index, const int node_value);
void __push_node_at(dllist *_dllist, const int index, const int data);
void pop_node_first(dllist *_dllist);
void pop_node_last(dllist *_dllist);
void __pop_node_at(dllist *_dllist, const int index);
void pop_node_at_index(dllist *_dllist, const int index);

// Node access
int get_node(const dllist *_dllist, const int index);
void update_node(dllist *_dllist, const int index, const int new_value);