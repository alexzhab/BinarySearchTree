#ifndef PAIR_H
#define PAIR_H

#include <iostream>

template<typename T, typename U>
class Pair {
private:
    T m_first;
    U m_second;

public:
    Pair(const T& first, const U& second)
    : m_first(first)
    , m_second(second) {
    }
    Pair(const Pair<T, U>& p)
    : m_first(p.get_first())
    , m_second(p.get_second()) {
    }
    ~Pair() = default;

    // non-const getters
    T& get_first() {
        return m_first;
    }
    U& get_second() {
        return m_second;
    }

    // const getters
    const T& get_first() const {
        return m_first;
    }
    const U& get_second() const {
        return m_second;
    }

    friend std::ostream& operator<<(std::ostream& os, const Pair<T, U>& p) {
        os << p.get_first() << " x" << p.get_second() << std::endl;
        return os;
    }
};

#endif // PAIR_H
