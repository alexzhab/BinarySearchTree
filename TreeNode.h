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

    // const getters
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

    // non-const getters
    TreeNode<T>* get_parent() {
        return m_parent;
    }
    TreeNode<T>* get_lchild() {
        return m_lchild;
    }
    TreeNode<T>* get_rchild() {
        return m_rchild;
    }

    // setters
    void set_data(const T& data) {
        m_data = data;
    }
    void set_parent(TreeNode<T>* const node) {
        m_parent = node;
    }
    void set_lchild(TreeNode<T>* const node) {
        m_lchild = node;
    }
    void set_rchild(TreeNode<T>* const node) {
        m_rchild = node;
    }

    friend std::ostream & operator<<(std::ostream & os, const TreeNode<T>& node) {
        os << node.get_data() << " " << node.get_lchild() << std::endl;
        return os;
    }
};

template<typename T>
struct Functor {
    bool operator()(const T& t1, const T& t2) {
        return (t1 < t2);
    }
};

template<typename T>
class BinTree {
private:
    TreeNode<T>* m_root{nullptr};
    Functor<T> m_compare;
public:
    // constructors
    BinTree() = default;
    BinTree(const T& data) {
        m_root = new TreeNode<T>(data);
    }
    BinTree(const BinTree& tree) {
        if (tree.m_root)
            copyTree(tree.m_root, m_root);
    }
    BinTree & operator=(const BinTree<T>& tree) {
        if (&tree == this)
            return *this;
        ~BinTree();

        if (tree.m_root)
            copyTree(tree.m_root, m_root);

        return *this;
    }
    ~BinTree() {
        if (m_root)
            deleteTree(m_root);
        m_root = nullptr;
    }

    void copyTree(const TreeNode<T>* src, TreeNode<T>*& dst) {
        dst = new TreeNode<T>(*src);
        const TreeNode<T>* src_lchild = src->get_lchild();
        const TreeNode<T>* src_rchild = src->get_rchild();

        TreeNode<T>* dst_lchild = dst->get_lchild();
        TreeNode<T>* dst_rchild = dst->get_rchild();
        if (src_lchild)
            copyTree(src_lchild, dst_lchild);
        if (src_rchild)
            copyTree(src_rchild, dst_rchild);
    }

    void deleteTree(TreeNode<T>* node) {
        TreeNode<T>* lchild = node->get_lchild();
        TreeNode<T>* rchild = node->get_rchild();
        if (lchild)
            deleteTree(lchild);
        if (rchild)
            deleteTree(rchild);
        delete node;
    }
};

#endif // TREE_NODE_H