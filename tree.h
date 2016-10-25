#ifndef TREE_H
#define TREE_H

#include <fstream>
#include <iostream>
#include <stdlib.h>

#define ALL_OK 0
#define ALL_BAD 1

using namespace std;

class Node {
public:
    Node(int key, Node* parent);
    ~Node();
    int key;
    Node* left;
    Node* right;
    Node* parent;
};

class Tree{
private:
    void delNode(Node* tmp);
    Node* getMaxNode(Node* ptr);
public:
    Tree();
    ~Tree();
    Node* root;
    void insert(int digit);
    void del(int digit);
    void find(int digit);
    void print_tree(ofstream &f_target, Node* root);
};




#endif // TREE_H
