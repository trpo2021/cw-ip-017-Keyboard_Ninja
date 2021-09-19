#include <SFML/Graphics.hpp>
#include <game.h>
#include <iostream>
#include <locale>
#include <string>
#include <vector>
using namespace std;
using namespace sf;

struct button {
    int number;
    Vector2f position;
    string folder;
    bool active;
};

int getSymbolWidth(Text text)
{
    cout << text.findCharacterPos(1).x << endl;
    return text.findCharacterPos(2).x - text.findCharacterPos(1).x;
}

vector<button> getButtons()
{
    vector<button> buttons;
    for (int i = 1; i < 27; i++) {
        button currentButton;
        currentButton.number = i;
        if (i <= 10) {
            currentButton.position = Vector2f(i * 70 + 600, 700);
        } else if (i <= 19) {
            currentButton.position = Vector2f((i - 9.5) * 70 + 600, 770);
        } else {
            currentButton.position = Vector2f((i - 17.5) * 70 + 600, 840);
        }
        string fold = "source/keys/" + to_string(i) + ".png";
        currentButton.folder = fold;
        buttons.push_back(currentButton);
    }
    return buttons;
}

void drawButtons(RenderWindow& window, vector<button> buttons)
{
    for (unsigned int i = 0; i < buttons.size(); i++) {
        Texture texture;
        if (!texture.loadFromFile(buttons[i].folder)) {
            cout << "Error, " << buttons[i].folder << " not found" << endl;
        }
        RectangleShape currentButton;
        currentButton.setSize(Vector2f(60, 60));
        currentButton.setPosition(buttons[i].position);
        currentButton.setTexture(&texture);
        window.draw(currentButton);
    }
}

void startGame(sf::RenderWindow& window)
{
    Font font;
    if (!font.loadFromFile("source/OpenSans-Regular.ttf")) {
        cout << "Error, source/OpenSans-Regular.ttf not found" << endl;
    }

    vector<button> buttons = getButtons();

    Text symbols;
    symbols.setFont(font);
    symbols.setCharacterSize(40);

    @ @-66, 10 + 101,
            9 @ @ void startGame(sf::RenderWindow & window)

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
        window.draw(display);
        window.draw(currentSymbol);
        drawButtons(window, buttons);
        symbols.setString(levelStr);
        window.draw(symbols);

        window.display();
        sleep(milliseconds(1000 / 60));
        window.clear();
    }
}