#include "TreeNode.h"
#include <iostream>

int main() {
    int arr[] = {5, 3, 7, 6, 10, 1, 3, 8, 4, 9};
    BinTree<int> tree1(arr, 10);
    tree1.add(0);
    std::cout << "Init tree:" << std::endl << tree1;

    BinTree<int> tree2 = tree1;
    std::cout << "Copied tree:" << std::endl << tree2;

    auto it = tree1.find(8);
    if (it != nullptr) {
        std::cout << "Found value: " << *it;

        auto next = tree1.get_next(it);
        if (next)
            std::cout << "Next: " << *next;

        auto prev = tree1.get_prev(it);
        if (prev)
            std::cout << "Prev: " << *prev;
    }

    std::cout << std::boolalpha << tree1.contains(12) << " " << tree1.contains(6) << std::endl;

    tree1.remove(1);
    std::cout << "Removed 1:" << std::endl
              << tree1;

    tree1.remove(9);
    std::cout << "Removed 9:" << std::endl
              << tree1;

    if (tree1.min() != nullptr)
        std::cout << "Min: " << *tree1.min();
    if (tree1.max() != nullptr)
        std::cout << "Max: " << *tree1.max();

    std::cout << "Print with iterators:" << std::endl;
    for (auto it = tree1.cbegin(), end = tree1.cend(); it != end; ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    return 0;
}
