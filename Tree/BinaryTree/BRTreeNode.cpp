class BRTreeNode{
public:
        //black = 0, red = 1
        bool _blackRed = 0;
        int data;
        BRTreeNode* left = nullptr;
        BRTreeNode* right = nullptr;
        BRTreeNode* parent = nullptr;
public:
    BRTreeNode(){}
    BRTreeNode(int val): data(val){}
    BRTreeNode(int val, BRTreeNode* l, BRTreeNode* r) : data(val), left(l), right(r){}
    BRTreeNode(int val, BRTreeNode* p, BRTreeNode* l, BRTreeNode* r) : data(val), parent(p), left(l), right(r){}

    void LeftRotation(BRTreeNode*);
    void RightRotation(BRTreeNode*);
    BRTreeNode* Successor();
    BRTreeNode* Predecessor();
    BRTreeNode* Minimum();
    BRTreeNode* Maximum();
    ~BRTreeNode(){}
};

std::ostream& operator<<(std::ostream& os, BRTreeNode* node){
    os<<node->data;
    return os;
}
//
//void BRTreeNode::LeftRotation(BRTreeNode* nil) {
//    BRTreeNode rot = this->right;
//    this->left = rot->right;
//    if(rot->right != nil){
//        root->right->parent = this;
//    }
//    rot->parent = this->parent;
//    else if(this->parent ==  nil){
//        root = rot;
//    }
//    else{
//        this->parent->right = rot;
//    }
//    rot->right = this;
//    this->parent = rot;
//}
//
//void BRTreeNode::RightRotation(BRTreeNode* nil) {
//    BRTreeNode rot = this->left;
//    this->right = rot->left;
//    if(rot->left != nil){
//        rot->left->parent = this;
//    }
//    rot->parent = this->parent;
//    else if(this->parent ==  nil){
//        root = rot;
//    }
//    else{
//        this->parent->right = rot;
//    }
//    rot->left = this;
//    this->parent = rot;
//}

BRTreeNode* BRTreeNode::Minimum(){
    BRTreeNode* node = this;
    while(node->left)
        node = node->left;
    return node;
}

BRTreeNode* BRTreeNode::Maximum(){
    BRTreeNode* node = this;
    while(node->right)
        node = node->right;
    return node;
}

BRTreeNode* BRTreeNode::Successor(){
    BRTreeNode* node = this;
    if(node->right)
        return node->right;
    BRTreeNode* p = node->parent;
    while(p && p->right == node){
        node = p;
        p = p->parent;
    }
    return p;
}

BRTreeNode* BRTreeNode::Predecessor(){
    BRTreeNode* node = this;
    if(node->left)
        return node->left;
    BRTreeNode* p = node->parent;
    while(p && p->left == node){
        node = p;
        p = p->parent;
    }
    return p;
}