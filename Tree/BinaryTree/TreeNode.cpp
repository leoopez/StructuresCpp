#include<iostream>
template<typename T>
class TreeNode{
public:
    int _height;
    T data;
    TreeNode<T>* left =   nullptr;
    TreeNode<T>* right =  nullptr;
    TreeNode<T>* parent = nullptr;
public:
    TreeNode(){}

    TreeNode(T val): data(val){}
	TreeNode(T val, TreeNode<T>* l, TreeNode<T>* r) : data(val), left(l), right(r){}
	TreeNode(T val, TreeNode<T>* p, TreeNode<T>* l, TreeNode<T>* r) : data(val), parent(p), left(l), right(r){}

    TreeNode* Minimum(){
        TreeNode* node = this;
        while(node->left)
            node = node->left;
        return node;
    }

    TreeNode* Maximum(){
        TreeNode* node = this;
        while(node->right)
            node = node->right;
        return node;
    }

    TreeNode* Successor(){
        TreeNode* node = this;
        if(node->right)
            return node->right->Minimum();
        TreeNode* p = node->parent;
        while(p && p->right == node){
            node = p;
            p = p->parent;
        }
        return p;
    }

    TreeNode* Predecessor(){
        TreeNode* node = this;
        if(node->left)
            return node->left->Maximum();
        TreeNode* p = node->parent;
        while(p && p->left == node){
            node = p;
            p = p->parent;
        }
        return p;
    }

    bool isBalanced() {
        if(!this->left || !this->right)
            return true;
        return (abs(this->left->_height - this->right->_height) < 2);
    }
    ~TreeNode(){}
};

template<typename T>
std::ostream& operator<<(std::ostream& os, TreeNode<T>* node) {
    os << node->data;
    return os;
}
template<typename T>
void Print(TreeNode<T>* node){
    std::ostream& os = std::cout;
    if(node->parent)
        os<<"  "<<node->parent->data<<'\n';
    else
        os<<"  null\n";
    os<<"   |\n   "<<node->data<<'\n';
    os<<" /   \\\n";
    if(node->left)
        os<<node->left->data<<"     ";
    else
        os<<"null  ";
    if(node->right)
        os<<node->right->data;
    else
        os<<"null";
    os<<std::endl;
}