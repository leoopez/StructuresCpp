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

    void print_pre_order();

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


    friend std::ostream& operator<<(std::ostream& os, AVLNode* node){
        os<<node->data<<" h:"<<node->_height;
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