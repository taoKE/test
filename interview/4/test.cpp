#include <iostream>
#include "bst.h"

int main() {
    BST tree(new BSTNode(20));
    tree.insert(10);
    tree.insert(30);

    return 0;
}
