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
    string letter;
    bool active;
};

int getSymbolWidth(Text text)
{
    return text.findCharacterPos(2).x - text.findCharacterPos(1).x;
}

vector<button> getButtons()
{
    vector<string> letters
            = {"q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "a", "s", "d",
               "f", "g", "h", "j", "k", "l", "z", "x", "c", "v", "b", "n", "m"};
    vector<button> buttons;
    for (int i = 1; i < 27; i++) {
        button currentButton;
        currentButton.number = i;
        currentButton.letter = letters[i - 1];
        if (i <= 10) {
            currentButton.position = Vector2f(i * 70 + 600, 700);
        } else if (i <= 19) {
            @ @-36, 6 + 40,
                    7 @ @vector<button> getButtons()

                            currentButton.position
                    = Vector2f((i - 9.5) * 70 + 600, 770);
        } else {
            currentButton.position = Vector2f((i - 17.5) * 70 + 600, 840);
        }
        string fold = "source/keys/" + to_string(i) + ".png";
        currentButton.folder = fold;
        currentButton.active = false;
        buttons.push_back(currentButton);
    }
    return buttons;

    @ @-52, 10 + 57,
            23 @ @ void drawButtons(
                    RenderWindow & window, vector<button> buttons)
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
        if (buttons[i].active) {
            currentButton.setFillColor(Color::Yellow);
        }
        window.draw(currentButton);
    }
}

int getActiveButtonId(unsigned int unicode, vector<button> buttons)
{
    for (unsigned int i = 0; i < buttons.size(); i++) {
        if (buttons[i].letter == static_cast<char>(unicode)) {
            return i;
        }
    }
    return -1;
}

void startGame(sf::RenderWindow& window)
{
    Font font;

    @ @-81, 6 + 99,
            8 @ @ void startGame(sf::RenderWindow & window)

                    if (!font.loadFromFile("source/OpenSans-Regular.ttf"))
    {
        cout << "Error, source/OpenSans-Regular.ttf not found" << endl;
    }
    vector<button> buttons = getButtons();
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

    int activeButtonId = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            @ @-89, 6 + 109,
                    12 @ @ void startGame(sf::RenderWindow & window)

                            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    buttons[activeButtonId].active = false;
                    activeButtonId
                            = getActiveButtonId(event.text.unicode, buttons);
                    if (activeButtonId >= 0) {
                        buttons[activeButtonId].active = true;
                    }
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