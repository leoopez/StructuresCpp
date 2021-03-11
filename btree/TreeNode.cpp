#include<iostream>

class TreeNode{
	public:
        int _height;
		int data;
		TreeNode* left =   nullptr;
		TreeNode* right =  nullptr;
		TreeNode* parent = nullptr;

	public:
		TreeNode(){}
		TreeNode(int val): data(val){}
		//TreeNode(int val, TreeNode* p):parent(p){}
		TreeNode(int val, TreeNode* l, TreeNode* r) : data(val), left(l), right(r){}
		TreeNode(int val, TreeNode* p, TreeNode* l, TreeNode* r) : data(val), parent(p), left(l), right(r){}

		TreeNode* Successor();
		TreeNode* Predecessor();
		TreeNode* Minimum();
		TreeNode* Maximum();
		bool isBalanced();
		~TreeNode(){}
};

std::ostream& operator<<(std::ostream& os, TreeNode* node){
    //try{
        os<<node->data;
        return os;
    /*}
    catch(int e){
        os<<"nullptr";
        return os;
    }*/
}

TreeNode* TreeNode::Minimum(){
    TreeNode* node = this;
    while(node->left)
        node = node->left;
    return node;
}

TreeNode* TreeNode::Maximum(){
    TreeNode* node = this;
    while(node->right)
        node = node->right;
    return node;
}

TreeNode* TreeNode::Successor(){
    TreeNode* node = this;
    if(node->right)
        return node->right;
    TreeNode* p = node->parent;
    while(p && p->right == node){
        node = p;
        p = p->parent;
    }
    return p;
}

TreeNode* TreeNode::Predecessor(){
    TreeNode* node = this;
    if(node->left)
        return node->left;
    TreeNode* p = node->parent;
    while(p && p->left == node){
        node = p;
        p = p->parent;
    }
    return p;
}

bool TreeNode::isBalanced() {
    if(!this->left || !this->right)
        return true;
    return (abs(this->left->_height - this->right->_height) < 2);
}
