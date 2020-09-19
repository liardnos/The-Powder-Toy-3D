/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** hello
*/

#include "../my.h"
#include <stdlib.h>

void *lld_write_start(lld_t *lld, long int pos, void *data)
{
    //if (pos >= lld->data) write(2, "db lld write < 0\n", 17);
    lld = lld->next;
    for (int i = 0; pos > i; lld = lld->next, i++);
    void *data2 = lld->data;
    lld->data = data;
    return (data2);
}

void *lld_write_end(lld_t *lld, long int pos, void *data)
{
    //if (pos >= lld->data) write(2, "db lld write >= lld->data\n", 26);
    lld_t *lld_o = lld;
    lld = lld->prev;
    for (int i = ((long long int)lld_o->data)-1; pos < i; lld = lld->prev, i--);
    void *data2 = lld->data;
    lld->data = data;
    return (data2);
}

void *lld_write(lld_t *lld, int poss, void *data)
{
    long int pos = (long int)poss;
    if ((long int)lld->data/2 >= (long int)pos){
        data = lld_write_start(lld, pos, data);
    } else {
        data = lld_write_end(lld, pos, data);
    }
    return (data);
}
