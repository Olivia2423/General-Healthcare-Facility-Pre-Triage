// PreTriage.cpp

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "PreTriage.h"
#include "TriagePatient.h"
#include "TestPatient.h"

#include "Ticket.h"

using namespace std;
namespace seneca {

    PreTriage::PreTriage(const char* dataFilename) : m_averContagionWait(15), 
        m_averTriageWait(5),
        m_appMenu("General Healthcare Facility Pre-Triage Application\n1- Register\n2- Admit\n3- View Lineup\n0- Exit", 3),
        m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2) {
        m_dataFilename = new char[strlen(dataFilename) + 1];
        strcpy(m_dataFilename, dataFilename);
        load();
    }

    PreTriage::~PreTriage() {
        save();
        deallocate();
    }

  

    void PreTriage::run()
    {
        int selection;
        do
        {
            m_appMenu >> selection;
            if (selection == 1)
            {
                reg();
            }
            else if (selection == 2)
            {
                admit();
            }
        } while (selection);
    }
    //counts the number of patients with the same type as the argument. Returns the product of the count by the average wait times.
    const Time PreTriage::getWaitTime(const Patient& p) const {
        int count = 0;
        Time temp;

        for (int i = 0; i < m_lineupSize; i++) {
            if (m_lineup[i]->type() == p.type() && m_lineup[i]->number() != p.number()) {
                count++;
            }
        }

        // Calculate wait time based on the count of matching patients and average wait time
        return p.type() == 'C' ? temp = count * int(m_averContagionWait) :
            temp = count * int(m_averTriageWait);
    }



    void PreTriage::setAverageWaitTime(const Patient& p) {
        Time CT;
        CT.reset(); // Assuming reset() sets CT to the current time

        Time PTT = (Time)(p); // Assuming this converts Patient's ticket time to Time object
        Time& AWT = p.type() == 'C' ? m_averContagionWait : m_averTriageWait;

        unsigned int PTN = p.number();

        // Calculate new average wait time using the formula provided
        AWT = ((CT - PTT) + (AWT * (PTN - 1))) / PTN;
    }



  /*  void PreTriage::reg()
    {
        int selection = 0;
        if (m_lineupSize >= maxNoOfPatients)
        {
            cout << "Line up full!" << endl;
        }
        else
        {
            m_pMenu >> selection;
            if (selection == 1)
            {
                m_lineup[m_lineupSize] = new CovidPatient();
                m_lineup[m_lineupSize++]->setArrivalTime();
            }
            else if (selection == 2)
            {
                m_lineup[m_lineupSize] = new TriagePatient();
                m_lineup[m_lineupSize++]->setArrivalTime();
            }
            cout << "Please enter patient information: " << endl;
            m_lineup[m_lineupSize - 1]->fileIO(false);
            m_lineup[m_lineupSize - 1]->read(cin);
            cout << endl;

            cout << "******************************************" << endl;
            m_lineup[m_lineupSize - 1]->write(cout);
            cout << "Estimated Wait Time: ";
            cout << getWaitTime(*m_lineup[m_lineupSize - 1]) << endl;
            cout << "******************************************" << endl << endl;
        }
    }*/


    void PreTriage::reg()
    {
        int selection = 0;
        if (m_lineupSize >= maxNoOfPatients)
        {
            cout << "Line up full!" << endl;
        }
        else
        {
            m_pMenu >> selection;
            if (selection == 1)
            {
                m_lineup[m_lineupSize] = new TestPatient();
                m_lineup[m_lineupSize++]->setArrivalTime();
            }
            else if (selection == 2)
            {
                m_lineup[m_lineupSize] = new TriagePatient();
                m_lineup[m_lineupSize++]->setArrivalTime();
            }
            cout << "Please enter patient information: " << endl;
            m_lineup[m_lineupSize - 1]->fileIO(false);
            m_lineup[m_lineupSize - 1]->read(cin);
            cout << endl;

            cout << "******************************************" << endl;
            m_lineup[m_lineupSize - 1]->write(cout);
            cout << "Estimated Wait Time: ";
            cout << getWaitTime(*m_lineup[m_lineupSize - 1]) << endl;
            cout << "******************************************" << endl << endl;
        }
    }


    void PreTriage::admit() {
        int selection = 1, index = 0;
        m_pMenu >> selection;
        if (selection == 1) {
            index = indexOfFirstInLine('C');
        }
        else if (selection == 2) {
            index = indexOfFirstInLine('T');
        }
        if (selection && index > -1) {
            cout << endl << "******************************************" << endl;
            cout << "Calling for ";
            m_lineup[index]->write(cout);
            cout << "******************************************" << endl << endl;
            setAverageWaitTime(*m_lineup[index]);
            removePatientFromLineup(index);
        }
    }


 



    int PreTriage::indexOfFirstInLine(char type) const
    {
        int i;
        for (i = 0; i < m_lineupSize && m_lineup[i]->type() != type; i++);

        return i == m_lineupSize ? -1 : i;
    }

    void PreTriage::removePatientFromLineup(int index) {
        removeDynamicElement(m_lineup, index, m_lineupSize);
    }

    //void PreTriage::load() {
    //    char type = 'x';
    //    Patient* p = nullptr;
    //    ifstream fin(m_dataFilename);
    //    cout << "Loading data..." << endl;

    //    if (fin) {
    //        fin >> m_averCovidWait;
    //        fin.ignore(1000, ',');
    //        fin >> m_averTriageWait;
    //        fin.ignore(1000, '\n');

    //        while (fin && m_lineupSize < maxNoOfPatients) {
    //            type = '\0';
    //            fin >> type;
    //            fin.ignore(1000, ',');
    //            if (type != '\0') {
    //                if (type == 'C') {
    //                    p = new CovidPatient();
    //                }
    //                else if (type == 'T') {
    //                    p = new TriagePatient();
    //                }
    //                if (p) {
    //                    p->read(fin); // Call read directly
    //                    m_lineup[m_lineupSize++] = p;
    //                }
    //            }
    //        }
    //    }
    //    if (fin) {
    //        cout << "Warning: number of records exceeded " << maxNoOfPatients << endl;
    //    }
    //    if (!m_lineupSize) {
    //        cout << "No data or bad data file!" << endl;
    //    }
    //    else {
    //        cout << m_lineupSize << " Records imported..." << endl;
    //    }
    //    cout << endl;
    //}

    void PreTriage::load()
    {
        char type = 'x';
        Patient* p = nullptr;
        ifstream fin(m_dataFilename);
        cout << "Loading data..." << endl;

        if (fin)
        {
            fin >> m_averContagionWait;
            fin.ignore(1000, ',');
            fin >> m_averTriageWait;
            fin.ignore(1000, '\n');

            while (fin && m_lineupSize < maxNoOfPatients)
            {
                type = '\0';
                fin >> type;
                fin.ignore(1000, ',');
                if (type != '\0')
                {
                    if (type == 'C')
                    {
                        p = new TestPatient();
                    }
                    else if (type == 'T')
                    {
                        p = new TriagePatient();
                    }
                    if (p)
                    {
                        p->fileIO(true);
                        p->read(fin);
                        p->fileIO(false);
                        m_lineup[m_lineupSize++] = p;
                    }
                }
            }
        }
        if (fin)
        {
            cout << "Warning: number of records exceeded " << maxNoOfPatients << endl;
        }
        if (!m_lineupSize)
        {
            cout << "No data or bad data file!" << endl;
        }
        else
        {
            cout << m_lineupSize << " Records imported..." << endl;
        }
        cout << endl;
    }



    //////////////////////////////

    void PreTriage::viewLineup() {
        cout << "******************************************" << endl;
        cout << "Current lineup:" << endl;
        for (int i = 0; i < m_lineupSize; ++i) {
            cout << (i + 1) << "- ";
            m_lineup[i]->write(cout) << endl;
        }
        cout << "******************************************" << endl << endl;
    }



    void PreTriage::save() const {
        cout << "Saving lineup..." << endl;
        int covidCount = 0, triageCount = 0;
        for (int i = 0; i < m_lineupSize; i++) {
            if (m_lineup[i]->type() == 'C')
                covidCount++;
            else if (m_lineup[i]->type() == 'T')
                triageCount++;
        }

        ofstream file(m_dataFilename);
        if (file.is_open()) {
            file << m_averContagionWait << "," << m_averTriageWait << endl;
            for (int i = 0; i < m_lineupSize; i++) {
                if (m_lineup[i]->type() == 'C' || m_lineup[i]->type() == 'T')
                    m_lineup[i]->write(file) << endl;
            }
            cout << covidCount << " Contagion Tests and " << triageCount << " Triage records were saved!" << endl;
            file.close(); // Close the ofstream object after writing to the file
        }
        else {
            cout << "Error: Unable to open file for writing." << endl << endl;
        }
    }





    void PreTriage::printEmptyFileContent(ifstream& file) const {
        file.seekg(0); // Move the file pointer to the beginning of the file
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
    }






    void PreTriage::deallocate() {
        for (int i = 0; i < m_lineupSize; i++) {
            delete m_lineup[i];
            m_lineup[i] = nullptr;
        }
        delete[] m_dataFilename;
    }

}
