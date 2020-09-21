# include <iostream>
#include <SFML/Graphics.hpp>

#include "../Header.hpp"

extern "C" {
    #include "../../lib/my.h"
}

/*
f_function need

^p->life--;

if (life <= 0) ?


p->x += p->vx;
p->y += p->vy;

p->vx += map->gravity_x;
p->vy += map->gravity_y;

*/



void f_NONE(particle_t* p, struct map* map)
{
    
}

void f_STONE(particle_t* p, struct map* map)
{

}

void f_DIAMOND(particle_t* p, struct map* map)
{

}

void f_FIRE(particle_t* p, struct map* map)
{

}

void f_SMOKE(particle_t* p, struct map* map)
{

}


void (*p_fonc_table[])(particle_t* p, struct map* map) =
{
    f_NONE,
    f_STONE,
    f_DIAMOND,
    f_FIRE,
    f_SMOKE
};


map_t* map_malloc(int x, int y, int z)
{
    map_t* map = (map_t*)malloc(sizeof(map_t));
    if (!map)
        goto mem_error;
    map->size_x = x;
    map->size_y = y;
    map->size_z = z;

    //alloc 3D linked list
    map->map = (lld_t****)malloc(sizeof(lld_t**) * x);
    if (!map->map)
        goto mem_error;
    for (int i = 0; i < x; i++) {
        map->map[i] = (lld_t***)malloc(sizeof(lld_t*) * y);
        if (!map->map[i])
            goto mem_error;
        for (int j = 0; j < y; j++) {
            map->map[i][j] = (lld_t**)malloc(sizeof(lld_t*) * y);
            if (!map->map[i][j])
                goto mem_error;
            for (int k = 0; k < z; k++) {
                map->map[i][j][k] = (lld_t *)lld_init();
                if (!map->map[i][j][k])
                    goto mem_error;
            }
        }
    }
    
    //init particle linked list
    map->particles = lld_init();
    if (!map->particles)
        goto mem_error;

    map->p_fonc = p_fonc_table;


    if (0) {
    mem_error:
        std::cout << "malloc failed" << std::endl;
        exit(1);
    }

    return (map);
}

void map_free(map_t *map)
{
    //alloc 3D linked list
    for (int i = 0; i < map->size_x; i++) {
        for (int j = 0; j < map->size_y; j++) {
            for (int k = 0; k < map->size_z; k++) {
                lld_free(map->map[i][j][k]);
            }
            free(map->map[i][j]);
        }
        free(map->map[i]);
    }
    free(map->map);


    free(map);
}


