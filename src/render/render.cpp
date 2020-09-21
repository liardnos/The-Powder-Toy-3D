# include <iostream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>

#include "../Header.hpp"

extern "C" {
	#include "../../lib/my.h"
}


void draw_bottom_grid(map_t* map, player_t* player)
{

}

int render_simulation(map_t* map, player_t *player)
{

	for (lld_t* mv = map->particles->next; mv; mv = mv->next) {

	}

	//success 
	return (0);
}