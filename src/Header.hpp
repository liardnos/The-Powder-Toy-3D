

//simulation data
#ifndef _sim_h_
#define _sim_h_


extern "C" {
#include "../../lib/my.h"
}



//particle type
enum {
    P_NONE = 0,
    P_STONE = 1,
    P_DIAMOND = 2,
    P_FIRE = 3,
    P_SMOKE = 4
};

typedef struct particle {
    int type; //type of particle (
    int life;
    float temp;
    unsigned char color[3];
    float x;
    float y;
    float vx;
    float vy;
} particle_t;


typedef struct map {
    //map
    int size_x; //+2
    int size_y; //+2
    int size_z; //+2
    lld_t**** map; // [[[(lld*)*size_z]*size_y]*size_x]

    //gravity
    float gravity_x = 0;
    float gravity_y = 10 / 60;

    //particle call
    void (**p_fonc)(particle_t* p, struct map* map);

    //particle list
    lld_t* particles;

} map_t;

//fonction

map_t* map_malloc(int x, int y, int z); //alocate map_t for desired size
void map_free(map_t *map); //free an alocate map


#endif


#ifndef _player_h_
#define _player_h_

typedef struct player {
    float ax = 0; //camera x angle (yaw) 
    float ay = 0; //camera y angle (pitch)
    float x = 0; //player position
    float y = 0;
    float z = 0;
    float* matrix; //final 4*4 transformation matrix
} player_t;

#endif

