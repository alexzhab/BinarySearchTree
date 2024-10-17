#ifndef SET_MAP_H
#define SET_MAP_H
#include "TreeNode.h"
#include <iostream>

template<typename T, typename U>
class Pair {
private:
    T m_first;
    U m_second;

public:
    Pair(const T &first, const U &second)
    : m_first(first)
    , m_second(second) {
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
        os << p.get_first() << p.get_second() << std::endl;
        return os;
    }
};

template<typename T, typename Functor=Compare>
class Set {
private:
    BinTree<T, Functor>* m_tree;

public:
    Set(BinTree<T, Functor>* tree) 
    : m_tree(tree) {
    }
    ~Set() = default;

    void add(const T& data) {
        m_tree->add(data);
    }

    bool contains(const T& data) const {
        return m_tree->contains(data);
    }

#endif // SET_MAP_H
