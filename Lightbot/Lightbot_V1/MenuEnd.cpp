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

#include "MenuEnd.h"

void MenuEnd::init() {
    m_buttons.clear();
    this->add_image("images/endLevel.png",391,249);
    Button* b = new Button(416,317,"images/mainMenuEnd.png");
    m_buttons.push_back(b);
    b = new Button(571,317,"images/restartLevel.png");
    m_buttons.push_back(b);
    b = new Button(770,317,"images/nextLevel.png");
    m_buttons.push_back(b);
}

void MenuEnd::switchButtonEditor() {
    delete m_buttons[m_buttons.size()-1];
    m_buttons.pop_back();
    Button* b = new Button(770,317,"images/newLevelEnd.png");
    m_buttons.push_back(b);
    m_buttons[1]->setPosition({581,317});
    delete m_buttons[0];
    m_buttons[0] = new Button(416,317,"images/saveLevel.png");
}

void MenuEnd::switchButtonBack() {
    delete m_buttons[m_buttons.size()-1];
    m_buttons.pop_back();
    Button* b = new Button(770,317,"images/nextLevel.png");
    m_buttons[1]->setPosition({571,317});
    m_buttons.push_back(b);
    delete m_buttons[0];
    m_buttons[0] = new Button(416,317,"images/mainMenuEnd.png");
}
