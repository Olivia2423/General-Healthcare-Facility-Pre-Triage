#define _CRT_SECURE_NO_WARNINGS

#include "Menu.h"

namespace seneca {

    Menu::Menu() {
        // Default constructor initializes an empty menu
        m_title = "";
    }


    Menu::Menu(const std::string& title, int optionsCount) : m_title(title) {
        m_options.reserve(optionsCount);
    }

    void Menu::addOption(const std::string& option) {
        m_options.push_back(option);
    }

    Menu::~Menu() {
        // No dynamic memory to deallocate explicitly, so no action required
    }

    bool Menu::operator>>(int& selection) const {
        std::cout << m_title << std::endl;
        for (size_t i = 0; i < m_options.size(); ++i) {
            std::cout << i + 1 << ". " << m_options[i] << std::endl;
        }
        std::cout << "> ";
        std::cin >> selection;
        return !!std::cin; // Return true if input was successful, false otherwise
    }

}
