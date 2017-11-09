#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <vector>
#include "Grid.h"
#include "Robot.h"
#include "Button.h"
#include "Menu.h"

const int MAX_MAIN = 24;            //  max instructions in the "main" box
const int MAX_PROC = 12;            // max instructions in the proc1/2 box
const int INSTRUCTION_MARGIN_X = 25;     // x margin of a instruction button
const int INSTRUCTION_MARGIN_Y = 15;     // y margin of a instruction button

class Program
{
private:
    bool        m_used = false;         // boolean used so that the user can't make infinite loop (exemple : P1 in P2 and P2 in P1)

    int         m_currentPosition= 0;   // current position in the program
    std::string m_prog_string;          // string of all the instruction whom are inside the instructions boxes (F = forward, L = Left, R = Right, I = light)

    void action(Grid &grid, Robot *robot);                      // function that change the direction or the position of the robot
    void vecToProg(std::string &prog, std::vector<int> vec);    // function that check the instructions box and create a string of all the program in the right order with letters (see before for the letters code)
public:
    //Destructor
    ~Program();

    std::vector<int>        m_main;             // contains all the type of instructions of the main box with int
    std::vector<int>        m_proc1;            // contains all the type of instructions of the P1 box with int
    std::vector<int>        m_proc2;            // contains all the type of instructions of the P2 box with int

    std::vector<Button*>    m_main_buttons;     // contains all the Buttons instructions of the main box
    std::vector<Button*>    m_proc1_buttons;    // contains all the Buttons instructions of the P1 box
    std::vector<Button*>    m_proc2_buttons;    // contains all the Buttons instructions of the P2 box

    int         max_prog_size() const;  // return the size of the current program
    int         position()      const;  // return the current position of the program
    std::string prog_string()   const;  // return the string program

    void reset_prog();      // delete all the instrctions of the program
    void reset_position();  // reset the current position to 0 (default)

    int buttonContains(const sf::Vector2f &mouse, const int &nb) const;     // check for the position in parameters if it's inside a button of the box (nb equals the number of the box -> 0 = main, 1 = P1 and 2 = P2)

    void            next(Grid &grid, Robot *robot);             // execute the action of the next instruction
    sf::Vector2f    nextPosForward(const Robot *robot) const;   // return the position of the case forward in function of the direction of the robot

    int     buttonTypeCalculation(const std::string &filename); // check the filename of a button and transform it to a int (check the function the int that correspond to an instruction)
    void    positionCalculationMain(const int &nb);             // calculate the position where the next instruction should be placed in the main box
    void    positionCalculationProc1(const int &nb);            // calculate the position where the next instruction should be placed in the P1 box
    void    positionCalculationProc2(const int &nb);            // calculate the position where the next instruction should be placed in the P2 box

    int     insertPos(const sf::Vector2f &mouse, const int &nb) const;                  // function that return the number where the instruction can be placed in function of the mouse pointer
    void    addInstruction(const std::string &filename, const int &nb, const int &pos); // add the selected instruction in the program
    void    deleteInstruction(const Button *b, const int &nb);                          // delete the selected instruction in the program
    void    clearPrograms();

    void draw_to(sf::RenderWindow &win);
};

#endif // PROGRAM_H
