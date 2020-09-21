#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>

extern "C" {
    #include "../lib/my.h"
}

#include "Header.hpp"

int main()
{
    map_t *map = map_malloc(128, 128, 128);




    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.display();
        window.clear();
    }

    map_free(map);

    char a;
    std::cout << "press enter to quit" << std::endl;
    std::cin >> a;

    return 0;
}
