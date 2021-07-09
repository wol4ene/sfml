#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
using namespace std;

int main()
{
    sf::RenderWindow window{sf::VideoMode{800, 600}, "First SFML Window!"};
    window.setFramerateLimit(30);

    sf::CircleShape shape(200, 100);
    shape.setFillColor(sf::Color::Green);

    /* Textures must live as long as sprites, sprites simply hold
     * a reference to a texture */
    sf::Texture texture1;
    sf::Texture texture2;
    if (!texture1.loadFromFile("images/greybrickwall007x800.png")) {
        cout << "Error\n";
    }
    if (!texture2.loadFromFile("images/stone_wall_3.png")) {
        cout << "Error\n";
    }

    /* Create sprites, set their textures */
    sf::Sprite sprite1;
    sprite1.setTexture(texture1);

    sf::Sprite sprite2{texture2};

    sf::Sprite sprite3{texture1, sf::IntRect{0,0,64,64}};
    sprite3.setPosition(250,250);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.draw(sprite1);   /* draw sprite1 */
        window.draw(sprite2);   /* draw sprite2 */
        window.draw(shape);
        window.draw(sprite3);   /* draw sprite3 */
        window.display();
    }

    return 0;
}
