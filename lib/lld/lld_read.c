/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** hello
*/

#include "../my.h"
#include <stdlib.h>

void *lld_read_start(lld_t *lld, long int pos)
{
    //if (pos >= lld->data) write(2, "db lld read < 0\n", 16);
    lld = lld->next;
    for (int i = 0; pos > i; lld = lld->next, i++);
    void *data = lld->data;
    return (data);
}

void *lld_read_end(lld_t *lld, long int pos)
{
    //if (pos >= lld->data) write(2, "db lld read >= lld->data\n", 25);
    lld_t *lld_o = lld;
    lld = lld->prev;
    for (int i = (int)lld_o->data-1; pos < i; lld = lld->prev, i--);
    void *data = lld->data;
    return (data);
}

void *lld_read(lld_t *lld, int poss)
{
    long int pos = (long int)poss;
    if ((long int)lld->data/2 >= (long int)pos){
        lld = (lld_t*)lld_read_start(lld, pos);
    } else {
        lld = (lld_t*)lld_read_end(lld, pos);
    }
    return (lld);
}
