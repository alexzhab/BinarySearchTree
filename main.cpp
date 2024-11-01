#include "TreeNode.h"
#include "SetMap.h"
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

    tree1.remove(6);
    std::cout << "Removed 6:" << std::endl
              << tree1;

    tree1.remove(5);
    std::cout << "Removed 5:" << std::endl
              << tree1;

    if (tree1.min() != nullptr)
        std::cout << "Min: " << *tree1.min();
    if (tree1.max() != nullptr)
        std::cout << "Max: " << *tree1.max();

    std::cout << "Print with iterators:" << std::endl;
    for (auto it = tree1.cbegin(), end = tree1.cend(); it != end; ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    Set<int> s(&tree1);
    std::cout << s.contains(10) << std::endl;
    s.add(11);
    std::cout << s;
    std::cout << "Print with iterators:" << std::endl;
    for (auto it = s.cbegin(), end = s.cend(); it != end; ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    Multiset<int> ms;
    ms.add(1);
    ms.add(3);
    ms.add(5);
    ms.add(1);
    ms.add(1);
    std::cout << ms;

    return 0;
}
