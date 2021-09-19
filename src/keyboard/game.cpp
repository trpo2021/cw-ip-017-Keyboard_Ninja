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
            currentButton.position = Vector2f((i - 9.5) * 70 + 600, 770);
        } else {
            currentButton.position = Vector2f((i - 17.5) * 70 + 600, 840);
        }

        string fold = "source/keys/" + to_string(i) + ".png";
        currentButton.folder = fold;
        currentButton.active = false;
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

void startGame(sf::RenderWindow& window, string levelStr)
{
    Font font;
    if (!font.loadFromFile("source/OpenSans-Regular.ttf")) {
        cout << "Error, source/OpenSans-Regular.ttf not found" << endl;
    }

    vector<button> buttons = getButtons();

    Text symbols;
    symbols.setFont(font);
    symbols.setCharacterSize(40);
    symbols.setFillColor(Color::Black);

    symbols.setString(levelStr);
    symbols.setPosition(950, 295);

    RectangleShape display(Vector2f(1920, 50));
    display.setPosition(Vector2f(0, 300));

    RectangleShape currentSymbol(Vector2f(23, 50));
    currentSymbol.setPosition(Vector2f(949, 300));
    currentSymbol.setFillColor(Color(250, 150, 100, 160));

    RectangleShape stats(Vector2f(1000, 600));
    stats.setPosition(Vector2f(460, 240));
    stats.setFillColor(Color(200, 200, 200));

    Text congratulation;
    congratulation.setFont(font);
    congratulation.setCharacterSize(60);
    congratulation.setFillColor(Color::Black);
    congratulation.setString("Congratulation!!! Level complete");
    congratulation.setPosition(Vector2f(510, 300));

    RectangleShape backButton(Vector2f(500, 100));
    backButton.setPosition(Vector2f(710, 530));
    backButton.setFillColor(Color(244, 202, 181));

    Text backButtonText;
    backButtonText.setFont(font);
    backButtonText.setCharacterSize(50);
    backButtonText.setFillColor(Color::Black);
    backButtonText.setString("back to menu");
    backButtonText.setPosition(Vector2f(800, 550));

    int activeButtonId = 0;
    bool gameOver = false;

    while (window.isOpen()) {
        if (gameOver) {
            gameOver = false;
            break;
        }
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
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
                        currentSymbol.setFillColor(Color(244, 136, 181));

                    } else {
                        currentSymbol.setFillColor(Color(244, 202, 181));
                    }
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                FloatRect backButtonBounds = backButton.getGlobalBounds();
                if (backButtonBounds.contains(
                            event.mouseMove.x, event.mouseMove.y)) {
                    backButton.setFillColor(Color(250, 150, 100));
                } else {
                    backButton.setFillColor(Color(244, 136, 181));
                }
            }
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    FloatRect backButtonBounds = backButton.getGlobalBounds();
                    if (backButtonBounds.contains(
                                event.mouseButton.x, event.mouseButton.y)) {
                        gameOver = true;
                    }
                }
            }
        }

        window.draw(display);
        window.draw(currentSymbol);
        drawButtons(window, buttons);
        symbols.setString(levelStr);
        window.draw(symbols);
        if (levelStr.size() == 0) {
            window.draw(stats);
            window.draw(congratulation);
            window.draw(backButton);
            window.draw(backButtonText);
        }

        window.display();
        sleep(milliseconds(1000 / 60));
        window.clear();
    }
}
