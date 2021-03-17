//
// Created by leort on 3/17/2021.
//

#ifndef STRUCTURESCPP_REDBLACKTREE_H
#define STRUCTURESCPP_REDBLACKTREE_H

template <typename T>
void RedBlackTree<T>::insert(RedBlackNode* to_insert){
    if(root == nil){
        root = to_insert;
        to_insert->parent = nil;
        to_insert->left   = nil;
        to_insert->right  = nil;
        _size++;
        return;
    }

    RedBlackNode* node = root;
    RedBlackNode* parent = nil;

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
    to_insert->_color = 1;
    _fixup_insert(to_insert);
    _size++;
    return;
}

template <typename T>
void RedBlackTree<T>::remove(RedBlackNode * to_delete){
    std::function<void(RedBlackNode*, RedBlackNode*)> delete_node = [&](RedBlackNode* u, RedBlackNode* v){
        if(u->parent == nil)
            root = v;
        else if (u->parent->left == u)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    };

    RedBlackNode* y = to_delete;
    RedBlackNode* x;
    int _color = y->_color;
    if(to_delete->left == nil){
        x = to_delete->right;
        delete_node(to_delete, to_delete->right);
    }

    else if(to_delete->right == nil){
        x = to_delete->left;
        delete_node(to_delete, to_delete->left);
    }
    else {
        y = successor(to_delete);
        _color = y->_color;
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
        y->_color = to_delete->_color;
    }
    if (_color == 0) {
        _fixup_remove(x);
    }
}

template <typename T>
void RedBlackTree<T>::print_in_order(){
    std::ostream& os = std::cout;
    std::function<void(RedBlackNode*)> InOrder = [&](RedBlackNode* node){
        if(node == nil) return;
        InOrder(node->left);
        os<<node<<" ";
        InOrder(node->right);
    };
    InOrder(root);
    os<<std::endl;
}

template <typename T>
void  RedBlackTree<T>::print_pre_order(){
    std::ostream& os = std::cout;
    std::function<void(RedBlackNode*)> PreOrder = [&](RedBlackNode* node){
        if(node == nil) return;
        os<<node<<" ";
        PreOrder(node->left);
        PreOrder(node->right);
    };
    PreOrder(root);
    os<<std::endl;
}
template <typename T>
void RedBlackTree<T>::print_post_order(){
    std::ostream& os = std::cout;
    std::function<void(RedBlackNode*)> PostOrder = [&](RedBlackNode* node){
        if(node == nil) return;
        PostOrder(node->right);
        os<<node<<" ";
        PostOrder(node->left);

    };
    PostOrder(root);
    os<<std::endl;
}

template <typename T>
void RedBlackTree<T>::_fixup_insert(RedBlackNode* node){
    while(node->parent->_color == 1){
        if(node->parent == node->parent->parent->left){
            RedBlackNode* uncle = node->parent->parent->right;
            if(uncle->_color == 1){
                node->parent->_color = 0;
                uncle->_color = 0;
                node->parent->parent->_color = 1;
                node = node->parent->parent;
            }
            else {
                if (node == node->parent->right) {
                    node = node->parent;
                    _left_rotation(node);
                }
                node->parent->_color = 0;
                node->parent->parent->_color = 1;
                _right_rotation(node->parent->parent);
            }
        }
        else{
            RedBlackNode* y = node->parent->parent->left;
            if(y->_color == 1){
                node->parent->_color = 0;
                y->_color = 0;
                node->parent->parent->_color = 1;
                node = node->parent->parent;
            }
            else{
                if(node == node->parent->left){
                    node = node->parent;
                    _right_rotation(node);
                }
                node->parent->_color = 0;
                node->parent->parent->_color = 1;
                _left_rotation(node->parent->parent);
            }
        }
        root->_color = 0;
    }
}

template <typename T>
void RedBlackTree<T>::_left_rotation(RedBlackNode* to_rotate) {
    RedBlackNode*  rot = to_rotate->right;
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
void RedBlackTree<T>::_right_rotation(RedBlackNode* to_rotate) {
    RedBlackNode*  rot = to_rotate->left;
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
void RedBlackTree<T>::_fixup_remove(RedBlackNode *node) {
    while(node != root && node->_color == 0){
        if(node == node->parent->left){
            RedBlackNode* uncle = node->parent->right;
            if(uncle->_color == 1) {
                uncle->_color = 0;
                node->parent->_color = 1;
                _left_rotation(node->parent);
                uncle = node->parent->right;
            }
            if(uncle->left->_color == 0 && uncle->right->_color == 0){
                uncle->_color = 1;
                node = node->parent;
            }
            else{
                if(uncle->right->_color == 0){
                    uncle->left->_color = 0;
                    uncle->_color = 1;
                    _right_rotation(uncle);
                    uncle = node->parent->right;
                }
                uncle->_color = node->parent->_color;
                node->parent->_color = 0;
                uncle->right->_color = 0;
                _left_rotation(node->parent);
                node = root;
            }
        }else{
            RedBlackNode* uncle = node->parent->left;
            if(uncle->_color == 1) {
                uncle->_color = 0;
                node->parent->_color = 1;
                _right_rotation(node->parent);
                uncle = node->parent->left;
            }
            if(uncle->right->_color == 0 && uncle->left->_color == 0){
                uncle->_color = 1;
                node = node->parent;
            }
            else{
                if(uncle->left->_color == 0){
                    uncle->right->_color = 0;
                    uncle->_color = 1;
                    _left_rotation(uncle);
                    uncle = node->parent->left;
                }
                uncle->_color = node->parent->_color;
                node->parent->_color = 0;
                uncle->left->_color = 0;
                _right_rotation(node->parent);
                node = root;
            }
        }
    }
    node->_color = 0;
}

template <typename T>
typename RedBlackTree<T>::RedBlackNode* RedBlackTree<T>::minimum(RedBlackNode*  node){
    while(node->left != nil)
        node = node->left;
    return node;
}

template <typename T>
typename RedBlackTree<T>::RedBlackNode* RedBlackTree<T>::maximum(RedBlackNode*  node){
    while(node->right!=nil)
        node = node->right;
    return node;
}

template <typename T>
typename RedBlackTree<T>::RedBlackNode* RedBlackTree<T>::successor(RedBlackNode*  node){
    if(node->right != nil)
        return minimum(node->right);
    RedBlackNode* p = node->parent;
    while(p!=nil && p->right == node){
        node = p;
        p = p->parent;
    }
    return p;
}

template <typename T>
typename RedBlackTree<T>::RedBlackNode* RedBlackTree<T>::predecessor(RedBlackNode*  node){
    if(node->left != nil)
        return maximum(node->left);
    RedBlackNode* p = node->parent;
    while(p!=nil && p->left == node){
        node = p;
        p = p->parent;
    }
    return p;
}
#endif //STRUCTURESCPP_REDBLACKTREE_H
