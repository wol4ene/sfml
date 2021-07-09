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

    /**
     * Method1: start at rectLeft/rectTop of 0,0
     * view is 12 tiles by 12 tiles
     */
    //sf::View view(sf::FloatRect(0.f, 0.f, 12*32, 12*32));

    /**
     * Method2: centered at tile 6,6, view is 12 tiles by 12 tiles
     */
    sf::View view(sf::Vector2f(6*32, 6*32), sf::Vector2f(12*32, 12*32));
    //sf::View view(sf::Vector2f(8*32, 8*32), sf::Vector2f(9*32, 9*32));

    /**
     * Method3: view is half size of the default view
     */
    //sf::View view = window.getDefaultView();
    //view.zoom(0.9f);

    window.setView(view);

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

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

        printf("mouse window x,y = %d/%d, world x,y = %f/%f\n",
                mousePos.x, mousePos.y, worldPos.x, worldPos.y);

#if 0
        sf::Vector2f world_pos = myPlayer.get_position();
        printf("character world x,y = %f/%f\n", world_pos.x, world_pos.y);
        sf::Vector2i view_pos = window.mapCoordsToPixel(world_pos);
        printf("character view x,y = %d/%d\n", view_pos.x, view_pos.y);

        printf("view center: x,y = %f/%f, left edge = %f right edge = %f\n",
                view.getCenter().x, view.getCenter().y,
                view.getCenter().x - 144, view.getCenter().x + 144);
#endif
        //view.setCenter(myPlayer.get_position());
        //view.move(2.f,2.f);
        //window.setView(view);

        /* Update states */
        sf::Time delta_time = clock.restart();
        myPlayer.update(delta_time);
        game_map.update();

        /* Rander all objects to screen */
        window.clear(sf::Color::Blue);
        window.draw(game_map);
        window.draw(myPlayer);
        window.display();
    }

    return 0;
}
