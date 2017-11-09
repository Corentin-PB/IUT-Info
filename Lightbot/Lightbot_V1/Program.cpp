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

#include "Program.h"
#include "Appli.h"

Program::~Program() {
    for(Button* b : m_main_buttons)
        delete b;
    for(Button* b : m_proc1_buttons)
        delete b;
    for(Button* b : m_proc2_buttons)
        delete b;
}

void Program::action(Grid &grid,Robot *robot)
{
    if (m_prog_string.size() != 0) {
        switch(m_prog_string.at(m_currentPosition)) {
        case 'F': // Avancer
            if (grid.isInGrid(nextPosForward(robot)))
            robot->setPosition(nextPosForward(robot),grid);
            m_currentPosition++;
            break;
        case 'L': // Tourner Gauche
            if(robot->getDirection() == 0) {
                robot->setDirection(5);
            } else {
                robot->setDirection(robot->getDirection()-1);
            }
            m_currentPosition++;
            break;
        case 'R': // Tourner Droite
            if (robot->getDirection() == 5) {
                robot->setDirection(0);
            } else {
                robot->setDirection(robot->getDirection()+1);
            }
            m_currentPosition++;
            break;
        case 'I': // Allumer
            grid.lightUpCase( robot->getPosition() );
            m_currentPosition++;
            break;
        }
    }
}

void Program::vecToProg(std::string & prog, std::vector<int> vec)
{
    for (unsigned int i = 0; i < vec.size(); i ++)
    {
        switch (vec.at(i)) {
        case 1:
            prog += 'F';
            break;
        case 2:
            prog += 'L';
            break;
        case 3:
            prog += 'R';
            break;
        case 4:
            prog += 'I';
            break;
        case 5:
            vecToProg(prog,m_proc1);
            break;
        case 6:
            vecToProg(prog,m_proc2);
            break;
        }
    }
}

int Program::max_prog_size() const {
    int cptP1 = 0, cptP2 = 0;
    for (auto a : m_main) {
        if (a == 5)
            cptP1++;
        else if (a == 6)
            cptP2++;
    }
    for (auto a : m_proc1) {
        if (a == 5)
            cptP1++;
        else if (a == 6)
            cptP2++;
    }
    for (auto a : m_proc2) {
        if (a == 5)
            cptP1++;
        else if (a == 6)
            cptP2++;
    }
    int i = m_main.size() + (cptP1*m_proc1.size()) + (cptP2*m_proc2.size()) - cptP1 - cptP2;
    return i;
}

int Program::position() const {
    return m_currentPosition;
}

std::string Program::prog_string() const {
    return m_prog_string;
}

void Program::reset_prog() {
    m_prog_string.clear();
}

void Program::reset_position() {
    m_currentPosition = 0;
}

int Program::buttonContains(const sf::Vector2f &mouse, const int &nb) const {
    unsigned int i = 0;
    bool found = false;
    if(nb == 0) {
        while( !found && i< m_main_buttons.size() ) {
            if(m_main_buttons[i]->contains(mouse))
                found = true;
            else
                i++;
        }
    }
    else if(nb == 1) {
        while( !found && i< m_proc1_buttons.size() ) {
            if(m_proc1_buttons[i]->contains(mouse))
                found = true;
            else
                i++;
        }
    }
    else if(nb == 2) {
        while( !found && i< m_proc2_buttons.size() ) {
            if(m_proc2_buttons[i]->contains(mouse))
                found = true;
            else
                i++;
        }
    }
    if(found)
        return i;
    else return -1;
}

void Program::next(Grid &grid,Robot *robot) {
    action(grid,robot);
}

sf::Vector2f Program::nextPosForward(const Robot *robot) const {
    if( ((int)robot->getPosition().x % 2) == 0 ) {
        sf::Vector2f pos_robot = robot->getPosition();
        switch(robot->getDirection()) {
        case 0:
            return {pos_robot.x,pos_robot.y-1};
            break;
        case 1:
            return {pos_robot.x+1,pos_robot.y-1};
            break;
        case 2:
            return {pos_robot.x+1,pos_robot.y};
            break;
        case 3:
            return {pos_robot.x,pos_robot.y+1};
            break;
        case 4:
            return {pos_robot.x-1,pos_robot.y};
            break;
        case 5:
            return {pos_robot.x-1,pos_robot.y-1};
            break;
        default:
            return pos_robot;
            break;
        }
    } else {
        sf::Vector2f pos_robot = robot->getPosition();
        switch(robot->getDirection()) {
        case 0:
            return {pos_robot.x,pos_robot.y-1};
            break;
        case 1:
            return {pos_robot.x+1,pos_robot.y};
            break;
        case 2:
            return {pos_robot.x+1,pos_robot.y+1};
            break;
        case 3:
            return {pos_robot.x,pos_robot.y+1};
            break;
        case 4:
            return {pos_robot.x-1,pos_robot.y+1};
            break;
        case 5:
            return {pos_robot.x-1,pos_robot.y};
            break;
        default:
            return pos_robot;
            break;
        }
    }
}

int Program::buttonTypeCalculation(const std::string &filename) {
    if(filename.find("forward") != std::string::npos)
        return 1;
    else if(filename.find("light") != std::string::npos)
        return 4;
    else if (filename.find("P1") != std::string::npos)
        return 5;
    else if (filename.find("P2") != std::string::npos)
        return 6;
    else if (filename.find("Left") != std::string::npos)
        return 2;
    else if (filename.find("Right") != std::string::npos)
        return 3;
    return -1;
}

void Program::positionCalculationMain(const int &nb) {
    for(unsigned i = nb; i<m_main_buttons.size(); i++)
        m_main_buttons[i]->setPosition({POS_MAIN.x + 20 + (i%6)*(INSTRUCTION_MARGIN_X+INSTRUCTION_SIZE),
                                        POS_MAIN.y + 20 + (i/6)*(INSTRUCTION_MARGIN_Y+INSTRUCTION_SIZE)});
}
void Program::positionCalculationProc1(const int &nb) {
    for(unsigned i = nb; i<m_proc1_buttons.size(); i++)
        m_proc1_buttons[i]->setPosition({POS_PROC1.x + 20 + (i%6)*(INSTRUCTION_MARGIN_X+INSTRUCTION_SIZE),
                                         POS_PROC1.y + 20 + (i/6)*(INSTRUCTION_MARGIN_Y+INSTRUCTION_SIZE)});
}
void Program::positionCalculationProc2(const int &nb) {
    for(unsigned i = nb; i<m_proc2_buttons.size(); i++)
        m_proc2_buttons[i]->setPosition({POS_PROC2.x + 20 + (i%6)*(INSTRUCTION_MARGIN_X+INSTRUCTION_SIZE),
                                         POS_PROC2.y + 20 + (i/6)*(INSTRUCTION_MARGIN_Y+INSTRUCTION_SIZE)});
}

int Program::insertPos(const sf::Vector2f &mouse, const int &nb) const {
    unsigned i = 0;
    bool found = false;
    if(nb == 0)
        while(!found && i<m_main_buttons.size()) {
            if( mouse.y > m_main_buttons[i]->getPosition().y - INSTRUCTION_MARGIN_Y/2
                    && mouse.y < m_main_buttons[i]->getPosition().y + INSTRUCTION_SIZE + INSTRUCTION_MARGIN_Y/2
                    && mouse.x > m_main_buttons[i]->getPosition().x - INSTRUCTION_MARGIN_X - INSTRUCTION_SIZE/2
                    && mouse.x < m_main_buttons[i]->getPosition().x + INSTRUCTION_SIZE/2)
                found = true;
            else i++;
        }
    else if(nb == 1)
        while(!found && i<m_proc1_buttons.size()) {
            if( mouse.y > m_proc1_buttons[i]->getPosition().y - INSTRUCTION_MARGIN_Y/2
                    && mouse.y < m_proc1_buttons[i]->getPosition().y + INSTRUCTION_SIZE + INSTRUCTION_MARGIN_Y/2
                    && mouse.x > m_proc1_buttons[i]->getPosition().x - INSTRUCTION_MARGIN_X - INSTRUCTION_SIZE/2
                    && mouse.x < m_proc1_buttons[i]->getPosition().x + INSTRUCTION_SIZE/2)
                found = true;
            else i++;
        }
    else if(nb == 2)
        while(!found && i<m_proc2_buttons.size()) {
            if( mouse.y > m_proc2_buttons[i]->getPosition().y - INSTRUCTION_MARGIN_Y/2
                    && mouse.y < m_proc2_buttons[i]->getPosition().y + INSTRUCTION_SIZE + INSTRUCTION_MARGIN_Y/2
                    && mouse.x > m_proc2_buttons[i]->getPosition().x - INSTRUCTION_MARGIN_X - INSTRUCTION_SIZE/2
                    && mouse.x < m_proc2_buttons[i]->getPosition().x + INSTRUCTION_SIZE/2)
                found = true;
            else i++;
        }
    if(found)
        return i;
    else return -1;
}

void Program::addInstruction(const std::string &filename, const int &nb, const int &pos) {
    switch(nb) {
    case 0:
        if(pos != -1) {
            m_main_buttons.insert(m_main_buttons.begin()+pos,new Button(filename));
            m_main.insert(m_main.begin()+pos,buttonTypeCalculation(filename));
            positionCalculationMain(pos);
        } else {
            m_main_buttons.push_back(new Button(filename));
            m_main.push_back(buttonTypeCalculation(filename));
            positionCalculationMain(m_main_buttons.size()-1);
        }

        break;
    case 1:
        if (buttonTypeCalculation(filename) != 5) {
            if (buttonTypeCalculation(filename) == 6 && m_used == true) {

            }
            else {
                if (buttonTypeCalculation(filename) == 6) { m_used = true; }
                if(pos != -1) {
                    m_proc1_buttons.insert(m_proc1_buttons.begin()+pos,new Button(filename));
                    m_proc1.insert(m_proc1.begin()+pos,buttonTypeCalculation(filename));
                    positionCalculationProc1(pos);
                } else {
                    m_proc1_buttons.push_back(new Button(filename));
                    m_proc1.push_back(buttonTypeCalculation(filename));
                    positionCalculationProc1(m_proc1_buttons.size()-1);
                }
            }
        }
        break;
    case 2:
        if (buttonTypeCalculation(filename) != 6) {
            if (buttonTypeCalculation(filename) == 5 && m_used == true) {

            }
            else {
                if (buttonTypeCalculation(filename) == 5) { m_used = true; }
                if(pos != -1) {
                    m_proc2_buttons.insert(m_proc2_buttons.begin()+pos,new Button(filename));
                    m_proc2.insert(m_proc2.begin()+pos,buttonTypeCalculation(filename));
                    positionCalculationProc2(pos);
                }
                else {
                    m_proc2_buttons.push_back(new Button(filename));
                    m_proc2.push_back(buttonTypeCalculation(filename));
                    positionCalculationProc2(m_proc2_buttons.size()-1);
                }
            }
            break;
        }
    }
    m_prog_string.clear();
    vecToProg(m_prog_string,m_main);
}

void Program::deleteInstruction(const Button *b, const int &nb) {
    bool found = false;
    unsigned i = 0;
    if(nb == 0) {
        while(!found && i<m_main_buttons.size()) {
            if(m_main_buttons[i] == b)
                found = true;
            else i++;
        }
        if(found) {
            m_main_buttons.erase(m_main_buttons.begin()+i);
            m_main.erase(m_main.begin()+i);
            delete b;
        }
    }
    else if(nb == 1) {
        while(!found && i<m_proc1_buttons.size()) {
            if(m_proc1_buttons[i] == b)
                found = true;
            else i++;
        }
        if(found) {
            if (m_proc1[i] == 6)
                m_used = false;
            m_proc1_buttons.erase(m_proc1_buttons.begin()+i);
            m_proc1.erase(m_proc1.begin()+i);
            delete b;
        }
    }
    else if(nb == 2) {
        while(!found && i<m_proc2_buttons.size()) {
            if(m_proc2_buttons[i] == b)
                found = true;
            else i++;
        }
        if(found) {
            if (m_proc2[i] == 5)
                m_used = false;
            m_proc2_buttons.erase(m_proc2_buttons.begin()+i);
            m_proc2.erase(m_proc2.begin()+i);
            delete b;
        }
    }
    m_prog_string.clear();
    vecToProg(m_prog_string,m_main);
}

void Program::clearPrograms() {
    for(Button* b : m_main_buttons)
        delete b;
    m_main_buttons.clear();
    m_main.clear();
    for(Button* b : m_proc1_buttons)
        delete b;
    m_proc1_buttons.clear();
    m_proc1.clear();
    for(Button* b : m_proc2_buttons)
        delete b;
    m_proc2_buttons.clear();
    m_proc2.clear();
    m_prog_string.clear();
}

void Program::draw_to(sf::RenderWindow &win) {
    for(Button* a : m_main_buttons )
        a->draw_to(win);
    for(Button* a : m_proc1_buttons )
        a->draw_to(win);
    for(Button* a : m_proc2_buttons )
        a->draw_to(win);
}
