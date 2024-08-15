
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <sstream>
#include "Patient.h"
#include "Time.h"

using namespace std;

namespace seneca {

    // Constructor
    Patient::Patient(int ticketNumber)
        : m_name(nullptr), m_OHIP(0), m_ticket(ticketNumber) {}

    // Copy constructor
    Patient::Patient(const Patient& other) {
        m_OHIP = other.m_OHIP;
        m_ticket = other.m_ticket;
        if (other.m_name != nullptr) {
            m_name = new char[strlen(other.m_name) + 1];
            strcpy(m_name, other.m_name);
        }
        else {
            m_name = nullptr;
        }
    }

    // Assignment operator
    Patient& Patient::operator=(const Patient& other) {
        if (this != &other) {
            // Copy OHIP and ticket
            m_OHIP = other.m_OHIP;
            m_ticket = other.m_ticket;

            // Copy name
            delete[] m_name;
            if (other.m_name != nullptr) {
                m_name = new char[strlen(other.m_name) + 1];
                strcpy(m_name, other.m_name);
            }
            else {
                m_name = nullptr;
            }
        }
        return *this;
    }

    // Destructor
    Patient::~Patient() {
        delete[] m_name;
    }

    // Member functions

    // Implementation of char type() method
    char Patient::type() const {
        return 'W'; // Base class patient type
    }

    // Implementation of comparison with a character
    bool Patient::operator==(char type) const {
        return this->type() == type;
    }

    // Implementation of comparison with another Patient
    bool Patient::operator==(const Patient& other) const {
        return this->type() == other.type();
    }

    // Modifier method to set arrival time
    void Patient::setArrivalTime() {
        m_ticket.resetTime(); // Resetting ticket time
    }

    //unsigned int Patient::time() const {
    //    return m_ticket.time().totalMinutes();
    //}


    //////////////////////////
    // Query method to retrieve arrival time
    //unsigned int Patient::time() const {
    //    unsigned int arrivalTime = m_ticket.time().totalMinutes();
    //    int hours = arrivalTime / 60; 
    //    int minutes = arrivalTime % 60; 
    //    return (hours * 100) + minutes; 


    //}






    std::string Patient::time() const {
        unsigned int totalMinutes = m_ticket.time().totalMinutes();
        unsigned int hours = totalMinutes / 60; // Calculate hours
        unsigned int minutes = totalMinutes % 60; // Calculate remaining minutes

        // Construct the formatted time string
        std::ostringstream formattedTime;
        formattedTime << std::setw(2) << std::setfill('0') << hours << ":"; // HH
        formattedTime << std::setw(2) << std::setfill('0') << minutes; // MM

        return formattedTime.str(); // Return the time as a string in HH:MM format
    }

    // Query method to retrieve ticket number
    int Patient::number() const {
        return m_ticket.number();
    }

    // Cast overload to boolean
    Patient::operator bool() const {
        return (m_name != nullptr && m_OHIP != 0);
    }

    // Cast overload to const char*
    Patient::operator const char* () const {
        return m_name;
    }

    // Virtual function overrides

    // Implementation of write method
    std::ostream& Patient::write(std::ostream& os) const {
        // Output patient information based on ostream type
        if (&os == &std::cout) {
            // For cout
            if (m_name == nullptr || m_OHIP == 0) {
                os << "Invalid Patient Record"
                    << endl;

            }
            else {
                os << "Ticket No: " << m_ticket.number() << ", Issued at: " << m_ticket.time() << std::endl

                    << m_name << ", OHIP: " << m_OHIP << std::endl;


            }
        }
        else if (&os == &clog) {
            // For clog
            if (m_name == nullptr || m_OHIP == 0) {
                os << "Invalid Patient Record";
            }
            else {
              /*  os << std::left << std::setw(53) << std::setfill(' ') << (m_name != nullptr ? m_name : "") << m_OHIP
                    << std::setw(5) << std::right << m_ticket.number() << ' ' << m_ticket.time();*/

                os << setw(53) << setfill('.') << left << (m_name != nullptr ? m_name : "")
                    << setfill(' ') << right << setw(7) << m_OHIP
                    << setw(3) << " "
                    << setw(1) << m_ticket.number() << " " 
                    << m_ticket.time();

            }


        }
        else {
            // For other objects (e.g., file)
            if (m_name == nullptr || m_OHIP == 0) {
                os << "Invalid Patient Record";
            }
            else {
                os << type() << ',' << (m_name != nullptr ? m_name : "") << ',' << m_OHIP << ',';
                m_ticket.write(os); // Write ticket information

            }
        }
        return os;
    }

    // Implementation of read method
    std::istream& Patient::read(std::istream& is) {
        char tempName[51]; // Temporary buffer for name
        int tempOHIP;      // Temporary variable for OHIP number

        if (&is == &cin) {
            cout << "Name: ";
            is.get(tempName, 51); // Read name
            is.ignore(10000, '\n'); // Ignore rest of the input buffer
            cout << "OHIP: ";
            while (!(is >> tempOHIP) || tempOHIP < 100000000 || tempOHIP > 999999999) {
                if (is.fail()) {
                    cerr << "Bad integer value, try again: ";
                    is.clear();
                }
                else {
                    cerr << "Invalid value enterd, retry[100000000 <= value <= 999999999]: ";
                }
                is.ignore(10000, '\n'); // Ignore rest of the input buffer
            }
        }
        else {
            is.get(tempName, 51, ','); // Read name
            is.ignore(10000, ',');     // Ignore comma
            is >> tempOHIP;            // Read OHIP
            is.ignore(10000, ',');     // Ignore comma
            m_ticket.read(is);         // Read ticket information
        }

        // Dynamically allocate memory for name
        delete[] m_name;
        m_name = new char[strlen(tempName) + 1];
        strcpy(m_name, tempName);
        m_OHIP = tempOHIP;

        return is;
    }



} // namespace seneca
