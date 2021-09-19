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
    textButton.setFillColor(Color::White);

    RectangleShape menuButton1(Vector2f(500, 100));
    RectangleShape menuButton2(Vector2f(500, 100));

    menuButton1.setFillColor(Color(0, 0, 0));
    menuButton1.setOutlineColor(Color(250, 150, 100));
    menuButton1.setOutlineThickness(5);
    menuButton1.setPosition(Vector2f(710, 400));

    menuButton2.setFillColor(Color(0, 0, 0));
    menuButton2.setOutlineColor(Color(250, 150, 100));
    menuButton2.setOutlineThickness(5);
    menuButton2.setPosition(Vector2f(710, 550));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            FloatRect boundsButton1 = menuButton1.getGlobalBounds();
            FloatRect boundsButton2 = menuButton2.getGlobalBounds();
            if (event.type == sf::Event::MouseMoved) {
                if (boundsButton1.contains(
                            event.mouseMove.x, event.mouseMove.y)) {
                    menuButton1.setFillColor(Color(250, 150, 100));
                } else {
                    menuButton1.setFillColor(Color(0, 0, 0));
                }
                if (boundsButton2.contains(
                            event.mouseMove.x, event.mouseMove.y)) {
                    menuButton2.setFillColor(Color(250, 150, 100));
                } else {
                    menuButton2.setFillColor(Color(0, 0, 0));
                }
            }
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    if (boundsButton1.contains(
                                event.mouseButton.x, event.mouseButton.y)) {
                        cout << "Start game";
                    }
                    if (boundsButton2.contains(
                                event.mouseButton.x, event.mouseButton.y)) {
                        window.close();
                    }
                }
            }
        }

        //рисуем заголовок
        @ @-38, 11 + 74,
                9 @ @ void initMenu(sf::RenderWindow & window)
                        window.draw(textButton);

        //отрисовываем кнопки

        window.draw(menuButton1);
        window.draw(menuButton2);

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