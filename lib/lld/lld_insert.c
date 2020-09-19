/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** hello
*/

#include "../my.h"
#include <stdlib.h>

void lld_insert_start(lld_t *lld, void *data, long int pos)
{
    lld_t *lld_o = lld;
    lld->data = (void *)((u64)lld->data + 1);
    lld_t *tmp = (lld_t*)malloc(sizeof(lld_t));
    tmp->data = data;
    for (int i = 0; pos > i; lld = lld->next, i++);
    tmp->next = lld->next;
    if (pos)
        tmp->prev = lld;
    else
        tmp->prev = 0;
    lld->next = tmp;
    if (tmp->next != 0)
        tmp->next->prev = tmp;
    else
        lld_o->prev = tmp;
}

void lld_insert_end(lld_t *lld, void *data, long int pos)
{
    lld_t *lld_o = lld;
    lld->data = (void*)((u64)lld->data + 1);
    lld_t *tmp = (lld_t*)malloc(sizeof(lld_t));
    tmp->data = data;
    for (int i = (int)lld->data; pos < i; lld = lld->prev, i--);
    tmp->next = lld->next;
    if (pos)
        tmp->prev = lld;
    else
        tmp->prev = 0;
    lld->next = tmp;
    if (tmp->next != 0)
        tmp->next->prev = tmp;
    else
        lld_o->prev = tmp;
}

void lld_insert(lld_t *lld, int poss, void *data)
{
    long int pos = (long int)poss;
    if ((long int)lld->data/2 >= (long int)pos)
        lld_insert_start(lld, data, pos);
    else
        lld_insert_end(lld, data, pos);

}
