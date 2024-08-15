#ifndef SENECA_IOABLE_H
#define SENECA_IOABLE_H

namespace seneca {

    class IOAble {
    public:
        virtual std::ostream& write(std::ostream& os) const = 0;
        virtual std::istream& read(std::istream& is) = 0;
        virtual ~IOAble() {}
    };

    std::ostream& operator<<(std::ostream& os, const IOAble& io);
    std::istream& operator>>(std::istream& is, IOAble& io);

}

#endif
