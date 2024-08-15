#ifndef SENECA_TRGPAT_H
#define SENECA_TRGPAT_H
#include "Patient.h"

namespace seneca {
    extern int nextTriageTicket;
    class TriagePatient : public Patient {
        char* m_symtoms;
    public:
        TriagePatient();
        ~TriagePatient() override;
        virtual char type() const;
        std::ostream& write(std::ostream& ostr = std::cout) const override;
        std::istream& read(std::istream& istr = std::cin) override;

    };
}

#endif // !SENECA_TRGPAT_H
