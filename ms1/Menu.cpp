/***********************************************************************
// OOP244 Project
//
// File  Utils.h
// Author  Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name                 Date            Reason
***********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <sstream>
#include "Menu.h"


namespace seneca {

    Menu::Menu(const char* menuContent, int numberOfTabs)
        : m_text(nullptr), m_numOptions(0), m_numTabs(numberOfTabs) {

        copyText(menuContent);

        const char* ptr = m_text;
        while (*ptr) {
            if (*ptr == '\n')
                ++m_numOptions;
            ++ptr;
        }
    }

    Menu::~Menu() {
        deallocateMemory();
    }

    void Menu::copyText(const char* text) {
        if (text) {
            m_text = new char[strlen(text) + 1];
            strcpy(m_text, text);
        }
        else {
            m_text = nullptr;
        }
    }


    void Menu::deallocateMemory() {
        delete[] m_text;
    }

    void Menu::display() const {
        std::istringstream iss(m_text);
        std::string line;
        while (std::getline(iss, line)) {
            for (int i = 0; i < m_numTabs; ++i)
                std::cout << "   ";
            std::cout << line << std::endl;
        }
        // Print the exit option
        for (int i = 0; i < m_numTabs; ++i)
            std::cout << "   ";
        std::cout << "0- Exit\n> ";

    }
    void Menu::displaySubMenu() const {
        // Print the submenu header

        // Print submenu content with indentation
        std::istringstream iss(m_text);
        std::string line;
        while (std::getline(iss, line)) {
            std::cout << "   "; // Add four spaces for submenu indentation
            std::cout << line << std::endl;
        }

        // Print the exit option with aligned input prompt
        std::cout << "   0- Exit\n";
        std::cout << "   > "; // No need for additional spaces before the input prompt
    }

    int& Menu::operator>>(int& selection) {
        if (m_numTabs > 0) {
            // If it's a submenu, use displaySubMenu() to show the menu
            displaySubMenu();
        }
        else {
            // Otherwise, use display() to show the menu
            display();
        }

        while (true) {
            std::cin >> selection;

            // Check if the input stream is empty after reading the integer
            if (std::cin.peek() != EOF && std::cin.peek() != '\n') {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "Only enter an integer, try again: ";
            }
            else if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "Bad integer value, try again: ";
            }
            else if (selection < 0 || selection > m_numOptions) {
                std::cout << "Invalid value enterd, retry[0 <= value <= " << m_numOptions << "]: ";
            }
            else {
                break;
            }
        }
        return selection;
    }
}
