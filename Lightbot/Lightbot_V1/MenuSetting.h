#ifndef MENUSETTING_H
#define MENUSETTING_H

#include "Menu.h"

const sf::Vector2f ROBOT_POS1 = {100,400};
const sf::Vector2f ROBOT_POS2 = {250,400};
const sf::Vector2f ROBOT_POS3 = {400,400};

class MenuSetting : public Menu
{
private:
    sf::RectangleShape  m_robot_selector;                       // rectangle that shows the selected robot skin
    std::string         m_selected_skin = "images/robotHD.png"; // file of the selected robot skin
public:
    // Constructor
    MenuSetting();

    void init(const std::string &filename, const int &lumi);    // initialisation of menu values and attibutes depending on file and luminosity value

    // Getters
    int getCursorValue() const;
    const std::string getChoice() const;

    // Setters
    void setCursor(const int &x);
    void setChoice(const std::string &filename);

    void draw_to_setting(sf::RenderWindow &window);
};

#endif // MENUSETTING_H
