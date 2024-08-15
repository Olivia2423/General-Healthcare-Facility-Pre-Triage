#define _CRT_SECURE_NO_WARNINGS

#include <ios>
#include <ostream>
#include <string.h>
#include <limits>
#include "Patient.h"
namespace seneca {
    Patient::Patient(int ticketNum) : m_ticket(ticketNum) {
        m_ohipNum = 0;
        m_name = nullptr;
    }
    Patient::Patient(Patient& other) :m_ticket(other.m_ticket) {

        m_name = new char[strlen(other.m_name) + 1];
        m_ohipNum = other.m_ohipNum;
        strncpy(m_name, other.m_name, strlen(other.m_name));
        m_name[strlen(other.m_name)] = '\0';
    }
    Patient::Patient(Patient&& other) : m_ticket(other.m_ticket) {
        m_name = other.m_name;
        other.m_name = nullptr;
        m_ohipNum = other.m_ohipNum;
    }
    Patient& Patient::operator=(Patient& rhs) {
        m_ticket = rhs.m_ticket;
        m_ohipNum = rhs.m_ohipNum;
        delete[] m_name;
        m_name = new char[strlen(rhs.m_name) + 1];
        strncpy(m_name, rhs.m_name, strlen(rhs.m_name));
        m_name[strlen(rhs.m_name)] = '\0';
        return *this;
    }
    Patient::~Patient() {
        delete[] m_name;
    }


    ///////////////////////////////
       // 
       // 
    bool Patient::fileIO() const
    {
        return IO_flag;
    }
    void Patient::fileIO(bool file)
    {
        IO_flag = file;
    }
    /////////////////////////////////

    bool Patient::operator==(const char type) const {
        return this->type() == type;
    }
    bool Patient::operator==(const Patient& rhs) const {
        return this->type() == rhs.type();
    }
    void Patient::setArrivalTime() {
        m_ticket.resetTime();
    }
    Time Patient::time() const {
        return m_ticket.time();
    }
    int Patient::number() const {
        return m_ticket.number();
    }
    Patient::operator bool() const {
        return (m_ohipNum != 0) && (m_name != nullptr);
    }
    Patient::operator const char* () const {
        return m_name;
    }
    std::ostream& Patient::write(std::ostream& ostr) const {
        if (&ostr == &std::clog) {
            if (!bool(*this)) {
                ostr << "Invalid Patient Record";
            }
            else {
                ostr.width(53);
                ostr.fill('.');
                ostr.setf(std::ios_base::left);
                ostr << m_name;
                ostr.unsetf(std::ios_base::left);
                ostr.fill(' ');
                ostr << m_ohipNum;
                ostr.width(5);
                ostr << this->number();
                ostr << ' ';
                ostr << this->time();
            }
        }
        else if (&ostr == &std::cout) {
            if (!bool(*this)) {
                ostr << "Invalid Patient Record";
            }
            else {
                m_ticket.write(ostr);
                ostr << std::endl;
                ostr << m_name;
                ostr << ", OHIP: " << m_ohipNum << std::endl;
            }
        }
        else {
            ostr << this->type() << ',';
            ostr << m_name << ',';
            ostr << m_ohipNum << ',';
            m_ticket.write(ostr);
        }
        return ostr;
    }
    std::istream& Patient::read(std::istream& istr) {
        if (&istr == &std::cin) {
            bool valid = 1;
            char buffer[51];
            std::cout << "Name: ";
            if (istr.peek() == '\n') {
                istr.clear();
                istr.ignore();
            }
            istr.getline(buffer, 51, '\n');
            delete[] m_name;
            m_name = new char[strlen(buffer) + 1];
            strncpy(m_name, buffer, strlen(buffer));
            m_name[strlen(buffer)] = '\0';
            std::cout << "OHIP: ";
            do {
                valid = true;
                istr >> m_ohipNum;
                if (istr.fail()) {
                    istr.clear();
                    istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Bad integer value, try again: ";
                    valid = 0;
                }
                else if (m_ohipNum < 100000000 || m_ohipNum > 999999999) {
                    std::cout << "Invalid value enterd, retry[100000000 <= value <= 999999999]: ";
                    valid = 0;
                }
            } while (!valid);
        }
        else {
            char temp;
            char buffer[51];
            istr.get(buffer, 51, ',');
            delete[] m_name;
            m_name = new char[strlen(buffer) + 1];
            strncpy(m_name, buffer, strlen(buffer));
            m_name[strlen(buffer)] = '\0';
            istr.ignore(std::numeric_limits<std::streamsize>::max(), ',');
            istr.clear();
            istr >> m_ohipNum >> temp;
            m_ticket.read(istr);
        }

        if (istr.fail()) {
            delete[] m_name;
            m_name = nullptr;
        }
        return istr;
    }
}
