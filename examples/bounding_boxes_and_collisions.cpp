#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
using namespace std;

int main()
{
    sf::RenderWindow window{sf::VideoMode{800, 600}, "First SFML Window!"};
    window.setFramerateLimit(30);

    /* Create texture + sprite */
    sf::Texture texture1;
    if (!texture1.loadFromFile("images/stone_wall_3.png")) {
        cout << "Error\n";
    }
    sf::Sprite sprite1{texture1, sf::IntRect{0,0,50,50}};
    sf::Sprite sprite2{texture1, sf::IntRect{0,0,80,80}};

    /* Start each sprite at opposite ends of screen, same offset down */
    sprite1.setPosition(30,30);
    sprite2.setPosition(700,30);

    /* Default movement */
    sf::Vector2f s1_mov {5,0};
    sf::Vector2f s2_mov {-5,0};

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        /* Bounding boxes for each sprite */
        sf::FloatRect s1_box {sprite1.getGlobalBounds()};
        sf::FloatRect s2_box = sprite2.getGlobalBounds();

        /* If boxes collide, reverse the movement */
        if (s1_box.intersects(s2_box)) {
            cout << "Collision\n";
            s1_mov.x = -s1_mov.x;
            s2_mov.x = -s2_mov.x;
        }

        sprite1.move(s1_mov);
        sprite2.move(s2_mov);

        window.clear();
        window.draw(sprite1);   /* draw sprite */
        window.draw(sprite2);   /* draw sprite */
        window.display();
    }

    return 0;
}
