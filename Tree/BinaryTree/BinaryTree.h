#include<iostream>
#include<functional>
#include<vector>

template <typename T>
class BinaryTree{
public:
    BinaryTree(){}
    BinaryTree(std::vector<T>& values){
        for(T i : values){
            this->insert(new TreeNode(i));
        }
    }


    class TreeNode{
    public:
        int _height;
        T data;
        TreeNode* left =   nullptr;
        TreeNode* right =  nullptr;
        TreeNode* parent = nullptr;
    public:
        TreeNode(){}

        TreeNode(T val): data(val){}
        TreeNode(T val, TreeNode* l, TreeNode* r) : data(val), left(l), right(r){}
        TreeNode(T val, TreeNode* p, TreeNode* l, TreeNode* r) : data(val), parent(p), left(l), right(r){}

        friend std::ostream& operator<<(std::ostream& os, TreeNode* node) {
            os << node->data;
            return os;
        }

        ~TreeNode(){}
    };

    TreeNode* root = nullptr;
    int _size = 0;
public:

    TreeNode* getRoot(){ return root;}
    int getSize() {return _size;}

    void print_in_order();
    void print_pre_order();
    void print_post_order();

    void remove(TreeNode* to_delete);
    void insert(TreeNode* to_delete);
    TreeNode* search(T& key);

    TreeNode* minimum(TreeNode* node);
    TreeNode* maximum(TreeNode* node);
    TreeNode* predecessor(TreeNode* node);
    TreeNode* successor(TreeNode* node);

    ~BinaryTree(){};
};

#include "BinaryTree.hpp"