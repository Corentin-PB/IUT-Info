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

#include "Robot.h"

void Robot::init(const Grid &grid,sf::Vector2f pos, int direction)
{
    m_position = pos;
    m_direction = direction;
    if( m_filename == "")
        m_image.loadFromFile("images/robotHD.png");
    else m_image.loadFromFile(m_filename);
    m_image.setSmooth(1);
    m_sprite.setTexture(m_image);
    setPosition(pos,grid);
    m_sprite.setOrigin({m_sprite.getLocalBounds().width/2,m_sprite.getLocalBounds().height/2});
    m_sprite.setScale(grid.getRadius()/m_sprite.getTextureRect().width ,grid.getRadius()/m_sprite.getTextureRect().height );
    setDirection(direction);
}

int Robot::getDirection() const {
    return m_direction;
}

sf::Vector2f Robot::getPosition() const {
    return m_position;
}

void Robot::setDirection(const int &dir) {
    m_direction = dir;
    m_sprite.setRotation(60*dir);
}

void Robot::setPosition(const sf::Vector2f &pos, Grid grid) {
    m_position = pos;
    m_sprite.setPosition({ (float)grid.getCase(m_position).getPosition().x
                           , (float)grid.getCase(m_position).getPosition().y });
}

bool Robot::contains(const sf::Vector2f &pos) {
    if(m_filename.find("2") != std::string::npos || m_filename.find("3") != std::string::npos)
        return m_sprite.getGlobalBounds().contains(pos);
    else
        return (m_sprite.getGlobalBounds().width/2 >= sqrt( pow( ( (m_sprite.getPosition().x) - pos.x) , 2)
                                                           + pow( ( (m_sprite.getPosition().y) - pos.y) , 2) ));
}

void Robot::rotate(const bool &direction) {
    if (!direction)
        m_sprite.setRotation(m_sprite.getRotation()-2);
    else if (direction)
        m_sprite.setRotation(m_sprite.getRotation()+2);
}

void Robot::forward(const float &r) {
    float x = m_sprite.getPosition().x;
    float y = m_sprite.getPosition().y;
    switch(m_direction) {
    case 0:
        m_sprite.setPosition(x, y - 2*(r*sin(M_PI/3))/30);
        break;
    case 1:
        m_sprite.setPosition(x + (r+r*cos(M_PI/3))/30
                             ,y - (r*sin(M_PI/3))/30);
        break;
    case 2:
        m_sprite.setPosition(x + (r+r*cos(M_PI/3))/30
                             ,y + (r*sin(M_PI/3))/30);
        break;
    case 3:
        m_sprite.setPosition(x, y + 2*(r*sin(M_PI/3))/30);
        break;
    case 4:
        m_sprite.setPosition(x - (r+r*cos(M_PI/3))/30
                             ,y + (r*sin(M_PI/3))/30);
        break;
    case 5:
        m_sprite.setPosition(x - (r+r*cos(M_PI/3))/30
                             ,y - (r*sin(M_PI/3))/30);
        break;
    default:
        break;
    }
}

void Robot::scaleRadius(const Grid &grid) {
    m_sprite.setScale(grid.getRadius()/m_sprite.getTextureRect().width
                       ,grid.getRadius()/m_sprite.getTextureRect().width);
    m_sprite.setPosition({ (float)grid.getCase(m_position).getPosition().x
                         , (float)grid.getCase(m_position).getPosition().y });
}

void Robot::setTexture(const std::string &filename) {
    m_filename = filename;
}

void Robot::draw_to(sf::RenderWindow &window) {
    window.draw(m_sprite);
}
