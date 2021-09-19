#include <SFML/Graphics.hpp>
#include <game.h>
#include <iostream>
#include <levels.h>
#include <locale>

using namespace std;
using namespace sf;

vector<levelButton> initButtons()
{
    vector<levelButton> buttons;
    vector<string> levelStrings
            = {"fjfjf jfjff jfjfj fjfff fjjjj jdkjf kdjfk kdfjj jfjjk kddfj "
               "dfjkk kjfdd lskdf sdklj sdlfk dkfjs",
               "jfdsl allks all dakl lasd lsass lskd kdjfsl alsdkj askdj ksjkd "
               "alkak asdkd alsdfk",
               "day jack fall lan zzxcv mack mask lad dall jam mad",
               "the day was very cold until i decided to take the initiative "
               "to take everything into my own hands and do it"};
    for (int i = 0; i < 4; i++) {
        levelButton currentButton;
        if (i < 2) {
            currentButton.position = Vector2f(i * 400 + 100, 200);
        } else {
            currentButton.position = Vector2f((i - 2) * 400 + 100, 400);
        }
        currentButton.levelStr = levelStrings[i];
        currentButton.text = "level " + to_string(i + 1);
        buttons.push_back(currentButton);
    }
    levelButton currentButton;
    currentButton.position = Vector2f(1500, 900);
    currentButton.text = "back";
    buttons.push_back(currentButton);
    return buttons;
}

void drawLevelButtons(
        RenderWindow& window,
        vector<levelButton> buttons,
        RectangleShape currentButton)
{
    currentButton.setSize(Vector2f(300, 100));
    currentButton.setFillColor(Color(0, 0, 0));
    currentButton.setOutlineColor(Color(250, 150, 100));
    currentButton.setOutlineThickness(5);
    currentButton.setPosition(Vector2f(710, 400));

    Font font;
    if (!font.loadFromFile("source/OpenSans-Regular.ttf")) {
        cout << "Error, source/OpenSans-Regular.ttf not found" << endl;
    }

    Text buttonText;
    buttonText.setFont(font);
    buttonText.setCharacterSize(48);
    buttonText.setFillColor(Color::White);

    for (unsigned int i = 0; i < buttons.size(); i++) {
        currentButton.setPosition(buttons[i].position);
        if (buttons[i].active) {
            currentButton.setFillColor(Color(250, 150, 100));
        } else {
            currentButton.setFillColor(Color(0, 0, 0));
        }
        buttonText.setPosition(Vector2f(
                buttons[i].position.x + 50, buttons[i].position.y + 20));
        buttonText.setString(buttons[i].text);
        window.draw(currentButton);
        window.draw(buttonText);
    }
}

void openLevels(RenderWindow& window)
{
    bool menuBack = false;

    vector<levelButton> buttons = initButtons();

    RectangleShape currentButton;

    Font font;
    if (!font.loadFromFile("source/OpenSans-Regular.ttf")) {
        cout << "Error, source/OpenSans-Regular.ttf not found" << endl;
    }

    Text article;
    article.setFont(font);
    article.setCharacterSize(48);
    article.setFillColor(Color::White);
    article.setPosition(300, 100);
    article.setString("Choose level");

    while (window.isOpen()) {
        if (menuBack) {
            menuBack = false;
            break;
        }
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseMoved) {
                for (unsigned int i = 0; i < buttons.size(); i++) {
                    RectangleShape currentButton(Vector2f(300, 100));
                    currentButton.setPosition(buttons[i].position);
                    FloatRect bounds = currentButton.getGlobalBounds();
                    if (bounds.contains(event.mouseMove.x, event.mouseMove.y)) {
                        buttons[i].active = true;
                    } else {
                        buttons[i].active = false;
                    }
                }
            }
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    for (unsigned int i = 0; i < buttons.size(); i++) {
                        RectangleShape currentButton(Vector2f(300, 100));
                        currentButton.setPosition(buttons[i].position);
                        FloatRect bounds = currentButton.getGlobalBounds();
                        if (bounds.contains(
                                    event.mouseButton.x, event.mouseButton.y)) {
                            if (i == 4) {
                                menuBack = true;
                            } else {
                                startGame(window, buttons[i].levelStr);
                            }
                        }
                    }
                }
            }
        }
        drawLevelButtons(window, buttons, currentButton);
        window.draw(article);
        window.display();
        sleep(milliseconds(1000 / 60));
        window.clear();
    }
}
