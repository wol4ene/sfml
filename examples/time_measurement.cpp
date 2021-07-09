#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

int main()
{
    sf::RenderWindow window{sf::VideoMode{640, 480}, "First SFML Window!"};
    window.setFramerateLimit(30);
    sf::CircleShape shape(200.f, 6);
    shape.setFillColor(sf::Color::Green);

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch(event.type) {
            case sf::Event::Closed:
                cout << "window closed\n";
                window.close();
                break;
            default:
                break;
            }
        }

        /* Measure elapsed time between two points */
#if 0
        sf::Time t1 = clock.getElapsedTime();
        sf::sleep(sf::seconds(1));
        sf::Time t2 = clock.getElapsedTime();
        cout << "Elapsed: " << (t2-t1).asMicroseconds() << " us" << endl;
#endif
        
        /* Measure each game-loop iteration */
        sf::Time loop_time = clock.restart();
        cout << "Elapsed: " << loop_time.asMicroseconds() << " us" << endl;

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
