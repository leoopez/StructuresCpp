//
// Created by leort on 3/18/2021.
//

#ifndef STRUCTURESCPP_AVLTREE_HPP
#define STRUCTURESCPP_AVLTREE_HPP

template <typename T>
void AVLTree<T>::insert(AVLNode* node){

    if(root == nullptr){
        root = node;
        _size++;
        return;
    }

    AVLNode* parent = nullptr;
    AVLNode* pos = root;

    while(pos){
        parent = pos;
        if(pos->data > node->data){
            pos = pos->left;
            parent->_height = 1 + std::max(getHeight(parent->left)+1, getHeight(parent->right));
        }

        else{
            pos = pos->right;
            parent->_height = 1 + std::max(getHeight(parent->left), getHeight(parent->right)+1);
        }
    }
    if(parent->data > node->data)
        parent->left = node;
    else
        parent->right = node;
    node->parent = parent;
    _size++;
    _fixup_insert(node);
}

template <typename T>
void AVLTree<T>::_updateHeight(AVLNode* node){
    node->_height = 1 + std::max(getHeight(node->left), getHeight(node->right));
}


template <typename T>
void AVLTree<T>::_fixup_insert(AVLNode* node){

    short int bal = getHeight(node->left) - getHeight(node->right);
    if(bal > 1 || bal < -1){
        _balance(node, bal);
    }else{
        _updateHeight(node);
    }

    if(!node->parent) return;

    _fixup_insert(node->parent);
}

template <typename T>
void AVLTree<T>::_balance(AVLNode* node, short int& b){
    if(b == -2) {
        if (getHeight(node->right->left) < getHeight(node->right->right)) {
            _left_rotation(node->right);
        }
        else {
            _right_rotation(node->right->left);
            _left_rotation(node->right);
        }
    }
    else{
        if(getHeight(node->left->right) < getHeight(node->left->left)){
            _right_rotation(node->left);
        }
        else{
            _left_rotation(node->left->right);;
            _right_rotation(node->left);
        }
    }
}

template <typename T>
void AVLTree<T>::_left_rotation(AVLNode* node){

    AVLNode* temp = node->parent;
    temp->right = node->left;
    node->left = temp;
    node->parent = temp->parent;

    temp->parent = node;

    if(!node->parent){
        root = node;
    }
    else{
        if(node->parent->right == temp){
            node->parent->right = node;
        }
        else{
            node->parent->left = node;
        }

    }
    _updateHeight(temp);
    _updateHeight(node);
}

template <typename T>
void AVLTree<T>::_right_rotation(AVLNode* node){
    AVLNode* temp = node->parent;
    temp->left = node->right;
    node->right = temp;
    node->parent = temp->parent;
    temp->parent = node;

    if(!node->parent){
        root = node;
    }
    else{
        if(node->parent->left == temp){
            node->parent->left = node;
        }
        else{
            node->parent->right = node;
        }
    }
    _updateHeight(temp);
    _updateHeight(node);
}


template <typename T>
typename AVLTree<T>::AVLNode* AVLTree<T>::search(T& key) const {
    AVLTree* node = root;
    while(node){
        if(node->val > key)
            node = node->left;
        else if(node->val < key)
            node = node->right;
        return node;
    }
    return node;
}


template <typename T>
void AVLTree<T>::remove(AVLNode* node){
    std::function<void(AVLNode*, AVLNode*)> swap = [&](AVLNode* u, AVLNode* v){
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
    AVLNode* y = nullptr;
    if(!node->left){
        y = node->left;
        swap(node, node->left);
        y->_height = 1 + std::max(getHeight(y->left),getHeight(y->right));
    }
    else if(!node->right){
        y = node->left;
        swap(node, node->left);
        y->_height = 1 + std::max(getHeight(y->left),getHeight(y->right));
    }
    else {
        y = successor(node);
        if (y->parent != node) {
            swap(y, y->right);
            y->parent = node->parent;
        }
        swap(node, y);
        y->left = node->left;
        y->left->parent = y;
        y->_height = 1 + std::max(getHeight(y->left),getHeight(y->right));
        _fixup_insert(y);
    }

    delete node;

    //_fixup_insert(to_balance);
    _size--;
    return;
}


template <typename T>
typename AVLTree<T>::AVLNode* AVLTree<T>::minimum(AVLNode* node){
    while(node->left)
        node = node->left;
    return node;
}

template <typename T>
typename AVLTree<T>::AVLNode* AVLTree<T>::maximum(AVLNode* node){
    while(node->right)
        node = node->right;
    return node;
}

template <typename T>
typename AVLTree<T>::AVLNode* AVLTree<T>::predecessor(AVLNode* node){
    if(node->left)
        return maximum(node->left);
    AVLNode* p = node->parent;
    while(p && p->left == node){
        node = p;
        p = p->parent;
    }
    return p;
}

template <typename T>
typename AVLTree<T>::AVLNode* AVLTree<T>::successor(AVLNode* node){
    if(node->right)
        return minimum(node->right);
    AVLNode* p = node->parent;
    while(p && p->right == node){
        node = p;
        p = p->parent;
    }
    return p;
}

template <typename T>
void AVLTree<T>::print_pre_order(){
    std::ostream& os = std::cout;
    std::function<void(AVLNode*)> PreOrder = [&](AVLNode* node){
        if(!node) return;

        os<<node<<" ";
        PreOrder(node->left);
        PreOrder(node->right);
    };
    PreOrder(root);
    os<<std::endl;
}
#endif //STRUCTURESCPP_AVLTREE_HPP