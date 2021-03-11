#include<iostream>
#include<functional>
#include<vector>

class TreeNode{
	public:
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
		~TreeNode(){}
};

std::ostream& operator<<(std::ostream& os, TreeNode* node){
    os<<node->data;
    return os;
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

class Tree{
    private:
		TreeNode* root = nullptr;
		int _height = 0;
		int _size = 0;

	public:	
		Tree(){}
		Tree(TreeNode* node) : root(node){}
		Tree(std::vector<int>&);
		void InOrderTreeWalk();
		void PreOrderTreeWalk();
		void PostOrderTreeWalk();
		TreeNode* TreeSearch(int);

		void Insert(TreeNode*);
		void Delete(TreeNode*);
};

Tree::Tree(std::vector<int>& values){
    for(int i : values){
        this->Insert(new TreeNode(i));
    }
}
void Tree::InOrderTreeWalk(){
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

void Tree::PreOrderTreeWalk(){
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

void Tree::PostOrderTreeWalk(){
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

TreeNode* Tree::TreeSearch(int key){
	std::function<TreeNode*(TreeNode*,int)> NodeSearch = [&](TreeNode* node, int k){		
		if(!node || node->data == k) return node;
		if(node->data > k) return NodeSearch(node->left, k);return NodeSearch(node->right, k);
	};
	return NodeSearch(root, key);
	
}

void Tree::Insert(TreeNode* node){
    TreeNode* par;

    if(!root){
        root = node;
        return;
    }
    TreeNode* pos = root;
    while(pos){
        par = pos;
        if(pos->data < node->data)
            pos = pos->right;
        else
            pos = pos->left;
    }
    if(par->data < node->data){
        par->right = node;
        node->parent = par;
    }
    else {
        par->left = node;
        node->parent = par;
    }
    _size++;
    return;
}

void Tree::Delete(TreeNode* node){
	std::function<void(TreeNode*,TreeNode*)> Replace = [&](TreeNode* u, TreeNode* v){
		if(!u->parent)
		    root = v;
		else if(u == u->parent->left)u->parent->left = v;
		else u->parent->right = v;
		if(v)
			v->parent = u->parent;
	};
	if(!node->left)
		Replace(node, node->right);
	else if(!node->right)
		Replace(node, node->left);
	else{
		TreeNode* next = node->Successor();
		if(next->parent != node){
			Replace(next, next->right);
			next->right = node->right;
			next->right->parent = next;
		}
		Replace(node, next);
		next->left = node->left;
		next->left->parent = next;
	}
	_size--;
}

int main(){
	std::vector<int> values = {6,4,7,2,5,8,9,1,3};
	Tree* tree = new Tree(values);
	tree->InOrderTreeWalk();
	tree->PreOrderTreeWalk();
	tree->PostOrderTreeWalk();
	return 0;
}
