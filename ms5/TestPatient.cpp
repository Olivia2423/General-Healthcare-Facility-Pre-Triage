#define _CRT_SECURE_NO_WARNINGS

#include "TestPatient.h"

namespace seneca {

    int nextTestTicket = 1;

    char TestPatient::type() const {
        return 'C';
    }

    TestPatient::TestPatient() : Patient::Patient(nextTestTicket) {
        nextTestTicket++;
    }

    std::ostream& TestPatient::write(std::ostream& ostr) const {
        if (&ostr == &std::cout) {
            ostr << "Contagion TEST\n";
        }
        return Patient::write(ostr);
    }

    std::istream& TestPatient::read(std::istream& istr) {
        Patient::read(istr);
        if (&istr != &std::cin) {
            nextTestTicket = this->number() + 1;
        }
        return istr;
    }

}

