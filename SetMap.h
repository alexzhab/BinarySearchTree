#ifndef SET_MAP_H
#define SET_MAP_H

#include "Pair.h"
#include "TreeNode.h"
#include <iostream>

template<typename T, typename Functor=Compare>
class Set {
private:
    BinTree<T, Functor>* m_tree{nullptr};

public:
    Set() {
        m_tree = new BinTree<T, Functor>();
    }
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

    friend std::ostream& operator<<(std::ostream& os, const Set<T, Functor>& set) {
        os << *(set.m_tree) << std::endl;
        return os;
    }

    typename BinTree<T, Functor>::ConstIterator cbegin() const {
        return m_tree->cbegin();
    }
    typename BinTree<T, Functor>::ConstIterator cend() const {
        return m_tree->cend();
    }
    typename BinTree<T, Functor>::ConstIterator& operator--() = delete;
    typename BinTree<T, Functor>::ConstIterator& operator--(int) = delete;
};

template<typename T, typename Functor>
struct PairCompare {
    bool operator()(const Pair<T, int>& t1, const Pair<T, int>& t2) const {
        return Functor()(t1.get_first(), t2.get_first());
    }
};

template<typename T, typename Functor=Compare>
class Multiset {
    using Internal_T = Pair<T, int>;
private:
    BinTree<Pair<T, int>, PairCompare<T, Functor>>* m_tree;
    
public:
    Multiset() {
        m_tree = new BinTree<Internal_T, PairCompare<T, Functor>>();
    }
    ~Multiset() = default;

    void add(const T& data) {
        Pair<T, int> p(data, 1);
        TreeNode<Pair<T, int>>* found = const_cast<TreeNode<Pair<T, int>>*>(m_tree->find(p));
        if (found) {
            int& counter = found->get_data().get_second();
            counter++;
        }
        else {
            m_tree->add(p);
        }
    }

    bool contains(const T& data) const {
        return m_tree->contains(data);
    }

    friend std::ostream& operator<<(std::ostream& os, const Multiset<T, Functor>& mset) {
        os << *(mset.m_tree) << std::endl;
        return os;
    }

    typename BinTree<T, Functor>::ConstIterator cbegin() const {
        return m_tree->cbegin();
    }
    typename BinTree<T, Functor>::ConstIterator cend() const {
        return m_tree->cend();
    }
    typename BinTree<T, Functor>::ConstIterator& operator--() = delete;
    typename BinTree<T, Functor>::ConstIterator& operator--(int) = delete;
};

#endif // SET_MAP_H
