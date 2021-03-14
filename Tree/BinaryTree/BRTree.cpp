#include "BRTreeNode.cpp"
#include<iostream>
#include<functional>

template <typename T>
class BRTree{
public:
    BRTreeNode<T>* nil = new BRTreeNode<T>();
    BRTreeNode<T>* root = nil;

    int _size = 0;
    int _height = 0;
public:
    BRTree(){}
    BRTree(std::vector<T>& values){
        for(T i : values)
            this->Insert(new BRTreeNode<T>(i));
    }

    void Insert(BRTreeNode<T>* to_insert){
        if(root == nil){
            root = to_insert;
            to_insert->parent = nil;
            to_insert->left   = nil;
            to_insert->right  = nil;
            _size++;
            return;
        }

        BRTreeNode<T>* node = root;
        BRTreeNode<T>* parent = nil;

        while(node != nil) {
            parent = node;
            if (to_insert->data > node->data)
                node = node->right;
            else
                node = node->left;
        }

        if (parent->data > to_insert->data)
            parent->left  = to_insert;
        else
            parent->right = to_insert;

        to_insert->parent = parent;
        to_insert->left  = nil;
        to_insert->right = nil;
        to_insert->color = 1;
        FixUp_Insert(to_insert);
        _size++;
        return;
    }

    void Delete(BRTreeNode<T> * to_delete){
        std::function<void(BRTreeNode<T>*, BRTreeNode<T>*)> delete_node = [&](BRTreeNode<T>* u, BRTreeNode<T>* v){
            if(u->parent == nil)
                root = v;
            else if (u->parent->left == u)
                u->parent->left = v;
            else
                u->parent->right = v;
            v->parent = u->parent;
        };

        BRTreeNode<T>* y = to_delete;
        BRTreeNode<T>* x;
        int color = y->color;
        if(to_delete->left == nil){
            x = to_delete->right;
            delete_node(to_delete, to_delete->right);
        }

        else if(to_delete->right == nil){
            x = to_delete->left;
            delete_node(to_delete, to_delete->left);
        }
        else {
            y = to_delete->Successor(nil);
            color = y->color;
            x = y->right;
            if (y->parent == to_delete) {
                x->parent = y;
            }else{
                delete_node(y, y->right);
                y->right = to_delete->right;
                y->right->parent = y;
            }
            delete_node(to_delete, y);
            y->left = to_delete->left;
            y->left->parent = y;
            y->color = to_delete->color;
        }
        if (color == 0) {
            FixUp_Delete(x);
        }
    }


    void InOrderTreeWalk(){
        std::ostream& os = std::cout;
        std::function<void(BRTreeNode<T>*)> InOrder = [&](BRTreeNode<T>* node){
            if(node == nil) return;
            InOrder(node->left);
            os<<node<<" ";
            InOrder(node->right);
        };
        InOrder(root);
        os<<std::endl;
    }

    void PreOrderTreeWalk(){
        std::ostream& os = std::cout;
        std::function<void(BRTreeNode<T>*)> PreOrder = [&](BRTreeNode<T>* node){
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
        std::function<void(BRTreeNode<T>*)> PostOrder = [&](BRTreeNode<T>* node){
            if(!node) return;
            PostOrder(node->right);
            os<<node<<" ";
            PostOrder(node->left);

        };
        PostOrder(root);
        os<<std::endl;
    }

    //Subroutines
    void LeftRotation(BRTreeNode<T>*);
    void RightRotation(BRTreeNode<T>*);
    void FixUp_Insert(BRTreeNode<T>*);
    void FixUp_Delete(BRTreeNode<T>*);
};


template <typename T>
void BRTree<T>::FixUp_Insert(BRTreeNode<T>* node){
    while(node->parent->color == 1){
        if(node->parent == node->parent->parent->left){
            BRTreeNode<T>* uncle = node->parent->parent->right;
            if(uncle->color == 1){
                node->parent->color = 0;
                uncle->color = 0;
                node->parent->parent->color = 1;
                node = node->parent->parent;
            }
            else {
                if (node == node->parent->right) {
                    node = node->parent;
                    LeftRotation(node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;
                RightRotation(node->parent->parent);
            }
        }
        else{
            BRTreeNode<T>* y = node->parent->parent->left;
            if(y->color == 1){
                node->parent->color = 0;
                y->color = 0;
                node->parent->parent->color = 1;
                node = node->parent->parent;
            }
            else{
                if(node == node->parent->left){
                    node = node->parent;
                    RightRotation(node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;
                LeftRotation(node->parent->parent);
            }
        }
        root->color = 0;
    }
}

template <typename T>
void BRTree<T>::LeftRotation(BRTreeNode<T>* to_rotate) {
    BRTreeNode<T>*  rot = to_rotate->right;
    to_rotate->right = rot->left;
    if(rot->left != nil){
        rot->left->parent = to_rotate;
    }
    rot->parent = to_rotate->parent;
    if(to_rotate->parent ==  nil){
        root = rot;
    }
    else if(to_rotate->parent->left == to_rotate){
        to_rotate->parent->left = rot;
    }
    else
        to_rotate->parent->right = rot;
    rot->left = to_rotate;
    to_rotate->parent = rot;
}

template <typename T>
void BRTree<T>::RightRotation(BRTreeNode<T>* to_rotate) {
    BRTreeNode<T>*  rot = to_rotate->left;
    to_rotate->left = rot->right;
    if(rot->right != nil){
        rot->right->parent = to_rotate;
    }
    rot->parent = to_rotate->parent;
    if(to_rotate->parent ==  nil){
        root = rot;
    }
    else if(to_rotate->parent->right == to_rotate){
        to_rotate->parent->right = rot;
    }
    else
        to_rotate->parent->left = rot;
    rot->right = to_rotate;
    to_rotate->parent = rot;
}

template<typename T>
void BRTree<T>::FixUp_Delete(BRTreeNode<T> *node) {
    while(node != root && node->color == 0){
        if(node == node->parent->left){
            BRTreeNode<T>* uncle = node->parent->right;
            if(uncle->color == 1) {
                uncle->color = 0;
                node->parent->color = 1;
                LeftRotation(node->parent);
                uncle = node->parent->right;
            }
            if(uncle->left->color == 0 && uncle->right->color == 0){
                uncle->color = 1;
                node = node->parent;
            }
            else{
                if(uncle->right->color == 0){
                    uncle->left->color = 0;
                    uncle->color = 1;
                    RightRotation(uncle);
                    uncle = node->parent->right;
                }
                uncle->color = node->parent->color;
                node->parent->color = 0;
                uncle->right->color = 0;
                LeftRotation(node->parent);
                node = root;
            }
        }else{
            BRTreeNode<T>* uncle = node->parent->left;
            if(uncle->color == 1) {
                uncle->color = 0;
                node->parent->color = 1;
                RightRotation(node->parent);
                uncle = node->parent->left;
            }
            if(uncle->right->color == 0 && uncle->left->color == 0){
                uncle->color = 1;
                node = node->parent;
            }
            else{
                if(uncle->left->color == 0){
                    uncle->right->color = 0;
                    uncle->color = 1;
                    LeftRotation(uncle);
                    uncle = node->parent->left;
                }
                uncle->color = node->parent->color;
                node->parent->color = 0;
                uncle->left->color = 0;
                RightRotation(node->parent);
                node = root;
            }
        }
    }
    node->color = 0;
}