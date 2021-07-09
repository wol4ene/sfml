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

    /* Load font from on-disk font file.
     * Font must live as long as Text that references it */
    sf::Font font;
    if (!font.loadFromFile("images/Arial.ttf")) {
        cout << "error\n";
    }

    /* Create text, set various fields */
    sf::Text text;
    text.setFont(font);
    text.setString("Hello world");
    text.setCharacterSize(100); // pixels
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Underlined | sf::Text::Italic);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.draw(shape);
        window.draw(text);  /* draw the text */
        window.display();
    }

    return 0;
}
