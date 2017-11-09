#ifndef ROBOT_H
#define ROBOT_H

#include <SFML/Graphics.hpp>
#include "Grid.h"
#include <math.h>

class Robot
{
private:
    int             m_direction = 0;    // robot direction

    sf::Vector2f    m_position;         // robot position
    sf::Texture     m_image;            // robot texture
    sf::Sprite      m_sprite;           // robot
    std::string     m_filename = "";    // robot file name
public:
    void init(const Grid &grid, sf::Vector2f pos, int direction);   // initialisation of robot values and attributes (can be used as a reset function)

    // Getters
    int             getDirection()  const;
    sf::Vector2f    getPosition()   const;

    // Setters
    void setDirection(const int &dir);
    void setPosition(const sf::Vector2f &pos, Grid grid);

    bool contains(const sf::Vector2f &pos);         // verify if position is one the robot

    void rotate(const bool &direction);             // turn the robot
    void forward(const float &r);                   // move the robot forward

    void scaleRadius(const Grid &grid);             // update the radius of the robot
    void setTexture(const std::string& filename);   // change the texture of the robot (skin)

    void draw_to(sf::RenderWindow &window);
};

#endif // ROBOT_H
