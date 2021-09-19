#include <SFML/Graphics.hpp>
#include <string>

struct button {
    int number;
    sf::Vector2f position;
    std::string folder;
    std::string letter;
    bool active;
};

void startGame(sf::RenderWindow& window, std::string levelStr);
std::vector<button> getButtons();
int getActiveButtonId(unsigned int unicode, std::vector<button> buttons);
