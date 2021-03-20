#ifndef STRUCTURESCPP_REDBLACKTRESS_H
#define STRUCTURESCPP_REDBLACKTRESS_H

template <typename T>
class RedBlackTree{
public:

    class RedBlackNode;
    RedBlackNode* nil = new RedBlackNode();
    RedBlackNode* root = nil;

    int _size = 0;
    int _height = 0;
public:
    RedBlackTree(){}
    RedBlackTree(std::vector<T>& values){
        for(T i : values)
            this->insert(new RedBlackNode(i));
    }

    void insert(RedBlackNode*);
    void remove(RedBlackNode*);

    //Subroutines
    void _left_rotation(RedBlackNode*);
    void _right_rotation(RedBlackNode*);
    void _fixup_insert(RedBlackNode*);
    void _fixup_remove(RedBlackNode*);

    void print_in_order();
    void print_pre_order();
    void print_post_order();

    RedBlackNode* minimum(RedBlackNode* node);
    RedBlackNode* maximum(RedBlackNode* node);
    RedBlackNode* successor(RedBlackNode* node);
    RedBlackNode* predecessor(RedBlackNode* node);

    ~RedBlackTree(){}
};

template <typename T>
class RedBlackTree<T>::RedBlackNode{
public:
    //black = 0, red = 1
    bool _color = 0;
    T data;
    RedBlackNode* left = nullptr;
    RedBlackNode* right = nullptr;
    RedBlackNode* parent = nullptr;
public:
    RedBlackNode(){}
    RedBlackNode(T& val): data(val){}
    RedBlackNode(T& val, RedBlackNode* l, RedBlackNode* r) : data(val), left(l), right(r){}
    RedBlackNode(T& val, RedBlackNode* p, RedBlackNode* l, RedBlackNode* r) : data(val), parent(p), left(l), right(r){}
    ~RedBlackNode(){}

    friend std::ostream& operator<<(std::ostream& os, RedBlackNode* node){
        os<<node->data;
        return os;
    }
};

#endif //STRUCTURESCPP_REDBLACKTRESS_H

#include "RedBlackTree.hpp"