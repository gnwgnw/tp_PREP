#include "tree.h"


Node::Node(int digit, Node* parent){
    this->left = this->right = NULL;
    this->key = digit;
    this->parent = parent;
}

Node::~Node(){
   if(this->left)
       delete this->left;
    if(this->right)
       delete this->right;
}

Tree::Tree(){
    root = NULL;
}

Tree::~Tree(){
    if (root)
        delete root;
}


void Tree::insert(int digit){
    Node* tmp = NULL;

    if (this->root == NULL){
        this->root = new Node(digit, NULL);
        return;
    }
    tmp = this->root;
    while (tmp){
        if (digit > tmp->key){
            if (tmp->right){
                tmp = tmp->right;
                continue;
            }else{
                tmp->right = new Node(digit, tmp);
                return;
            }
        }else if (digit < tmp->key){
            if (tmp->left){
                tmp = tmp->left;
                continue;
            }else{
                tmp->left = new Node(digit, tmp);
                return;
            }
        }else
            return;
    }
    return;
}



Node* Tree::getMaxNode(Node *ptr) {
    while (ptr->right) {
        ptr = ptr->right;
    }
    return ptr;
}


void Tree::delNode(Node* tmp){
    if (tmp->left && tmp->right) {
        Node* localMax = getMaxNode(tmp->left);
        tmp->key = localMax->key;
        delNode(localMax);
        return;
    } else if (tmp->left) {
        if (tmp->parent == NULL){
            tmp->left->parent = NULL;
            this->root = tmp->left;
        }
        else if (tmp == tmp->parent->left) {
            tmp->parent->left = tmp->left;
            tmp->left->parent = tmp->parent;
        } else {
            tmp->parent->right = tmp->left;
            tmp->left->parent = tmp->parent;
        }
    } else if (tmp->right) {
        if (tmp->parent == NULL){
            tmp->right->parent = NULL;
            this->root = tmp->right;
        }
        else if (tmp == tmp->parent->right) {
            tmp->parent->right = tmp->right;
            tmp->right->parent = tmp->parent;
        } else {
            tmp->parent->left = tmp->right;
            tmp->right->parent = tmp->parent;
        }
    } else{
        if (tmp->parent == NULL)
            this->root = NULL;
        else
        {
           if (tmp == tmp->parent->left)
                tmp->parent->left = NULL;
            else
                tmp->parent->right = NULL;
        }
    }
    tmp->left = NULL;
    tmp->right = NULL;
    delete tmp;
}

void Tree::del(int digit){
    Node* tmp = this->root;
    while (tmp){
        if (digit > tmp->key){
            if (tmp->right){
                tmp = tmp->right;
                continue;
            }else
                return;
        }else if (digit < tmp->key){
            if (tmp->left){
                tmp = tmp->left;
                continue;
            }else
                return;
        }else{
            delNode(tmp);
            return;
        }
    }
    return;
}


void Tree::find(int digit){
    Node* tmp = this->root;
    while (tmp){
        if (digit > tmp->key){
            if (tmp->right){
                tmp = tmp->right;
                continue;
            }else
                break;
        }else if (digit < tmp->key){
            if (tmp->left){
                tmp = tmp->left;
                continue;
            }else
                break;
        }else{
            cout << digit << " yes" << endl;
            return;
        }
    }
    cout << digit << " no" << endl;
    return;
}


void Tree::print_tree(ofstream &f_target, Node* root){
    if (root){
        print_tree(f_target, root->left);
        f_target << root->key << endl;
        print_tree(f_target, root->right);
    }
}


















