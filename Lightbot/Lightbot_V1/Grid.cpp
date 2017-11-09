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

#include "Grid.h"

int Grid::width() const {
    return m_width;
}

int Grid::height() const {
    return m_height;
}

int Grid::direction() const {
    return m_direction;
}

float Grid::getRadius() const {
    return m_radius;
}

std::vector<int> Grid::grid() const {
    return m_grid;
}

sf::Vector2f Grid::position() const {
    return m_position;
}

sf::CircleShape Grid::getCase(const sf::Vector2f &pos) const {
    return m_hexas[pos.y*m_width+pos.x];
}

void Grid::setDirection(int direction) {
    m_direction = direction;
}

void Grid::setPosition(sf::Vector2f position) {
    m_position = position;
}

float Grid::adaptatedRadius() const {
    int x = RECT_SIZE.x-RECT_POS.x;
    int y = RECT_SIZE.y-RECT_POS.y;
    float radius_number;
    if(m_width%2 == 0)
        radius_number = 1.0*m_width/2*3+0.25;
    else radius_number = 1.0*m_width/2*3+2;
    if( ((1.0*x-MARGIN)/radius_number) > ((1.0*y-MARGIN)/m_height/2*cos(M_PI/6)) )
        return ((1.0*y-MARGIN)/m_height/2*cos(M_PI/6));
    else return ((1.0*x-MARGIN)/radius_number);
}

void Grid::setHexaPlus(const sf::Vector2f &hexa) {
    int temp = (hexa.y*m_width)+hexa.x;
    if (m_grid.at(temp)!= 3)
        m_grid.at(temp) += 1;
    else {
        m_grid.at(temp) = 0;
    }
    changeColor(temp);
}

void Grid::changeColor(const int &nb) {
    if (m_grid[nb] == 0) {
        m_hexas[nb].setFillColor(sf::Color::Transparent);
        m_hexas[nb].setOutlineColor(sf::Color::Transparent);
    } else {
        if (m_grid[nb] == 1)
            m_hexas[nb].setFillColor(sf::Color(23, 23, 22));
        else if (m_grid[nb] == 2)
            m_hexas[nb].setFillColor(sf::Color(115, 159, 255));
        else if (m_grid[nb] == 3)
            m_hexas[nb].setFillColor(sf::Color(35, 29, 135));
        m_hexas[nb].setOutlineColor(sf::Color(0, 68, 226));
    }
}

void Grid::lightUpCase(const sf::Vector2f &pos) {
    if(m_grid[pos.y*m_width+pos.x] == 3) {
        m_hexas.at(pos.y*m_width+pos.x).setFillColor(sf::Color(115, 159, 255));
        m_grid[pos.y*m_width+pos.x] = 2;
    }
}

void Grid::clear() {
    m_grid.clear();
    m_hexas.clear();
}

bool Grid::contains(const sf::Vector2f &pos) const {
    return (pos.x >= 0 && pos.x <= m_height-1 && pos.y >= 0 && pos.y <= m_width-1);
}

bool Grid::isInGrid(const sf::Vector2f &pos) const {
    return (pos.x >= 0 && pos.x <= m_width-1 && pos.y >= 0 && pos.y <= m_height-1 && m_grid.at(pos.y*m_width+pos.x) != 0);
    return 0;
}

bool Grid::isPossible() {
    bool found = false;
    for (auto h : m_grid) {
        if (h == 3)
            found = true;
    }
    return found;
}

bool Grid::end() const {
    int i = 0;
    bool found = true;
    while( i < m_grid.size() && found ) {
        if (m_grid[i] == 3)
            found = false;
        else i++;
    }
    return found;
}

sf::Vector2f Grid::pos_to_vect(const sf::Vector2f & vect) const {

    float X = vect.x - (m_hexas[0].getPosition().x - m_radius) - m_radius;

    float Y = vect.y - (m_hexas[0].getPosition().y - m_radius) - m_radius;

    // Conversion en coordonnées cubiques
    float x = X * (2. / 3.) / m_radius;

    float z = ((-X / 3.) + sqrt(3.)/3. * Y ) / m_radius;

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

    return {rx,rz};
}

sf::Vector2f Grid::vect_to_pos(const int &nb) const {
    return {    RECT_POS.x+MARGIN/2+float(m_radius) + 1.5*(nb%m_width)*m_radius
                ,RECT_POS.y+MARGIN/2+float(m_radius) + (nb/m_width)*2*m_radius*cos(M_PI/6) + ((nb%m_width)%2)*m_radius*cos(M_PI/6) };
}

void Grid::load(const int &numNiveau, const bool &created) {
    std::fstream f;
    m_grid.clear();
    m_hexas.clear();
    if(created)
        if (numNiveau == -1)
            f.open( ("levels/temp.txt"), std::ios::in );
        else
            f.open( ( "levels/official/" + std::to_string(numNiveau) + ".txt" ).c_str(), std::ios::in );
    else {
        if (numNiveau == -1) {
            f.open( ( "levels/blancEditor.txt" ), std::ios::in );
        }
        else
            f.open( ( "levels/created/" + std::to_string(numNiveau) + ".txt" ).c_str(), std::ios::in );
    }
    if( f.fail() )
    {
        std::cerr << "ouverture en lecture impossible" << std::endl;
        exit(EXIT_FAILURE);
    }
    f >> m_position.x;
    f >> m_position.y;
    f >> m_direction;
    f >> m_width;
    f >> m_height;

    for(int i = 0; i<(m_height*m_width); i++) {
        int temp;
        f >> temp;
        m_grid.push_back(temp);
    }
    f.close();

    m_radius = adaptatedRadius();

    m_hexa.setOutlineThickness(2);
    m_hexa.setRadius(m_radius);
    m_hexa.setOrigin({float(m_radius),float(m_radius)});
    m_hexa.setPointCount(6);
    m_hexa.setRotation(90);
    m_hexa.setScale(1,1);

    for(int i = 0; i<(m_height*m_width); i++) {
        m_hexa.setPosition(vect_to_pos(i));
        m_hexas.push_back(m_hexa);
        changeColor(i);
    }
}

void Grid::load(const std::vector<int> &grid, const int &action) {
    m_grid.clear();
    m_hexas.clear();

    // action : 0 = addLine / 1 = deleteLine / 2 = addRow / 3 = deleteRow
    switch (action) {
    case 0:
        m_height++;
        break;
    case 1:
        if (m_height != 1)
            m_height--;
        break;
    case 2:
        m_width++;
        break;
    case 3:
        if (m_width != 1)
            m_width--;
        break;
    }

    for(int i = 0; i<(m_height*m_width); i++) {
        int temp;
        if (i < grid.size() && !(action == 2 && i%m_width <= m_width-1 )) {
            temp = grid[i];
            m_grid.push_back(temp);
        } else {
            m_grid.push_back(1);
        }
    }

    m_radius = adaptatedRadius();

    m_hexa.setOutlineThickness(2);
    m_hexa.setRadius(m_radius);
    m_hexa.setOrigin({float(m_radius),float(m_radius)});
    m_hexa.setPointCount(6);
    m_hexa.setRotation(90);
    m_hexa.setScale(1,1);

    for(int i = 0; i<(m_height*m_width); i++) {
        m_hexa.setPosition(vect_to_pos(i));
        m_hexas.push_back(m_hexa);
        changeColor(i);
    }
}

void Grid::save(int numNiveau) {
    std::string filename;
    if (numNiveau == -1) {
        filename = "levels/temp.txt";
    }
    else {
        filename += "levels/created/";
        filename += std::to_string(numNiveau);
        filename += ".txt";
    }
    std::ofstream f;
    f.open( ( filename ), std::ios::out );
    f << m_position.x;
    f << "\n";
    f << m_position.y;
    f << "\n";
    f << m_direction;
    f << "\n";
    f << m_width;
    f << "\n";
    f << m_height;

    for (auto h : m_grid) {
        f << "\n";
        f << h;
    }
    f.close();
}

void Grid::drawto(sf::RenderWindow &window) {
    for(auto a : m_hexas)
        window.draw(a);
}
