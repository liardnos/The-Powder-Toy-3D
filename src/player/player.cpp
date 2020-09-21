# include <iostream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>

#include "../Header.hpp"

extern "C" {
#include "../../lib/my.h"
}


player_t* player_malloc()
{
	player_t* player = (player_t*)malloc(sizeof(player_t));
	if (!player) {
		std::cout << "player allocation failed" << std::endl;
		exit(0);
	}


	player->matrix = mat3_init();
	return (player);
}

void player_free(player_t* player)
{
	free(player->matrix);
	free(player);
}