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

#include "Appli.h"


Appli::Appli() {
    m_menu.init();
    m_game.init();
    m_end_menu.init();
    m_editor.init();
    m_robot = new Robot();
    m_setting.init("images/robotHD.png",0);
    m_select_level.init(m_level_type,m_current_page);
    m_selected_window = 5;
    m_selected_button = -1;
    m_luminosity.setFillColor(sf::Color(255,255,255,0));
    m_luminosity.setOutlineThickness(0);
    m_luminosity.setSize({WINDOW_WIDHT,WINDOW_HEIGHT});
    m_luminosity.setPosition({0,0});
    m_insertionRect.setFillColor(sf::Color::Transparent);
    m_insertionRect.setSize({2,50});
    m_insertionRect.setOutlineThickness(0.);
}

Appli::~Appli () {
    delete m_robot;
}

void Appli::animation() {
    if (m_prog.m_main.size() != 0) {
        sf::Vector2f pos = m_prog.nextPosForward(m_robot);
        switch(m_prog.prog_string().at(m_prog.position())) {
        case 'L':
            for (int i = 1; i < 30; i++) {
                m_robot->rotate(false);
                draw();
            }
            break;
        case 'R':
            for (int i = 1; i < 30; i++) {
                m_robot->rotate(true);
                draw();
            }
            break;
        case 'F':
            if (m_grid.isInGrid(pos)) {
                for (int i = 1; i < 30; i++) {
                    m_robot->forward(m_grid.getRadius());
                    draw();
                }
            }
            break;
        default:
            break;
        }
    }
}

void Appli::draw() {
    m_window.clear(sf::Color::Black);
    switch(m_selected_window)
    {
    case 2:
        m_setting.draw_to_setting(m_window);
        break;
    case 5:
        m_menu.draw_to(m_window);
        break;
    case 0:
        m_grid.drawto(m_window);
        m_game.draw_to(m_window);
        m_robot->draw_to(m_window);

        m_prog.draw_to(m_window);
        if(m_insertionRect.getFillColor() != sf::Color::Transparent)
            m_window.draw(m_insertionRect);
        if( m_instruction != nullptr )
            m_instruction->draw_to(m_window);
        if (m_level_end)
            m_end_menu.draw_to(m_window);
        break;
    case 6:
        m_select_level.draw_to(m_window);
        break;
    case 7:
    {
        m_editor.draw_to(m_window);
        m_grid.drawto(m_window);
        m_robot->draw_to(m_window);
    }
        break;
    }
    m_window.draw(m_luminosity);
    m_window.display();
}

void Appli::keyPressed(sf::Keyboard::Key code)
{
    switch (code) {
    case  sf::Keyboard::Q :
        m_appli_running = false;
        break;
    case  sf::Keyboard::Escape :
        m_selected_window = 5;
        break;
    default:
        break;
    };
}

void Appli::mousePressed()
{
    switch (m_selected_window)
    {
    case 2:
        m_selected_button = m_setting.buttonContains(m_mouse);
        if(m_selected_button == 0) {
            m_robot->setTexture(m_setting.getChoice());
            m_selected_window = 5;
            m_selected_button = -1;
        }
        else if(m_selected_button >= 1 && m_selected_button <= 3)
            m_setting.setChoice(m_setting.getButtonFile(m_selected_button));
        else if(m_selected_button == 4) {
            m_selected_button = 5;
            m_setting.setCursor(m_mouse.x);
            int lum = m_setting.getCursorValue();
            if(lum >= 0)
                m_luminosity.setFillColor(sf::Color(255,255,255,lum));
            else
                m_luminosity.setFillColor(sf::Color(0,0,0,-lum));

        }
        break;
    case 6:
        m_selected_button = m_select_level.buttonContains(m_mouse);
        if(m_selected_button == 0)
            m_selected_window = 5;
        else if(m_selected_button == 1 && m_level_type == 1) {
            m_level_type = 0;
            m_select_level.init(m_level_type,m_current_page);
        }
        else if(m_selected_button == 2 && m_level_type == 0) {
            m_level_type = 1;
            m_select_level.init(m_level_type,m_current_page);
        }
        else if(m_select_level.levelNumber(m_level_type) > 10
                && m_selected_button == 3
                && m_current_page > 0) {
            m_current_page--;
            m_select_level.init(m_level_type,m_current_page);
        }
        else if(m_select_level.levelNumber(m_level_type) > (m_current_page+1)*10
                && m_selected_button == 4) {
            m_current_page++;
            m_select_level.init(m_level_type,m_current_page);
        }
        else if(m_selected_button >= ( 3 + 2*(m_select_level.levelNumber(m_level_type) > 10) ) ) {
            m_selected_level = m_selected_button-2 - 2*(m_select_level.levelNumber(m_level_type) > 10) + m_current_page*10;
            m_grid.load(m_selected_level,m_level_type);
            m_robot->init(m_grid,m_grid.position(),m_grid.direction());
            m_selected_window = 0;
        }
        m_selected_button = -1;
        break;
    case 5:
        m_selected_button = m_menu.buttonContainsMenu(m_mouse);
        if(m_selected_button != -1)
            m_menu.buttonSwitch(m_selected_button);
        break;
    case 7:
        if(m_robot->contains(m_mouse)) {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                if(m_robot->getDirection() == 5) {
                    m_robot->setDirection(0);
                    m_grid.setDirection(0);
                } else {
                    m_robot->setDirection(m_robot->getDirection()+1);
                    m_grid.setDirection(m_robot->getDirection()+1);
                }
            }
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if(m_robot->getDirection() == 0) {
                    m_robot->setDirection(5);
                    m_grid.setDirection(5);
                } else {
                    m_robot->setDirection(m_robot->getDirection()-1);
                    m_grid.setDirection(m_robot->getDirection()-1);
                }
            }
        }
        else if(sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
            sf::Vector2f temp = m_grid.pos_to_vect(m_mouse);
            if (m_grid.contains(temp) && m_grid.grid().at((temp.y*m_grid.width())+temp.x) != 0) {
                m_robot->setPosition(temp,m_grid);
                m_grid.setPosition(temp);
            }
        }
        else {
            m_selected_button = m_editor.buttonContains(m_mouse);
            std::vector<int> temp2 = m_grid.grid();
            if(m_selected_button == -1) {
                sf::Vector2f temp = m_grid.pos_to_vect(m_mouse);
                if (m_grid.contains(temp)) {
                    m_grid.setHexaPlus(temp);
                }
            } else if(m_selected_button == 0) {
                m_grid.load(temp2,1);
                m_robot->scaleRadius(m_grid);
            } else if(m_selected_button == 1) {
                m_grid.load(temp2,0);
                m_robot->scaleRadius(m_grid);
            } else if(m_selected_button == 2) {
                m_grid.load(temp2,3);
                m_robot->scaleRadius(m_grid);
            } else if(m_selected_button == 3) {
                m_grid.load(temp2,2);
                m_robot->scaleRadius(m_grid);
            } else if(m_selected_button == 4) {
                if (m_grid.isPossible()) {
                    m_grid.save(-1);
                    m_from_editor = true;
                    m_end_menu.switchButtonEditor();
                    m_game.switchButtonEditor();
                    m_robot->scaleRadius(m_grid);
                    m_selected_window = 0;
                }
            } else if(m_selected_button == 5) {
                m_grid.load(-1,false);
                m_robot->setPosition(m_grid.position(),m_grid);
                m_robot->setDirection(m_grid.direction());
            } else if(m_selected_button == 6) {
                m_grid.clear();
                m_from_editor = false;
                m_end_menu.switchButtonBack();
                m_selected_window = 5;
            }
        }
        m_selected_button = -1;
        break;
    case 0:
        if (!m_level_end) {
            if (m_incomplete_end) {
                m_selected_button = m_game.buttonContains(m_mouse);
                if(m_selected_button == 13) {
                    m_prog.reset_position();
                    m_incomplete_end = false;
                    if (!m_from_editor) {
                        m_grid.load(m_selected_level,m_level_type);
                    }
                    else
                        m_grid.load(-1,true);
                    m_robot->init(m_grid,m_grid.position(),m_grid.direction());
                    m_game.deleteButtonReset();
                }
            }
            else {
                m_selected_button = m_game.buttonContains(m_mouse);
                if(m_selected_button >= 0 && m_selected_button <=5) {
                    m_instruction = new Button(m_game.getButtonFile(m_selected_button));
                    m_instruction->setPosition( {m_mouse.x-m_instruction->getSize().x/2,
                                                 m_mouse.y-m_instruction->getSize().y/2});
                    m_instruction->setScale(1.2,1.2);
                }
                else if(m_selected_button == 8)
                    m_prog.clearPrograms();
                else if(m_selected_button == 9) {
                    if (m_from_editor) {
                        m_game.switchButtonBack();
                        m_selected_window = 7;
                    } else {
                        m_selected_window = 5;
                    }
                }
                else if(m_selected_button == 10) {
                    int b = m_prog.buttonContains(m_mouse,0);
                    if( b != -1 ) {
                        m_instruction = new Button(m_prog.m_main_buttons[b]->getFile());
                        m_instruction->setPosition( {m_mouse.x-m_instruction->getSize().x/2,
                                                     m_mouse.y-m_instruction->getSize().y/2});
                        m_instruction->setScale(1.2,1.2);
                        m_prog.deleteInstruction(m_prog.m_main_buttons[b],0);
                        m_prog.positionCalculationMain(b);
                    }
                }
                else if(m_selected_button == 11) {
                    int b = m_prog.buttonContains(m_mouse,1);
                    if( b != -1 ) {
                        m_instruction = new Button(m_prog.m_proc1_buttons[b]->getFile());
                        m_instruction->setPosition( {m_mouse.x-m_instruction->getSize().x/2,
                                                     m_mouse.y-m_instruction->getSize().y/2});
                        m_instruction->setScale(1.2,1.2);
                        m_prog.deleteInstruction(m_prog.m_proc1_buttons[b],1);
                        m_prog.positionCalculationProc1(b);
                    }
                }
                else if(m_selected_button == 12) {
                    int b = m_prog.buttonContains(m_mouse,2);
                    if( b != -1 ) {
                        m_instruction = new Button(m_prog.m_proc2_buttons[b]->getFile());
                        m_instruction->setPosition( {m_mouse.x-m_instruction->getSize().x/2,
                                                     m_mouse.y-m_instruction->getSize().y/2});
                        m_instruction->setScale(1.2,1.2);
                        m_prog.deleteInstruction(m_prog.m_proc2_buttons[b],2);
                        m_prog.positionCalculationProc2(b);
                    }
                }
                else if(m_selected_button == 13) {
                    if (m_from_editor) {
                        m_selected_window = 7;
                    }
                }
                else if(m_selected_button == 6) {
                    if (m_prog.position() != m_prog.max_prog_size())
                        m_prog.reset_position();
                    for (int i = 0; i < m_prog.max_prog_size(); i++)
                    {
                        animation();
                        m_prog.next(m_grid,m_robot);
                    }
                    if (m_grid.end()) {
                        m_level_end = true;
                    } else {
                        m_incomplete_end = true;
                        m_game.addButtonReset();
                    }

                    m_prog.reset_position();
                }
                else if (m_selected_button == 7) {
                    if (m_prog.position() != m_prog.max_prog_size()) {
                        animation();
                        m_prog.next(m_grid,m_robot);
                    }
                    if (m_prog.position() == m_prog.max_prog_size()) {
                        m_prog.reset_position();
                        if (m_grid.end()) {
                            m_level_end = true;
                        } else {
                            m_incomplete_end = true;
                            m_game.addButtonReset();
                        }
                    }
                }
            }
        } else m_selected_button = m_end_menu.buttonContains(m_mouse);
        if(m_selected_button == 0 && m_level_end) {
            if (m_from_editor) {
                m_grid.load(-1,true);
                m_grid.save(m_select_level.levelNumber(0)+1);
            }
            m_prog.clearPrograms();
            m_robot->setPosition(m_grid.position(),m_grid);
            m_robot->setDirection(m_grid.direction());
            m_selected_window = 5;
            m_from_editor = false;
            m_level_end = false;
        }
        else if(m_selected_button == 1 && m_level_end) {
            m_prog.clearPrograms();
            if (m_from_editor) {
                m_grid.load(-1,true);
            } else {
                m_grid.load(m_selected_level,m_level_type);
            }
            m_robot->init(m_grid,m_grid.position(),m_grid.direction());
            m_robot->scaleRadius(m_grid);
            m_level_end = false;
        }
        else if(m_selected_button == 2 && m_level_end) {
            if (!m_from_editor) {
                m_prog.clearPrograms();
                m_selected_level++;
                m_grid.load(m_selected_level, m_level_type);
                m_robot->init(m_grid,m_grid.position(),m_grid.direction());
                m_robot->scaleRadius(m_grid);
                m_level_end = false;
            } else {
                m_selected_window = 7;
                m_grid.load(-1,false);
                m_robot->setPosition(m_grid.position(),m_grid);
                m_robot->setDirection(m_grid.direction());
            }
        }
        m_selected_button = -1;

        break;
    default:
        break;
    }
}

void Appli::mouseReleased()
{
    m_insertionRect.setFillColor(sf::Color::Transparent);
    switch (m_selected_window)
    {
    case 2:
        if(m_selected_button == 5) {
            m_selected_button = -1;
        }
        break;
    case 5:
        if( m_selected_button != -1) {
            m_menu.buttonSwitch(m_selected_button);
            if (m_selected_button == 0)
                m_selected_window = 6;
            else if (m_selected_button == 1)
                m_appli_running = false;
            else if(m_selected_button == 2)
                m_selected_window = 2;
            else if (m_selected_button == 3) {
                m_selected_window = 7;
                m_grid.load(-1,false);
                m_robot->init(m_grid,m_grid.position(),m_grid.direction());
            }
        }
        break;
    case 0:
        if( m_instruction != nullptr) {
            if(m_game.buttonContains(m_mouse) == 10) {
                int insertpos = m_prog.insertPos(m_mouse,0);
                if(insertpos == -1)
                    m_prog.addInstruction(m_instruction->getFile(),0,-1);
                else m_prog.addInstruction(m_instruction->getFile(),0,insertpos);
            }
            if(m_game.buttonContains(m_mouse) == 11) {
                int insertpos = m_prog.insertPos(m_mouse,1);
                if(insertpos == -1)
                    m_prog.addInstruction(m_instruction->getFile(),1,-1);
                else m_prog.addInstruction(m_instruction->getFile(),1,insertpos);
            }
            if(m_game.buttonContains(m_mouse) == 12) {
                int insertpos = m_prog.insertPos(m_mouse,2);
                if(insertpos == -1)
                    m_prog.addInstruction(m_instruction->getFile(),2,-1);
                else m_prog.addInstruction(m_instruction->getFile(),2,insertpos);
            }
            delete m_instruction;
            m_instruction = nullptr;
        }
        break;
    default:
        break;
    }
}

void Appli::mouseMoved() {
    switch (m_selected_window) {
    case 0:
        if( m_instruction != nullptr ) {
            m_instruction->setPosition( {m_mouse.x-m_instruction->getSize().x/2, m_mouse.y-m_instruction->getSize().y/2});
            m_selected_button = m_game.buttonContains(m_mouse);
            if(m_selected_button == 10
                    ) {
                int insertpos = m_prog.insertPos(m_mouse,0);
                if (insertpos != -1) {
                    m_insertionRect.setFillColor(sf::Color::White);
                    m_insertionRect.setPosition({ m_prog.m_main_buttons[insertpos]->getPosition().x - INSTRUCTION_MARGIN_X/2 - m_insertionRect.getSize().x/2,
                                                  m_prog.m_main_buttons[insertpos]->getPosition().y - 5}); }
                else
                    m_insertionRect.setFillColor(sf::Color::Transparent);
            } else if(m_selected_button == 11) {
                int insertpos = m_prog.insertPos(m_mouse,1);
                if (insertpos != -1) {
                    m_insertionRect.setFillColor(sf::Color::White);
                    m_insertionRect.setPosition({ m_prog.m_proc1_buttons[insertpos]->getPosition().x - INSTRUCTION_MARGIN_X/2 - m_insertionRect.getSize().x/2,
                                                  m_prog.m_proc1_buttons[insertpos]->getPosition().y - 5}); }
                else
                    m_insertionRect.setFillColor(sf::Color::Transparent); }
            else if(m_selected_button == 12) {
                int insertpos = m_prog.insertPos(m_mouse,2);
                if (insertpos != -1) {
                    m_insertionRect.setFillColor(sf::Color::White);
                    m_insertionRect.setPosition({ m_prog.m_proc2_buttons[insertpos]->getPosition().x - INSTRUCTION_MARGIN_X/2 - m_insertionRect.getSize().x/2 ,
                                                  m_prog.m_proc2_buttons[insertpos]->getPosition().y - 5}); }
                else
                    m_insertionRect.setFillColor(sf::Color::Transparent);
            }
        }
        break;
    case 2:
        if(m_selected_button == 5) {
            m_setting.setCursor(m_mouse.x);
            int lum = m_setting.getCursorValue();
            if(lum >= 0)
                m_luminosity.setFillColor(sf::Color(255,255,255,lum));
            else
                m_luminosity.setFillColor(sf::Color(0,0,0,-lum));
        }
        break;
    }
}

void Appli::run()
{
    m_window.create(sf::VideoMode {WINDOW_WIDHT,WINDOW_HEIGHT,32},
                    "Lightbot",
                    sf::Style::Close
                    );

    m_window.setFramerateLimit(60);

    m_appli_running = true;
    while (m_appli_running) {
        process_events();
        draw();
    }
}

void Appli::process_events()
{
    sf::Event event;
    while ( m_window.pollEvent(event) ) {
        switch (event.type) {
        case sf::Event::Closed :
            m_appli_running = false;
            break;
        case  sf::Event::KeyPressed :
            keyPressed(event.key.code);
            break;
        case sf::Event::MouseButtonPressed :
            m_button = event.mouseButton.button;
            mousePressed();
            break;
        case sf::Event::MouseButtonReleased :
            m_button = event.mouseButton.button;
            mouseReleased();
            break;
        case sf::Event::MouseMoved :
            m_mouse = m_window.mapPixelToCoords( {event.mouseMove.x,
                                                  event.mouseMove.y });
            mouseMoved();
            break;
        default:
            break;
        }
    }
}
