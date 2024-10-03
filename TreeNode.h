#ifndef TREE_NODE_H
#define TREE_NODE_H

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
    TreeNode(const TreeNode& node) {
        set_data(node.get_data());
        set_parent(node.get_parent());
        set_lchild(node.get_lchild());
        set_rchild(node.get_rchild());
    }

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
    void set_parent(const TreeNode<T>* node) {
        m_parent = new TreeNode((node->get_parent())->get_data());
    }
    void set_lchild(const TreeNode<T>* node) {
        m_lchild = new TreeNode((node->get_lchild())->get_data());
    }
    void set_rchild(const TreeNode<T>* node) {
        m_rchild = new TreeNode((node->get_rchild())->get_data());
    }
};


#endif // TREE_NODE_H