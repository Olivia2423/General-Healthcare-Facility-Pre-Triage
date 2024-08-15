#ifndef SENECA_MENU_H
#define SENECA_MENU_H

#include <iostream>
#include <vector>
#include <string>

namespace seneca {

    class Menu {
        std::vector<std::string> m_options;
        std::string m_title;

    public:
        Menu();
        Menu(const std::string& title, int optionsCount);
        ~Menu();
        void addOption(const std::string& option);
        bool operator>>(int& selection) const;
    };

}

#endif // SENECA_MENU_H
