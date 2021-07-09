#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "tiled_map_parser.h"
#include "game_map.h"

using namespace std;

class Player : public sf::Drawable {
    public:
        Player(const sf::Texture& texture) : character {texture, {0,0,64,64}} {}

        void update(const sf::Time& delta_time);

    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            target.draw(character, states);
        }
        sf::Sprite character;
        int row = 0;
        int col = 0;
        int grid_size = 64;
        float velocity = 100;
};

void
Player::update(const sf::Time& delta_time)
{
    bool moved = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        character.move(0, -(velocity * delta_time.asSeconds()));
        row = 0;
        moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        character.move(-(velocity * delta_time.asSeconds()), 0);
        row = 1;
        moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        character.move(0, velocity * delta_time.asSeconds());
        row = 2;
        moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        character.move(velocity * delta_time.asSeconds(), 0);
        row = 3;
        moved = true;
    }

    if (moved) {
        col = ((col +1) % 8);
        character.setTextureRect({(col + 1) * grid_size, /*+1 since 0th is idle */
                                 row * grid_size,
                                 grid_size,
                                 grid_size});
    } else {
        character.setTextureRect({0,
                                 row * grid_size,
                                 grid_size,
                                 grid_size});
    }
}


int main()
{
    sf::RenderWindow window{sf::VideoMode{16*32, 16*32}, "test game"};
    window.setFramerateLimit(30);

    sf::Texture player_tex;
    if (!player_tex.loadFromFile("images/BODY_skeleton.png")) {
        cout << "Error\n";
    }
    Player myPlayer{player_tex};

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
