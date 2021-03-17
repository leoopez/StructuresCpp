//
// Created by leort on 3/17/2021.
//

#ifndef STRUCTURESCPP_BINARYTREE_HPP
#define STRUCTURESCPP_BINARYTREE_HPP

template <typename T>
void BinaryTree<T>::print_in_order(){
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

template <typename T>
void BinaryTree<T>::print_pre_order(){
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

template <typename T>
void BinaryTree<T>::print_post_order(){
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

template <typename T>
typename BinaryTree<T>::TreeNode* BinaryTree<T>::search(T& key){
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

template <typename T>
void BinaryTree<T>::insert(TreeNode* to_insert) {
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

template <typename T>
void BinaryTree<T>::remove(TreeNode* to_delete) {
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
        TreeNode* next = successor(to_delete);
        if(next->parent != to_delete){
            delete_node(next,next->right);
            next->parent = to_delete->parent;
        }
        delete_node(to_delete, next);
        next->left = to_delete->left;
        next->left->parent = next;
    }
    delete to_delete;
    _size--;
    return;
}

template<typename T>
typename BinaryTree<T>::TreeNode* BinaryTree<T>::minimum(TreeNode* node){
    while(node->left)
        node = node->left;
    return node;
}

template<typename T>
typename BinaryTree<T>::TreeNode* BinaryTree<T>::maximum(TreeNode* node){
    while(node->right)
        node = node->right;
    return node;
}

template <typename T>
typename BinaryTree<T>::TreeNode* BinaryTree<T>::successor(TreeNode* node){
    if(node->right)
        return minimum(node->right);
    TreeNode* p = node->parent;
    while(p && p->right == node){
        node = p;
        p = p->parent;
    }
    return p;
}

template <typename T>
typename BinaryTree<T>::TreeNode* BinaryTree<T>::predecessor(TreeNode* node){
    if(node->left)
        return maximum(node->left);
    TreeNode* p = node->parent;
    while(p && p->left == node){
        node = p;
        p = p->parent;
    }
    return p;
}
#endif //STRUCTURESCPP_BINARYTREE_HPP
