#define CATCH_CONFIG_MAIN
#include <SFML/Graphics.hpp>
#include <catch.hpp>
#include <game.h>
#include <iostream>
#include <levels.h>
#include <locale>
#include <menu.h>
#include <string>
#include <vector>

TEST_CASE("LEVELS", "")
{
    SECTION("init buttons")
    {
        std::vector<levelButton> buttons = initButtons();

        CHECK(buttons.size() == 5);
        system("pause");
    }
}

TEST_CASE("GAME", "")
{
    SECTION("get buttons")
    {
        std::vector<button> buttons = getButtons();

        CHECK(buttons.size() == 26);
        system("pause");
    }

    SECTION("get active button id")
    {
        std::vector<button> buttons = getButtons();

        CHECK(getActiveButtonId(200, buttons) == -1);
        CHECK(getActiveButtonId(120, buttons) == 20);
        CHECK(getActiveButtonId(100, buttons) == 12);
        CHECK(getActiveButtonId(50, buttons) == -1);
        CHECK(getActiveButtonId(1, buttons) == -1);
        CHECK(getActiveButtonId(0, buttons) == -1);
        CHECK(getActiveButtonId(-1, buttons) == -1);
        system("pause");
    }
}
