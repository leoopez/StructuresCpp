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
        pos->_height++;
        parent = pos;
        if(pos->data > node->data)
            pos = pos->left;
        else
            pos = pos->right;
    }
    if(parent->data > node->data)
        parent->left = node;
    else
        parent->right = node;
    node->parent = parent;
    _size++;
    //_fixup_insert(parent->parent);
}

template <typename T>
void AVLTree<T>::remove(AVLNode* node){

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
//
//
//template <typename T>
//void AVLTree<T>::_fixup_insert(AVLNode* node){
//
//
//
//
//}
//
//template <typename T>
//int AVLTree<T>::_getBalance(AVLNode* node){
//
//}

//template <typename T>
//void AVLTree<T>::_left_rotation(AVLNode* node){
//
//    node->right->left = node;
//    node->right->parent = node->parent;
//    node->parent = node->right->parent;
//    node->right = node->right->left;
//    return;
//}

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
