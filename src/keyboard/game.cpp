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

void startGame(sf::RenderWindow& window) vector<button> getButtons()
{
    Texture keyboardTexture;
    if (!keyboardTexture.loadFromFile("source/keyboard.png")) {
        cout << "Error, source/keyboard.png not found" << endl;
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

    RectangleShape keyboard(Vector2f(1200, 400));
    keyboard.setPosition(Vector2f(360, 680));
    keyboard.setTexture(&keyboardTexture);
    void drawButtons(RenderWindow & window, vector<button> buttons)
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

    void startGame(sf::RenderWindow & window)
    {
        Font font;
        if (!font.loadFromFile("source/OpenSans-Regular.ttf")) {
            cout << "Error, source/OpenSans-Regular.ttf not found" << endl;
        }

        vector<button> buttons = getButtons();

        Text symbols;
        symbols.setFont(font);
        symbols.setCharacterSize(40);
        @ @-66, 10 + 101, 9 @ @ void startGame(sf::RenderWindow & window)
    }
}
}
window.draw(keyboard);
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