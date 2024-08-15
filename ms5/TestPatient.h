#ifndef SENECA_TESTPAT_H
#define SENECA_TESTPAT_H
#include "Patient.h"
#include <iostream>
namespace seneca {
    extern int nextTestTicket;
    class TestPatient : public Patient {
    public:
        TestPatient();
        virtual char type() const;
        std::ostream& write(std::ostream& ostr = std::cout) const override;
        std::istream& read(std::istream& istr = std::cin) override;
    };
}
#endif // !SENECA_TESTPAT_H
