#ifndef SENECA_MENU_H
#define SENECA_MENU_H

namespace seneca {

    class Menu {
        char* m_text;
        int m_numOptions;
        int m_numTabs;

        void copyText(const char* text);
        void deallocateMemory();

    public:
        Menu(const char* menuContent, int numberOfTabs = 0);
        ~Menu();

        Menu(const Menu& other) = delete;
        Menu& operator=(const Menu& other) = delete;

        void display() const;
        void displaySubMenu() const; // New function for displaying sub-menu

        int& operator>>(int& selection);
    };

}

#endif 
