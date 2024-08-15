#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include "Time.h"
#include "Utils.h"


namespace seneca {

    Time::Time(unsigned int min) : m_minutes(min) {}

    Time& Time::reset() {
        m_minutes = U.getTime();
        return *this;
    }

    unsigned int Time::totalMinutes() const {
        return m_minutes;
    }

    Time Time::operator-(const Time& other) const {
        int diff = static_cast<int>(m_minutes) - static_cast<int>(other.m_minutes);
        if (diff < 0)
            diff += 24 * 60; // Adding 24 hours in minutes
        return Time(diff);
    }

    Time& Time::operator-=(const Time& other) {
        *this = *this - other;
        return *this;
    }

    Time& Time::operator*=(int value) {
        m_minutes *= value;
        return *this;
    }

    Time::operator unsigned int() const {
        return m_minutes;
    }

    std::ostream& Time::write(std::ostream& os) const {
        os << std::setfill('0') << std::setw(2) << m_minutes / 60 << ":" << std::setw(2) << m_minutes % 60;
        return os;
    }


    std::istream& Time::read(std::istream& is) {
        int hours, minutes;
        char colon;
        is >> hours;
        if (is.peek() != ':') {
            is.setstate(std::ios::failbit);
            return is;
        }
        is >> colon >> minutes;
        if (colon != ':' || is.fail()) {
            is.setstate(std::ios::failbit);
            return is;
        }
        m_minutes = hours * 60 + minutes;
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const Time& time) {
        return time.write(os);
    }

    std::istream& operator>>(std::istream& is, Time& time) {
        return time.read(is);
    }

}
