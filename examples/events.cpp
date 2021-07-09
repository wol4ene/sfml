#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

int main()
{
    sf::RenderWindow window{sf::VideoMode{640, 480}, "First SFML Window!"};
    sf::CircleShape shape(200.f, 30);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch(event.type) {
            case sf::Event::TextEntered:
                cout << "Char: " << static_cast<char>(event.text.unicode) << endl;
                break;
            case sf::Event::Closed:
                cout << "window closed\n";
                window.close();
                break;
            case sf::Event::KeyPressed:
                cout << "user pressed key\n";
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                break;
            case sf::Event::KeyReleased:
                cout << "user released key\n";
                break;
            case sf::Event::Resized:
                cout << "window resized\n";
                cout << "new width: " << event.size.width << endl;
                cout << "new height: " << event.size.height << endl;
                break;
            case sf::Event::LostFocus:
                // pause game
                cout << "window lost focus\n";
                break;
            case sf::Event::GainedFocus:
                // restart game
                cout << "window gained focus\n";
                break;
            case sf::Event::MouseMoved:
                break; //chatty
                cout << "new mouse x: " << event.mouseMove.x << endl;
                cout << "new mouse y: " << event.mouseMove.y << endl;
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    cout << "left button press" << endl;
                    cout << "mouse x: " << event.mouseButton.x << endl;
                    cout << "mouse y: " << event.mouseButton.y << endl;
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    cout << "right button press" << endl;
                } else if (event.mouseButton.button == sf::Mouse::Middle) {
                    cout << "middle button press" << endl;
                } else {
                    cout << "unknown button press" << endl;
                }
                break;
            case sf::Event::MouseWheelScrolled:
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    cout << "wheel type: vertical\n";
                } else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel) {
                    cout << "wheel type: horizontal\n";
                } else {
                    cout << "wheel type: unknown\n";
                }
                cout << "wheel movement: " << event.mouseWheelScroll.delta << endl;
                cout << "mouse x: " << event.mouseWheelScroll.x << endl;
                cout << "mouse y: " << event.mouseWheelScroll.y << endl;
                break;
            default:
                break;
            }
        }

        window.clear();
        window.draw(shape);
        window.draw(rect);
        window.display();
    }

    return 0;
}
