#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

struct levelButton {
    sf::Vector2f position;
    std::string text;
    std::string levelStr;
    bool active;
};

void openLevels(sf::RenderWindow& window);
std::vector<levelButton> initButtons();
