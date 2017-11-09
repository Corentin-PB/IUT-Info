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

#include "Button.h"

Button::Button(const std::string &file)
    :m_fileName{file}
{
    m_image.loadFromFile(m_fileName);
    m_sprite.setTexture(m_image);
}

Button::Button(const int &x, const int &y, const int &w, const int &h) {
    m_sprite.setTextureRect( sf::IntRect({0,0},{w,h}) );
    m_sprite.setPosition({ (float)x, (float)y});
}

Button::Button(const int &x, const int &y, const std::string &file)
    :m_fileName{file}
{
    m_image.loadFromFile(m_fileName);
    m_image.setSmooth(1);
    m_sprite.setTexture(m_image);
    m_sprite.setPosition({ (float)x, (float)y});
}

Button::Button(const int &x, const int &y, const std::string &file, const float &scale)
    :m_fileName{file}
{
    m_image.loadFromFile(m_fileName);
    m_image.setSmooth(1);
    m_sprite.setTexture(m_image);
    m_sprite.setPosition({ (float)x, (float)y});
    m_sprite.setScale(scale,scale);
}

Button::Button(const int &x, const int &y, const std::string &file, const std::string &text, const int &type)
    :m_fileName{file}, m_type{type}
{
    m_with_text = 1;
    m_image.loadFromFile(m_fileName);
    m_image.setSmooth(1);
    m_sprite.setTexture(m_image);
    m_sprite.setPosition({ (float)x, (float)y});
    m_font.loadFromFile("OpenSans-Regular.ttf");
    m_text.setString(text);
    m_text.setFont(m_font);
    m_text.setColor(sf::Color::White);
    m_text.setCharacterSize(getSize().y/2);
    m_text.setPosition({ (float)x + m_sprite.getGlobalBounds().width/2 - m_text.getGlobalBounds().width/2
                         ,(float)y + m_sprite.getGlobalBounds().height/2 - m_text.getGlobalBounds().height/2
                         + m_text.getPosition().y - m_text.getGlobalBounds().top});
}

Button::Button(const int &x, const int &y, const std::string &file, const float &scale, const int &type)
    :m_fileName{file}, m_type{type}
{
    m_image.loadFromFile(m_fileName);
    m_image.setSmooth(1);
    m_sprite.setTexture(m_image);
    m_sprite.setPosition({ (float)x, (float)y});
    m_sprite.setScale(scale,scale);
}

bool Button::contains(const sf::Vector2f &vect) const {
    if(m_type == 1)
        return containsCircle(vect);
    else if(m_type == 2)
        return containsHexa(vect);
    else
        return m_sprite.getGlobalBounds().contains(vect);
}

bool Button::containsMenu(const sf::Vector2f &vect) const {
    int width = m_sprite.getTexture()->getSize().x;
    int height = m_sprite.getTexture()->getSize().y;
    int x = m_sprite.getPosition().x;
    int y = m_sprite.getPosition().y;
    return ( (vect.x >= x+50*m_sprite.getScale().x)
            && (vect.x <= x+(width-50)*m_sprite.getScale().x)
            && (vect.y >= y+45*m_sprite.getScale().x)
            && (vect.y <= y+(height-45)*m_sprite.getScale().x));
}

bool Button::containsCircle(const sf::Vector2f &vect) const {
    return (m_sprite.getGlobalBounds().width/2 >= sqrt( pow( ( (m_sprite.getPosition().x+m_sprite.getGlobalBounds().width / 2) - vect.x) , 2)
                                                       + pow( ( (m_sprite.getPosition().y+m_sprite.getGlobalBounds().height / 2) - vect.y) , 2) ));
}

bool Button::containsHexa(const sf::Vector2f &vect) const {

    float radius = m_sprite.getGlobalBounds().height/2;

    float X = vect.x - (m_sprite.getPosition().x) - radius;

    float Y = vect.y - (m_sprite.getPosition().y) - radius;

    // Conversion en coordonnées cubiques
    float x = (X * sqrt(3)/3 - Y / 3) / radius;
    float z = Y * 2/3 / radius;

    float y = - ( x + z );

    // coordonnées cubiques arrondies
    int rx = std::round(x);
    int ry = std::round(y);
    int rz = std::round(z);

    // écarts par rapport aux arrondis
    float xd = std::abs(rx - x);
    float yd = std::abs(ry - y);
    float zd = std::abs(rz - z);

    if ( xd > yd  && xd > zd )
        rx = - ( ry + rz );       // on rectifie xd si il a le plus grand écart
    else if ( yd > zd )
        ry = - ( rx + rz);        // ou zd si plus grand écart que yd
    else
        rz = - ( rx + ry );

    //axial to offset
    rz = rz + (rx - (rx & 1)) / 2;

    return (rz == 0 && rx == 0);
}

void Button::changeTexture(const int &nb) {
    switch(nb) {
    case 0:
        m_image.loadFromFile("images/backToEditor.png");
        break;
    case 1:
        m_image.loadFromFile("images/backMenu.png");
        break;
    }
    m_sprite.setTexture(m_image);
}

void Button::switchMainButton() {
    if( m_fileName.find("Pushed") != std::string::npos) {
        m_fileName.erase(m_fileName.size()-10,10);
        m_fileName += ".png";
    }
    else {
        m_fileName.erase(m_fileName.size()-4,4);
        m_fileName += "Pushed.png";
    }
    m_image.loadFromFile(m_fileName);
    m_sprite.setTexture(m_image);
}

int Button::getType() const {
    return m_type;
}

sf::Vector2i Button::getSize() const {
    return {m_sprite.getTextureRect().width, m_sprite.getTextureRect().height};
}

std::string Button::getFile() const {
    return m_fileName;
}

sf::Vector2f Button::getPosition() const {
    return m_sprite.getPosition();
}

void Button::setRotation(const int &r) {
    m_sprite.setRotation(r);
}

void Button::setScale(const float &x, const float &y) {
    m_sprite.setScale(x,y);
}

void Button::setPosition(const sf::Vector2f &pos) {
    m_sprite.setPosition(pos);
}

void Button::draw_to(sf::RenderWindow &window) {
    window.draw(m_sprite);
    if(m_with_text)
        window.draw(m_text);
}
