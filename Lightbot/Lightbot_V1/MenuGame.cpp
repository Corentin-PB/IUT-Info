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

#include "MenuGame.h"

void MenuGame::init() {
    this->add_image("images/LightbotInterface.png",0,0);
    Button* b = new Button(52,649,"images/lightInstruction.png");
    m_buttons.push_back(b);
    b = new Button(146,649,"images/forwardInstruction.png");
    m_buttons.push_back(b);
    b = new Button(240,649,"images/P1Instruction.png");
    m_buttons.push_back(b);
    b = new Button(334,649,"images/P2Instruction.png");
    m_buttons.push_back(b);
    b = new Button(428,649,"images/turnLeftInstruction.png");
    m_buttons.push_back(b);
    b = new Button(522,649,"images/turnRightInstruction.png");
    m_buttons.push_back(b);
    b = new Button(980,12,"images/playButton.png",1,1);
    m_buttons.push_back(b);
    b = new Button(1080,12,"images/stepByStepButton.png",1,1);
    m_buttons.push_back(b);
    b = new Button(1180,12,"images/trashButton.png",1,1);
    m_buttons.push_back(b);
    b = new Button(707,629,"images/backMenu.png");
    m_buttons.push_back(b);
    b = new Button(867,86,400,252);
    m_buttons.push_back(b);
    b = new Button(867,384,400,137);
    m_buttons.push_back(b);
    b = new Button(867,572,400,137);
    m_buttons.push_back(b);
}

void MenuGame::addButtonReset() {
    Button* b = new Button(694,299,"images/resetButton.png");
    m_buttons.push_back(b);
}

void MenuGame::deleteButtonReset() {
    delete m_buttons[m_buttons.size()-1];
    m_buttons.pop_back();
}

void MenuGame::switchButtonEditor() {
    m_buttons[9]->changeTexture(0);
}

void MenuGame::switchButtonBack() {
    m_buttons[9]->changeTexture(1);
}
