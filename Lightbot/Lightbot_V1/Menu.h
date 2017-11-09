#ifndef MENU_H
#define MENU_H

#include <vector>
#include "Button.h"
#include <iostream>
#include <dirent.h>

const sf::Vector2f POS_MAIN {867,86};
const sf::Vector2f POS_PROC1 {867,384};
const sf::Vector2f POS_PROC2 {867,572};

class Menu
{
public:
    // Destructor
    ~Menu();

    sf::Texture             m_image;        // background texture
    sf::Sprite              m_background;   // background
    std::vector<Button*>    m_buttons;      // menu buttons

    // Getters
    std::string getButtonFile(const int &nb) const; // gather the file of a button

    int buttonContains(const sf::Vector2f &mouse) const;    // verify if position on a button

    void add_image(const std::string &file, const int &x, const int &y);    // add the background

    void draw_to(sf::RenderWindow &window);
};

#endif // MENU_H
