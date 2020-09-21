

extern "C" {
    #include "../lib/my.h"
}


#ifndef _sim_h_
#define _sim_h_

typedef struct map {
    //map
    int size_x; //+2
    int size_y; //+2
    lld_t **map; // [[lld*(size_y+2)]*(size_x+2)]

    //gravity
    float gravity_x = 0;
    float gravity_y = 10/60;

} map_t;

typedef struct particle {
    int type
    int life;
    float temp;
    unsigned char color[3];
    float x;
    float y;
    float vx;
    float vy;
} particle_t;

#endif
