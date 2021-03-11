#include<iostream>
#include<functional>
#include<vector>
#include "TreeNode.cpp"

class BTree{
    private:
		TreeNode* root = nullptr;
		int _height = 0;
		int _size = 0;

	public:	
		BTree(){}
		BTree(TreeNode* node) : root(node){}
		BTree(std::vector<int>&);
		TreeNode* getRoot(){ return root;}
		int getHeight() {return _height;}
		int getSize() {return _size;}
		void InOrderTreeWalk();
		void PreOrderTreeWalk();
		void PostOrderTreeWalk();

		TreeNode* TreeSearch(int);

		void Insert(TreeNode*);
		void Delete(TreeNode*);
		~BTree();
};

BTree::BTree(std::vector<int>& values){
    for(int i : values){
        this->Insert(new TreeNode(i));
    }
}
void BTree::InOrderTreeWalk(){
    std::ostream& os = std::cout;
	std::function<void(TreeNode*)> InOrder = [&](TreeNode* node){
		if(!node) return;
		InOrder(node->left);
		os<<node<<" ";
		InOrder(node->right);
	};
	InOrder(root);
	os<<std::endl;
}

void BTree::PreOrderTreeWalk(){
    std::ostream& os = std::cout;
	std::function<void(TreeNode*)> PreOrder = [&](TreeNode* node){
		if(!node) return;
		os<<node<<" ";
		PreOrder(node->left);
		PreOrder(node->right);
	};
	PreOrder(root);
	os<<std::endl;
}

void BTree::PostOrderTreeWalk(){
    std::ostream& os = std::cout;
    std::function<void(TreeNode*)> PostOrder = [&](TreeNode* node){
        if(!node) return;
        PostOrder(node->right);
        os<<node<<" ";
        PostOrder(node->left);

    };
    PostOrder(root);
    os<<std::endl;
}

TreeNode* BTree::TreeSearch(int key){
    TreeNode* node = root;
    while(node){
        if(node->data > key)
            node = node->left;
        else if(node->data<key)
            node = node->right;
        else
            return node;
    }
    return nullptr;
}

void BTree::Insert(TreeNode* to_insert) {
    if(!root){
        root = to_insert;
        _size++;
        return;
    }

    TreeNode* node = root;
    TreeNode* parent;
    while(node) {
        parent = node;
        if (node->data > to_insert->data)
            node = node->left;
        else
            node = node->right;
    }
    if (parent->data > to_insert->data)
        parent->left = to_insert;
    else
        parent->right = to_insert;
    to_insert->parent = parent;
    _size++;
    return;
}

void BTree::Delete(TreeNode* to_delete) {
    if(!to_delete) return;
    std::function<void(TreeNode*, TreeNode*)> delete_node = [&](TreeNode* u, TreeNode* v){
        if(!u->parent){
            root = v;
        }
        else if (u->parent->left == u)
            u->left = v;
        else
            u->right = v;
        if(v)
            v->parent = u->parent;
    };

    if(!to_delete->left)
        delete_node(to_delete, to_delete->right);
    else if(!to_delete->right)
        delete_node(to_delete, to_delete->left);
    else{
        TreeNode* successor = to_delete->Successor();
        if(successor->parent != to_delete){
            delete_node(successor,successor->right);
            successor->parent = to_delete->parent;
        }
        delete_node(to_delete, successor);
        successor->left = to_delete->left;
        successor->left->parent = successor;
    }

    _size--;
    return;
}
int main(){
    std::vector<int> values = {6,4,8,2,5,7,9,1,3};
    BTree* tree = new BTree(values);
    tree->InOrderTreeWalk();
    for(int i = 0; i<values.size();i++){
        TreeNode* node = tree->getRoot();
        tree->Delete(node);
    }
    tree->PreOrderTreeWalk();
    return 0;
}