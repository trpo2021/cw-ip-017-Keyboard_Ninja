#include <SFML/Graphics.hpp>
#include <iostream>
#include <menu.h>

using namespace std;
using namespace sf;

void initMenu(sf::RenderWindow& window)
{
    RectangleShape rectangle(Vector2f(120, 50));
    rectangle.setSize(Vector2f(100, 100));
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.draw(rectangle);
        window.display();
        sleep(milliseconds(1000 / 60));
        window.clear();
    }
}