#include "dllist.h"

int alloc_count = 0;

dllist *dllist_init(void)
{
    dllist *_dllist = malloc(sizeof(dllist));
    assert(_dllist != NULL);
    alloc_count++;

    _dllist->size = 0;
    _dllist->head = NULL;
    _dllist->tail = NULL;
    return _dllist;
}

void dllist_free(
    dllist **_dllist)
{
    node *current_node = (*_dllist)->head;
    while (current_node != NULL)
    {
        node *temp = current_node->next;
        free(current_node);
        alloc_count -= 1;
        current_node = temp;
    }

    (*_dllist)->size = 0;
    free(*_dllist);
    *_dllist = NULL;
    alloc_count -= 1;
}

int dllist_is_empty(const dllist *_dllist) { return (_dllist->size == 0); }
int dllist_get_size(const dllist *_dllist) { return _dllist->size; }

void dllist_print(
    const dllist *_dllist)
{
    node *iterator = _dllist->head;
    while (iterator != NULL)
    {
        printf("%d ", iterator->data);
        iterator = iterator->next;
    }
    putchar('\n');
}

void dllist_empty(
    dllist *_dllist)
{
    while (!dllist_is_empty(_dllist))
        pop_node_first(_dllist);
}

node *__create_node(
    const int data)
{
    node *_node = malloc(sizeof(node));
    assert(_node != NULL);
    alloc_count++;

    _node->data = data;
    _node->prev = NULL;
    _node->next = NULL;
    return _node;
}

void push_node_first(
    dllist *_dllist,
    const int data)
{
    node *new_node = __create_node(data);

    if (_dllist->head == NULL)
    {
        _dllist->head = new_node;
        _dllist->tail = new_node;
    }
    else
    {
        _dllist->head->prev = new_node;
        new_node->next = _dllist->head;
        _dllist->head = new_node;
    }
    _dllist->size += 1;
}

void push_node_last(
    dllist *_dllist,
    const int data)
{
    node *new_node = __create_node(data); // create new_node, with data.
    if (_dllist->head == NULL)
    {
        _dllist->head = new_node;
        _dllist->tail = new_node;
    }
    else
    {
        _dllist->tail->next = new_node;
        new_node->prev = _dllist->tail;
        _dllist->tail->next = new_node;

        _dllist->tail = new_node;
    }
    _dllist->size++;
}

void push_node_at_index(
    dllist *_dllist,
    const int index,
    const int data)
{
    if (index < 0 || dllist_is_empty(_dllist))
        return;

    if (index == 0)
    {
        push_node_first(_dllist, data);
        return;
    }

    if (index == _dllist->size)
    {
        push_node_last(_dllist, data);
        return;
    }

    __push_node_at(_dllist, index, data);
}

void __push_node_at(
    dllist *_dllist,
    const int index,
    const int data)
{
    int i = 1;
    node *current_node = _dllist->head->next;

    while (i < index && current_node != NULL)
    {
        current_node = current_node->next;
        i++;
    }

    if (current_node == NULL)
        return;

    node *new_node = __create_node(data);

    new_node->prev = current_node->prev;
    new_node->next = current_node;

    current_node->prev->next = new_node;
    current_node->prev = new_node;

    _dllist->size += 1;
}

void pop_node_first(
    dllist *_dllist)
{
    if (dllist_is_empty(_dllist))
        return;

    node *rm_head = _dllist->head;
    _dllist->head = _dllist->head->next;

    if (_dllist->head == NULL)
        _dllist->tail = NULL;
    else
        _dllist->head->prev = NULL;

    free(rm_head);
    alloc_count -= 1;

    _dllist->size -= 1;
}

void pop_node_last(
    dllist *_dllist)
{
    if (dllist_is_empty(_dllist))
        return;

    node *rm_tail = _dllist->tail;
    _dllist->tail = _dllist->tail->prev;

    if (_dllist->tail == NULL)
        _dllist->head = NULL;
    else
        _dllist->tail->next = NULL;

    free(rm_tail);
    alloc_count -= 1;

    _dllist->size -= 1;
}

void __pop_node_at(
    dllist *_dllist,
    const int index)
{
    int i = 1;
    node *current_node = _dllist->head->next;

    while (i < index && current_node != NULL)
    {
        current_node = current_node->next;
        i += 1;
    }

    if (current_node == NULL)
        return;

    node *rm_node = current_node;
    current_node->prev->next = rm_node->next;
    current_node->next->prev = rm_node->prev;

    free(rm_node);
    alloc_count -= 1;

    _dllist->size -= 1;
}
void pop_node_at_index(
    dllist *_dllist,
    const int index)
{
    if (dllist_is_empty(_dllist) || index < 0 || index >= _dllist->size)
        return;

    if (index == 0)
    {
        pop_node_first(_dllist);
        return;
    }

    if (index == _dllist->size - 1)
    {
        pop_node_last(_dllist);
        return;
    }

    __pop_node_at(_dllist, index);
}

int get_node(
    const dllist *_dllist,
    const int index)
{
    int i = 0;
    node *trav = _dllist->head;

    while (trav != NULL && i < index)
    {
        trav = trav->next;
        i += 1;
    }

    assert(trav != NULL);
    return trav->data;
}

void update_node(
    dllist *_dllist,
    const int index,
    const int newVal)
{
    int i = 0;
    node *trav = _dllist->head;

    while (trav != NULL && i < index)
    {
        trav = trav->next;
        i += 1;
    }

    assert(trav != NULL);
    trav->data = newVal;
}
