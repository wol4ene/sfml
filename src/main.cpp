#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "tiled_map_parser.h"
#include "game_map.h"
#include "player.h"

using namespace std;

int main()
{
    sf::RenderWindow window{sf::VideoMode{16*32, 16*32}, "test game"};
    window.setFramerateLimit(30);

    sf::Texture player_tex;
    if (!player_tex.loadFromFile("images/BODY_skeleton.png")) {
        cout << "Error\n";
    }
    Player myPlayer{player_tex, 64 /* gridsize */, 100.0f /* velocity */};

    GameMap game_map{"images/map4.json", "images/atlas_32x.png"};
    game_map.dump_map_info();
    game_map.dump_tile_layers();
    game_map.dump_object_layers();
    game_map.dump_tile_sets();

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Time delta_time = clock.restart();

        /* Update states */
        myPlayer.update(delta_time);

        sf::Time t1 = clock.getElapsedTime();
        game_map.update();
        sf::Time t2 = clock.getElapsedTime();
        cout << "Game map render: " << (t2-t1).asMicroseconds() << "us" << endl;

        /* Rander all objects to screen */
        window.clear(sf::Color::Blue);
        window.draw(game_map);
        window.draw(myPlayer);
        window.display();
    }

    return 0;
}
