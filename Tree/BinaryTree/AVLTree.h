#ifndef STRUCTURESCPP_AVLTREE_H
#define STRUCTURESCPP_AVLTREE_H

template <typename T>
class AVLTree{

public:
    class AVLNode;
    AVLNode* root = nullptr;
    unsigned _size = 0;
    AVLTree(){}
    AVLTree(std::vector<T>& values){
        for(T& v: values){
            this->insert(new AVLNode(v));

        }
    }
    ~AVLTree(){}

    void insert(AVLNode* to_insert);
    void remove(AVLNode* to_remove);
    AVLNode* search(T& key) const;

    int getHeight(AVLNode* node);

    //subrutines
    void _fixup_insert(AVLNode* node);
    void _left_rotation(AVLNode* node);
    void _right_rotation(AVLNode* node);
    void _right_left_rotation(AVLNode* node);
    void _left_right_rotation(AVLNode* node);

    void _balance(AVLNode* node, short int& b);
    void print_pre_order();
    void _updateHeight(AVLNode* node);



};

template <typename T>
class AVLTree<T>::AVLNode{
public:
    int _height = 0;
    T data;
    AVLNode* left = nullptr;
    AVLNode* right= nullptr;
    AVLNode* parent = nullptr;

    AVLNode(){}
    AVLNode(T& val):data(val){}
    AVLNode(T& val, AVLNode* l, AVLNode* r): data(val), left(l), right(r){}
    AVLNode(T& val, AVLNode* p, AVLNode* l, AVLNode* r): data(val), parent(p), left(l), right(r){}

    void print_info(){
        std::cout<<"node: "<<this<<"h("<<this->_height<<") "<<"(p:"<<this->parent<<" l:"<<this->left<<" r:"<<this->right<<")"<<std::endl;
    }
    friend std::ostream& operator<<(std::ostream& os, AVLNode* node){
        if(!node) os<<"null";
        else os<<node->data;
        return os;
    }
};

template <typename T>
int AVLTree<T>::getHeight(AVLNode* node){
    if(!node) return -1;
    return node->_height;
}



#endif //STRUCTURESCPP_AVLTREE_H
#include "AVLTree.hpp"