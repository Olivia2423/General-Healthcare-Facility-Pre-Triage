// PreTriage.h

#ifndef SENECA_PRETRIAGE_H
#define SENECA_PRETRIAGE_H

#include <fstream>
#include "Patient.h"
#include "Menu.h"
#include "Utils.h"

using namespace std;

namespace seneca {

    const int maxNoOfPatients = 100;
    class PreTriage {
        Time
            m_averContagionWait,
            m_averTriageWait;
        Patient* m_lineup[maxNoOfPatients]{};
        char* m_dataFilename = nullptr;
        int m_lineupSize = 0;
        Menu
            m_appMenu,
            m_pMenu;
        void reg();
        void admit();
        const Time getWaitTime(const Patient& p) const;
        void setAverageWaitTime(const Patient& p);
        int indexOfFirstInLine(char type) const;
        void removePatientFromLineup(int index);
        void load();
        void save() const;
        void deallocate();
        void loadPatients();
    public:
        void viewLineup();
        PreTriage(const char* dataFilename);
        ~PreTriage();
        void run(void);
        void printEmptyFileContent(ifstream& file) const;
  

    };
}
#endif // !PRETRIAGE_H
