#ifndef MENUSELECT_H
#define MENUSELECT_H

#include "Menu.h"

class MenuSelect : public Menu
{
public:
    void init(const bool &created, const int &page);    // initialisation of menu values and attibutes depending on page number and level type

    unsigned int levelNumber(const bool &created) const;    // get the number of level with the specified type
};

#endif // MENUSELECT_H
