#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <fstream>
#include <iostream>

const sf::Vector2f RECT_SIZE = {841,617};   // size of grid container
const sf::Vector2f RECT_POS = {22,22};      // position of grid container
const int MARGIN = 100;                     // margin of haxegon grid

class Grid
{
public:
    // Getters
    int                 width()                             const;
    int                 height()                            const;
    int                 direction()                         const;
    float               getRadius()                         const;
    std::vector<int>    grid()                              const;
    sf::Vector2f        position()                          const;
    sf::CircleShape     getCase(const sf::Vector2f &pos)    const;

    // Setters
    void setDirection(int direction);
    void setPosition(sf::Vector2f position);

    float adaptatedRadius() const;  // calculate optimized radius

    void setHexaPlus(const sf::Vector2f &hexa);     // change the type of the haxagon
    void changeColor(const int &nb);                // change the color of a case
    void lightUpCase( const sf::Vector2f &pos);     // light up a case
    void clear();                                   // clear grid

    // Contains and tests functions
    bool contains(const sf::Vector2f &pos)  const;  // test if vector position is in grid
    bool isInGrid(const sf::Vector2f &pos)  const;  //
    bool isPossible();                              //
    bool end()                              const;  //

    sf::Vector2f pos_to_vect(const sf::Vector2f &vect)   const;  // convert x,y position to vector position
    sf::Vector2f vect_to_pos(const int &nb)             const;  // convert vector position to x,y position

    void load(const int &numNiveau, const bool &created);       // load from file
    void load(const std::vector<int> &grid, const int &action); // load from variables
    void save(int numNiveau);                                   // save as file

    void drawto(sf::RenderWindow &window);
private:
    int     m_height;   // number of lines
    int     m_width;    // number of columns
    double  m_radius;   // radius of hexagons

    int             m_direction;    // robot direction
    sf::Vector2f    m_position;     // robot position

    sf::CircleShape                 m_hexa;     // template hexagon
    std::vector<int>                m_grid;     // grid of values
    std::vector<sf::CircleShape>    m_hexas;    // grid of haxagons
};

#endif // GRID_H
