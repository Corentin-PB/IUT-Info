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

#include "MenuEditor.h"

void MenuEditor::init() {
    this->add_image("images/editorLightbot.png",0,0);
    Button* b = new Button(857,90,"images/lessButton.png",1,1);
    m_buttons.push_back(b);
    b = new Button(955,90,"images/plusButton.png",1,1);
    m_buttons.push_back(b);
    b = new Button(1068,90,"images/lessButton.png",1,1);
    m_buttons.push_back(b);
    b = new Button(1173,90,"images/plusButton.png",1,1);
    m_buttons.push_back(b);
    b = new Button(151,628,"images/testLevel.png");
    m_buttons.push_back(b);
    b = new Button(362,628,"images/newLevel.png");
    m_buttons.push_back(b);
    b = new Button(573,628,"images/mainMenuEditor.png");
    m_buttons.push_back(b);
}
