#include<iostream>

template <typename T >
class BRTreeNode{
public:
    //black = 0, red = 1
    bool color = 0;
    char data;
    BRTreeNode<T>* left = nullptr;
    BRTreeNode<T>* right = nullptr;
    BRTreeNode<T>* parent = nullptr;
public:
    BRTreeNode(){}
    BRTreeNode(int val): data(val){}
    BRTreeNode(int val, BRTreeNode<T>* l, BRTreeNode<T>* r) : data(val), left(l), right(r){}
    BRTreeNode(int val, BRTreeNode<T>* p, BRTreeNode<T>* l, BRTreeNode<T>* r) : data(val), parent(p), left(l), right(r){}

    ~BRTreeNode(){}
    BRTreeNode<T>* Minimum(BRTreeNode<T>*  nil){
        BRTreeNode* node = this;
        while(node->left != nil)
            node = node->left;
        return node;
    }

    BRTreeNode<T>* Maximum(BRTreeNode<T>*  nil){
        BRTreeNode<T>** node = this;
        while(node->right!=nil)
            node = node->right;
        return node;
    }

    BRTreeNode<T>* Successor(BRTreeNode<T>*  nil){
        BRTreeNode<T>* node = this;
        if(this->right != nil)
            return this->right->Minimum(nil);

        BRTreeNode<T>* p = node->parent;
        while(p!=nil && p->right == node){
            node = p;
            p = p->parent;
        }
        return p;
    }

    BRTreeNode<T>* Predecessor(BRTreeNode<T>*  nil){
        BRTreeNode<T>* node = this;
        if(node->left != nil)
            return node->left->Maximum(nil);
        BRTreeNode<T>* p = node->parent;
        while(p!=nil && p->left == node){
            node = p;
            p = p->parent;
        }
        return p;
    }

};
template <typename T>
std::ostream& operator<<(std::ostream& os, BRTreeNode<T>* node){
    os<<node->data;
    return os;
}

template<typename T>
void Print(BRTreeNode<T>* node, BRTreeNode<T>* nil){
    std::ostream& os = std::cout;
    if(node->parent != nil)
        os<<"  "<<node->parent->data<<'\n';
    else
        os<<"  null\n";
    os<<"   |\n   "<<node->data<<'\n';
    os<<" /   \\\n";
    if(node->left != nil)
        os<<node->left->data<<"     ";
    else
        os<<"null  ";
    if(node->right != nil)
        os<<node->right->data;
    else
        os<<"null";
    os<<std::endl;
}