#ifndef TREE_NODE_H
#define TREE_NODE_H
#include <iostream>
#include <cassert>

template<typename T>
class TreeNode {
private:
    T m_data;
    TreeNode<T>* m_parent;
    TreeNode<T>* m_lchild;
    TreeNode<T>* m_rchild;

public:
    // constructors
    TreeNode(const T& data)
    : m_data(data)
    , m_parent(nullptr)
    , m_lchild(nullptr)
    , m_rchild(nullptr) {
    }
    TreeNode(const TreeNode<T>& node) : TreeNode(node.get_data()) {
    }
    ~TreeNode() = default;

    // getters
    const T& get_data() const {
        return m_data;
    }
    const TreeNode<T>* get_parent() const {
        return m_parent;
    }
    const TreeNode<T>* get_lchild() const {
        return m_lchild;
    }
    const TreeNode<T>* get_rchild() const {
        return m_rchild;
    }

    // setters
    void set_data(const T& data) {
        m_data = data;
    }
    void set_parent(TreeNode<T> * const node) {
        m_parent = node;
    }
    void set_lchild(TreeNode<T> * const node) {
        m_lchild = node;
    }
    void set_rchild(TreeNode<T> * const node) {
        m_rchild = node;
    }

    friend std::ostream & operator<<(std::ostream & os, const TreeNode<T>& node) {
        os << node.get_data() << " " << node.get_lchild() << std::endl;
        return os;
    }
};


#endif // TREE_NODE_H