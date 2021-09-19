#include <SFML/Graphics.hpp>
#include <iostream>
#include <locale>
#include <menu.h>

using namespace std;
using namespace sf;

void initMenu(sf::RenderWindow& window)
{
    //инициализируем кнопку и текст
    Font font;
    if (!font.loadFromFile("source/OpenSans-Regular.ttf")) {
        cout << "Error, source/OpenSans-Regular.ttf not found" << endl;
    }

    Text textButton;
    textButton.setFont(font);
    textButton.setCharacterSize(48);
    textButton.setFillColor(sf::Color::White);

    RectangleShape menuButton(Vector2f(500, 100));
    menuButton.setFillColor(sf::Color(0, 0, 0));
    menuButton.setOutlineColor(sf::Color(250, 150, 100));
    menuButton.setOutlineThickness(5);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        //рисуем заголовок
        textButton.setString("KeyBoard Ninja");
        textButton.setPosition(Vector2f(790, 200));
        window.draw(textButton);

        //отрисовываем кнопки
        menuButton.setPosition(Vector2f(710, 400));
        window.draw(menuButton);

        menuButton.setPosition(Vector2f(710, 550));
        window.draw(menuButton);

        //отрисовываем текст на кнопках
        textButton.setPosition(Vector2f(880, 420));
        textButton.setString(L"Начать");
        window.draw(textButton);

        textButton.setPosition(Vector2f(885, 565));
        textButton.setString(L"Выход");
        window.draw(textButton);

        window.display();
        sleep(milliseconds(1000 / 60));
        window.clear();
    }
}