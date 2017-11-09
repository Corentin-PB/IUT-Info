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

#include "MenuSelect.h"

void MenuSelect::init(const bool &created, const int &page) {
    unsigned int first_level = page*10;
    this->add_image("images/levelSelect.png",0,0);
    m_buttons.clear();
    Button* b = new Button(689,50,"images/mainMenu.png");
    m_buttons.push_back(b);
    b = new Button(878,50,"images/createdLevels.png");
    m_buttons.push_back(b);
    b = new Button(1052,50,"images/officialLevels.png");
    m_buttons.push_back(b);

    unsigned int nb = levelNumber(created);

    if(nb > 10) {
        b = new Button(101,592,"images/nextPageLeft.png");
        m_buttons.push_back(b);
        b = new Button(1119,592,"images/nextPageRight.png");
        m_buttons.push_back(b);
    }

    unsigned int i = first_level;
    while(i<nb && i<=first_level+9) {
        b = new Button(87 + 55 + ((int)i%10%5)*(122+98),
                        168 + 56 + ((int)i%10/5)*(140+56),
                        "images/level.png",std::to_string(i+1),2);
        m_buttons.push_back(b);
        i++;
    }
}

unsigned int MenuSelect::levelNumber(const bool &created) const {
    DIR * dirp;
    struct dirent * entry;
    unsigned int nb = 0;
    if(created)
        dirp = opendir("levels/official/");
    else
        dirp = opendir("levels/created/");
    while ((entry = readdir(dirp)) != NULL) {
        if (entry->d_type == DT_REG) // DEBIAN
//        if (!(!strcmp(entry->d_name,".") || !strcmp(entry->d_name,"..") )) // WINDOWS
            nb++;
    }
    closedir(dirp);
    return nb;
}
