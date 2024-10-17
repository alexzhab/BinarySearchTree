#ifndef TREE_NODE_H
#define TREE_NODE_H
#include <iostream>
#include <sstream>
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
    TreeNode(const T& data, const TreeNode<T>* parent)
    : m_data(data)
    , m_parent(parent) {
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
        if (node)
            node->set_parent(this);
    }
    void set_rchild(TreeNode<T>* const node) {
        m_rchild = node;
        if (node)
            node->set_parent(this);
    }

    friend std::ostream & operator<<(std::ostream & os, const TreeNode<T>& node) {
        os << node.get_data() << std::endl;
        return os;
    }
};

template<typename T>
struct Functor {
    bool operator()(const T& t1, const T& t2) const {
        return (t1 < t2);
    }
};

template<typename T>
class BinTree {
private:
    TreeNode<T>* m_root{nullptr};
    Functor<T> m_compare;

    TreeNode<T>* copyTree(const TreeNode<T>* src) {
        TreeNode<T>* dst = new TreeNode<T>(*src);
        const TreeNode<T>* src_lchild = src->get_lchild();
        const TreeNode<T>* src_rchild = src->get_rchild();

        if (src_lchild)
            dst->set_lchild(copyTree(src_lchild));
        if (src_rchild)
            dst->set_rchild(copyTree(src_rchild));

        return dst;
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

    const TreeNode<T>* find(const TreeNode<T>* node, const T& data) const {
        if (!node)
            return nullptr;
        if (!m_compare(node->get_data(), data) && !m_compare(data, node->get_data()))
            return node;
        if (m_compare(data, node->get_data()))
            return find(node->get_lchild(), data);
        if (m_compare(node->get_data(), data))
            return find(node->get_rchild(), data);
        return nullptr;
    }

    TreeNode<T>* add(TreeNode<T>* node, const T& data) {
        if (!node) {
            node = new TreeNode<T>(data);
            return node;
        }
        if (m_compare(data, node->get_data()))
            node->set_lchild(add(node->get_lchild(), data));
        else if (m_compare(node->get_data(), data))
            node->set_rchild(add(node->get_rchild(), data));
        return node;
    }

    void remove(TreeNode<T>* node) {
        if (!node)
            return;
        if (!node->get_lchild() && !node->get_rchild()) {
            TreeNode<T> *parent = node->get_parent();
            if (m_compare(node->get_data(), parent->get_data()))
                parent->set_lchild(nullptr);
            else
                parent->set_rchild(nullptr);
            delete node;
        }
        else if (!node->get_lchild()) {
            TreeNode<T> *parent = node->get_parent();
            TreeNode<T> * r = node->get_rchild();
            if (m_compare(r->get_data(), parent->get_data()))
                parent->set_lchild(r);
            else
                parent->set_rchild(r);
            node->set_parent(nullptr);
            node->set_rchild(nullptr);
            delete node;
        }
        else if (!node->get_rchild()) {
            TreeNode<T> *parent = node->get_parent();
            TreeNode<T>  *l = node->get_lchild();
            if (m_compare(l->get_data(), parent->get_data()))
                parent->set_lchild(l);
            else
                parent->set_rchild(l);
            node->set_parent(nullptr);
            node->set_lchild(nullptr);
            delete node;
        }
        else {
            assert(false && "Not implemented.");
        }
    }

    const TreeNode<T>* min(const TreeNode<T>* node) const {
        if (node->get_lchild() == nullptr)
            return node;
        return min(node->get_lchild());
    }

    const TreeNode<T>* max(const TreeNode<T>* node) const {
        if (node->get_rchild() == nullptr)
            return node;
        return max(node->get_rchild());
    }

    void print(std::ostringstream& ostr, std::string padding, std::string pointer, const TreeNode<T>* node) const {
        if (node) {
            ostr << padding << pointer;
            ostr << node->get_data() << std::endl;

            if (pointer == "└──R " || pointer == "└──L ")
                padding += "   ";
            else if (pointer != "")
                padding += "│  ";
            print(ostr, padding, (node->get_lchild()) ? "├──R " : "└──R ", node->get_rchild());
            print(ostr, padding, "└──L ", node->get_lchild());
        }
    }

public:
    // constructors
    BinTree() = default;
    BinTree(const T& data) {
        m_root = new TreeNode<T>(data);
    }
    BinTree(const T* data, int size) {
        for (int i{}; i < size; ++i)
            this->add(data[i]);
    }
    BinTree(const BinTree& tree) {
        if (tree.m_root)
            m_root = copyTree(tree.m_root);
    }
    BinTree& operator=(const BinTree& tree) {
        if (&tree == this)
            return *this;
        ~BinTree();

        if (tree.m_root)
            m_root = copyTree(tree.m_root);

        return *this;
    }
    ~BinTree() {
        if (m_root)
            deleteTree(m_root);
        m_root = nullptr;
    }

    const TreeNode<T>* find(const T& data) const {
        return find(m_root, data);
    }

    bool contains(const T& data) const {
        return find(m_root, data) != nullptr;
    }

    void add(const T& data) {
        m_root = add(m_root, data);
    }

    void remove(const T& data) {
        TreeNode<T>* tmp = const_cast<TreeNode<T>*>(find(data));
        remove(tmp);
    }

    const TreeNode<T>* min() const {
        return min(m_root);
    }

    const TreeNode<T>* max() const {
        return max(m_root);
    }

    const TreeNode<T>* get_next(const TreeNode<T>* node) const {
        if (node->get_rchild() != nullptr)
            return min(node->get_rchild());

        const TreeNode<T>* parent = node->get_parent();
        const TreeNode<T>* tmp = node;
        while (parent != nullptr && tmp == parent->get_rchild()) {
            tmp = parent;
            parent = parent->get_parent();
        }
        return parent;
    }

    const TreeNode<T>* get_prev(const TreeNode<T>* node) const {
        if (node->get_lchild() != nullptr)
            return max(node->get_lchild());

        const TreeNode<T>* parent = node->get_parent();
        const TreeNode<T>* tmp = node;
        while (parent != nullptr && tmp == parent->get_lchild()) {
            tmp = parent;
            parent = parent->get_parent();
        }
        return parent;
    }

    friend std::ostream& operator<<(std::ostream& os, const BinTree& tree) {
        std::ostringstream ostr;
        ostr.precision(2);
        tree.print(ostr, "", "", tree.m_root);
        os << ostr.str();
        return os;
    }

    // const iterator
    struct ConstIterator {
    private:
        const BinTree<T> * m_tree;
        const TreeNode<T> * m_ptr;

    public:
        ConstIterator(const BinTree<T> * tree, const TreeNode<T> * ptr) 
        : m_tree(tree)
        , m_ptr(ptr) {
        }
        ~ConstIterator() = default;

        const T& operator*() const {
            assert(m_ptr != nullptr);
            return m_ptr->get_data();
        }

        const T& operator->() const {
            assert(m_ptr != nullptr);
            return m_ptr->get_data();
        }

        ConstIterator& operator++() {
            m_ptr = m_tree->get_next(m_ptr);
            return *this;
        }
        ConstIterator operator++(int) {
            ConstIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        ConstIterator& operator--() {
            m_ptr = m_tree->get_prev(m_ptr);
            return *this;
        }
        ConstIterator operator--(int) {
            ConstIterator tmp = *this;
            --(*this);
            return tmp;
        }

        friend bool operator==(const ConstIterator& a, const ConstIterator& b) {
            return a.m_ptr == b.m_ptr;
        }
        friend bool operator!=(const ConstIterator& a, const ConstIterator& b) {
            return a.m_ptr != b.m_ptr;
        }
    };

    ConstIterator cbegin() const {
        return ConstIterator(this, min(m_root));
    }
    ConstIterator cend() const {
        return ConstIterator(this, nullptr);
    }
};

#endif // TREE_NODE_H
