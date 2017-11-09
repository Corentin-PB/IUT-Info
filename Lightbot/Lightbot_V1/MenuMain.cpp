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

#include "MenuMain.h"

void MenuMain::init() {
    this->add_image("images/MenuBackground.png",0,0);
    Button* b = new Button(274,360,"images/play.png",0.6);
    m_buttons.push_back(b);
    b = new Button(393,508,"images/quit.png",0.6);
    m_buttons.push_back(b);
    b = new Button(666,508,"images/settings.png",0.6);
    m_buttons.push_back(b);
    b = new Button(789,360,"images/editor.png",0.6);
    m_buttons.push_back(b);
}

int MenuMain::buttonContainsMenu(const sf::Vector2f &mouse) const {
    for(unsigned i=0 ; i< m_buttons.size() ; i++)
        if(m_buttons[i]->containsMenu(mouse)==1)
            return i;
    return -1;
}

void MenuMain::buttonSwitch(const int &num) {
    m_buttons[num]->switchMainButton();
}
