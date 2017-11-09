#ifndef MENUEND_H
#define MENUEND_H

#include "Menu.h"

class MenuEnd : public Menu
{
public:
    void init();    // initialisation of menu values and attibutes

    void switchButtonEditor();  // switch finished level menu for editor purposes
    void switchButtonBack();    // switch finished level menu for game purposes
};

#endif // MENUEND_H
