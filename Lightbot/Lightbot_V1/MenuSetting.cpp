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

#include "MenuSetting.h"

MenuSetting::MenuSetting()
{
    m_robot_selector.setOutlineThickness(5);
    m_robot_selector.setOutlineColor(sf::Color::White);
    m_robot_selector.setFillColor(sf::Color::Transparent);
    m_robot_selector.setSize({120,120});
}


void MenuSetting::init(const std::string &filename, const int &lumi) {
    m_buttons.clear();
    this->add_image("images/settingsBackground.png",0,0);
    Button* b = new Button(1089,587,"images/mainMenu.png");
    m_buttons.push_back(b);
    b = new Button(ROBOT_POS1.x,ROBOT_POS1.y,"images/robotHD.png",0.16666,1);
    m_buttons.push_back(b);
    b = new Button(ROBOT_POS2.x,ROBOT_POS2.y,"images/robotHD2.png",0.16666);
    m_buttons.push_back(b);
    b = new Button(ROBOT_POS3.x,ROBOT_POS3.y,"images/robotHD3.png",0.16666);
    m_buttons.push_back(b);
    b = new Button(480,190,"images/backCursor.png");
    m_buttons.push_back(b);
    b = new Button(620+lumi,180,"images/cursor.png",1,1);
    m_buttons.push_back(b);
    setChoice(filename);
}

int MenuSetting::getCursorValue() const {
    return (m_buttons.at(5)->getPosition().x-640);
}

const std::string MenuSetting::getChoice() const {
    return m_selected_skin;
}

void MenuSetting::setCursor(const int &x) {
    if(x <= 800 && x >=480)
        m_buttons.at(5)->setPosition({x-20,180});
}

void MenuSetting::setChoice(const std::string &filename) {
    m_selected_skin = filename;
    if(filename.find("2") != std::string::npos)
        m_robot_selector.setPosition(ROBOT_POS2.x-10,ROBOT_POS2.y-10);
    else if(filename.find("3") != std::string::npos)
        m_robot_selector.setPosition(ROBOT_POS3.x-10,ROBOT_POS3.y-10);
    else m_robot_selector.setPosition(ROBOT_POS1.x-10,ROBOT_POS1.y-10);
}

void MenuSetting::draw_to_setting(sf::RenderWindow &window) {
    window.draw(m_background);
    for (Button* b : m_buttons) {
        b->draw_to(window);
    }
    window.draw(m_robot_selector);
}
