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
    sf::Sprite sprite{texture1, sf::IntRect{0,0,64,64}};

    /* set position */
    sprite.setPosition(250,250);

    /* set origin (defaults to 0,0 (top left corner) */
    sprite.setOrigin(32,32);

    /* set rotation (degrees clockwise) */
    //sprite.setRotation(45); 

    /* set scale (factor x, factor y) */
    sprite.setScale(1.5f, 5.0f);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        /* Move position each loop. 1pixel right, 1pixel up */
        //sprite.move(1,-1);

        /* Rotate 1degree clockwise */
        //sprite.rotate(1);

        window.clear();
        window.draw(sprite);   /* draw sprite */
        window.display();
    }

    return 0;
}
