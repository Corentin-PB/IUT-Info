#ifndef MENUGAME_H
#define MENUGAME_H

#include "Menu.h"

class MenuGame : public Menu
{
public:
    void init();    // initialisation of menu values and attibutes

    void addButtonReset();      // add a reset button
    void deleteButtonReset();   // delete reset button
    void switchButtonEditor();  // switch game buttons for editor purposes
    void switchButtonBack();    // switch buttons for game purposes
};

#endif // MENUGAME_H
