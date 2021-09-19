#include <SFML/Graphics.hpp>
#include <iostream>
#include <menu.h>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "keyboard ninja");
    initMenu(window);

    system("PAUSE");
    return 0;
}
