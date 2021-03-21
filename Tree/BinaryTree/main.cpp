#include<iostream>
#include<vector>
#include<memory>
#include<functional>
#include<algorithm>
#include<stack>

#include "BinaryTree.h"
#include "RedBlackTree.h"
#include "AVLTree.h"

void debug_1(){
    std::vector<int> values{1,2,3,4,5,6};

    using rdint = RedBlackTree<int>;
    std::unique_ptr<rdint> tree_1 = std::make_unique<rdint>(values);

    tree_1->print_post_order();
    tree_1->print_pre_order();

    std::cout<<tree_1->successor(tree_1->root)<<'\n';
    std::cout<<tree_1->predecessor(tree_1->root)<<'\n';

    while(tree_1->root != tree_1->nil){
        tree_1->print_in_order();
        tree_1->remove(tree_1->root);
    }

}
void debug_2(){
    std::vector<char> values_C{'a','b','c','d','e','f'};

    using btchar = BinaryTree<char>;
    std::unique_ptr<btchar> tree_2 = std::make_unique<btchar>(values_C);

    tree_2->print_post_order();
    tree_2->print_pre_order();

    std::cout<<tree_2->successor(tree_2->root)<<'\n';
    std::cout<<(!tree_2->predecessor(tree_2->root))<<'\n';

    while(tree_2->root){
        tree_2->print_in_order();
        tree_2->remove(tree_2->root);
    }wqqq
}

void debug_3(){
    std::vector<int> values_dbl{43, 18, 22, 9, 21, 6, 8, 20, 63, 50, 62, 51};
    using btdbl = AVLTree<int>;
    std::unique_ptr<btdbl> tree_3 = std::make_unique<btdbl>(values_dbl);
    //tree_3->print_pre_order();
    AVLTree<int>::AVLNode* node = tree_3->root;

    std::stack<AVLTree<int>::AVLNode*> nodes;

    nodes.push(node);
    while(!nodes.empty()){
        node = nodes.top();
        nodes.pop();
        if(node->left)
            nodes.push(node->left);
        if(node->right)
            nodes.push(node->right);
        node->print_info();
    }


}
int main(){
    //debug_1();
    //debug_2();
    debug_3();
    return 0;
}
