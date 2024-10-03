#ifndef TREE_NODE_H
#define TREE_NODE_H

template<typename T>
class TreeNode {
private:
    T m_data;
    TreeNode* m_parent;
    TreeNode* m_lchild;
    TreeNode* m_rchild;

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
    const TreeNode* get_parent() const {
        return m_parent;
    }
    const TreeNode* get_lchild() const {
        return m_lchild;
    }
    const TreeNode* get_rchild() const {
        return m_rchild;
    }

    // setters
    void set_data(const T& data) {
        m_data = data;
    }
    void set_parent(const TreeNode* node) {
        m_parent = new TreeNode(node.m_parent->m_data);
    }
    void set_lchild(const TreeNode* node) {
        m_lchild = new TreeNode(node.m_lchild->m_data);
    }
    void set_rchild(const TreeNode* node) {
        m_rchild = new TreeNode(node.m_rchild->m_data);
    }
};


#endif // TREE_NODE_H