#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <SFML/Graphics.hpp>

const int INSTRUCTION_SIZE = 40;

class Button
{
public:
    // Contructors
    Button(const std::string &file);
    Button(const int &x, const int &y, const int &w, const int &h); // button without texture
    Button(const int &x, const int &y, const std::string &file);
    Button(const int &x, const int &y, const std::string &file, const  float &scale);
    Button(const int &x, const int &y, const std::string &file, const std::string &text, const int &type); // button with text in center
    Button(const int &x, const int &y, const std::string &file, const float &scale, const int &type);

    // Contains funtions
    bool contains(const sf::Vector2f &vect)         const;  // main contains
    bool containsMenu(const sf::Vector2f &vect)     const;  // special contains for menu buttons
    bool containsCircle(const sf::Vector2f &vect)   const;  // contains for circle buttons
    bool containsHexa(const sf::Vector2f &vect)     const;  // contains for hexagonal buttons

    // Texture changes functions
    void changeTexture(const int &nb);  //
    void switchMainButton();            // switch main buttons texture

    // Getters
    int             getType()       const;
    sf::Vector2i    getSize()       const;
    std::string     getFile()       const;
    sf::Vector2f    getPosition()   const;

    // Setters
    void setRotation(const int &r);
    void setScale(const float &x, const float &y);
    void setPosition(const sf::Vector2f &pos);

    void draw_to(sf::RenderWindow &window);

private:
    bool m_with_text = 0;   // true = button with a text

    int m_type = 0;         // 0 = square/rectangle, 1 = circle, 2 = hexagon

    sf::Font    m_font;     // font of the text
    std::string m_fileName; // file name of the texture
    sf::Texture m_image;    // texture of the button
    sf::Sprite  m_sprite;   // button
    sf::Text    m_text;     // text of the button
};

#endif // BUTTON_H
