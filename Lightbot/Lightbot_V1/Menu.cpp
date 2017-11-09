//Copyright 2017 Pacaud Boehm Corentin & Colin Simon
/*
This file is part of Lightbot.

Lightbot is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Lightbot is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with Lightbot. If not, see http://www.gnu.org/licenses/.
*/

#include "Menu.h"


Menu::~Menu() {
    for(Button* b : m_buttons)
        delete b;
}

std::string Menu::getButtonFile(const int &nb) const {
    return m_buttons[nb]->getFile();
}

int Menu::buttonContains(const sf::Vector2f &mouse) const {
    for(unsigned i=0 ; i< m_buttons.size() ; i++)
        if(m_buttons[i]->contains(mouse) == 1)
                return i;
    return -1;
}

void Menu::add_image(const std::string &file, const int &x, const int &y) {
    m_image.loadFromFile(file);
    m_background.setTexture(m_image);
    m_background.setPosition({float(x),float(y)});
}

void Menu::draw_to(sf::RenderWindow &window) {
    window.draw(m_background);
    for (Button* b : m_buttons) {
        b->draw_to(window);
    }
}
