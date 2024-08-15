

#ifndef SENECA_TIME_H
#define SENECA_TIME_H


namespace seneca {

    class Time {
        unsigned int m_minutes;

    public:
        Time(unsigned int min = 0u);
        Time& reset();
        unsigned int totalMinutes() const;
        Time operator-(const Time& other) const;
        Time& operator-=(const Time& other);
        Time& operator*=(int value);
        operator unsigned int() const;

        std::ostream& write(std::ostream& os = std::cout) const;
        //   void write(std::ostream& os) const;

        std::istream& read(std::istream& is = std::cin);
    };

    std::ostream& operator<<(std::ostream& os, const Time& time);
    std::istream& operator>>(std::istream& is, Time& time);

}

#endif 

