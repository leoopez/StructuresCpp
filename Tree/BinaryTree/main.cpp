#include<iostream>
#include<vector>
#include<unistd.h>
#include "BinaryTree.h"
#include "RedBlackTree.h"
void debug_1(){
    std::vector<int> values{1,2,3,4,5,6};
    auto tree = new RedBlackTree<int>(values);
    tree->print_post_order();
    tree->print_pre_order();

    std::cout<<tree->successor(tree->root)<<'\n';
    std::cout<<tree->predecessor(tree->root)<<'\n';

    while(tree->root != tree->nil){
        tree->print_in_order();
        tree->remove(tree->root);
    }

}
void debug_2(){
    std::vector<char> values_C{'a','b','c','d','e','f'};

    auto tree_2 = new BinaryTree<char>(values_C);
    tree_2->print_post_order();
    tree_2->print_pre_order();

    std::cout<<tree_2->successor(tree_2->root)<<'\n';

    std::cout<<(!tree_2->predecessor(tree_2->root))<<'\n';

    while(tree_2->root){
        tree_2->print_in_order();
        tree_2->remove(tree_2->root);
    }
}
int main(){
    debug_1();
    debug_2();

    return 0;
}
