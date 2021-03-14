#include<iostream>
#include<functional>
#include<vector>
#include "TreeNode.cpp"

template <typename T>
class BTree{
private:
    TreeNode<T>* root = nullptr;
    int _height = 0;
    int _size = 0;
public:
    BTree(){}
    BTree(TreeNode<T>* node) : root(node){}
    BTree(std::vector<T>& values){
        for(T i : values){
            this->Insert(new TreeNode<T>(i));
        }
    }

    TreeNode<T>* getRoot(){ return root;}
    int getHeight() {return _height;}
    int getSize() {return _size;}

    void InOrderTreeWalk(){
        std::ostream& os = std::cout;
        std::function<void(TreeNode<T>*)> InOrder = [&](TreeNode<T>* node){
            if(!node) return;
            InOrder(node->left);
            os<<node<<" ";
            InOrder(node->right);
        };
        InOrder(root);
        os<<std::endl;
    }

    void PreOrderTreeWalk(){
        std::ostream& os = std::cout;
        std::function<void(TreeNode<T>*)> PreOrder = [&](TreeNode<T>* node){
            if(!node) return;
            os<<node<<" ";
            PreOrder(node->left);
            PreOrder(node->right);
        };
        PreOrder(root);
        os<<std::endl;
    }

    void PostOrderTreeWalk(){
        std::ostream& os = std::cout;
        std::function<void(TreeNode<T>*)> PostOrder = [&](TreeNode<T>* node){
            if(!node) return;
            PostOrder(node->right);
            os<<node<<" ";
            PostOrder(node->left);

        };
        PostOrder(root);
        os<<std::endl;
    }

    TreeNode<T>* Search(int key){
        TreeNode<T>* node = root;
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

    void Insert(TreeNode<T>* to_insert) {
        if(!root){
            root = to_insert;
            _size++;
            return;
        }

        TreeNode<T>* node = root;
        TreeNode<T>* parent;
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

    void Delete(TreeNode<T>* to_delete) {
        if(!to_delete) return;
        std::function<void(TreeNode<T>*, TreeNode<T>*)> delete_node = [&](TreeNode<T>* u, TreeNode<T>* v){
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
            TreeNode<T>* successor = to_delete->Successor();
            if(successor->parent != to_delete){
                delete_node(successor,successor->right);
                successor->parent = to_delete->parent;
            }
            delete_node(to_delete, successor);
            successor->left = to_delete->left;
            successor->left->parent = successor;
        }
        delete to_delete;
        _size--;
        return;
    }

    ~BTree(){};
};

