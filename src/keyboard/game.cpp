#include <SFML/Graphics.hpp>
#include <game.h>
#include <iostream>
#include <locale>
#include <string>
#include <vector>
using namespace std;
using namespace sf;

int getSymbolWidth(Text text)
{
    cout << text.findCharacterPos(1).x << endl;
    return text.findCharacterPos(2).x - text.findCharacterPos(1).x;
}

void startGame(sf::RenderWindow& window)
{
    Texture keyboardTexture;
    if (!keyboardTexture.loadFromFile("source/keyboard.png")) {
        cout << "Error, source/keyboard.png not found" << endl;
    }
    RectangleShape keyboard(Vector2f(1200, 400));
    keyboard.setPosition(Vector2f(360, 680));
    keyboard.setTexture(&keyboardTexture);
    Font font;
    if (!font.loadFromFile("source/OpenSans-Regular.ttf")) {
        cout << "Error, source/OpenSans-Regular.ttf not found" << endl;
    }
    Text symbols;
    symbols.setFont(font);
    symbols.setCharacterSize(40);
    symbols.setFillColor(Color::Black);
    string levelStr = "good luck and have a nice day!";
    symbols.setString(levelStr);
    symbols.setPosition(950, 295);
    RectangleShape display(Vector2f(1920, 50));
    display.setPosition(Vector2f(0, 300));

    RectangleShape currentSymbol(Vector2f(23, 50));
    currentSymbol.setPosition(Vector2f(949, 300));
    currentSymbol.setFillColor(Color(250, 150, 100, 160));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    if (static_cast<char>(event.text.unicode) == levelStr[0]) {
                        levelStr.erase(levelStr.begin());
                        currentSymbol.setSize(
                                Vector2f(getSymbolWidth(symbols), 50));
                        currentSymbol.setFillColor(Color(250, 150, 100, 160));

                    } else {
                        currentSymbol.setFillColor(Color(240, 50, 50, 160));
                    }
                }
            }
        }
        window.draw(keyboard);
        window.draw(display);
        window.draw(currentSymbol);
        symbols.setString(levelStr);
        window.draw(symbols);
        window.display();
        sleep(milliseconds(1000 / 60));
        window.clear();
    }
}