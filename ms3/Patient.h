
#ifndef SENECA_PATIENT_H
#define SENECA_PATIENT_H

#include <iostream>
#include "Ticket.h" // Include Ticket header file

namespace seneca {

    class Patient : public IOAble {
        char* m_name; // Dynamically allocated C-string for patient name
        int m_OHIP;   // OHIP number
        Ticket m_ticket; // Ticket object for patient lineup

    public:
        // Constructor
        Patient(int ticketNumber = 0);

        // Copy constructor
        Patient(const Patient& other);

        // Assignment operator
        Patient& operator=(const Patient& other);

        // Destructor
        ~Patient();

        // Member functions
        char type() const;
        bool operator==(char type) const; // Comparison with a character
        bool operator==(const Patient& other) const; // Comparison with another Patient
        void setArrivalTime(); // Modifier method to set arrival time
    //    unsigned int time() const; // Query method to retrieve arrival time

        std::string time() const;

        int number() const; // Query method to retrieve ticket number
        operator bool() const; // Cast overload to boolean
        operator const char* () const; // Cast overload to const char*

        // Virtual function overrides
        std::ostream& write(std::ostream& os) const override;
        std::istream& read(std::istream& is) override;
    };

} // namespace seneca

#endif // SENECA_PATIENT_H
