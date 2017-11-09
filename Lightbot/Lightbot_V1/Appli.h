#ifndef APPLI_H
#define APPLI_H

#include "Button.h"
#include <array>
#include <time.h>
#include "Robot.h"
#include "Program.h"
#include "MenuSelect.h"
#include "MenuMain.h"
#include "MenuGame.h"
#include "MenuEditor.h"
#include "MenuEnd.h"
#include "MenuSetting.h"

const int WINDOW_WIDHT = 1280;  // width of the windown application (in pixels)
const int WINDOW_HEIGHT = 720;  // height of the windown application (in pixels)

class Appli
{
public:
    // Constructor
    Appli();
    // Destructor
    ~Appli();
    // Function
    void run();

private:
    // Variables
    bool m_level_type = 1;          // 1 = official, 2 = created
    bool m_level_end = false;       // true = level finished
    bool m_incomplete_end = false;  // true = level failed
    bool m_from_editor = false;     // true = testing mode
    bool m_appli_running;           // true = application is working/openned

    int             m_selected_window;      // number of the actual window : 0 = game, 2 = settings, 5 = main menu, 6 = selection menu, 7 = editor
    int             m_selected_button;      // number of the selected button
    int             m_selected_level;       // number of the selected level
    unsigned int    m_current_page = 0;     // number of the current page


    MenuEditor  m_editor;       // editor
    MenuMain    m_menu;         // main menu
    MenuGame    m_game;         // game
    MenuSelect  m_select_level; // selection menu
    MenuEnd     m_end_menu;     // finished level menu
    MenuSetting m_setting;      // settings

    Button*     m_instruction = nullptr;    // texture of the selected instruction
    Grid        m_grid;                     // game grid
    Robot*      m_robot;                    // game robot
    Program     m_prog;                     // game program

    sf::RectangleShape  m_luminosity;       // luminosity Shape
    sf::RectangleShape  m_insertionRect;    // indication of insertion position

    sf::RenderWindow    m_window;           // application window

    sf::Vector2f        m_mouse;            // mouse position
    sf::Mouse::Button   m_button;           // selected button

    //Functions
    void animation();   // animations draw
    void draw();        // draw

    void keyPressed(sf::Keyboard::Key code);
    void mousePressed();
    void mouseReleased();
    void mouseMoved();

    void process_events();
};

#endif // APPLI_H
