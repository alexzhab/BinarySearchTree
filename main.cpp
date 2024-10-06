#include "TreeNode.h"
#include <iostream>

int main() {
    TreeNode<int> node1(5);
    TreeNode<int> node2(4);
    node1.set_lchild(&node2);

    TreeNode<int> node3(1);
    node3.set_lchild(&node2);

    std::cout << "node1: " << node1;
    std::cout << "node3: " << node3;

    BinTree<int> tree1;
    BinTree<int> tree2 = tree1;

    return 0;
}