#define _CRT_SECURE_NO_WARNINGS

#include "TriagePatient.h"
#include <string.h>
namespace seneca {
    int nextTriageTicket = 1;
    TriagePatient::TriagePatient() : Patient(nextTriageTicket) {
        m_symtoms = nullptr;
        nextTriageTicket++;
    }
    TriagePatient::~TriagePatient() {
        delete[] m_symtoms;
    }
    char TriagePatient::type() const {
        return 'T';
    }
    std::ostream& TriagePatient::write(std::ostream& ostr) const {
        if (&ostr == &std::cout) {
            ostr << "TRIAGE\n";
        }
        Patient::write(ostr);
        if (&ostr == &std::cout) {
            ostr << "Symptoms: ";
            ostr << m_symtoms << std::endl;
        }
        else if (&ostr != &std::clog) {
            ostr << ",";
            ostr << m_symtoms;
        }
        return ostr;
    }
    std::istream& TriagePatient::read(std::istream& istr) {
        char buffer[512];
        delete[] m_symtoms;
        Patient::read(istr);
        if (&istr != &std::cin) {
            istr.ignore();
            istr.getline(buffer, 512);
            this->m_symtoms = new char[strlen(buffer) + 1];
            strncpy(m_symtoms, buffer, strlen(buffer) + 1);
            nextTriageTicket = this->number() + 1;
        }
        else {
            std::cout << "Symptoms: ";
            istr.clear();
            istr.ignore(1000, '\n');
            istr.getline(buffer, 512);
            this->m_symtoms = new char[strlen(buffer) + 1];
            strncpy(m_symtoms, buffer, strlen(buffer) + 1);
        }

        if (istr.fail()) {
            delete[] m_symtoms;
            m_symtoms = nullptr;
        }
        return istr;
    }
}
