#ifndef MENUMAIN_H
#define MENUMAIN_H

#include "Menu.h"

class MenuMain : public Menu
{
public:
    void init();    // initialisation of menu values and attibutes

    int buttonContainsMenu(const sf::Vector2f &mouse) const;    // verify if position is on a button using the special contains for main menu buttons

    void buttonSwitch(const int &num);  // switch the selected button texture (Pressed or not)
};

#endif // MENUMAIN_H
